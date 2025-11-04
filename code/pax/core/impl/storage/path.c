#ifndef PAX_CORE_STORAGE_PATH_C
#define PAX_CORE_STORAGE_PATH_C

#include "./path.h"

#define PAX_PATH_STRING8_PREVIOUS pax_str8_vargs('.', '.')
#define PAX_PATH_STRING8_CURRENT  pax_str8_vargs('.')

#define PAX_PATH_STRING16_PREVIOUS pax_str16_vargs('.', '.')
#define PAX_PATH_STRING16_CURRENT  pax_str16_vargs('.')

#define PAX_PATH_STRING32_PREVIOUS pax_str32_vargs('.', '.')
#define PAX_PATH_STRING32_CURRENT  pax_str32_vargs('.')

Pax_Path
pax_path_create(Pax_Arena* arena, paxiword length)
{
    return pax_buffer8_create(arena, length);
}

paxiword
pax_path_insert_memory8(Pax_Path* self, paxu8* memory, paxiword length, Pax_String8 delim)
{
    Pax_String8 value =
        pax_string8_make(memory, length);

    return pax_path_insert_string8(self, value, delim);
}

paxiword
pax_path_insert_string8(Pax_Path* self, Pax_String8 value, Pax_String8 delim)
{
    paxiword result = 0;

    Pax_String8 left  = {0};
    Pax_String8 right = value;

    while (right.length > 0) {
        pax_string8_split(right, delim, &left, &right);

        if (pax_string8_is_equal(left, PAX_PATH_STRING8_CURRENT) != 0)
            continue;

        if (pax_string8_is_equal(left, PAX_PATH_STRING8_PREVIOUS) == 0) {
            paxiword size = left.length + 1;

            if (size <= 0 || size > self->capacity - self->length)
                break;

            if (self->length > 0)
                pax_buffer8_write_tail_string8(self, pax_str8("/"));

            pax_buffer8_write_tail_string8(self, left);

            result += 1;
        } else
            pax_path_remove_memory8(self, 0, 0);
    }

    return result;
}

paxiword
pax_path_remove_memory8(Pax_Path* self, paxu8* memory, paxiword length)
{
    paxiword index = self->length;

    for (; index > 0; index -= 1) {
        paxu8 item = self->memory[index - 1];

        if (item == PAX_ASCII_SLASH)
            break;
    }

    paxiword size = self->length - index;

    pax_buffer8_read_tail_memory8(self, memory, size);
    pax_buffer8_read_tail_memory8(self, 0, 1);

    return size + 1;
}

Pax_String8
pax_path_remove_string8(Pax_Path* self, Pax_Arena* arena)
{
    paxiword mark   = pax_arena_tell(arena);
    paxiword length = self->length;

    if (length <= 0) return (Pax_String8) {0};

    paxu8* memory = pax_arena_reserve(arena, paxu8, length);

    if (memory == 0) return (Pax_String8) {0};

    paxiword size = pax_path_remove_memory8(self, memory, length);

    if (size > 0 && size <= length) {
        Pax_String8 string = {0};

        string.memory = memory;
        string.length = size;

        pax_arena_rewind(arena, mark, size + 1);

        return string;
    }

    pax_arena_rewind(arena, mark, 0);

    return (Pax_String8) {0};
}

Pax_String8
pax_string8_from_path(Pax_Arena* arena, Pax_Path* path, paxi32 delim)
{
    paxiword mark   = pax_arena_tell(arena);
    paxiword length = path->length;

    if (length <= 0) return (Pax_String8) {0};

    paxu8* buffer = pax_arena_reserve(arena, paxu8, length + 1);

    if (buffer == 0) return (Pax_String8) {0};

    paxiword index = 0;
    paxiword other;

    while (index < length) {
        paxi32 unicode = 0;

        index += pax_utf8_read_forw(path->memory, path->length,
            index, &unicode);

        if (unicode == PAX_ASCII_SLASH)
            unicode = delim;

        other += pax_utf8_write_forw(buffer, length,
            other, unicode);
    }

    return pax_string8_make(buffer, length);
}

Pax_String16
pax_string16_from_path(Pax_Arena* arena, Pax_Path* path, paxi32 delim)
{
    paxiword mark   = pax_arena_tell(arena);
    paxiword length = pax_utf16_units_from_memory8(path->memory, path->length);

    if (length <= 0) return (Pax_String16) {0};

    paxu16* buffer = pax_arena_reserve(arena, paxu16, length + 1);

    if (buffer == 0) return (Pax_String16) {0};

    paxiword index = 0;
    paxiword other = 0;

    while (index < length) {
        paxi32 unicode = 0;

        index += pax_utf8_read_forw(path->memory, path->length,
            index, &unicode);

        if (unicode == PAX_ASCII_SLASH)
            unicode = delim;

        other += pax_utf16_write_forw(buffer, length,
            other, unicode);
    }

    return pax_string16_make(buffer, length);
}

Pax_String32
pax_string32_from_path(Pax_Arena* arena, Pax_Path* path, paxi32 delim)
{
    paxiword mark   = pax_arena_tell(arena);
    paxiword length = pax_utf32_units_from_memory8(path->memory, path->length);

    if (length <= 0) return (Pax_String32) {0};

    paxu32* buffer = pax_arena_reserve(arena, paxu32, length + 1);

    if (buffer == 0) return (Pax_String32) {0};

    paxiword index = 0;
    paxiword other = 0;

    while (index < length) {
        paxi32 unicode = 0;

        index += pax_utf8_read_forw(path->memory, path->length,
            index, &unicode);

        if (unicode == PAX_ASCII_SLASH)
            unicode = delim;

        other += pax_utf32_write_forw(buffer, length,
            other, unicode);
    }

    return pax_string32_make(buffer, length);
}

#endif // PAX_CORE_STORAGE_PATH_C
