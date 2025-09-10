#ifndef PX_STREAM_READER_C
#define PX_STREAM_READER_C

#include "reader.h"

PxReader
pxBufferReader(PxBuffer8* self, PxArena* arena, pxiword length)
{
    PxReader result = {0};

    if (self == 0 || length <= 0) return result;

    result.buffer = pxBuffer8Reserve(arena, length);

    if (result.buffer.length > 0) {
        result.ctxt = self;
        result.proc = &pxBuffer8ReadHead;
    }

    return result;
}

pxiword
pxReaderFill(PxReader* self)
{
    PxReaderProc* proc = pxCast(PxReaderProc*, self->proc);

    if (proc != 0)
        return proc(self->ctxt, &self->buffer);

    return 0;
}

pxu8
pxReaderPeekByte(PxReader* self, pxiword offset)
{
    if (offset < 0 || offset >= self->buffer.length)
        return 0;

    if (offset >= self->buffer.size) {
        pxiword length = offset - self->buffer.size + 1;
        pxiword amount = 0;

        for (pxiword i = 0; i < length;) {
            amount = pxReaderFill(self);

            if (amount != 0)
                i += amount;
            else
                return 0;
        }
    }

    return pxBuffer8GetForwOr(&self->buffer, offset, 0);
}

PxString8
pxReaderPeekString8(PxReader* self, PxArena* arena, pxiword length)
{
    if (length <= 0) return (PxString8) {0};

    pxiword offset = pxArenaOffset(arena);
    pxu8*   result = pxArenaReserve(arena, pxu8, length + 1);
    pxiword diff   = 0;
    pxu8    byte   = pxReaderPeekByte(self, 0);

    while (byte != 0 && diff < length) {
        result[diff] = byte;

        diff += 1;
        byte  = pxReaderPeekByte(self, diff);
    }

    if (diff < length)
        pxArenaRewind(arena, offset + diff + 1);

    return (PxString8) {
        .memory = result, .length = diff,
    };
}

PxString8
pxReaderPeekLine(PxReader* self, PxArena* arena, pxiword length)
{
    if (length <= 0) return (PxString8) {0};

    pxiword offset = pxArenaOffset(arena);
    pxu8*   result = pxArenaReserve(arena, pxu8, length + 1);
    pxiword diff   = 0;
    pxu8    byte   = pxReaderPeekByte(self, 0);

    while (byte != 0 && byte != 10 && diff < length) {
        result[diff] = byte;

        diff += 1;
        byte  = pxReaderPeekByte(self, diff);
    }

    if (diff < length)
        pxArenaRewind(arena, offset + diff + 1);

    return (PxString8) {
        .memory = result, .length = diff,
    };
}

pxu8
pxReaderByte(PxReader* self, pxiword offset)
{
    if (offset < 0) return 0;

    for (pxiword i = 0; i < offset;) {
        i += pxBuffer8DropHead(&self->buffer, offset - i);

        if (i < offset) {
            if (pxReaderFill(self) == 0)
                return 0;
        } else
            break;
    }

    return pxBuffer8GetForwOr(&self->buffer, 0, 0);
}

PxString8
pxReaderString8(PxReader* self, PxArena* arena, pxiword length)
{
    if (length <= 0) return (PxString8) {0};

    pxiword offset = pxArenaOffset(arena);
    pxu8*   result = pxArenaReserve(arena, pxu8, length + 1);
    pxiword diff   = 0;
    pxu8    byte   = pxReaderPeekByte(self, 0);

    while (byte != 0 && diff < length) {
        result[diff] = byte;

        diff += 1;
        byte  = pxReaderByte(self, 1);
    }

    if (diff < length)
        pxArenaRewind(arena, offset + diff + 1);

    return (PxString8) {
        .memory = result, .length = diff,
    };
}

PxString8
pxReaderLine(PxReader* self, PxArena* arena, pxiword length)
{
    if (length <= 0) return (PxString8) {0};

    pxiword offset = pxArenaOffset(arena);
    pxu8*   result = pxArenaReserve(arena, pxu8, length + 1);
    pxiword diff   = 0;
    pxu8    byte   = pxReaderPeekByte(self, 0);

    while (byte != 0 && byte != 10 && diff < length) {
        result[diff] = byte;

        diff += 1;
        byte  = pxReaderByte(self, 1);
    }

    byte = pxReaderByte(self, 1);

    if (diff < length)
        pxArenaRewind(arena, offset + diff + 1);

    return (PxString8) {
        .memory = result, .length = diff,
    };
}

#endif // PX_STREAM_READER_C
