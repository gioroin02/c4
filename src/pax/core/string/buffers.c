#ifndef PX_CORE_STRING_BUFFERS_C
#define PX_CORE_STRING_BUFFERS_C

#include "buffers.h"

pxiword
pxBuffer8WriteUnicodeHead(PxBuffer8* self, pxi32 value)
{
    PxUtf8 utf8 = {0};

    pxUtf8Encode(&utf8, value);

    pxiword prev = self->head + self->length - utf8.size;

    self->size += utf8.size;
    self->head  = prev % self->length;

    for (pxiword i = 0; i < utf8.size; i += 1)
        self->memory[(self->head + i) % self->length] = utf8.items[i];

    return utf8.size;
}

pxiword
pxBuffer8WriteMemory16Head(PxBuffer8* self, pxu16* memory, pxiword length)
{
    pxiword temp = pxUtf8UnitsFromMemory16(memory, length);
    pxiword size = px_min(temp, self->length - self->size);

    if (size <= 0 || size > self->length) return 0;

    pxiword prev = self->head + self->length - size;

    self->size += size;
    self->head  = prev % self->length;

    pxiword index = 0;
    pxiword other = 0;

    while (index < size) {
        PxUtf8 utf8    = {0};
        pxi32  unicode = 0;

        other += pxUtf16ReadForw(memory, length, other, &unicode);

        pxUtf8Encode(&utf8, unicode);

        for (pxiword i = 0; i < utf8.size; i += 1) {
            pxiword j = self->head + index + i;

            self->memory[j % self->length] =
                utf8.items[i];
        }

        index += utf8.size;
    }

    return other;
}

pxiword
pxBuffer8WriteMemory32Head(PxBuffer8* self, pxu32* memory, pxiword length)
{
    pxiword temp = pxUtf8UnitsFromMemory32(memory, length);
    pxiword size = px_min(temp, self->length - self->size);

    if (size <= 0 || size > self->length) return 0;

    pxiword prev = self->head + self->length - size;

    self->size += size;
    self->head  = prev % self->length;

    pxiword index = 0;
    pxiword other = 0;

    while (index < size) {
        PxUtf8 utf8    = {0};
        pxi32  unicode = 0;

        other += pxUtf32ReadForw(memory, length, other, &unicode);

        pxUtf8Encode(&utf8, unicode);

        for (pxiword i = 0; i < utf8.size; i += 1) {
            pxiword j = self->head + index + i;

            self->memory[j % self->length] =
                utf8.items[i];
        }

        index += utf8.size;
    }

    return other;
}

pxiword
pxBuffer8WriteString8Head(PxBuffer8* self, PxString8 string)
{
    return pxBuffer8WriteMemory8Head(self, string.memory, string.length);
}

pxiword
pxBuffer8WriteString16Head(PxBuffer8* self, PxString16 string)
{
    return pxBuffer8WriteMemory16Head(self, string.memory, string.length);
}

pxiword
pxBuffer8WriteString32Head(PxBuffer8* self, PxString32 string)
{
    return pxBuffer8WriteMemory32Head(self, string.memory, string.length);
}

pxiword
pxBuffer8WriteUnicodeTail(PxBuffer8* self, pxi32 value)
{
    PxUtf8 utf8 = {0};

    pxUtf8Encode(&utf8, value);

    pxiword next = self->tail + utf8.size;

    for (pxiword i = 0; i < utf8.size; i += 1)
        self->memory[(self->tail + i) % self->length] = utf8.items[i];

    self->size += utf8.size;
    self->tail  = next % self->length;

    return utf8.size;
}

pxiword
pxBuffer8WriteMemory16Tail(PxBuffer8* self, pxu16* memory, pxiword length)
{
    pxiword temp = pxUtf8UnitsFromMemory16(memory, length);
    pxiword size = px_min(temp, self->length - self->size);

    if (size <= 0 || size > self->length) return 0;

    pxiword next = self->tail + size;

    pxiword index = 0;
    pxiword other = 0;

    while (index < size) {
        PxUtf8 utf8    = {0};
        pxi32  unicode = 0;

        other += pxUtf16ReadForw(memory, length, other, &unicode);

        pxUtf8Encode(&utf8, unicode);

        for (pxiword i = 0; i < utf8.size; i += 1) {
            pxiword j = self->tail + index + i;

            self->memory[j % self->length] =
                utf8.items[i];
        }

        index += utf8.size;
    }

    self->size += size;
    self->tail  = next % self->length;

    return other;
}

pxiword
pxBuffer8WriteMemory32Tail(PxBuffer8* self, pxu32* memory, pxiword length)
{
    pxiword temp = pxUtf8UnitsFromMemory32(memory, length);
    pxiword size = px_min(temp, self->length - self->size);

    if (size <= 0 || size > self->length) return 0;

    pxiword next = self->tail + size;

    pxiword index = 0;
    pxiword other = 0;

    while (index < size) {
        PxUtf8 utf8    = {0};
        pxi32  unicode = 0;

        other += pxUtf32ReadForw(memory, length, other, &unicode);

        pxUtf8Encode(&utf8, unicode);

        for (pxiword i = 0; i < utf8.size; i += 1) {
            pxiword j = self->tail + index + i;

            self->memory[j % self->length] =
                utf8.items[i];
        }

        index += utf8.size;
    }

    self->size += size;
    self->tail  = next % self->length;

    return other;
}

