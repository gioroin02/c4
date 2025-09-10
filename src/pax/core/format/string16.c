#ifndef PX_CORE_FORMAT_STRING16_C
#define PX_CORE_FORMAT_STRING16_C

#include "string16.h"

PxString16
pxString16FromUnsigned8(PxArena* arena, pxuword radix, PxFormatOption options, pxu8 value)
{
    PxString16 result = {0};
    pxiword    size   = 0;
    pxu8       temp   = value;

    if (temp != 0) {
        for (pxuword t = temp; t != 0; t /= radix)
            size += 1;
    } else
        size += 1;

    if ((options & PX_FORMAT_OPTION_LEADING_PLUS) != 0)
        size += 1;

    pxiword offset = pxArenaOffset(arena);
    pxu16*  memory = pxArenaReserve(arena, pxu16, size + 1);

    pxiword amount = pxMemory16WriteUnsigned8(
        memory, size, radix, options, value);

    if (amount == size) {
        result.memory = memory;
        result.length = size;
    } else
        pxArenaRewind(arena, offset);

    return result;
}

PxString16
pxString16FromUnsigned16(PxArena* arena, pxuword radix, PxFormatOption options, pxu16 value)
{
    PxString16 result = {0};
    pxiword    size   = 0;
    pxu16      temp   = value;

    if (temp != 0) {
        for (pxuword t = temp; t != 0; t /= radix)
            size += 1;
    } else
        size += 1;

    if ((options & PX_FORMAT_OPTION_LEADING_PLUS) != 0)
        size += 1;

    pxiword offset = pxArenaOffset(arena);
    pxu16*  memory = pxArenaReserve(arena, pxu16, size + 1);

    pxiword amount = pxMemory16WriteUnsigned16(
        memory, size, radix, options, value);

    if (amount == size) {
        result.memory = memory;
        result.length = size;
    } else
        pxArenaRewind(arena, offset);

    return result;
}

PxString16
pxString16FromUnsigned32(PxArena* arena, pxuword radix, PxFormatOption options, pxu32 value)
{
    PxString16 result = {0};
    pxiword    size   = 0;
    pxu32      temp   = value;

    if (temp != 0) {
        for (pxuword t = temp; t != 0; t /= radix)
            size += 1;
    } else
        size += 1;

    if ((options & PX_FORMAT_OPTION_LEADING_PLUS) != 0)
        size += 1;

    pxiword offset = pxArenaOffset(arena);
    pxu16*  memory = pxArenaReserve(arena, pxu16, size + 1);

    pxiword amount = pxMemory16WriteUnsigned32(
        memory, size, radix, options, value);

    if (amount == size) {
        result.memory = memory;
        result.length = size;
    } else
        pxArenaRewind(arena, offset);

    return result;
}

PxString16
pxString16FromUnsigned64(PxArena* arena, pxuword radix, PxFormatOption options, pxu64 value)
{
    PxString16 result = {0};
    pxiword    size   = 0;
    pxu64      temp   = value;

    if (temp != 0) {
        for (pxuword t = temp; t != 0; t /= radix)
            size += 1;
    } else
        size += 1;

    if ((options & PX_FORMAT_OPTION_LEADING_PLUS) != 0)
        size += 1;

    pxiword offset = pxArenaOffset(arena);
    pxu16*  memory = pxArenaReserve(arena, pxu16, size + 1);

    pxiword amount = pxMemory16WriteUnsigned64(
        memory, size, radix, options, value);

    if (amount == size) {
        result.memory = memory;
        result.length = size;
    } else
        pxArenaRewind(arena, offset);

    return result;
}

PxString16
pxString16FromUnsigned(PxArena* arena, pxuword radix, PxFormatOption options, pxuword value)
{
    PxString16 result = {0};
    pxiword    size   = 0;
    pxuword    temp   = value;

    if (temp != 0) {
        for (pxuword t = temp; t != 0; t /= radix)
            size += 1;
    } else
        size += 1;

    if ((options & PX_FORMAT_OPTION_LEADING_PLUS) != 0)
        size += 1;

    pxiword offset = pxArenaOffset(arena);
    pxu16*  memory = pxArenaReserve(arena, pxu16, size + 1);

    pxiword amount = pxMemory16WriteUnsigned(
        memory, size, radix, options, value);

    if (amount == size) {
        result.memory = memory;
        result.length = size;
    } else
        pxArenaRewind(arena, offset);

    return result;
}

