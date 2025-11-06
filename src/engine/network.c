#ifndef C4_ENGINE_NETWORK_C
#define C4_ENGINE_NETWORK_C

#include "network.h"

pxuword
c4NetworkReaderProc(C4NetworkReaderCtxt* self)
{
    if (self == 0) return 1;

    PxJsonReader reader =
        pxJsonReaderReserve(self->source, &self->arena, 8);

    PxBuffer8 buffer = {0};

    if (self->source.buffer == 0) {
        buffer = pxBuffer8Reserve(&self->arena, PX_MEMORY_KIB);

        self->source =
            pxBufferedSource(self->source, &buffer);
    }

    pxiword offset = pxArenaOffset(&self->arena);
    pxb8    state  = 1;

    while (state != 0) {
        C4NetworkMsg message = {0};

        c4JsonReadNetworkMsg(&message, &reader, &self->arena);

        pxLockEnter(self->lock);

        if (message.type != C4_NETWORK_MSG_NONE)
            state = pxQueueInsertTail(self->queue, C4NetworkMsg, &message);

        pxLockLeave(self->lock);

        pxArenaRewind(&self->arena, offset);
    }

    return 0;
}

pxuword
c4NetworkWriterProc(C4NetworkWriterCtxt* self)
{
    if (self == 0) return 1;

    PxJsonWriter writer =
        pxJsonWriterReserve(self->target, &self->arena, 8);

    pxiword offset = pxArenaOffset(&self->arena);
    pxb8    state  = 1;

    while (state != 0) {
        C4NetworkMsg message = {0};

        pxLockEnter(self->lock);

        state = pxQueueRemoveHead(self->queue, C4NetworkMsg, &message);

        pxLockLeave(self->lock);

        if (message.type != C4_NETWORK_MSG_NONE)
            c4JsonWriteNetworkMsg(&message, &writer, &self->arena);

        pxArenaRewind(&self->arena, offset);
    }

    return 0;
}

C4NetworkSession
c4NetworkSessionCreate(PxArena* arena, pxiword length, PxAddrType type)
{
    C4NetworkSession result = {0};

    result.socket = pxSocketTcpCreate(arena, type);

    if (result.socket != 0) {
        result.input_lock  = pxLockCreate(arena);
        result.input_queue = pxQueueReserve(arena, C4NetworkMsg, length);

        result.output_lock  = pxLockCreate(arena);
        result.output_queue = pxQueueReserve(arena, C4NetworkMsg, length);
    }

    return result;
}

pxb8
c4NetworkSessionConnect(C4NetworkSession* self, PxAddr addr, pxu16 port)
{
    return pxSocketTcpConnect(self, addr, port);
}

pxb8
c4NetworkSessionReadMsg(C4NetworkSession* self, C4NetworkMsg* value)
{
    C4NetworkMsg result = {0};

    pxLockEnter(self->input_lock);

    pxb8 state = pxQueueRemoveHead(&self->input_queue,
        C4NetworkMsg, &result);

    pxLockLeave(self->input_lock);

    if (state != 0 && value != 0) *value = result;

    return state;
}

pxb8
c4NetworkSessionWriteMsg(C4NetworkSession* self, C4NetworkMsg value)
{
    pxLockEnter(self->output_lock);

    pxb8 state = pxQueueInsertTail(&self->output_queue,
        C4NetworkMsg, &value);

    pxLockLeave(self->output_lock);

    return state;
}

C4NetworkServer
c4NetworkServerCreate(PxArena* arena, pxiword length, PxAddrType type)
{
    C4NetworkServer result = {0};

    result.socket = pxSocketTcpCreate(arena, type);

    if (result.socket != 0)
        result.items = pxArrayReserve(arena, C4NetworkSession, length);

    return result;
}

pxb8
c4NetworkServerStart(C4NetworkServer* self, PxAddr addr, pxu16 port)
{
    if (pxSocketTcpBind(self->socket, addr, port) != 0)
        return pxSocketTcpListen(self->socket);

    return 0;
}

void
c4NetworkServerStop(C4NetworkServer* self)
{
    pxSocketTcpDestroy(self->socket);
}

pxiword
c4NetworkServerConnect(C4NetworkServer* self, PxArena* arena, pxiword length)
{
    C4NetworkSession value  = {0};
    pxiword          offset = pxArenaOffset(arena);

    value.socket = pxSocketTcpAccept(self->socket, arena);

    if (value.socket != 0) {
        value.input_lock  = pxLockCreate(arena);
        value.input_queue = pxQueueReserve(arena, C4NetworkMsg, length);

        value.output_lock  = pxLockCreate(arena);
        value.output_queue = pxQueueReserve(arena, C4NetworkMsg, length);

        pxiword index = self->items.size;

        if (pxArrayInsert(&self->items, index, C4NetworkSession, &value) != 0)
            return index + 1;
    }

    pxArenaRewind(arena, offset);

    return 0;
}

pxb8
c4NetworkServerGet(C4NetworkServer* self, pxiword index, C4NetworkSession* value)
{
    return pxArrayGet(&self->items, index, C4NetworkSession, value);
}

C4NetworkSession
c4NetworkServerGetOr(C4NetworkServer* self, pxiword index, C4NetworkSession value)
{
    C4NetworkSession result = {0};

    if (c4NetworkServerGet(self, index, &result) == 0)
        return value;

    return result;
}

pxb8
c4NetworkServerEchoMsg(C4NetworkServer* self, pxiword index, C4NetworkMsg value)
{
    pxb8 state = 1;

    for (pxiword i = 0; i < self->items.size; i += 1) {
        C4NetworkSession item = {0};

        if (i != index) {
            item = c4NetworkServerGetOr(self, i, item);

            if (c4NetworkSessionWriteMsg(&item, value) == 0)
                state = 0;
        }
    }

    return state;
}

pxb8
c4NetworkServerWriteMsg(C4NetworkServer* self, pxiword index, C4NetworkMsg value)
{
    C4NetworkSession item =
        c4NetworkServerGetOr(self, index, (C4NetworkSession) {0});

    if (c4NetworkSessionWriteMsg(&item, value) == 0)
        return 0;

    return 1;
}

pxb8
c4NetworkServerReadMsg(C4NetworkServer* self, pxiword index, C4NetworkMsg* value)
{
    C4NetworkSession item =
        c4NetworkServerGetOr(self, index, (C4NetworkSession) {0});

    if (c4NetworkSessionReadMsg(&item, value) == 0)
        return 0;

    return 1;
}

C4NetworkReaderCtxt*
c4NetworkSessionReaderCtxt(C4NetworkSession* self, PxArena* arena, pxiword length)
{
    C4NetworkReaderCtxt result = {0};

    result.source = pxSourceFromSocketTcp(self->socket);

    result.arena = pxArenaMake(pxArenaReserve(arena, pxu8, length), length);
    result.queue = &self->input_queue;
    result.lock  = self->input_lock;

    return pxArenaCopy(arena, &result, C4NetworkReaderCtxt, 1);
}

C4NetworkWriterCtxt*
c4NetworkSessionWriterCtxt(C4NetworkSession* self, PxArena* arena, pxiword length)
{
    C4NetworkWriterCtxt result = {0};

    result.target = pxTargetFromSocketTcp(self->socket);

    result.arena = pxArenaMake(pxArenaReserve(arena, pxu8, length), length);
    result.queue = &self->output_queue;
    result.lock  = self->output_lock;

    return pxArenaCopy(arena, &result, C4NetworkWriterCtxt, 1);
}

#endif // C4_ENGINE_NETWORK_C
