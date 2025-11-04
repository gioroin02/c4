#ifndef PAX_CORE_FORMAT_CONFIG_C
#define PAX_CORE_FORMAT_CONFIG_C

#include "./config.h"

paxuword
pax_magn_format_radix(Pax_Format_Radix radix)
{
    switch (radix) {
        case PAX_FORMAT_RADIX_2:  return 2;
        case PAX_FORMAT_RADIX_8:  return 8;
        case PAX_FORMAT_RADIX_10: return 10;
        case PAX_FORMAT_RADIX_16: return 16;

        default: break;
    }

    return 1;
}

paxb8
pax_unicode_is_digit(paxi32 value, Pax_Format_Radix radix, Pax_Format_Flag flags)
{
    switch (radix) {
        case PAX_FORMAT_RADIX_2:
        case PAX_FORMAT_RADIX_8:
        case PAX_FORMAT_RADIX_10: {
            if (value >= PAX_ASCII_ZERO && value <= PAX_ASCII_NINE)
                return 1;
        } break;

        case PAX_FORMAT_RADIX_16: {
            if (value >= PAX_ASCII_ZERO && value <= PAX_ASCII_NINE)
                return 1;

            if (value >= PAX_ASCII_UPPER_A && value <= PAX_ASCII_UPPER_F) {
                if ((flags & PAX_FORMAT_FLAG_UPPER) != 0)
                    return 1;
            }

            if (value >= PAX_ASCII_LOWER_A && value <= PAX_ASCII_LOWER_F)
                return 1;
        } break;

        default: break;
    }

    return 0;
}

paxi32
pax_unicode_from_digit(paxuword value, Pax_Format_Radix radix, Pax_Format_Flag flags)
{
    paxuword width = pax_magn_format_radix(radix);
    paxuword digit = value % width;

    switch (radix) {
        case PAX_FORMAT_RADIX_2:
        case PAX_FORMAT_RADIX_8:
        case PAX_FORMAT_RADIX_10: return PAX_ASCII_ZERO + digit;

        case PAX_FORMAT_RADIX_16: {
            if (digit < 10)
                return PAX_ASCII_ZERO + digit;

            if ((flags & PAX_FORMAT_FLAG_UPPER) != 0)
                return PAX_ASCII_UPPER_A + digit - 10;

            return PAX_ASCII_LOWER_A + digit - 10;
        } break;

        default: break;
    }

    return PX_ASCII_ITEMS;
}

paxuword
pax_digit_from_unicode(paxi32 value, Pax_Format_Radix radix, Pax_Format_Flag flags)
{
    switch (radix) {
        case PAX_FORMAT_RADIX_2:
        case PAX_FORMAT_RADIX_8:
        case PAX_FORMAT_RADIX_10: {
            if (value >= PAX_ASCII_ZERO && value <= PAX_ASCII_NINE)
                return value - PAX_ASCII_ZERO;
        } break;

        case PAX_FORMAT_RADIX_16: {
            if (value >= PAX_ASCII_ZERO && value <= PAX_ASCII_NINE)
                return value - PAX_ASCII_ZERO;

            if (value >= PAX_ASCII_UPPER_A && value <= PAX_ASCII_UPPER_F) {
                if ((flags & PAX_FORMAT_FLAG_UPPER) != 0)
                    return value - PAX_ASCII_UPPER_A + 10;
            }

            if (value >= PAX_ASCII_LOWER_A && value <= PAX_ASCII_LOWER_F)
                return value - PAX_ASCII_LOWER_A + 10;
        } break;

        default: break;
    }

    return pax_magn_format_radix(radix);
}

#endif // PAX_CORE_FORMAT_CONFIG_C
