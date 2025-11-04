#ifndef PAX_CORE_STRING_CONVERT_C
#define PAX_CORE_STRING_CONVERT_C

#include "./convert.h"

paxiword
pax_buffer8_write_head_string8(Pax_Buffer8* self, Pax_String8 value)
{
    return pax_buffer8_write_head_memory8(self,
        value.memory, value.length);
}

paxiword
pax_buffer8_write_tail_string8(Pax_Buffer8* self, Pax_String8 value)
{
    return pax_buffer8_write_tail_memory8(self,
        value.memory, value.length);
}

Pax_String8
pax_buffer8_read_head_string8(Pax_Buffer8* self, Pax_Arena* arena, paxiword length)
{
    paxiword mark = pax_arena_tell(arena);
    paxiword size = pax_between(length, 0, self->length);

    if (size <= 0) return (Pax_String8) {0};

    paxu8* result =
        pax_arena_reserve(arena, paxu8, size + 1);

    if (result == 0) return (Pax_String8) {0};

    if (pax_buffer8_read_head_memory8(self, result, size) == size)
        return pax_string8_make(result, size);

    pax_arena_rewind(arena, mark, 0);

    return (Pax_String8) {0};
}

Pax_String8
pax_buffer8_read_tail_string8(Pax_Buffer8* self, Pax_Arena* arena, paxiword length)
{
    paxiword mark = pax_arena_tell(arena);
    paxiword size = pax_between(length, 0, self->length);

    if (size <= 0) return (Pax_String8) {0};

    paxu8* result =
        pax_arena_reserve(arena, paxu8, size + 1);

    if (result == 0) return (Pax_String8) {0};

    if (pax_buffer8_read_tail_memory8(self, result, size) == size)
        return pax_string8_make(result, size);

    pax_arena_rewind(arena, mark, 0);

    return (Pax_String8) {0};
}

paxiword
pax_buffer16_write_head_string16(Pax_Buffer16* self, Pax_String16 value)
{
    return pax_buffer16_write_head_memory16(self,
        value.memory, value.length);
}

paxiword
pax_buffer16_write_tail_string16(Pax_Buffer16* self, Pax_String16 value)
{
    return pax_buffer16_write_tail_memory16(self,
        value.memory, value.length);
}

Pax_String16
pax_buffer16_read_head_string16(Pax_Buffer16* self, Pax_Arena* arena, paxiword length)
{
    paxiword mark = pax_arena_tell(arena);
    paxiword size = pax_between(length, 0, self->length);

    if (size <= 0) return (Pax_String16) {0};

    paxu16* result =
        pax_arena_reserve(arena, paxu16, size + 1);

    if (result == 0) return (Pax_String16) {0};

    if (pax_buffer16_read_head_memory16(self, result, size) == size)
        return pax_string16_make(result, size);

    pax_arena_rewind(arena, mark, 0);

    return (Pax_String16) {0};
}

Pax_String16
pax_buffer16_read_tail_string16(Pax_Buffer16* self, Pax_Arena* arena, paxiword length)
{
    paxiword mark = pax_arena_tell(arena);
    paxiword size = pax_between(length, 0, self->length);

    if (size <= 0) return (Pax_String16) {0};

    paxu16* result =
        pax_arena_reserve(arena, paxu16, size + 1);

    if (result == 0) return (Pax_String16) {0};

    if (pax_buffer16_read_tail_memory16(self, result, size) == size)
        return pax_string16_make(result, size);

    pax_arena_rewind(arena, mark, 0);

    return (Pax_String16) {0};
}

paxiword
pax_buffer32_write_head_string32(Pax_Buffer32* self, Pax_String32 value)
{
    return pax_buffer32_write_head_memory32(self,
        value.memory, value.length);
}

paxiword
pax_buffer32_write_tail_string32(Pax_Buffer32* self, Pax_String32 value)
{
    return pax_buffer32_write_tail_memory32(self,
        value.memory, value.length);
}