PxString16
pxString16FromInteger8(PxArena* arena, pxuword radix, PxFormatOption options, pxi8 value)
{
    PxString16 result = {0};
    pxiword    size   = 0;
    pxu8       temp   = pxMagnitudeInteger8(value);

    if (temp != 0) {
        for (pxuword t = temp; t != 0; t /= radix)
            size += 1;
    } else
        size += 1;

    if ((options & PX_FORMAT_OPTION_LEADING_PLUS) != 0)
        size += 1;

    pxiword offset = pxArenaOffset(arena);
    pxu16*  memory = pxArenaReserve(arena, pxu16, size + 1);

    pxiword amount = pxMemory16WriteInteger8(
        memory, size, radix, options, value);

    if (amount == size) {
        result.memory = memory;
        result.length = size;
    } else
        pxArenaRewind(arena, offset);

    return result;
}

PxString16
pxString16FromInteger16(PxArena* arena, pxuword radix, PxFormatOption options, pxi16 value)
{
    PxString16 result = {0};
    pxiword    size   = 0;
    pxu16      temp   = pxMagnitudeInteger16(value);

    if (temp != 0) {
        for (pxuword t = temp; t != 0; t /= radix)
            size += 1;
    } else
        size += 1;

    if ((options & PX_FORMAT_OPTION_LEADING_PLUS) != 0)
        size += 1;

    pxiword offset = pxArenaOffset(arena);
    pxu16*  memory = pxArenaReserve(arena, pxu16, size + 1);

    pxiword amount = pxMemory16WriteInteger16(
        memory, size, radix, options, value);

    if (amount == size) {
        result.memory = memory;
        result.length = size;
    } else
        pxArenaRewind(arena, offset);

    return result;
}

PxString16
pxString16FromInteger32(PxArena* arena, pxuword radix, PxFormatOption options, pxi32 value)
{
    PxString16 result = {0};
    pxiword    size   = 0;
    pxu32      temp   = pxMagnitudeInteger32(value);

    if (temp != 0) {
        for (pxuword t = temp; t != 0; t /= radix)
            size += 1;
    } else
        size += 1;

    if ((options & PX_FORMAT_OPTION_LEADING_PLUS) != 0)
        size += 1;

    pxiword offset = pxArenaOffset(arena);
    pxu16*  memory = pxArenaReserve(arena, pxu16, size + 1);

    pxiword amount = pxMemory16WriteInteger32(
        memory, size, radix, options, value);

    if (amount == size) {
        result.memory = memory;
        result.length = size;
    } else
        pxArenaRewind(arena, offset);

    return result;
}

PxString16
pxString16FromInteger64(PxArena* arena, pxuword radix, PxFormatOption options, pxi64 value)
{
    PxString16 result = {0};
    pxiword    size   = 0;
    pxu64      temp   = pxMagnitudeInteger64(value);

    if (temp != 0) {
        for (pxuword t = temp; t != 0; t /= radix)
            size += 1;
    } else
        size += 1;

    if ((options & PX_FORMAT_OPTION_LEADING_PLUS) != 0)
        size += 1;

    pxiword offset = pxArenaOffset(arena);
    pxu16*  memory = pxArenaReserve(arena, pxu16, size + 1);

    pxiword amount = pxMemory16WriteInteger64(
        memory, size, radix, options, value);

    if (amount == size) {
        result.memory = memory;
        result.length = size;
    } else
        pxArenaRewind(arena, offset);

    return result;
}

PxString16
pxString16FromInteger(PxArena* arena, pxuword radix, PxFormatOption options, pxiword value)
{
    PxString16 result = {0};
    pxiword    size   = 0;
    pxuword    temp   = pxMagnitudeInteger(value);

    if (temp != 0) {
        for (pxuword t = temp; t != 0; t /= radix)
            size += 1;
    } else
        size += 1;

    if ((options & PX_FORMAT_OPTION_LEADING_PLUS) != 0)
        size += 1;

    pxiword offset = pxArenaOffset(arena);
    pxu16*  memory = pxArenaReserve(arena, pxu16, size + 1);

    pxiword amount = pxMemory16WriteInteger(
        memory, size, radix, options, value);

    if (amount == size) {
        result.memory = memory;
        result.length = size;
    } else
        pxArenaRewind(arena, offset);

    return result;
}

