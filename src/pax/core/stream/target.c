#ifndef PX_CORE_STREAM_TARGET_C
#define PX_CORE_STREAM_TARGET_C

#include "target.h"

static pxiword
pxTargetWrite(PxTarget self, pxu8* memory, pxiword length)
{
    PxTargetProc* proc = px_as(PxTargetProc*, self.proc);

    if (proc != 0)
        return proc(self.ctxt, memory, length);

    return 0;
}

PxTarget
pxBufferedTarget(PxTarget self, PxBuffer8* buffer)
{
    PxTarget result = self;

    result.buffer = buffer;

    return result;
}

PxTarget
pxTargetFromBuffer8(PxBuffer8* self)
{
    PxTarget result = {0};

    if (self == 0) return result;

    result.ctxt = self;
    result.proc = &pxBuffer8WriteMemory8Tail;

    return result;
}

pxiword
pxTargetFlush(PxTarget self)
{
    if (self.buffer == 0) return 0;

    pxBuffer8Normalize(self.buffer);

    pxu8*   memory = self.buffer->memory;
    pxiword length = self.buffer->size;

    pxiword size = pxTargetWrite(self, memory, length);

    self.buffer->size -= size;
    self.buffer->head  = (self.buffer->head + size) % self.buffer->length;

    return size;
}

pxiword
pxTargetWriteMemory8(PxTarget self, pxu8* memory, pxiword length)
{
    if (self.buffer == 0) return pxTargetWrite(self, memory, length);

    pxiword size = self.buffer->length - self.buffer->size;

    if (length > self.buffer->length || length > size) {
        if (pxTargetFlush(self) <= 0) return 0;

        if (length > self.buffer->length)
            return pxTargetWrite(self, memory, length);
    }

    return pxBuffer8WriteMemory8Tail(self.buffer, memory, length);
}

pxiword
pxTargetWriteMemory16(PxTarget self, pxu16* memory, pxiword length)
{
    pxiword index  = 0;
    pxiword result = 0;

    while (index < length) {
        pxi32 unicode = 0;

        index  += pxUtf16ReadForw(memory, length, index, &unicode);
        result += pxTargetWriteUnicode(self, unicode);
    }

    return result;
}

pxiword
pxTargetWriteMemory32(PxTarget self, pxu32* memory, pxiword length)
{
    pxiword index  = 0;
    pxiword result = 0;

    while (index < length) {
        pxi32 unicode = 0;

        index  += pxUtf32ReadForw(memory, length, index, &unicode);
        result += pxTargetWriteUnicode(self, unicode);
    }

    return result;
}

pxiword
pxTargetWriteBuffer8(PxTarget self, PxBuffer8* value)
{
    pxBuffer8Normalize(value);

    pxu8*   memory = value->memory;
    pxiword length = value->size;
    pxiword size   = 0;
    pxiword temp   = 1;

    for (; size < length && temp != 0; size += temp)
        temp = pxTargetWriteMemory8(self, memory + size, length - size);

    value->size -= size;
    value->head  = (value->head + size) % value->length;

    return size;
}

pxiword
pxTargetWriteBuffer16(PxTarget self, PxBuffer16* value)
{
    pxBuffer16Normalize(value);

    pxu16*  memory = value->memory;
    pxiword length = value->size;
    pxiword size   = 0;
    pxiword temp   = 1;

    for (; size < length && temp != 0; size += temp)
        temp = pxTargetWriteMemory16(self, memory + size, length - size);

    value->size -= size;
    value->head  = (value->head + size) % value->length;

    return size;
}

pxiword
pxTargetWriteBuffer32(PxTarget self, PxBuffer32* value)
{
    pxBuffer32Normalize(value);

    pxu32*  memory = value->memory;
    pxiword length = value->size;
    pxiword size   = 0;
    pxiword temp   = 1;

    for (; size < length && temp != 0; size += temp)
        temp = pxTargetWriteMemory32(self, memory + size, length - size);

    value->size -= size;
    value->head  = (value->head + size) % value->length;

    return size;
}

pxiword
pxTargetWriteByte(PxTarget self, pxu8 value)
{
    return pxTargetWriteMemory8(self, &value, 1);
}

pxiword
pxTargetWriteString8(PxTarget self, PxString8 value)
{
    pxu8*   memory = value.memory;
    pxiword length = value.length;
    pxiword size   = 0;
    pxiword temp   = 1;

    for (; size < length && temp != 0; size += temp)
        temp = pxTargetWriteMemory8(self, memory + size, length - size);

    return size;
}

pxiword
pxTargetWriteString16(PxTarget self, PxString16 value)
{
    pxu16*  memory = value.memory;
    pxiword length = value.length;
    pxiword size   = 0;
    pxiword temp   = 1;

    for (; size < length && temp != 0; size += temp)
        temp = pxTargetWriteMemory16(self, memory + size, length - size);

    return size;
}

pxiword
pxTargetWriteString32(PxTarget self, PxString32 value)
{
    pxu32*  memory = value.memory;
    pxiword length = value.length;
    pxiword size   = 0;
    pxiword temp   = 1;

    for (; size < length && temp != 0; size += temp)
        temp = pxTargetWriteMemory32(self, memory + size, length - size);

    return size;
}

pxiword
pxTargetWriteUnicode(PxTarget self, pxi32 value)
{
    pxiword result = 0;
    PxUtf8  utf8   = {0};

    if (pxUtf8Encode(&utf8, value) == 0) return result;

    result = pxTargetWriteMemory8(self, utf8.items, utf8.size);

    return result;
}

#endif // PX_CORE_STREAM_TARGET_C
