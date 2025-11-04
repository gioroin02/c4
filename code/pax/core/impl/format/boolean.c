#ifndef PAX_CORE_FORMAT_BOOLEAN_C
#define PAX_CORE_FORMAT_BOOLEAN_C

#include "./boolean.h"

#define PAX_STRING8_LOWER_FALSE pax_str8("false")
#define PAX_STRING8_UPPER_FALSE pax_str8("FALSE")
#define PAX_STRING8_LOWER_TRUE  pax_str8("true")
#define PAX_STRING8_UPPER_TRUE  pax_str8("TRUE")

static const Pax_String8 PAX_STRING8_BOOLEANS[] =
{
    PAX_STRING8_LOWER_FALSE,
    PAX_STRING8_UPPER_FALSE,
    PAX_STRING8_LOWER_TRUE,
    PAX_STRING8_UPPER_TRUE,
};

paxiword
pax_boolean_digits(paxbword value, Pax_Format_Flag flags)
{
    return value != 0 ? 4 : 5;
}

paxiword
pax_memory8_write_boolean(paxu8* memory, paxiword length, paxbword value, Pax_Format_Flag flags)
{
    paxiword size  = pax_boolean_digits(value, flags);
    paxiword index = 0;
    paxuword upper = flags & PAX_FORMAT_FLAG_UPPER;

    if (size <= 0 || size > length) return 0;

    index += value != 0 ? 2 : 0;
    index += upper != 0 ? 1 : 0;

    Pax_String8 string = PAX_STRING8_BOOLEANS[index];

    for (paxiword i = 0; i < string.length; i += 1)
        memory[i] = string.memory[i];

    return size;
}

paxiword
pax_memory8_read_boolean(paxu8* memory, paxiword length, paxbword* value, Pax_Format_Flag flags)
{
    paxiword index = 0;

    if (length <= 0) return 0;

    switch (memory[0]) {
        case PAX_ASCII_LOWER_F: index = 0; break;
        case PAX_ASCII_UPPER_F: index = 1; break;
        case PAX_ASCII_LOWER_T: index = 2; break;
        case PAX_ASCII_UPPER_T: index = 3; break;

        default: return 0;
    }

    Pax_String8 string = PAX_STRING8_BOOLEANS[index];

    if (pax_string8_is_equal_memory8(string, memory, length) == 0)
        return 0;

    if (value != 0) *value = index >= 2 ? 1 : 0;

    return length;
}

Pax_String8
pax_string8_from_boolean(Pax_Arena* arena, paxbword value, Pax_Format_Flag flags)
{
    paxiword mark   = pax_arena_tell(arena);
    paxiword length = pax_boolean_digits(value, flags);

    paxu8* memory =
        pax_arena_reserve(arena, paxu8, length + 1);

    paxiword size = pax_memory8_write_boolean(
        memory, length, value, flags);

    if (size == length)
        return pax_string8_make(memory, length);

    pax_arena_rewind(arena, mark, 0);

    return (Pax_String8) {0};
}

paxb8
pax_boolean_from_string8(Pax_String8 string, paxbword* value, Pax_Format_Flag flags)
{
    paxu8*   memory = string.memory;
    paxiword length = string.length;

    paxiword size = pax_memory8_read_boolean(
        memory, length, value, flags);

    return size == length ? 1 : 0;
}

#endif // PAX_CORE_FORMAT_BOOLEAN_C
