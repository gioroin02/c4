#ifndef PX_CORE_FORMAT_CONFIG_C
#define PX_CORE_FORMAT_CONFIG_C

#include "config.h"

pxuword
pxMagnitudeFormatRadix(PxFormatRadix radix)
{
    switch (radix) {
        case PX_FORMAT_RADIX_2:  return 2;
        case PX_FORMAT_RADIX_8:  return 8;
        case PX_FORMAT_RADIX_10: return 10;
        case PX_FORMAT_RADIX_16: return 16;

        default: break;
    }

    return 1;
}

pxb8
pxUnicodeIsDigit(pxi32 value, PxFormatRadix radix, PxFormatFlag flags)
{
    switch (radix) {
        case PX_FORMAT_RADIX_2:
        case PX_FORMAT_RADIX_8:
        case PX_FORMAT_RADIX_10: {
            if (value >= PX_ASCII_ZERO && value <= PX_ASCII_NINE)
                return 1;
        } break;

        case PX_FORMAT_RADIX_16: {
            if (value >= PX_ASCII_ZERO && value <= PX_ASCII_NINE)
                return 1;

            if (value >= PX_ASCII_UPPER_A && value <= PX_ASCII_UPPER_F) {
                if ((flags & PX_FORMAT_FLAG_UPPER) != 0)
                    return 1;
            }

            if (value >= PX_ASCII_LOWER_A && value <= PX_ASCII_LOWER_F)
                return 1;
        } break;

        default: break;
    }

    return 0;
}

pxi32
pxUnicodeFromDigit(pxuword value, PxFormatRadix radix, PxFormatFlag flags)
{
    pxuword width = pxMagnitudeFormatRadix(radix);
    pxuword digit = value % width;

    switch (radix) {
        case PX_FORMAT_RADIX_2:
        case PX_FORMAT_RADIX_8:
        case PX_FORMAT_RADIX_10: return PX_ASCII_ZERO + digit;

        case PX_FORMAT_RADIX_16: {
            if (digit < 10)
                return PX_ASCII_ZERO + digit;

            if ((flags & PX_FORMAT_FLAG_UPPER) != 0)
                return PX_ASCII_UPPER_A + digit - 10;

            return PX_ASCII_LOWER_A + digit - 10;
        } break;

        default: break;
    }

    return PX_ASCII_POINTS;
}

pxuword
pxDigitFromUnicode(pxi32 value, PxFormatRadix radix, PxFormatFlag flags)
{
    switch (radix) {
        case PX_FORMAT_RADIX_2:
        case PX_FORMAT_RADIX_8:
        case PX_FORMAT_RADIX_10: {
            if (value >= PX_ASCII_ZERO && value <= PX_ASCII_NINE)
                return value - PX_ASCII_ZERO;
        } break;

        case PX_FORMAT_RADIX_16: {
            if (value >= PX_ASCII_ZERO && value <= PX_ASCII_NINE)
                return value - PX_ASCII_ZERO;

            if (value >= PX_ASCII_UPPER_A && value <= PX_ASCII_UPPER_F) {
                if ((flags & PX_FORMAT_FLAG_UPPER) != 0)
                    return value - PX_ASCII_UPPER_A + 10;
            }

            if (value >= PX_ASCII_LOWER_A && value <= PX_ASCII_LOWER_F)
                return value - PX_ASCII_LOWER_A + 10;
        } break;

        default: break;
    }

    return pxMagnitudeFormatRadix(radix);
}

#endif // PX_CORE_FORMAT_CONFIG_C
