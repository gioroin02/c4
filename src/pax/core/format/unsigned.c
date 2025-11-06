#ifndef PX_CORE_FORMAT_UNSIGNED_C
#define PX_CORE_FORMAT_UNSIGNED_C

#include "unsigned.h"

pxiword
pxUnsignedDigits(pxuword value, PxFormatRadix radix, PxFormatFlag flags)
{
    pxiword digits = 1;
    pxuword width  = pxMagnitudeFormatRadix(radix);
    pxuword temp   = value;

    if (width <= 1) return 0;

    temp /= width;

    for (; temp != 0; digits += 1)
        temp /= width;

    if ((flags & PX_FORMAT_FLAG_PLUS) != 0)
        digits += 1;

    return digits;
}

pxiword
pxMemory8WriteUnsigned(pxu8* memory, pxiword length, pxuword value, PxFormatRadix radix, PxFormatFlag flags)
{
    pxiword size  = pxUnsignedDigits(value, radix, flags);
    pxuword width = pxMagnitudeFormatRadix(radix);
    pxuword temp  = value;

    if (size <= 0 || size > length) return 0;

    pxiword index = size;

    while (index > 0) {
        pxi32 unicode =
            pxUnicodeFromDigit(temp, radix, flags);

        temp  /= width;
        index -= 1;

        if (pxUnicodeIsAscii(unicode) != 0)
            memory[index] = unicode;
        else
            return 0;
    }

    if ((flags & PX_FORMAT_FLAG_PLUS) != 0)
        memory[index] = PX_ASCII_PLUS;

    return size;
}

