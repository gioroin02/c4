#ifndef PX_CORE_STRING_CONVERT_C
#define PX_CORE_STRING_CONVERT_C

#include "convert.h"

PxString8
pxString8CopyMemory16(PxArena* arena, pxu16* memory, pxiword length)
{
    pxiword size =
        pxUtf8UnitsFromMemory16(memory, length);

    pxu8* result = pxArenaReserve(arena, pxu8, size + 1);

    if (result == 0 || size <= 0) return (PxString8) {0};

    pxiword index = 0;
    pxiword other = 0;

    while (other < length) {
        pxi32 unicode = 0;

        other += pxUtf16ReadForw(memory, length, other, &unicode);
        index += pxUtf8WriteForw(result, size, index, unicode);
    }

    return pxString8Make(result, size);
}

PxString8
pxString8CopyString16(PxArena* arena, PxString16 value)
{
    return pxString8CopyMemory16(arena, value.memory, value.length);
}

PxString8
pxString8CopyMemory32(PxArena* arena, pxu32* memory, pxiword length)
{
    pxiword size =
        pxUtf8UnitsFromMemory32(memory, length);

    pxu8* result = pxArenaReserve(arena, pxu8, size + 1);

    if (result == 0 || size <= 0) return (PxString8) {0};

    pxiword index = 0;
    pxiword other = 0;

    while (other < length) {
        pxi32 unicode = 0;

        other += pxUtf32ReadForw(memory, length, other, &unicode);
        index += pxUtf8WriteForw(result, size, index, unicode);
    }

    return pxString8Make(result, size);
}

PxString8
pxString8CopyString32(PxArena* arena, PxString32 value)
{
    return pxString8CopyMemory32(arena, value.memory, value.length);
}

pxiword
pxMemory8WriteUnicode(pxu8* memory, pxiword length, pxi32 value)
{
    return pxUtf8WriteForw(memory, length, 0, value);
}

pxiword
pxMemory8WriteString8(pxu8* memory, pxiword length, PxString8 value)
{
    if (value.length <= 0 || value.length > length)
        return 0;

    for (pxiword i = 0; i < value.length; i += 1)
        memory[i] = value.memory[i];

    return value.length;
}

pxiword
pxMemory8WriteString16(pxu8* memory, pxiword length, PxString16 value)
{
    pxiword size = pxUtf8UnitsFromMemory16(
        value.memory, value.length);

    if (size <= 0 || size > length) return 0;

    pxiword index = 0;
    pxiword other = 0;

    while (other < value.length) {
        pxi32 unicode = 0;

        index += pxUtf16ReadForw(value.memory, value.length,
            index, &unicode);

        other += pxUtf8WriteForw(memory, length, other, unicode);
    }

    return size;
}

pxiword
pxMemory8WriteString32(pxu8* memory, pxiword length, PxString32 value)
{
    pxiword size = pxUtf8UnitsFromMemory32(
        value.memory, value.length);

    if (size <= 0 || size > length) return 0;

    pxiword index = 0;
    pxiword other = 0;

    while (other < value.length) {
        pxi32 unicode = 0;

        index += pxUtf32ReadForw(value.memory, value.length,
            index, &unicode);

        other += pxUtf8WriteForw(memory, length, other, unicode);
    }

    return size;
}

PxString16
pxString16CopyMemory8(PxArena* arena, pxu8* memory, pxiword length)
{
    pxiword size =
        pxUtf16UnitsFromMemory8(memory, length);

    pxu16* result = pxArenaReserve(arena, pxu16, size + 1);

    if (result == 0 || size <= 0) return (PxString16) {0};

    pxiword index = 0;
    pxiword other = 0;

    while (other < length) {
        pxi32 unicode = 0;

        other += pxUtf8ReadForw(memory, length, other, &unicode);
        index += pxUtf16WriteForw(result, size, index, unicode);
    }

    return pxString16Make(result, size);
}

PxString16
pxString16CopyString8(PxArena* arena, PxString8 value)
{
    return pxString16CopyMemory8(arena, value.memory, value.length);
}

PxString16
pxString16CopyMemory32(PxArena* arena, pxu32* memory, pxiword length)
{
    pxiword size =
        pxUtf16UnitsFromMemory32(memory, length);

    pxu16* result = pxArenaReserve(arena, pxu16, size + 1);

    if (result == 0 || size <= 0) return (PxString16) {0};

    pxiword index = 0;
    pxiword other = 0;

    while (other < length) {
        pxi32 unicode = 0;

        other += pxUtf32ReadForw(memory, length, other, &unicode);
        index += pxUtf16WriteForw(result, size, index, unicode);
    }

    return pxString16Make(result, size);
}

PxString16
pxString16CopyString32(PxArena* arena, PxString32 value)
{
    return pxString16CopyMemory32(arena, value.memory, value.length);
}

