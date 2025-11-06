#ifndef PX_CORE_PROCESS_CHANNEL_C
#define PX_CORE_PROCESS_CHANNEL_C

#include "channel.h"

PxChannel
pxChannelOpen(PxArena* arena, pxiword length)
{
    PxChannel result = {0};

    result.lock = pxLockCreate(arena);

    if (result.lock != 0)
        result.buffer = pxBuffer8Reserve(arena, length);

    return result;
}

void
pxChannelClose(PxChannel* self)
{
    if (self != 0) pxLockDestroy(&self->lock);
}

pxb8
pxChannelIsOpen(PxChannel* self)
{
    return self->lock != 0 ? 1 : 0;
}

pxiword
pxChannelWrite(PxChannel* self, pxu8* memory, pxiword length)
{
    pxiword size = 0;

    pxLockEnter(self->lock);

    size = pxBuffer8WriteMemory8Tail(&self->buffer,
        memory, length);

    pxLockLeave(self->lock);

    return size;
}

pxiword
pxChannelRead(PxChannel* self, pxu8* memory, pxiword length)
{
    pxiword size = 0;

    pxLockEnter(self->lock);

    size = pxBuffer8ReadMemory8Head(&self->buffer,
        memory, length);

    pxLockLeave(self->lock);

    return size;
}

PxSource
pxSourceFromChannel(PxChannel* self)
{
    PxSource result = {0};

    if (self == 0) return result;

    result.ctxt = self;
    result.proc = &pxChannelRead;

    return result;
}

PxTarget
pxTargetFromChannel(PxChannel* self)
{
    PxTarget result = {0};

    if (self == 0) return result;

    result.ctxt = self;
    result.proc = &pxChannelWrite;

    return result;
}

#endif // PX_CORE_PROCESS_CHANNEL_C
