#ifndef PX_CORE_FORMAT_MEMORY8_C
#define PX_CORE_FORMAT_MEMORY8_C

#include "memory8.h"

pxiword
pxMemory8WriteUnsigned8(pxu8* memory, pxiword length, pxuword radix, PxFormatOption options, pxu8 value)
{
    pxiword size = 0;
    pxu8    temp = value;

    if (temp != 0) {
        for (pxuword t = temp; t != 0; t /= radix)
            size += 1;
    } else
        size += 1;

    if ((options & PX_FORMAT_OPTION_LEADING_PLUS) != 0)
        size += 1;

    if (size <= 0 || size > length) return 0;

    pxiword index = size;

    while (index > 0) {
        pxi32 digit = pxAsciiDigitFromValue(temp, radix,
            options & PX_FORMAT_OPTION_UPPER_CASE);

        index -= 1;
        temp  /= radix;

        if (digit != PX_ASCII_NULL)
            memory[index] = pxCast(pxu8, digit);
        else
            return 0;
    }

    if ((options & PX_FORMAT_OPTION_LEADING_PLUS) != 0)
        memory[index] = PX_ASCII_PLUS;

    return size;
}

pxiword
pxMemory8WriteUnsigned16(pxu8* memory, pxiword length, pxuword radix, PxFormatOption options, pxu16 value)
{
    pxiword size = 0;
    pxu16   temp = value;

    if (temp != 0) {
        for (pxuword t = temp; t != 0; t /= radix)
            size += 1;
    } else
        size += 1;

    if ((options & PX_FORMAT_OPTION_LEADING_PLUS) != 0)
        size += 1;

    if (size <= 0 || size > length) return 0;

    pxiword index = size;

    while (index > 0) {
        pxi32 digit = pxAsciiDigitFromValue(temp, radix,
            options & PX_FORMAT_OPTION_UPPER_CASE);

        index -= 1;
        temp  /= radix;

        if (digit != PX_ASCII_NULL)
            memory[index] = pxCast(pxu8, digit);
        else
            return 0;
    }

    if ((options & PX_FORMAT_OPTION_LEADING_PLUS) != 0)
        memory[index] = PX_ASCII_PLUS;

    return size;
}

pxiword
pxMemory8WriteUnsigned32(pxu8* memory, pxiword length, pxuword radix, PxFormatOption options, pxu32 value)
{
    pxiword size = 0;
    pxu32   temp = value;

    if (temp != 0) {
        for (pxuword t = temp; t != 0; t /= radix)
            size += 1;
    } else
        size += 1;

    if ((options & PX_FORMAT_OPTION_LEADING_PLUS) != 0)
        size += 1;

    if (size <= 0 || size > length) return 0;

    pxiword index = size;

    while (index > 0) {
        pxi32 digit = pxAsciiDigitFromValue(temp, radix,
            options & PX_FORMAT_OPTION_UPPER_CASE);

        index -= 1;
        temp  /= radix;

        if (digit != PX_ASCII_NULL)
            memory[index] = pxCast(pxu8, digit);
        else
            return 0;
    }

    if ((options & PX_FORMAT_OPTION_LEADING_PLUS) != 0)
        memory[index] = PX_ASCII_PLUS;

    return size;
}

pxiword
pxMemory8WriteUnsigned64(pxu8* memory, pxiword length, pxuword radix, PxFormatOption options, pxu64 value)
{
    pxiword size = 0;
    pxu64   temp = value;

    if (temp != 0) {
        for (pxuword t = temp; t != 0; t /= radix)
            size += 1;
    } else
        size += 1;

    if ((options & PX_FORMAT_OPTION_LEADING_PLUS) != 0)
        size += 1;

    if (size <= 0 || size > length) return 0;

    pxiword index = size;

    while (index > 0) {
        pxi32 digit = pxAsciiDigitFromValue(temp, radix,
            options & PX_FORMAT_OPTION_UPPER_CASE);

        index -= 1;
        temp  /= radix;

        if (digit != PX_ASCII_NULL)
            memory[index] = pxCast(pxu8, digit);
        else
            return 0;
    }

    if ((options & PX_FORMAT_OPTION_LEADING_PLUS) != 0)
        memory[index] = PX_ASCII_PLUS;

    return size;
}

