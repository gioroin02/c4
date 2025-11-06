#ifndef PX_CORE_FORMAT_INTEGER_C
#define PX_CORE_FORMAT_INTEGER_C

#include "unsigned.h"

pxiword
pxIntegerDigits(pxiword value, PxFormatRadix radix, PxFormatFlag flags)
{
    pxiword digits = 1;
    pxuword width  = pxMagnitudeFormatRadix(radix);
    pxuword temp   = pxMagnitudeInteger(value);
    pxb8    sign   = pxDirectionInteger(value) < 0 ? 1 : 0;

    if (width <= 1) return 0;

    temp /= width;

    for (; temp != 0; digits += 1)
        temp /= width;

    if (sign != 0 || (flags & PX_FORMAT_FLAG_PLUS) != 0)
        digits += 1;

    return digits;
}

pxiword
pxMemory8WriteInteger(pxu8* memory, pxiword length, pxiword value, PxFormatRadix radix, PxFormatFlag flags)
{
    pxiword size  = pxIntegerDigits(value, radix, flags);
    pxuword width = pxMagnitudeFormatRadix(radix);
    pxuword temp  = pxMagnitudeInteger(value);
    pxb8    sign  = pxDirectionInteger(value) < 0 ? 1 : 0;

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

    if (sign == 0 && (flags & PX_FORMAT_FLAG_PLUS) != 0)
        memory[index] = PX_ASCII_PLUS;

    if (sign != 0) memory[index] = PX_ASCII_MINUS;

    return size;
}

