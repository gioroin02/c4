#ifndef PAX_CORE_FORMAT_UNSIGNED_C
#define PAX_CORE_FORMAT_UNSIGNED_C

#include "./unsigned.h"

paxiword
pax_unsigned_digits(paxuword value, Pax_Format_Radix radix, Pax_Format_Flag flags)
{
    paxiword digits = 1;
    paxuword width  = pax_magn_format_radix(radix);
    paxuword temp   = value;

    if (width <= 1) return 0;

    temp /= width;

    for (; temp != 0; digits += 1)
        temp /= width;

    if ((flags & PAX_FORMAT_FLAG_PLUS) != 0)
        digits += 1;

    return digits;
}

paxiword
pax_memory8_write_unsigned(paxu8* memory, paxiword length, paxuword value, Pax_Format_Radix radix, Pax_Format_Flag flags)
{
    paxiword size  = pax_unsigned_digits(value, radix, flags);
    paxuword width = pax_magn_format_radix(radix);
    paxuword temp  = value;

    if (size <= 0 || size > length) return 0;

    paxiword index = size;

    while (index > 0) {
        paxi32 unicode =
            pax_unicode_from_digit(temp, radix, flags);

        temp  /= width;
        index -= 1;

        if (pax_unicode_is_ascii(unicode) != 0)
            memory[index] = unicode;
        else
            return 0;
    }

    if ((flags & PAX_FORMAT_FLAG_PLUS) != 0)
        memory[index] = PAX_ASCII_PLUS;

    return size;
}

paxiword
pax_memory8_read_unsigned(paxu8* memory, paxiword length, paxuword* value, Pax_Format_Radix radix, Pax_Format_Flag flags)
{
    paxiword index = 0;
    paxuword width = pax_magn_format_radix(radix);
    paxuword temp  = 0;

    if (length <= 0) return 0;

    switch (memory[index]) {
        case PAX_ASCII_PLUS: {
            if ((flags & PAX_FORMAT_FLAG_PLUS) == 0)
                return 0;

            index += 1;
        } break;

        default: break;
    }

    for (; index < length; index += 1) {
        paxuword digit =
            pax_digit_from_unicode(memory[index], radix, flags);

        if (digit < width) {
            if (temp > (PAX_UWORD_MAX - digit) / width)
                return 0;

            temp = temp * width + digit;
        } else
            return 0;
    }

    if (value != 0) * value = temp;

    return length;
}

Pax_String8
pax_string8_from_unsigned(Pax_Arena* arena, paxuword value, Pax_Format_Radix radix, Pax_Format_Flag flags)
{
    paxiword mark   = pax_arena_tell(arena);
    paxiword length = pax_unsigned_digits(value, radix, flags);

    paxu8* memory =
        pax_arena_reserve(arena, paxu8, length + 1);

    paxiword size = pax_memory8_write_unsigned(
        memory, length, value, radix, flags);

    if (size == length)
        return pax_string8_make(memory, length);

    pax_arena_rewind(arena, mark, 0);

    return (Pax_String8) {0};
}

paxb8
pax_unsigned_from_string8(Pax_String8 string, paxuword* value, Pax_Format_Radix radix, Pax_Format_Flag flags)
{
    paxu8*   memory = string.memory;
    paxiword length = string.length;

    paxiword size = pax_memory8_read_unsigned(
        memory, length, value, radix, flags);

    return size == length ? 1 : 0;
}

#endif // PAX_CORE_FORMAT_UNSIGNED_C