Pax_String32
pax_buffer32_read_head_string32(Pax_Buffer32* self, Pax_Arena* arena, paxiword length)
{
    paxiword mark = pax_arena_tell(arena);
    paxiword size = pax_between(length, 0, self->length);

    if (size <= 0) return (Pax_String32) {0};

    paxu32* result =
        pax_arena_reserve(arena, paxu32, size + 1);

    if (result == 0) return (Pax_String32) {0};

    if (pax_buffer32_read_head_memory32(self, result, size) == size)
        return pax_string32_make(result, size);

    pax_arena_rewind(arena, mark, 0);

    return (Pax_String32) {0};
}

Pax_String32
pax_buffer32_read_tail_string32(Pax_Buffer32* self, Pax_Arena* arena, paxiword length)
{
    paxiword mark = pax_arena_tell(arena);
    paxiword size = pax_between(length, 0, self->length);

    if (size <= 0) return (Pax_String32) {0};

    paxu32* result =
        pax_arena_reserve(arena, paxu32, size + 1);

    if (result == 0) return (Pax_String32) {0};

    if (pax_buffer32_read_tail_memory32(self, result, size) == size)
        return pax_string32_make(result, size);

    pax_arena_rewind(arena, mark, 0);

    return (Pax_String32) {0};
}

Pax_String8
pax_string8_copy_memory16(Pax_Arena* arena, paxu16* memory, paxiword length)
{
    paxiword mark = pax_arena_tell(arena);
    paxiword size = pax_utf8_units_from_memory16(memory, length);

    if (size <= 0) return (Pax_String8) {0};

    Pax_Buffer8 buffer = pax_buffer8_create(arena, size + 1);

    if (pax_buffer8_capacity(&buffer) <= 0)
        return (Pax_String8) {0};

    paxiword index = 0;
    paxiword temp  = 1;

    for (; index < length && temp != 0; index += temp) {
        paxi32 unicode = 0;

        temp = pax_utf16_read_forw(memory, length, index, &unicode);

        pax_buffer8_write_tail_unicode(&buffer, unicode);
    }

    if (buffer.length == size) {
        Pax_String8 string = {0};

        string.memory = buffer.memory;
        string.length = buffer.length;

        return string;
    }

    pax_arena_rewind(arena, mark, 0);

    return (Pax_String8) {0};
}

Pax_String8
pax_string8_copy_string16(Pax_Arena* arena, Pax_String16 value)
{
    return pax_string8_copy_memory16(arena, value.memory, value.length);
}

Pax_String8
pax_string8_copy_memory32(Pax_Arena* arena, paxu32* memory, paxiword length)
{
    paxiword mark = pax_arena_tell(arena);
    paxiword size = pax_utf8_units_from_memory32(memory, length);

    if (size <= 0) return (Pax_String8) {0};

    Pax_Buffer8 buffer = pax_buffer8_create(arena, size + 1);

    if (pax_buffer8_capacity(&buffer) <= 0)
        return (Pax_String8) {0};

    paxiword index = 0;
    paxiword temp  = 1;

    for (; index < length && temp != 0; index += temp) {
        paxi32 unicode = 0;

        temp = pax_utf32_read_forw(memory, length, index, &unicode);

        pax_buffer8_write_tail_unicode(&buffer, unicode);
    }

    if (buffer.length == size) {
        Pax_String8 string = {0};

        string.memory = buffer.memory;
        string.length = buffer.length;

        return string;
    }

    pax_arena_rewind(arena, mark, 0);

    return (Pax_String8) {0};
}

Pax_String8
pax_string8_copy_string32(Pax_Arena* arena, Pax_String32 value)
{
    return pax_string8_copy_memory32(arena, value.memory, value.length);
}

Pax_String16
pax_string16_copy_memory8(Pax_Arena* arena, paxu8* memory, paxiword length)
{
    paxiword mark = pax_arena_tell(arena);
    paxiword size = pax_utf16_units_from_memory8(memory, length);

    if (size <= 0) return (Pax_String16) {0};

    Pax_Buffer16 buffer = pax_buffer16_create(arena, size + 1);

    if (pax_buffer16_capacity(&buffer) <= 0)
        return (Pax_String16) {0};

    paxiword index = 0;
    paxiword temp  = 1;

    for (; index < length && temp != 0; index += temp) {
        paxi32 unicode = 0;

        temp = pax_utf8_read_forw(memory, length, index, &unicode);

        pax_buffer16_write_tail_unicode(&buffer, unicode);
    }

    if (buffer.length == size) {
        Pax_String16 string = {0};

        string.memory = pax_as(paxu16*, buffer.memory);
        string.length = buffer.length;

        return string;
    }

    pax_arena_rewind(arena, mark, 0);

    return (Pax_String16) {0};
}