pxiword
pxMemory8ReadUnsigned(pxu8* memory, pxiword length, pxuword* value, PxFormatRadix radix, PxFormatFlag flags)
{
    pxiword index = 0;
    pxuword width = pxMagnitudeFormatRadix(radix);
    pxuword temp  = 0;

    if (length <= 0) return 0;

    switch (memory[index]) {
        case PX_ASCII_PLUS: {
            if ((flags & PX_FORMAT_FLAG_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        default: break;
    }

    for (; index < length; index += 1) {
        pxuword digit =
            pxDigitFromUnicode(memory[index], radix, flags);

        if (digit < width) {
            if (temp > (PX_UWORD_MAX - digit) / width)
                return 0;

            temp = temp * width + digit;
        } else
            return 0;
    }

    if (value != 0) * value = temp;

    return length;
}

pxiword
pxMemory16WriteUnsigned(pxu16* memory, pxiword length, pxuword value, PxFormatRadix radix, PxFormatFlag flags)
{
    pxiword size  = pxUnsignedDigits(value, radix, flags);
    pxuword width = pxMagnitudeFormatRadix(radix);
    pxuword temp  = value;

    if (size <= 0 || size > length) return 0;

    pxiword index = size;

    while (index > 0) {
        pxi32 unicode =
            pxUnicodeFromDigit(temp, radix, flags);

        temp  /= width;
        index -= 1;

        if (pxUnicodeIsAscii(unicode) != 0)
            memory[index] = unicode;
        else
            return 0;
    }

    if ((flags & PX_FORMAT_FLAG_PLUS) != 0)
        memory[index] = PX_ASCII_PLUS;

    return size;
}

pxiword
pxMemory16ReadUnsigned(pxu16* memory, pxiword length, pxuword* value, PxFormatRadix radix, PxFormatFlag flags)
{
    pxiword index = 0;
    pxuword width = pxMagnitudeFormatRadix(radix);
    pxuword temp  = 0;

    if (length <= 0) return 0;

    switch (memory[index]) {
        case PX_ASCII_PLUS: {
            if ((flags & PX_FORMAT_FLAG_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        default: break;
    }

    for (; index < length; index += 1) {
        pxuword digit =
            pxDigitFromUnicode(memory[index], radix, flags);

        if (digit < width) {
            if (temp > (PX_UWORD_MAX - digit) / width)
                return 0;

            temp = temp * width + digit;
        } else
            return 0;
    }

    if (value != 0) * value = temp;

    return length;
}

pxiword
pxMemory32WriteUnsigned(pxu32* memory, pxiword length, pxuword value, PxFormatRadix radix, PxFormatFlag flags)
{
    pxiword size  = pxUnsignedDigits(value, radix, flags);
    pxuword width = pxMagnitudeFormatRadix(radix);
    pxuword temp  = value;

    if (size <= 0 || size > length) return 0;

    pxiword index = size;

    while (index > 0) {
        pxi32 unicode =
            pxUnicodeFromDigit(temp, radix, flags);

        temp  /= width;
        index -= 1;

        if (pxUnicodeIsAscii(unicode) != 0)
            memory[index] = unicode;
        else
            return 0;
    }

    if ((flags & PX_FORMAT_FLAG_PLUS) != 0)
        memory[index] = PX_ASCII_PLUS;

    return size;
}

pxiword
pxMemory32ReadUnsigned(pxu32* memory, pxiword length, pxuword* value, PxFormatRadix radix, PxFormatFlag flags)
{
    pxiword index = 0;
    pxuword width = pxMagnitudeFormatRadix(radix);
    pxuword temp  = 0;

    if (length <= 0) return 0;

    switch (memory[index]) {
        case PX_ASCII_PLUS: {
            if ((flags & PX_FORMAT_FLAG_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        default: break;
    }

    for (; index < length; index += 1) {
        pxuword digit =
            pxDigitFromUnicode(memory[index], radix, flags);

        if (digit < width) {
            if (temp > (PX_UWORD_MAX - digit) / width)
                return 0;

            temp = temp * width + digit;
        } else
            return 0;
    }

    if (value != 0) * value = temp;

    return length;
}

PxString8
pxString8FromUnsigned(PxArena* arena, pxuword value, PxFormatRadix radix, PxFormatFlag flags)
{
    pxiword offset = pxArenaOffset(arena);
    pxiword length = pxUnsignedDigits(value, radix, flags);

    pxu8* memory =
        pxArenaReserve(arena, pxu8, length + 1);

    pxiword size = pxMemory8WriteUnsigned(
        memory, length, value, radix, flags);

    if (size == length)
        return pxString8Make(memory, length);

    pxArenaRewind(arena, offset);

    return (PxString8) {0};
}

pxb8
pxUnsignedFromString8(PxString8 string, pxuword* value, PxFormatRadix radix, PxFormatFlag flags)
{
    pxu8*   memory = string.memory;
    pxiword length = string.length;

    pxiword size = pxMemory8ReadUnsigned(
        memory, length, value, radix, flags);

    if (size == length) return 1;

    return 0;
}

PxString16
pxString16FromUnsigned(PxArena* arena, pxuword value, PxFormatRadix radix, PxFormatFlag flags)
{
    pxiword offset = pxArenaOffset(arena);
    pxiword length = pxUnsignedDigits(value, radix, flags);

    pxu16* memory =
        pxArenaReserve(arena, pxu16, length + 1);

    pxiword size = pxMemory16WriteUnsigned(
        memory, length, value, radix, flags);

    if (size == length)
        return pxString16Make(memory, length);

    pxArenaRewind(arena, offset);

    return (PxString16) {0};
}

pxb8
pxUnsignedFromString16(PxString16 string, pxuword* value, PxFormatRadix radix, PxFormatFlag flags)
{
    pxu16*  memory = string.memory;
    pxiword length = string.length;

    pxiword size = pxMemory16ReadUnsigned(
        memory, length, value, radix, flags);

    if (size == length) return 1;

    return 0;
}

PxString32
pxString32FromUnsigned(PxArena* arena, pxuword value, PxFormatRadix radix, PxFormatFlag flags)
{
    pxiword offset = pxArenaOffset(arena);
    pxiword length = pxUnsignedDigits(value, radix, flags);

    pxu32* memory =
        pxArenaReserve(arena, pxu32, length + 1);

    pxiword size = pxMemory32WriteUnsigned(
        memory, length, value, radix, flags);

    if (size == length)
        return pxString32Make(memory, length);

    pxArenaRewind(arena, offset);

    return (PxString32) {0};
}

pxb8
pxUnsignedFromString32(PxString32 string, pxuword* value, PxFormatRadix radix, PxFormatFlag flags)
{
    pxu32*  memory = string.memory;
    pxiword length = string.length;

    pxiword size = pxMemory32ReadUnsigned(
        memory, length, value, radix, flags);

    if (size == length) return 1;

    return 0;
}

#endif // PX_CORE_FORMAT_UNSIGNED_C