pxiword
pxMemory8WriteUnsigned(pxu8* memory, pxiword length, pxuword radix, PxFormatOption options, pxuword value)
{
    pxiword size = 0;
    pxuword temp = value;

    if (temp != 0) {
        for (pxuword t = temp; t != 0; t /= radix)
            size += 1;
    } else
        size += 1;

    if ((options & PX_FORMAT_OPTION_LEADING_PLUS) != 0)
        size += 1;

    if (size <= 0 || size > length) return 0;

    pxiword index = size;

    while (index > 0) {
        pxi32 digit = pxAsciiDigitFromValue(temp, radix,
            options & PX_FORMAT_OPTION_UPPER_CASE);

        index -= 1;
        temp  /= radix;

        if (digit != PX_ASCII_NULL)
            memory[index] = pxCast(pxu8, digit);
        else
            return 0;
    }

    if ((options & PX_FORMAT_OPTION_LEADING_PLUS) != 0)
        memory[index] = PX_ASCII_PLUS;

    return size;
}

pxiword
pxMemory8WriteInteger8(pxu8* memory, pxiword length, pxuword radix, PxFormatOption options, pxi8 value)
{
    pxiword size = 0;
    pxu8    temp = pxMagnitudeInteger8(value);
    pxb8    sign = pxDirectionInteger8(value) < 0 ? 1 : 0;

    if (temp != 0) {
        for (pxuword t = temp; t != 0; t /= radix)
            size += 1;
    } else
        size += 1;

    if (sign != 0 || (options & PX_FORMAT_OPTION_LEADING_PLUS) != 0)
        size += 1;

    if (size <= 0 || size > length) return 0;

    pxiword index = size;

    while (index > 0) {
        pxi32 digit = pxAsciiDigitFromValue(temp, radix,
            options & PX_FORMAT_OPTION_UPPER_CASE);

        index -= 1;
        temp  /= radix;

        if (digit != PX_ASCII_NULL)
            memory[index] = pxCast(pxu8, digit);
        else
            return 0;
    }

    if (sign != 0) memory[index] = PX_ASCII_MINUS;

    if (sign == 0 && (options & PX_FORMAT_OPTION_LEADING_PLUS) != 0)
        memory[index] = PX_ASCII_PLUS;

    return size;
}

pxiword
pxMemory8WriteInteger16(pxu8* memory, pxiword length, pxuword radix, PxFormatOption options, pxi16 value)
{
    pxiword size = 0;
    pxu16   temp = pxMagnitudeInteger16(value);
    pxb8    sign = pxDirectionInteger16(value) < 0 ? 1 : 0;

    if (temp != 0) {
        for (pxuword t = temp; t != 0; t /= radix)
            size += 1;
    } else
        size += 1;

    if (sign != 0 || (options & PX_FORMAT_OPTION_LEADING_PLUS) != 0)
        size += 1;

    if (size <= 0 || size > length) return 0;

    pxiword index = size;

    while (index > 0) {
        pxi32 digit = pxAsciiDigitFromValue(temp, radix,
            options & PX_FORMAT_OPTION_UPPER_CASE);

        index -= 1;
        temp  /= radix;

        if (digit != PX_ASCII_NULL)
            memory[index] = pxCast(pxu8, digit);
        else
            return 0;
    }

    if (sign != 0) memory[index] = PX_ASCII_MINUS;

    if (sign == 0 && (options & PX_FORMAT_OPTION_LEADING_PLUS) != 0)
        memory[index] = PX_ASCII_PLUS;

    return size;
}