pxiword
pxBuffer8WriteString8Tail(PxBuffer8* self, PxString8 string)
{
    return pxBuffer8WriteMemory8Tail(self, string.memory, string.length);
}

pxiword
pxBuffer8WriteString16Tail(PxBuffer8* self, PxString16 string)
{
    return pxBuffer8WriteMemory16Tail(self, string.memory, string.length);
}

pxiword
pxBuffer8WriteString32Tail(PxBuffer8* self, PxString32 string)
{
    return pxBuffer8WriteMemory32Tail(self, string.memory, string.length);
}

PxString8
pxBuffer8ReadString8Head(PxBuffer8* self, PxArena* arena, pxiword length)
{
    pxiword size = px_min(self->size, length);

    if (size <= 0 || size > self->size) return (PxString8) {0};

    pxu8* result = pxArenaReserve(arena, pxu8, size + 1);

    if (result != 0) {
        pxBuffer8ReadMemory8Head(self,
            result, size);

        return pxString8Make(result, size);
    }

    return (PxString8) {0};
}

PxString8
pxBuffer8ReadString8Tail(PxBuffer8* self, PxArena* arena, pxiword length)
{
    pxiword size = px_min(self->size, length);

    if (size <= 0 || size > self->size) return (PxString8) {0};

    pxu8* result = pxArenaReserve(arena, pxu8, size + 1);

    if (result != 0) {
        pxBuffer8ReadMemory8Tail(self,
            result, size);

        return pxString8Make(result, size);
    }

    return (PxString8) {0};
}

PxString8
pxBuffer8PeekString8Head(PxBuffer8* self, PxArena* arena, pxiword length)
{
    pxiword size = px_min(self->size, length);

    if (size <= 0 || size > self->size) return (PxString8) {0};

    pxu8* result = pxArenaReserve(arena, pxu8, size + 1);

    if (result != 0) {
        pxBuffer8PeekMemory8Head(self,
            result, size);

        return pxString8Make(result, size);
    }

    return (PxString8) {0};
}

PxString8
pxBuffer8PeekString8Tail(PxBuffer8* self, PxArena* arena, pxiword length)
{
    pxiword size = px_min(self->size, length);

    if (size <= 0 || size > self->size) return (PxString8) {0};

    pxu8* result = pxArenaReserve(arena, pxu8, size + 1);

    if (result != 0) {
        pxBuffer8PeekMemory8Tail(self,
            result, size);

        return pxString8Make(result, size);
    }

    return (PxString8) {0};
}

pxiword
pxBuffer16WriteUnicodeHead(PxBuffer16* self, pxi32 value)
{
    PxUtf16 utf16 = {0};

    pxUtf16Encode(&utf16, value);

    pxiword prev = self->head + self->length - utf16.size;

    self->size += utf16.size;
    self->head  = prev % self->length;

    for (pxiword i = 0; i < utf16.size; i += 1)
        self->memory[(self->head + i) % self->length] = utf16.items[i];

    return utf16.size;
}

pxiword
pxBuffer16WriteString16Head(PxBuffer16* self, PxString16 string)
{
    return pxBuffer16WriteMemory16Head(self, string.memory, string.length);
}

pxiword
pxBuffer16WriteUnicodeTail(PxBuffer16* self, pxi32 value)
{
    PxUtf16 utf16 = {0};

    pxUtf16Encode(&utf16, value);

    pxiword next = self->tail + utf16.size;

    for (pxiword i = 0; i < utf16.size; i += 1)
        self->memory[(self->tail + i) % self->length] = utf16.items[i];

    self->size += utf16.size;
    self->tail  = next % self->length;

    return utf16.size;
}

pxiword
pxBuffer16WriteString16Tail(PxBuffer16* self, PxString16 string)
{
    return pxBuffer16WriteMemory16Tail(self, string.memory, string.length);
}

pxiword
pxBuffer32WriteUnicodeHead(PxBuffer32* self, pxi32 value)
{
    PxUtf32 utf32 = {0};

    pxUtf32Encode(&utf32, value);

    pxiword prev = self->head + self->length - utf32.size;

    self->size += utf32.size;
    self->head  = prev % self->length;

    for (pxiword i = 0; i < utf32.size; i += 1)
        self->memory[(self->head + i) % self->length] = utf32.items[i];

    return utf32.size;
}

pxiword
pxBuffer32WriteString32Head(PxBuffer32* self, PxString32 string)
{
    return pxBuffer32WriteMemory32Head(self, string.memory, string.length);
}

pxiword
pxBuffer32WriteUnicodeTail(PxBuffer32* self, pxi32 value)
{
    PxUtf32 utf32 = {0};

    pxUtf32Encode(&utf32, value);

    pxiword next = self->tail + utf32.size;

    for (pxiword i = 0; i < utf32.size; i += 1)
        self->memory[(self->tail + i) % self->length] = utf32.items[i];

    self->size += utf32.size;
    self->tail  = next % self->length;

    return utf32.size;
}

pxiword
pxBuffer32WriteString32Tail(PxBuffer32* self, PxString32 string)
{
    return pxBuffer32WriteMemory32Tail(self, string.memory, string.length);
}

#endif // PX_CORE_STRING_BUFFERS_C