Pax_String16
pax_string16_copy_string8(Pax_Arena* arena, Pax_String8 value)
{
    return pax_string16_copy_memory8(arena, value.memory, value.length);
}

Pax_String16
pax_string16_copy_memory32(Pax_Arena* arena, paxu32* memory, paxiword length)
{
    paxiword mark = pax_arena_tell(arena);
    paxiword size = pax_utf16_units_from_memory32(memory, length);

    if (size <= 0) return (Pax_String16) {0};

    Pax_Buffer16 buffer = pax_buffer16_create(arena, size + 1);

    if (pax_buffer16_capacity(&buffer) <= 0)
        return (Pax_String16) {0};

    paxiword index = 0;
    paxiword temp  = 1;

    for (; index < length && temp != 0; index += temp) {
        paxi32 unicode = 0;

        temp = pax_utf32_read_forw(memory, length, index, &unicode);

        pax_buffer16_write_tail_unicode(&buffer, unicode);
    }

    if (buffer.length == size) {
        Pax_String16 string = {0};

        string.memory = pax_as(paxu16*, buffer.memory);
        string.length = buffer.length;

        return string;
    }

    pax_arena_rewind(arena, mark, 0);

    return (Pax_String16) {0};
}

Pax_String16
pax_string16_copy_string32(Pax_Arena* arena, Pax_String32 value)
{
    return pax_string16_copy_memory32(arena, value.memory, value.length);
}

Pax_String32
pax_string32_copy_memory8(Pax_Arena* arena, paxu8* memory, paxiword length)
{
    paxiword mark = pax_arena_tell(arena);
    paxiword size = pax_utf32_units_from_memory8(memory, length);

    if (size <= 0) return (Pax_String32) {0};

    Pax_Buffer32 buffer = pax_buffer32_create(arena, size + 1);

    if (pax_buffer32_capacity(&buffer) <= 0)
        return (Pax_String32) {0};

    paxiword index = 0;
    paxiword temp  = 1;

    for (; index < length && temp != 0; index += temp) {
        paxi32 unicode = 0;

        temp = pax_utf8_read_forw(memory, length, index, &unicode);

        pax_buffer32_write_tail_unicode(&buffer, unicode);
    }

    if (buffer.length == size) {
        Pax_String32 string = {0};

        string.memory = pax_as(paxu32*, buffer.memory);
        string.length = buffer.length;

        return string;
    }

    pax_arena_rewind(arena, mark, 0);

    return (Pax_String32) {0};
}

Pax_String32
pax_string32_copy_string8(Pax_Arena* arena, Pax_String8 value)
{
    return pax_string32_copy_memory8(arena, value.memory, value.length);
}

Pax_String32
pax_string32_copy_memory16(Pax_Arena* arena, paxu16* memory, paxiword length)
{
    paxiword mark = pax_arena_tell(arena);
    paxiword size = pax_utf32_units_from_memory16(memory, length);

    if (size <= 0) return (Pax_String32) {0};

    Pax_Buffer32 buffer = pax_buffer32_create(arena, size + 1);

    if (pax_buffer32_capacity(&buffer) <= 0)
        return (Pax_String32) {0};

    paxiword index = 0;
    paxiword temp  = 1;

    for (; index < length && temp != 0; index += temp) {
        paxi32 unicode = 0;

        temp = pax_utf16_read_forw(memory, length, index, &unicode);

        pax_buffer32_write_tail_unicode(&buffer, unicode);
    }

    if (buffer.length == size) {
        Pax_String32 string = {0};

        string.memory = pax_as(paxu32*, buffer.memory);
        string.length = buffer.length;

        return string;
    }

    pax_arena_rewind(arena, mark, 0);

    return (Pax_String32) {0};
}

Pax_String32
pax_string32_copy_string16(Pax_Arena* arena, Pax_String16 value)
{
    return pax_string32_copy_memory16(arena, value.memory, value.length);
}

#endif // PAX_CORE_STRING_CONVERT_C