pxiword
pxMemory8WriteInteger32(pxu8* memory, pxiword length, pxuword radix, PxFormatOption options, pxi32 value)
{
    pxiword size = 0;
    pxu32   temp = pxMagnitudeInteger32(value);
    pxb8    sign = pxDirectionInteger32(value) < 0 ? 1 : 0;

    if (temp != 0) {
        for (pxuword t = temp; t != 0; t /= radix)
            size += 1;
    } else
        size += 1;

    if (sign != 0 || (options & PX_FORMAT_OPTION_LEADING_PLUS) != 0)
        size += 1;

    if (size <= 0 || size > length) return 0;

    pxiword index = size;

    while (index > 0) {
        pxi32 digit = pxAsciiDigitFromValue(temp, radix,
            options & PX_FORMAT_OPTION_UPPER_CASE);

        index -= 1;
        temp  /= radix;

        if (digit != PX_ASCII_NULL)
            memory[index] = pxCast(pxu8, digit);
        else
            return 0;
    }

    if (sign != 0) memory[index] = PX_ASCII_MINUS;

    if (sign == 0 && (options & PX_FORMAT_OPTION_LEADING_PLUS) != 0)
        memory[index] = PX_ASCII_PLUS;

    return size;
}

pxiword
pxMemory8WriteInteger64(pxu8* memory, pxiword length, pxuword radix, PxFormatOption options, pxi64 value)
{
    pxiword size = 0;
    pxu64   temp = pxMagnitudeInteger64(value);
    pxb8    sign = pxDirectionInteger64(value) < 0 ? 1 : 0;

    if (temp != 0) {
        for (pxuword t = temp; t != 0; t /= radix)
            size += 1;
    } else
        size += 1;

    if (sign != 0 || (options & PX_FORMAT_OPTION_LEADING_PLUS) != 0)
        size += 1;

    if (size <= 0 || size > length) return 0;

    pxiword index = size;

    while (index > 0) {
        pxi32 digit = pxAsciiDigitFromValue(temp, radix,
            options & PX_FORMAT_OPTION_UPPER_CASE);

        index -= 1;
        temp  /= radix;

        if (digit != PX_ASCII_NULL)
            memory[index] = pxCast(pxu8, digit);
        else
            return 0;
    }

    if (sign != 0) memory[index] = PX_ASCII_MINUS;

    if (sign == 0 && (options & PX_FORMAT_OPTION_LEADING_PLUS) != 0)
        memory[index] = PX_ASCII_PLUS;

    return size;
}

pxiword
pxMemory8WriteInteger(pxu8* memory, pxiword length, pxuword radix, PxFormatOption options, pxiword value)
{
    pxiword size = 0;
    pxuword temp = pxMagnitudeInteger(value);
    pxb8    sign = pxDirectionInteger(value) < 0 ? 1 : 0;

    if (temp != 0) {
        for (pxuword t = temp; t != 0; t /= radix)
            size += 1;
    } else
        size += 1;

    if (sign != 0 || (options & PX_FORMAT_OPTION_LEADING_PLUS) != 0)
        size += 1;

    if (size <= 0 || size > length) return 0;

    pxiword index = size;

    while (index > 0) {
        pxi32 digit = pxAsciiDigitFromValue(temp, radix,
            options & PX_FORMAT_OPTION_UPPER_CASE);

        index -= 1;
        temp  /= radix;

        if (digit != PX_ASCII_NULL)
            memory[index] = pxCast(pxu8, digit);
        else
            return 0;
    }

    if (sign != 0) memory[index] = PX_ASCII_MINUS;

    if (sign == 0 && (options & PX_FORMAT_OPTION_LEADING_PLUS) != 0)
        memory[index] = PX_ASCII_PLUS;

    return size;
}

#endif // PX_CORE_FORMAT_MEMORY8_C
