#ifndef PAX_CORE_FORMAT_CONFIG_H
#define PAX_CORE_FORMAT_CONFIG_H

#include "./import.h"

typedef enum Pax_Format_Radix
{
    PAX_FORMAT_RADIX_NONE = 0,
    PAX_FORMAT_RADIX_2    = 2,
    PAX_FORMAT_RADIX_8    = 8,
    PAX_FORMAT_RADIX_10   = 10,
    PAX_FORMAT_RADIX_16   = 16,
}
Pax_Format_Radix;

typedef enum Pax_Format_Flag
{
    PAX_FORMAT_FLAG_NONE  = 0,
    PAX_FORMAT_FLAG_PLUS  = 1 << 0,
    PAX_FORMAT_FLAG_UPPER = 1 << 1,
}
Pax_Format_Flag;

paxuword
pax_magn_format_radix(Pax_Format_Radix radix);

paxb8
pax_unicode_is_digit(paxi32 value, Pax_Format_Radix radix, Pax_Format_Flag flags);

paxi32
pax_unicode_from_digit(paxuword value, Pax_Format_Radix radix, Pax_Format_Flag flags);

paxuword
pax_digit_from_unicode(paxi32 value, Pax_Format_Radix radix, Pax_Format_Flag flags);

#endif // PAX_CORE_FORMAT_CONFIG_H
