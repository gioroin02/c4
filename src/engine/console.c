#ifndef C4_ENGINE_CONSOLE_C
#define C4_ENGINE_CONSOLE_C

#include "console.h"

pxuword
c4ConsoleReaderProc(C4ConsoleReaderCtxt* self)
{
    if (self == 0) return 1;

    PxConsoleQueue reader =
        pxConsoleQueueReserve(&self->arena, PX_MEMORY_KIB);

    pxiword offset = pxArenaOffset(&self->arena);
    pxb8    state  = 1;

    while (state != 0) {
        PxConsoleMsg message = {0};

        pxSourceReadBuffer8(self->source,
            pxConsoleQueueBuffer8(&reader));

        pxConsoleQueueReadMsg(&reader, &self->arena, &message);

        pxLockEnter(self->lock);

        if (message.type != PX_CONSOLE_MSG_NONE)
            state = pxQueueInsertTail(self->queue, PxConsoleMsg, &message);

        pxLockLeave(self->lock);

        pxArenaRewind(&self->arena, offset);
    }

    return 0;
}

C4Console
c4ConsoleCreate(PxArena* arena, pxiword length)
{
    C4Console result = {0};

    result.console = pxConsoleCreate(arena);

    result.input_lock  = pxLockCreate(arena);
    result.input_queue = pxQueueReserve(arena, PxConsoleMsg, length);

    result.output_queue = pxConsoleQueueReserve(arena, length);

    return result;
}

pxb8
c4ConsoleReadMsg(C4Console* self, PxConsoleMsg* value)
{
    PxConsoleMsg result = {0};

    pxLockEnter(self->input_lock);

    pxb8 state = pxQueueRemoveHead(&self->input_queue,
        PxConsoleMsg, &result);

    pxLockLeave(self->input_lock);

    if (state != 0 && value != 0) *value = result;

    return state;
}

pxb8
c4ConsoleWriteMsg(C4Console* self, PxConsoleMsg value)
{
    return pxConsoleQueueWriteMsg(&self->output_queue, value);
}

pxb8
c4ConsoleWriteBatch(C4Console* self, C4ConsoleBatch* batch)
{
    C4ConsoleCell item = c4ConsoleBatchGetOr(batch, 0, 0, (C4ConsoleCell) {0});

    PxConsoleColor text = item.text;
    PxConsoleColor back = item.back;

    c4ConsoleWriteMsg(self, pxConsoleMsgCursorMove(0, 0));
    c4ConsoleWriteMsg(self, pxConsoleMsgStyleText(text));
    c4ConsoleWriteMsg(self, pxConsoleMsgStyleBack(back));

    for (pxiword j = 0; j < batch->height; j += 1) {
        for (pxiword i = 0; i < batch->width; i += 1) {
            item = c4ConsoleBatchGetOr(batch, i, j, (C4ConsoleCell) {0});

            if (pxConsoleColorIsEqual(text, item.text) == 0) {
                c4ConsoleWriteMsg(self,
                    pxConsoleMsgStyleText(item.text));

                text = item.text;
            }

            if (pxConsoleColorIsEqual(back, item.back) == 0) {
                c4ConsoleWriteMsg(self,
                    pxConsoleMsgStyleBack(item.back));

                back = item.back;
            }

            c4ConsoleWriteMsg(self, pxConsoleMsgUnicode(item.unicode));
        }

        c4ConsoleWriteMsg(self, pxConsoleMsgCursorMove(0, j + 1));
    }

    return 1;
}

pxb8
c4ConsoleFlush(C4Console* self)
{
    PxTarget   target = pxTargetFromConsole(self->console);
    PxBuffer8* buffer = pxConsoleQueueBuffer8(&self->output_queue);

    pxiword size = buffer->size;

    pxiword result = pxTargetWriteBuffer8(target, buffer);

    return result == size ? 1 : 0;
}

C4ConsoleReaderCtxt*
c4ConsoleReaderCtxt(C4Console* self, PxArena* arena, pxiword length)
{
    C4ConsoleReaderCtxt result = {0};

    result.source = pxSourceFromConsole(self->console);

    result.arena = pxArenaMake(pxArenaReserve(arena, pxu8, length), length);
    result.queue = &self->input_queue;
    result.lock  = self->input_lock;

    return pxArenaCopy(arena, &result, C4ConsoleReaderCtxt, 1);
}

#endif // C4_ENGINE_CONSOLE_C