pxb8
pxUnsigned8FromString16(pxu8* self, pxuword radix, PxFormatOption options, PxString16 string)
{
    pxiword index = 0;
    pxu8    temp  = 0;

    if (string.length <= 0) return 0;

    switch (string.memory[index]) {
        case PX_ASCII_PLUS: {
            if ((options & PX_FORMAT_OPTION_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        default: break;
    }

    if ((options & PX_FORMAT_OPTION_LEADING_ZERO) == 0) {
        pxi32 unicode = string.memory[index];

        if (string.length > index + 1 && unicode == PX_ASCII_ZERO)
            return 0;
    }

    for (; index < string.length; index += 1) {
        pxu8 digit = pxAsciiValueFromDigit(string.memory[index], radix,
            options & PX_FORMAT_OPTION_UPPER_CASE);

        if (digit < 0 || digit >= radix) return 0;

        if (temp > (PX_U8_MAX - digit) / radix)
            return 0;

        temp = temp * radix + digit;
    }

    if (self != 0) *self = temp;

    return 1;
}

pxb8
pxUnsigned16FromString16(pxu16* self, pxuword radix, PxFormatOption options, PxString16 string)
{
    pxiword index = 0;
    pxu16   temp  = 0;

    if (string.length <= 0) return 0;

    switch (string.memory[index]) {
        case PX_ASCII_PLUS: {
            if ((options & PX_FORMAT_OPTION_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        default: break;
    }

    if ((options & PX_FORMAT_OPTION_LEADING_ZERO) == 0) {
        pxi32 unicode = string.memory[index];

        if (string.length > index + 1 && unicode == PX_ASCII_ZERO)
            return 0;
    }

    for (; index < string.length; index += 1) {
        pxu8 digit = pxAsciiValueFromDigit(string.memory[index], radix,
            options & PX_FORMAT_OPTION_UPPER_CASE);

        if (digit < 0 || digit >= radix) return 0;

        if (temp > (PX_U16_MAX - digit) / radix)
            return 0;

        temp = temp * radix + digit;
    }

    if (self != 0) *self = temp;

    return 1;
}

pxb8
pxUnsigned32FromString16(pxu32* self, pxuword radix, PxFormatOption options, PxString16 string)
{
    pxiword index = 0;
    pxu32   temp  = 0;

    if (string.length <= 0) return 0;

    switch (string.memory[index]) {
        case PX_ASCII_PLUS: {
            if ((options & PX_FORMAT_OPTION_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        default: break;
    }

    if ((options & PX_FORMAT_OPTION_LEADING_ZERO) == 0) {
        pxi32 unicode = string.memory[index];

        if (string.length > index + 1 && unicode == PX_ASCII_ZERO)
            return 0;
    }

    for (; index < string.length; index += 1) {
        pxu8 digit = pxAsciiValueFromDigit(string.memory[index], radix,
            options & PX_FORMAT_OPTION_UPPER_CASE);

        if (digit < 0 || digit >= radix) return 0;

        if (temp > (PX_U32_MAX - digit) / radix)
            return 0;

        temp = temp * radix + digit;
    }

    if (self != 0) *self = temp;

    return 1;
}

pxb8
pxUnsigned64FromString16(pxu64* self, pxuword radix, PxFormatOption options, PxString16 string)
{
    pxiword index = 0;
    pxu64   temp  = 0;

    if (string.length <= 0) return 0;

    switch (string.memory[index]) {
        case PX_ASCII_PLUS: {
            if ((options & PX_FORMAT_OPTION_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        default: break;
    }

    if ((options & PX_FORMAT_OPTION_LEADING_ZERO) == 0) {
        pxi32 unicode = string.memory[index];

        if (string.length > index + 1 && unicode == PX_ASCII_ZERO)
            return 0;
    }

    for (; index < string.length; index += 1) {
        pxu8 digit = pxAsciiValueFromDigit(string.memory[index], radix,
            options & PX_FORMAT_OPTION_UPPER_CASE);

        if (digit < 0 || digit >= radix) return 0;

        if (temp > (PX_U64_MAX - digit) / radix)
            return 0;

        temp = temp * radix + digit;
    }

    if (self != 0) *self = temp;

    return 1;
}

pxb8
pxUnsignedFromString16(pxuword* self, pxuword radix, PxFormatOption options, PxString16 string)
{
    pxiword index = 0;
    pxuword temp  = 0;

    if (string.length <= 0) return 0;

    switch (string.memory[index]) {
        case PX_ASCII_PLUS: {
            if ((options & PX_FORMAT_OPTION_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        default: break;
    }

    if ((options & PX_FORMAT_OPTION_LEADING_ZERO) == 0) {
        pxi32 unicode = string.memory[index];

        if (string.length > index + 1 && unicode == PX_ASCII_ZERO)
            return 0;
    }

    for (; index < string.length; index += 1) {
        pxu8 digit = pxAsciiValueFromDigit(string.memory[index], radix,
            options & PX_FORMAT_OPTION_UPPER_CASE);

        if (digit < 0 || digit >= radix) return 0;

        if (temp > (PX_UWORD_MAX - digit) / radix)
            return 0;

        temp = temp * radix + digit;
    }

    if (self != 0) *self = temp;

    return 1;
}

pxb8
pxInteger8FromString16(pxi8* self, pxuword radix, PxFormatOption options, PxString16 string)
{
    pxiword index = 0;
    pxi8    temp  = 0;
    pxb8    sign  = 0;

    if (string.length <= 0) return 0;

    switch (string.memory[index]) {
        case PX_ASCII_PLUS: {
            if ((options & PX_FORMAT_OPTION_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        case PX_ASCII_MINUS: {
            index += 1;
            sign   = 1;
        } break;

        default: break;
    }

    if ((options & PX_FORMAT_OPTION_LEADING_ZERO) == 0) {
        pxi32 unicode = string.memory[index];

        if (string.length > index + 1 && unicode == PX_ASCII_ZERO)
            return 0;
    }

    for (; index < string.length; index += 1) {
        pxu8 digit = pxAsciiValueFromDigit(string.memory[index], radix,
            options & PX_FORMAT_OPTION_UPPER_CASE);

        if (digit < 0 || digit >= radix) return 0;

        switch (sign) {
            case 0: {
                if (temp > (PX_I8_MAX - digit) / pxCast(pxiword, radix))
                    return 0;

                temp = temp * radix + digit;
            } break;

            case 1: {
                if (temp < (PX_I8_MIN + digit) / pxCast(pxiword, radix))
                    return 0;

                temp = temp * radix - digit;
            } break;

            default: return 0;
        }
    }

    if (self != 0) *self = temp;

    return 1;
}

pxb8
pxInteger16FromString16(pxi16* self, pxuword radix, PxFormatOption options, PxString16 string)
{
    pxiword index = 0;
    pxi16   temp  = 0;
    pxb8    sign  = 0;

    if (string.length <= 0) return 0;

    switch (string.memory[index]) {
        case PX_ASCII_PLUS: {
            if ((options & PX_FORMAT_OPTION_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        case PX_ASCII_MINUS: {
            index += 1;
            sign   = 1;
        } break;

        default: break;
    }

    if ((options & PX_FORMAT_OPTION_LEADING_ZERO) == 0) {
        pxi32 unicode = string.memory[index];

        if (string.length > index + 1 && unicode == PX_ASCII_ZERO)
            return 0;
    }

    for (; index < string.length; index += 1) {
        pxu8 digit = pxAsciiValueFromDigit(string.memory[index], radix,
            options & PX_FORMAT_OPTION_UPPER_CASE);

        if (digit < 0 || digit >= radix) return 0;

        switch (sign) {
            case 0: {
                if (temp > (PX_I16_MAX - digit) / pxCast(pxiword, radix))
                    return 0;

                temp = temp * radix + digit;
            } break;

            case 1: {
                if (temp < (PX_I16_MIN + digit) / pxCast(pxiword, radix))
                    return 0;

                temp = temp * radix - digit;
            } break;

            default: return 0;
        }
    }

    if (self != 0) *self = temp;

    return 1;
}

pxb8
pxInteger32FromString16(pxi32* self, pxuword radix, PxFormatOption options, PxString16 string)
{
    pxiword index = 0;
    pxi32   temp  = 0;
    pxb8    sign  = 0;

    if (string.length <= 0) return 0;

    switch (string.memory[index]) {
        case PX_ASCII_PLUS: {
            if ((options & PX_FORMAT_OPTION_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        case PX_ASCII_MINUS: {
            index += 1;
            sign   = 1;
        } break;

        default: break;
    }

    if ((options & PX_FORMAT_OPTION_LEADING_ZERO) == 0) {
        pxi32 unicode = string.memory[index];

        if (string.length > index + 1 && unicode == PX_ASCII_ZERO)
            return 0;
    }

    for (; index < string.length; index += 1) {
        pxu8 digit = pxAsciiValueFromDigit(string.memory[index], radix,
            options & PX_FORMAT_OPTION_UPPER_CASE);

        if (digit < 0 || digit >= radix) return 0;

        switch (sign) {
            case 0: {
                if (temp > (PX_I32_MAX - digit) / pxCast(pxiword, radix))
                    return 0;

                temp = temp * radix + digit;
            } break;

            case 1: {
                if (temp < (PX_I32_MIN + digit) / pxCast(pxiword, radix))
                    return 0;

                temp = temp * radix - digit;
            } break;

            default: return 0;
        }
    }

    if (self != 0) *self = temp;

    return 1;
}

pxb8
pxInteger64FromString16(pxi64* self, pxuword radix, PxFormatOption options, PxString16 string)
{
    pxiword index = 0;
    pxi64   temp  = 0;
    pxb8    sign  = 0;

    if (string.length <= 0) return 0;

    switch (string.memory[index]) {
        case PX_ASCII_PLUS: {
            if ((options & PX_FORMAT_OPTION_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        case PX_ASCII_MINUS: {
            index += 1;
            sign   = 1;
        } break;

        default: break;
    }

    if ((options & PX_FORMAT_OPTION_LEADING_ZERO) == 0) {
        pxi32 unicode = string.memory[index];

        if (string.length > index + 1 && unicode == PX_ASCII_ZERO)
            return 0;
    }

    for (; index < string.length; index += 1) {
        pxu8 digit = pxAsciiValueFromDigit(string.memory[index], radix,
            options & PX_FORMAT_OPTION_UPPER_CASE);

        if (digit < 0 || digit >= radix) return 0;

        switch (sign) {
            case 0: {
                if (temp > (PX_I64_MAX - digit) / pxCast(pxiword, radix))
                    return 0;

                temp = temp * radix + digit;
            } break;

            case 1: {
                if (temp < (PX_I64_MIN + digit) / pxCast(pxiword, radix))
                    return 0;

                temp = temp * radix - digit;
            } break;

            default: return 0;
        }
    }

    if (self != 0) *self = temp;

    return 1;
}

pxb8
pxIntegerFromString16(pxiword* self, pxuword radix, PxFormatOption options, PxString16 string)
{
    pxiword index = 0;
    pxiword temp  = 0;
    pxb8    sign  = 0;

    if (string.length <= 0) return 0;

    switch (string.memory[index]) {
        case PX_ASCII_PLUS: {
            if ((options & PX_FORMAT_OPTION_LEADING_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        case PX_ASCII_MINUS: {
            index += 1;
            sign   = 1;
        } break;

        default: break;
    }

    if ((options & PX_FORMAT_OPTION_LEADING_ZERO) == 0) {
        pxi32 unicode = string.memory[index];

        if (string.length > index + 1 && unicode == PX_ASCII_ZERO)
            return 0;
    }

    for (; index < string.length; index += 1) {
        pxu8 digit = pxAsciiValueFromDigit(string.memory[index], radix,
            options & PX_FORMAT_OPTION_UPPER_CASE);

        if (digit < 0 || digit >= radix) return 0;

        switch (sign) {
            case 0: {
                if (temp > (PX_IWORD_MAX - digit) / pxCast(pxiword, radix))
                    return 0;

                temp = temp * radix + digit;
            } break;

            case 1: {
                if (temp < (PX_IWORD_MIN + digit) / pxCast(pxiword, radix))
                    return 0;

                temp = temp * radix - digit;
            } break;

            default: return 0;
        }
    }

    if (self != 0) *self = temp;

    return 1;
}

#endif // PX_CORE_FORMAT_STRING16_C