pxiword
pxMemory8ReadInteger(pxu8* memory, pxiword length, pxiword* value, PxFormatRadix radix, PxFormatFlag flags)
{
    pxiword index = 0;
    pxiword width = pxMagnitudeFormatRadix(radix);
    pxiword temp  = 0;
    pxb8    sign  = 0;

    if (length <= 0) return 0;

    switch (memory[index]) {
        case PX_ASCII_PLUS: {
            if ((flags & PX_FORMAT_FLAG_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        case PX_ASCII_MINUS: sign = 1; index += 1; break;

        default: break;
    }

    for (; index < length; index += 1) {
        pxiword digit =
            pxDigitFromUnicode(memory[index], radix, flags);

        if (digit >= width) return 0;

        switch (sign) {
            case 0: {
                if (temp > (PX_IWORD_MAX - digit) / width)
                    return 0;

                temp = temp * width + digit;
            } break;

            default: {
                if (temp < (PX_IWORD_MIN + digit) / width)
                    return 0;

                temp = temp * width - digit;
            } break;
        }
    }

    if (value != 0) * value = temp;

    return length;
}

pxiword
pxMemory16WriteInteger(pxu16* memory, pxiword length, pxiword value, PxFormatRadix radix, PxFormatFlag flags)
{
    pxiword size  = pxIntegerDigits(value, radix, flags);
    pxuword width = pxMagnitudeFormatRadix(radix);
    pxuword temp  = pxMagnitudeInteger(value);
    pxb8    sign  = pxDirectionInteger(value) < 0 ? 1 : 0;

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

    if (sign == 0 && (flags & PX_FORMAT_FLAG_PLUS) != 0)
        memory[index] = PX_ASCII_PLUS;

    if (sign != 0) memory[index] = PX_ASCII_MINUS;

    return size;
}

pxiword
pxMemory16ReadInteger(pxu16* memory, pxiword length, pxiword* value, PxFormatRadix radix, PxFormatFlag flags)
{
    pxiword index = 0;
    pxiword width = pxMagnitudeFormatRadix(radix);
    pxiword temp  = 0;
    pxb8    sign  = 0;

    if (length <= 0) return 0;

    switch (memory[index]) {
        case PX_ASCII_PLUS: {
            if ((flags & PX_FORMAT_FLAG_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        case PX_ASCII_MINUS: sign = 1; index += 1; break;

        default: break;
    }

    for (; index < length; index += 1) {
        pxiword digit =
            pxDigitFromUnicode(memory[index], radix, flags);

        if (digit >= width) return 0;

        switch (sign) {
            case 0: {
                if (temp > (PX_IWORD_MAX - digit) / width)
                    return 0;

                temp = temp * width + digit;
            } break;

            default: {
                if (temp < (PX_IWORD_MIN + digit) / width)
                    return 0;

                temp = temp * width - digit;
            } break;
        }
    }

    if (value != 0) * value = temp;

    return length;
}

pxiword
pxMemory32WriteInteger(pxu32* memory, pxiword length, pxiword value, PxFormatRadix radix, PxFormatFlag flags)
{
    pxiword size  = pxIntegerDigits(value, radix, flags);
    pxuword width = pxMagnitudeFormatRadix(radix);
    pxuword temp  = pxMagnitudeInteger(value);
    pxb8    sign  = pxDirectionInteger(value) < 0 ? 1 : 0;

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

    if (sign == 0 && (flags & PX_FORMAT_FLAG_PLUS) != 0)
        memory[index] = PX_ASCII_PLUS;

    if (sign != 0) memory[index] = PX_ASCII_MINUS;

    return size;
}

pxiword
pxMemory32ReadInteger(pxu32* memory, pxiword length, pxiword* value, PxFormatRadix radix, PxFormatFlag flags)
{
    pxiword index = 0;
    pxiword width = pxMagnitudeFormatRadix(radix);
    pxiword temp  = 0;
    pxb8    sign  = 0;

    if (length <= 0) return 0;

    switch (memory[index]) {
        case PX_ASCII_PLUS: {
            if ((flags & PX_FORMAT_FLAG_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        case PX_ASCII_MINUS: sign = 1; index += 1; break;

        default: break;
    }

    for (; index < length; index += 1) {
        pxiword digit =
            pxDigitFromUnicode(memory[index], radix, flags);

        if (digit >= width) return 0;

        switch (sign) {
            case 0: {
                if (temp > (PX_IWORD_MAX - digit) / width)
                    return 0;

                temp = temp * width + digit;
            } break;

            default: {
                if (temp < (PX_IWORD_MIN + digit) / width)
                    return 0;

                temp = temp * width - digit;
            } break;
        }
    }

    if (value != 0) * value = temp;

    return length;
}

PxString8
pxString8FromInteger(PxArena* arena, pxiword value, PxFormatRadix radix, PxFormatFlag flags)
{
    pxiword offset = pxArenaOffset(arena);
    pxiword length = pxIntegerDigits(value, radix, flags);

    pxu8* memory =
        pxArenaReserve(arena, pxu8, length + 1);

    pxiword size = pxMemory8WriteInteger(
        memory, length, value, radix, flags);

    if (size == length)
        return pxString8Make(memory, length);

    pxArenaRewind(arena, offset);

    return (PxString8) {0};
}

pxb8
pxIntegerFromString8(PxString8 string, pxiword* value, PxFormatRadix radix, PxFormatFlag flags)
{
    pxu8*   memory = string.memory;
    pxiword length = string.length;

    pxiword size = pxMemory8ReadInteger(
        memory, length, value, radix, flags);

    if (size == length) return 1;

    return 0;
}

PxString16
pxString16FromInteger(PxArena* arena, pxiword value, PxFormatRadix radix, PxFormatFlag flags)
{
    pxiword offset = pxArenaOffset(arena);
    pxiword length = pxIntegerDigits(value, radix, flags);

    pxu16* memory =
        pxArenaReserve(arena, pxu16, length + 1);

    pxiword size = pxMemory16WriteInteger(
        memory, length, value, radix, flags);

    if (size == length)
        return pxString16Make(memory, length);

    pxArenaRewind(arena, offset);

    return (PxString16) {0};
}

pxb8
pxIntegerFromString16(PxString16 string, pxiword* value, PxFormatRadix radix, PxFormatFlag flags)
{
    pxu16*  memory = string.memory;
    pxiword length = string.length;

    pxiword size = pxMemory16ReadInteger(
        memory, length, value, radix, flags);

    if (size == length) return 1;

    return 0;
}

PxString32
pxString32FromInteger(PxArena* arena, pxiword value, PxFormatRadix radix, PxFormatFlag flags)
{
    pxiword offset = pxArenaOffset(arena);
    pxiword length = pxIntegerDigits(value, radix, flags);

    pxu32* memory =
        pxArenaReserve(arena, pxu32, length + 1);

    pxiword size = pxMemory32WriteInteger(
        memory, length, value, radix, flags);

    if (size == length)
        return pxString32Make(memory, length);

    pxArenaRewind(arena, offset);

    return (PxString32) {0};
}

pxb8
pxIntegerFromString32(PxString32 string, pxiword* value, PxFormatRadix radix, PxFormatFlag flags)
{
    pxu32*  memory = string.memory;
    pxiword length = string.length;

    pxiword size = pxMemory32ReadInteger(
        memory, length, value, radix, flags);

    if (size == length) return 1;

    return 0;
}

#endif // PX_CORE_FORMAT_INTEGER_C
