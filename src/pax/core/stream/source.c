#ifndef PX_CORE_STREAM_SOURCE_C
#define PX_CORE_STREAM_SOURCE_C

#include "source.h"

static pxiword
pxSourceRead(PxSource self, pxu8* memory, pxiword length)
{
    PxSourceProc* proc = px_as(PxSourceProc*, self.proc);

    if (proc != 0)
        return proc(self.ctxt, memory, length);

    return 0;
}

PxSource
pxBufferedSource(PxSource self, PxBuffer8* buffer)
{
    PxSource result = self;

    result.buffer = buffer;

    return result;
}

PxSource
pxSourceFromBuffer8(PxBuffer8* self)
{
    PxSource result = {0};

    if (self == 0) return result;

    result.ctxt = self;
    result.proc = &pxBuffer8ReadMemory8Head;

    return result;
}

pxiword
pxSourceFill(PxSource self)
{
    if (self.buffer == 0) return 0;

    pxBuffer8Normalize(self.buffer);

    pxu8*   memory = self.buffer->memory + self.buffer->size;
    pxiword length = self.buffer->length - self.buffer->size;

    pxiword size = pxSourceRead(self, memory, length);

    self.buffer->size += size;
    self.buffer->tail  = (self.buffer->tail + size) % self.buffer->length;

    return size;
}

pxiword
pxSourceDrop(PxSource self, pxiword amount)
{
    pxiword temp = 1;

    for (pxiword i = 0; i < amount && temp != 0; i += temp) {
        if (self.buffer->size <= 0 && pxSourceFill(self) <= 0)
            return amount - i;

        temp = pxBuffer8DropHead(self.buffer, amount - i);
    }

    return amount;
}

pxiword
pxSourceReadMemory8(PxSource self, pxu8* memory, pxiword length)
{
    if (self.buffer == 0) return pxSourceRead(self, memory, length);

    pxiword temp = 0;

    for (pxiword i = 0; i < length; i += temp) {
        if (self.buffer->size <= 0 && pxSourceFill(self) <= 0)
            return length - i;

        temp = pxBuffer8ReadMemory8Head(self.buffer, memory + i, length - i);
    }

    return length;
}

pxiword
pxSourceReadBuffer8(PxSource self, PxBuffer8* value)
{
    pxBuffer8Normalize(value);

    pxu8*   memory = value->memory + value->size;
    pxiword length = value->length - value->size;

    pxiword size = pxSourceReadMemory8(self, memory, length);

    value->size += size;
    value->tail  = (value->tail + size) % value->length;

    return size;
}

pxu8
pxSourceReadByte(PxSource self)
{
    pxu8 result = 0;

    if (pxSourceReadMemory8(self, &result, 1) <= 0)
        return 0;

    return result;
}

PxString8
pxSourceReadString8(PxSource self, PxArena* arena, pxiword length)
{
    pxiword offset = pxArenaOffset(arena);
    pxu8*   memory = pxArenaReserve(arena, pxu8, length + 1);

    pxiword size = pxSourceReadMemory8(self, memory, length);

    if (size < length)
        pxArenaRewind(arena, offset + size + 1);

    return pxString8Make(memory, size);
}

pxiword
pxSourceReadUnicode(PxSource self, pxi32* value)
{
    PxUtf8  utf8   = {0};

    if (pxSourceReadMemory8(self, utf8.items, 1) <= 0)
        return 0;

    utf8.size = pxUtf8UnitsToRead(utf8.items[0]);

    pxSourceReadMemory8(self, utf8.items + 1, utf8.size - 1);

    pxUtf8Decode(&utf8, value);

    return utf8.size;
}

pxiword
pxSourcePeekMemory8(PxSource self, pxu8* memory, pxiword length)
{
    if (self.buffer == 0) return 0;

    pxiword temp = 0;

    for (pxiword i = 0; i < length; i += temp) {
        if (self.buffer->size <= 0 && pxSourceFill(self) <= 0)
            return length - i;

        temp = pxBuffer8PeekMemory8Head(self.buffer + i,
            memory + i, length - i);
    }

    return length;
}

pxiword
pxSourcePeekBuffer8(PxSource self, PxBuffer8* value)
{
    pxBuffer8Normalize(value);

    pxu8*   memory = value->memory + value->size;
    pxiword length = value->length - value->size;

    pxiword size = pxSourcePeekMemory8(self, memory, length);

    value->size += size;
    value->tail  = (value->tail + size) % value->length;

    return size;
}

pxu8
pxSourcePeekByte(PxSource self)
{
    pxu8 result = 0;

    if (pxSourcePeekMemory8(self, &result, 1) <= 0)
        return 0;

    return result;
}

PxString8
pxSourcePeekString8(PxSource self, PxArena* arena, pxiword length)
{
    pxiword offset = pxArenaOffset(arena);
    pxu8*   memory = pxArenaReserve(arena, pxu8, length + 1);

    pxiword size = pxSourcePeekMemory8(self, memory, length);

    if (size < length)
        pxArenaRewind(arena, offset + size + 1);

    return pxString8Make(memory, size);
}

pxiword
pxSourcePeekUnicode(PxSource self, pxi32* value)
{
    PxUtf8 utf8 = {0};

    if (pxSourcePeekMemory8(self, utf8.items, 1) <= 0)
        return 0;

    utf8.size = pxUtf8UnitsToRead(utf8.items[0]);

    pxSourcePeekMemory8(self, utf8.items, utf8.size);

    pxUtf8Decode(&utf8, value);

    return utf8.size;
}

#endif // PX_CORE_STREAM_SOURCE_C