pxiword
pxMemory16WriteUnicode(pxu16* memory, pxiword length, pxi32 value)
{
    return pxUtf16WriteForw(memory, length, 0, value);
}

pxiword
pxMemory16WriteString8(pxu16* memory, pxiword length, PxString8 value)
{
    pxiword size = pxUtf16UnitsFromMemory8(
        value.memory, value.length);

    if (size <= 0 || size > length) return 0;

    pxiword index = 0;
    pxiword other = 0;

    while (other < value.length) {
        pxi32 unicode = 0;

        index += pxUtf8ReadForw(value.memory, value.length,
            index, &unicode);

        other += pxUtf16WriteForw(memory, length, other, unicode);
    }

    return size;
}

pxiword
pxMemory16WriteString16(pxu16* memory, pxiword length, PxString16 value)
{
    if (value.length <= 0 || value.length > length)
        return 0;

    for (pxiword i = 0; i < value.length; i += 1)
        memory[i] = value.memory[i];

    return value.length;
}

pxiword
pxMemory16WriteString32(pxu16* memory, pxiword length, PxString32 value)
{
    pxiword size = pxUtf16UnitsFromMemory32(
        value.memory, value.length);

    if (size <= 0 || size > length) return 0;

    pxiword index = 0;
    pxiword other = 0;

    while (other < value.length) {
        pxi32 unicode = 0;

        index += pxUtf32ReadForw(value.memory, value.length,
            index, &unicode);

        other += pxUtf16WriteForw(memory, length, other, unicode);
    }

    return size;
}

PxString32
pxString32CopyMemory8(PxArena* arena, pxu8* memory, pxiword length)
{
    pxiword size =
        pxUtf32UnitsFromMemory8(memory, length);

    pxu32* result = pxArenaReserve(arena, pxu32, size + 1);

    if (result == 0 || size <= 0) return (PxString32) {0};

    pxiword index = 0;
    pxiword other = 0;

    while (other < length) {
        pxi32 unicode = 0;

        other += pxUtf8ReadForw(memory, length, other, &unicode);
        index += pxUtf32WriteForw(result, size, index, unicode);
    }

    return pxString32Make(result, size);
}

PxString32
pxString32CopyString8(PxArena* arena, PxString8 value)
{
    return pxString32CopyMemory8(arena, value.memory, value.length);
}

PxString32
pxString32CopyMemory16(PxArena* arena, pxu16* memory, pxiword length)
{
    pxiword size =
        pxUtf32UnitsFromMemory16(memory, length);

    pxu32* result = pxArenaReserve(arena, pxu32, size + 1);

    if (result == 0 || size <= 0) return (PxString32) {0};

    pxiword index = 0;
    pxiword other = 0;

    while (other < length) {
        pxi32 unicode = 0;

        other += pxUtf16ReadForw(memory, length, other, &unicode);
        index += pxUtf32WriteForw(result, size, index, unicode);
    }

    return pxString32Make(result, size);
}

PxString32
pxString32CopyString16(PxArena* arena, PxString16 value)
{
    return pxString32CopyMemory16(arena, value.memory, value.length);
}

pxiword
pxMemory32WriteUnicode(pxu32* memory, pxiword length, pxi32 value)
{
    return pxUtf32WriteForw(memory, length, 0, value);
}

pxiword
pxMemory32WriteString8(pxu32* memory, pxiword length, PxString8 value)
{
    pxiword size = pxUtf32UnitsFromMemory8(
        value.memory, value.length);

    if (size <= 0 || size > length) return 0;

    pxiword index = 0;
    pxiword other = 0;

    while (other < value.length) {
        pxi32 unicode = 0;

        index += pxUtf8ReadForw(value.memory, value.length,
            index, &unicode);

        other += pxUtf32WriteForw(memory, length, other, unicode);
    }

    return size;
}

pxiword
pxMemory32WriteString16(pxu32* memory, pxiword length, PxString16 value)
{
    pxiword size = pxUtf32UnitsFromMemory16(
        value.memory, value.length);

    if (size <= 0 || size > length) return 0;

    pxiword index = 0;
    pxiword other = 0;

    while (other < value.length) {
        pxi32 unicode = 0;

        index += pxUtf16ReadForw(value.memory, value.length,
            index, &unicode);

        other += pxUtf32WriteForw(memory, length, other, unicode);
    }

    return size;
}

pxiword
pxMemory32WriteString32(pxu32* memory, pxiword length, PxString32 value)
{
    if (value.length <= 0 || value.length > length)
        return 0;

    for (pxiword i = 0; i < value.length; i += 1)
        memory[i] = value.memory[i];

    return value.length;
}

#endif // PX_CORE_STRING_CONVERT_C
