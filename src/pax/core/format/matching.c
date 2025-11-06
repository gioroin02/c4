#ifndef PX_CORE_FORMAT_MATCHING_C
#define PX_CORE_FORMAT_MATCHING_C

#include "matching.h"

static pxb8
pxUnicodeIsUnsignedDigit(pxi32 value, PxFormatRadix radix, PxFormatFlag flags)
{
    if ((flags & PX_FORMAT_FLAG_PLUS) != 0 && value == PX_ASCII_PLUS)
        return 1;

    if (pxUnicodeIsDigit(value, radix, flags) != 0) return 1;

    return 0;
}

static pxb8
pxUnicodeIsIntegerDigit(pxi32 value, PxFormatRadix radix, PxFormatFlag flags)
{
    if ((flags & PX_FORMAT_FLAG_PLUS) != 0 && value == PX_ASCII_PLUS)
        return 1;

    if (value == PX_ASCII_MINUS) return 1;

    if (pxUnicodeIsDigit(value, radix, flags) != 0) return 1;

    return 0;
}

static pxb8
pxUnicodeIsBooleanDigit(pxi32 value, PxFormatFlag flags)
{
    switch (value) {
        case PX_ASCII_LOWER_T:
        case PX_ASCII_LOWER_R:
        case PX_ASCII_LOWER_U:
        case PX_ASCII_LOWER_E: {
            if ((flags & PX_FORMAT_FLAG_UPPER) != 0)
                return 0;

            return 1;
        } break;

        case PX_ASCII_UPPER_T:
        case PX_ASCII_UPPER_R:
        case PX_ASCII_UPPER_U:
        case PX_ASCII_UPPER_E: {
            if ((flags & PX_FORMAT_FLAG_UPPER) == 0)
                return 0;

            return 1;
        } break;

        default: break;
    }

    return 0;
}

PxString8
pxSourceMatchUnsigned(PxSource source, PxArena* arena, pxiword length, PxFormatRadix radix, PxFormatFlag flags)
{
    if (length <= 0) return pxString8Make(0, 0);

    pxiword offset = pxArenaOffset(arena);
    pxu8*   memory = pxArenaReserve(arena, pxu8, length + 1);

    if (memory == 0) return pxString8Make(0, 0);

    pxiword size = 0;
    pxu8    byte = pxSourcePeekByte(source);

    while (pxUnicodeIsUnsignedDigit(byte, radix, flags) != 0) {
        memory[size] = byte;

        pxSourceDrop(source, 1);

        size += 1;
        byte  = pxSourcePeekByte(source);
    }

    if (size < length) pxArenaRewind(arena, offset + size + 1);

    return pxString8Make(memory, size);
}

PxString8
pxSourceMatchInteger(PxSource source, PxArena* arena, pxiword length, PxFormatRadix radix, PxFormatFlag flags)
{
    if (length <= 0) return pxString8Make(0, 0);

    pxiword offset = pxArenaOffset(arena);
    pxu8*   memory = pxArenaReserve(arena, pxu8, length + 1);

    if (memory == 0) return pxString8Make(0, 0);

    pxiword size = 0;
    pxu8    byte = pxSourcePeekByte(source);

    while (pxUnicodeIsIntegerDigit(byte, radix, flags) != 0) {
        memory[size] = byte;

        pxSourceDrop(source, 1);

        size += 1;
        byte  = pxSourcePeekByte(source);
    }

    if (size < length) pxArenaRewind(arena, offset + size + 1);

    return pxString8Make(memory, size);
}

PxString8
pxSourceMatchBoolean(PxSource source, PxArena* arena, pxiword length, PxFormatFlag flags)
{
    if (length <= 0) return pxString8Make(0, 0);

    pxiword offset = pxArenaOffset(arena);
    pxu8*   memory = pxArenaReserve(arena, pxu8, length + 1);

    if (memory == 0) return pxString8Make(0, 0);

    pxiword size = 0;
    pxu8    byte = pxSourcePeekByte(source);

    while (pxUnicodeIsBooleanDigit(byte, flags) != 0) {
        memory[size] = byte;

        pxSourceDrop(source, 1);

        size += 1;
        byte  = pxSourcePeekByte(source);
    }

    if (size < length) pxArenaRewind(arena, offset + size + 1);

    return pxString8Make(memory, size);
}

#endif // PX_CORE_FORMAT_MATCHING_C
