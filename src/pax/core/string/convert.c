#ifndef PX_CORE_STRING_CONVERT_C
#define PX_CORE_STRING_CONVERT_C

#include "convert.h"

pxiword
pxUtf8UnitsFromMemory16(pxu16* memory, pxiword length)
{
    pxiword result = 0;

    for (pxiword index = 0; index < length;) {
        pxi32 unicode = 0;

        pxiword read = pxUtf16ReadMemory16Forw(
            memory, length, index, &unicode);

        pxiword write = pxUtf8UnitsToWrite(unicode);

        if (read <= 0 || write <= 0) return 0;

        index  += read;
        result += write;
    }

    return result;
}

pxiword
pxUtf8UnitsFromMemory32(pxu32* memory, pxiword length)
{
    pxiword result = 0;

    for (pxiword index = 0; index < length;) {
        pxi32 unicode = 0;

        pxiword read = pxUtf32ReadMemory32Forw(
            memory, length, index, &unicode);

        pxiword write = pxUtf8UnitsToWrite(unicode);

        if (read <= 0 || write <= 0) return 0;

        index  += read;
        result += write;
    }

    return result;
}

PxString8
pxString8CopyString16(PxArena* arena, PxString16 value)
{
    pxiword length = pxUtf8UnitsFromMemory16(
        value.memory, value.length);

    pxu8* result = pxArenaReserve(arena, pxu8, length + 1);

    if (result == 0 || length <= 0) return (PxString8) {0};

    pxiword index = 0;
    pxiword other = 0;

    while (index < length) {
        pxi32 unicode = 0;

        other += pxUtf16ReadMemory16Forw(
            value.memory, value.length, other, &unicode);

        index += pxUtf8WriteMemory8Forw(
            result, length ,index, unicode);
    }

    return (PxString8) {
        .memory = result,
        .length = length,
    };
}

PxString8
pxString8CopyString32(PxArena* arena, PxString32 value)
{
    pxiword length = pxUtf8UnitsFromMemory32(
        value.memory, value.length);

    pxu8* result = pxArenaReserve(arena, pxu8, length + 1);

    if (result == 0 || length <= 0) return (PxString8) {0};

    pxiword index = 0;
    pxiword other = 0;

    while (index < length) {
        pxi32 unicode = 0;

        other += pxUtf32ReadMemory32Forw(
            value.memory, value.length, other, &unicode);

        index += pxUtf8WriteMemory8Forw(
            result, length ,index, unicode);
    }

    return (PxString8) {
        .memory = result,
        .length = length,
    };
}

pxiword
pxUtf16UnitsFromMemory8(pxu8* memory, pxiword length)
{
    pxiword result = 0;

    for (pxiword index = 0; index < length;) {
        pxi32 unicode = 0;

        pxiword read = pxUtf8ReadMemory8Forw(
            memory, length, index, &unicode);

        pxiword write = pxUtf16UnitsToWrite(unicode);

        if (read <= 0 || write <= 0) return 0;

        index  += read;
        result += write;
    }

    return result;
}

pxiword
pxUtf16UnitsFromMemory32(pxu32* memory, pxiword length)
{
    pxiword result = 0;

    for (pxiword index = 0; index < length;) {
        pxi32 unicode = 0;

        pxiword read = pxUtf32ReadMemory32Forw(
            memory, length, index, &unicode);

        pxiword write = pxUtf16UnitsToWrite(unicode);

        if (read <= 0 || write <= 0) return 0;

        index  += read;
        result += write;
    }

    return result;
}

PxString16
pxString16CopyString8(PxArena* arena, PxString8 value)
{
    pxiword length = pxUtf16UnitsFromMemory8(
        value.memory, value.length);

    pxu16* result = pxArenaReserve(arena, pxu16, length + 1);

    if (result == 0 || length <= 0) return (PxString16) {0};

    pxiword index = 0;
    pxiword other = 0;

    while (index < length) {
        pxi32 unicode = 0;

        other += pxUtf8ReadMemory8Forw(
            value.memory, value.length, other, &unicode);

        index += pxUtf16WriteMemory16Forw(
            result, length ,index, unicode);
    }

    return (PxString16) {
        .memory = result,
        .length = length,
    };
}

PxString16
pxString16CopyString32(PxArena* arena, PxString32 value)
{
    pxiword length = pxUtf16UnitsFromMemory32(
        value.memory, value.length);

    pxu16* result = pxArenaReserve(arena, pxu16, length + 1);

    if (result == 0 || length <= 0) return (PxString16) {0};

    pxiword index = 0;
    pxiword other = 0;

    while (index < length) {
        pxi32 unicode = 0;

        other += pxUtf32ReadMemory32Forw(
            value.memory, value.length, other, &unicode);

        index += pxUtf16WriteMemory16Forw(
            result, length ,index, unicode);
    }

    return (PxString16) {
        .memory = result,
        .length = length,
    };
}

pxiword
pxUtf32UnitsFromMemory8(pxu8* memory, pxiword length)
{
    pxiword result = 0;

    for (pxiword index = 0; index < length;) {
        pxi32 unicode = 0;

        pxiword read = pxUtf8ReadMemory8Forw(
            memory, length, index, &unicode);

        pxiword write = pxUtf32UnitsToWrite(unicode);

        if (read <= 0 || write <= 0) return 0;

        index  += read;
        result += write;
    }

    return result;
}

pxiword
pxUtf32UnitsFromMemory16(pxu16* memory, pxiword length)
{
    pxiword result = 0;

    for (pxiword index = 0; index < length;) {
        pxi32 unicode = 0;

        pxiword read = pxUtf16ReadMemory16Forw(
            memory, length, index, &unicode);

        pxiword write = pxUtf32UnitsToWrite(unicode);

        if (read <= 0 || write <= 0) return 0;

        index  += read;
        result += write;
    }

    return result;
}

PxString32
pxString32CopyString8(PxArena* arena, PxString8 value)
{
    pxiword length = pxUtf32UnitsFromMemory8(
        value.memory, value.length);

    pxu32* result = pxArenaReserve(arena, pxu32, length + 1);

    if (result == 0 || length <= 0) return (PxString32) {0};

    pxiword index = 0;
    pxiword other = 0;

    while (index < length) {
        pxi32 unicode = 0;

        other += pxUtf8ReadMemory8Forw(
            value.memory, value.length, other, &unicode);

        index += pxUtf32WriteMemory32Forw(
            result, length ,index, unicode);
    }

    return (PxString32) {
        .memory = result,
        .length = length,
    };
}

PxString32
pxString32CopyString16(PxArena* arena, PxString16 value)
{
    pxiword length = pxUtf32UnitsFromMemory16(
        value.memory, value.length);

    pxu32* result = pxArenaReserve(arena, pxu32, length + 1);

    if (result == 0 || length <= 0) return (PxString32) {0};

    pxiword index = 0;
    pxiword other = 0;

    while (index < length) {
        pxi32 unicode = 0;

        other += pxUtf16ReadMemory16Forw(
            value.memory, value.length, other, &unicode);

        index += pxUtf32WriteMemory32Forw(
            result, length ,index, unicode);
    }

    return (PxString32) {
        .memory = result,
        .length = length,
    };
}

#endif // PX_CORE_STRING_CONVERT_C
