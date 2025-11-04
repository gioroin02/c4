#ifndef PAX_CORE_STRING_STRING8_C
#define PAX_CORE_STRING_STRING8_C

#include "./string8.h"

Pax_String8
pax_string8_make(paxu8* memory, paxiword length)
{
    Pax_String8 result = {0};

    if (memory != 0 && length > 0) {
        result.memory = memory;
        result.length = length;
    }

    return result;
}

Pax_String8
pax_string8_from_memory(void* memory, paxiword length, paxiword stride)
{
    paxiword index = 0;

    if (stride != pax_size(paxu8)) return (Pax_String8) {0};

    while (index < length) {
        if (pax_as(paxu8*, memory)[index] == 0)
            break;

        index += 1;
    }

    return pax_string8_make(memory, index);
}

Pax_String8
pax_string8_copy(Pax_Arena* arena, Pax_String8 value)
{
    return pax_string8_copy_memory8(arena, value.memory, value.length);
}

Pax_String8
pax_string8_copy_memory8(Pax_Arena* arena, paxu8* memory, paxiword length)
{
    if (memory == 0 || length <= 0) return (Pax_String8) {0};

    paxiword    mark   = pax_arena_tell(arena);
    Pax_Buffer8 buffer = pax_buffer8_create(arena, length + 1);

    if (pax_buffer8_capacity(&buffer) > 0) {
        Pax_String8 string = {0};

        string.memory  = buffer.memory;
        string.length += pax_buffer8_write_tail_memory8(&buffer, memory, length);

        if (string.length == length)
            return string;
    }

    pax_arena_rewind(arena, mark, 0);

    return (Pax_String8) {0};
}

Pax_String8
pax_string8_copy_unicode(Pax_Arena* arena, paxi32 value)
{
    Pax_UTF8 utf8 = {0};

    if (pax_utf8_encode(&utf8, value) > 0)
        return pax_string8_copy_memory8(arena, utf8.items, utf8.size);

    return (Pax_String8) {0};
}

Pax_String8
pax_string8_range(Pax_String8 self, paxiword start, paxiword stop)
{
    return pax_string8_range_length(self, start, stop - start);
}

Pax_String8
pax_string8_range_length(Pax_String8 self, paxiword index, paxiword length)
{
    index  = pax_between(index,  0, self.length - 1);
    length = pax_between(length, 0, self.length - index);

    if (length <= 0) return (Pax_String8) {0};

    paxu8* memory = self.memory + index;

    return pax_string8_make(memory, length);
}

Pax_String8
pax_string8_range_head(Pax_String8 self, paxiword head)
{
    return pax_string8_range(self, head, self.length);
}

Pax_String8
pax_string8_range_tail(Pax_String8 self, paxiword tail)
{
    return pax_string8_range(self, 0, tail);
}

paxiword
pax_string8_peek_memory8(Pax_String8 self, paxiword index, paxu8* memory, paxiword length)
{
    paxiword stride = pax_size(paxu8);

    index  = pax_between(index,  0, self.length - 1);
    length = pax_between(length, 0, self.length - index);

    Pax_Slice slice =
        pax_slice_make(self.memory, self.length, stride);

    Pax_Slice other = pax_slice_make(memory, length, stride);

    pax_slice_read(slice, index, other);

    return length;
}

paxu8
pax_string8_peek_or_none(Pax_String8 self, paxiword index)
{
    if (index < 0 || index >= self.length)
        return 0;

    return self.memory[index];
}

paxb8
pax_string8_is_equal(Pax_String8 self, Pax_String8 value)
{
    return pax_string8_is_equal_memory8(self, value.memory, value.length);
}

paxb8
pax_string8_is_equal_memory8(Pax_String8 self, paxu8* memory, paxiword length)
{
    paxiword stride = pax_size(paxu8);

    Pax_Slice slice =
        pax_slice_make(self.memory, self.length, stride);

    Pax_Slice other = pax_slice_make(memory, length, stride);

    return pax_slice_is_equal(slice, other);
}

paxb8
pax_string8_begins_with(Pax_String8 self, Pax_String8 value)
{
    return pax_string8_begins_with_memory8(self, value.memory, value.length);
}

paxb8
pax_string8_begins_with_memory8(Pax_String8 self, paxu8* memory, paxiword length)
{
    Pax_String8 slice =
        pax_string8_range_length(self, 0, length);

    if (length > self.length) return 0;

    return pax_string8_is_equal_memory8(slice, memory, length);
}

paxb8
pax_string8_ends_with(Pax_String8 self, Pax_String8 value)
{
    return pax_string8_ends_with_memory8(self, value.memory, value.length);
}

paxb8
pax_string8_ends_with_memory8(Pax_String8 self, paxu8* memory, paxiword length)
{
    Pax_String8 slice =
        pax_string8_range_length(self, self.length - length, length);

    if (length > self.length) return 0;

    return pax_string8_is_equal_memory8(slice, memory, length);
}

paxiword
pax_string8_contains(Pax_String8 self, Pax_String8 value)
{
    return pax_string8_contains_memory8(self, value.memory, value.length);
}

paxiword
pax_string8_contains_memory8(Pax_String8 self, paxu8* memory, paxiword length)
{
    paxiword result = 0;

    if (length > self.length) return result;

    for (paxiword i = 0; i < self.length - length + 1; i += 1) {
        Pax_String8 slice = pax_string8_range_length(self, i, length);

        if (pax_string8_is_equal_memory8(slice, memory, length) != 0)
            result += 1, i += length - 1;
    }

    return result;
}

Pax_String8
pax_string8_trim_spaces(Pax_String8 self)
{
    paxiword units = 0;
    paxiword start = 0;
    paxiword stop  = self.length;

    for (; start < stop; start += units) {
        paxi32 unicode = 0;

        units = pax_utf8_read_forw(self.memory,
            self.length, start, &unicode);

        if (units <= 0) return (Pax_String8) {0};

        if (pax_unicode_is_ascii_cntrl(unicode) == 0)
            break;
    }

    for (; start < stop; stop -= units) {
        paxi32 unicode = 0;

        units = pax_utf8_read_back(self.memory,
            self.length, stop - 1, &unicode);

        if (units <= 0) return (Pax_String8) {0};

        if (pax_unicode_is_ascii_cntrl(unicode) == 0)
            break;
    }

    return pax_string8_range(self, start, stop);
}

Pax_String8
pax_string8_trim_spaces_head(Pax_String8 self)
{
    paxiword units = 0;
    paxiword start = 0;
    paxiword stop  = self.length;

    for (; start < stop; start += units) {
        paxi32 unicode = 0;

        units = pax_utf8_read_forw(self.memory,
            self.length, start, &unicode);

        if (units <= 0) return (Pax_String8) {0};

        if (pax_unicode_is_ascii_cntrl(unicode) == 0)
            break;
    }

    return pax_string8_range(self, start, stop);
}

Pax_String8
pax_string8_trim_spaces_tail(Pax_String8 self)
{
    paxiword units = 0;
    paxiword start = 0;
    paxiword stop  = self.length;

    for (; start < stop; stop -= units) {
        paxi32 unicode = 0;

        units = pax_utf8_read_back(self.memory,
            self.length, stop - 1, &unicode);

        if (units <= 0) return (Pax_String8) {0};

        if (pax_unicode_is_ascii_cntrl(unicode) == 0)
            break;
    }

    return pax_string8_range(self, start, stop);
}

Pax_String8
pax_string8_trim_prefix(Pax_String8 self, Pax_String8 prefix)
{
    if (pax_string8_begins_with(self, prefix) != 0)
        return pax_string8_range(self, prefix.length, self.length);

    return pax_string8_range_length(self, 0, self.length);
}

Pax_String8
pax_string8_trim_prefix_memory8(Pax_String8 self, paxu8* memory, paxiword length)
{
    if (pax_string8_begins_with_memory8(self, memory, length) != 0)
        return pax_string8_range(self, length, self.length);

    return pax_string8_range_length(self, 0, self.length);
}

Pax_String8
pax_string8_trim_suffix(Pax_String8 self, Pax_String8 suffix)
{
    if (pax_string8_ends_with(self, suffix) != 0)
        return pax_string8_range(self, 0, self.length - suffix.length);

    return pax_string8_range_length(self, 0, self.length);
}

Pax_String8
pax_string8_trim_suffix_memory8(Pax_String8 self, paxu8* memory, paxiword length)
{
    if (pax_string8_ends_with_memory8(self, memory, length) != 0)
        return pax_string8_range(self, 0, self.length - length);

    return pax_string8_range_length(self, 0, self.length);
}

paxb8
pax_string8_find_first(Pax_String8 self, paxiword start, Pax_String8 value, paxiword* index)
{
    return pax_string8_find_first_memory8(self, start, value.memory, value.length, index);
}

paxb8
pax_string8_find_first_memory8(Pax_String8 self, paxiword start, paxu8* memory, paxiword length, paxiword* index)
{
    paxb8 state = 0;

    start = pax_between(start, 0, self.length);

    for (paxiword i = start; i < self.length; i += 1) {
        Pax_String8 slice =
            pax_string8_range_length(self, i, length);

        state = pax_string8_is_equal_memory8(slice, memory, length);

        if (state == 0) continue;
        if (index != 0) *index = i;

        return 1;
    }

    return 0;
}

paxb8
pax_string8_find_last(Pax_String8 self, paxiword start, Pax_String8 value, paxiword* index)
{
    return pax_string8_find_last_memory8(self, start, value.memory, value.length, index);
}

paxb8
pax_string8_find_last_memory8(Pax_String8 self, paxiword start, paxu8* memory, paxiword length, paxiword* index)
{
    paxb8 state = 0;

    start = pax_between(start, 0, self.length);

    for (paxiword i = start; i > 0; i -= 1) {
        Pax_String8 slice =
            pax_string8_range_length(self, i - length, length);

        state = pax_string8_is_equal_memory8(slice, memory, length);

        if (state == 0) continue;
        if (index != 0) *index = i - length;

        return 1;
    }

    return 0;
}

paxiword
pax_string8_split(Pax_String8 self, Pax_String8 pivot, Pax_String8* left, Pax_String8* right)
{
    return pax_string8_split_memory8(self, pivot.memory, pivot.length, left, right);
}

paxiword
pax_string8_split_memory8(Pax_String8 self, paxu8* memory, paxiword length, Pax_String8* left, Pax_String8* right)
{
    paxiword start = 0;
    paxiword stop  = self.length;
    paxiword index = self.length;

    paxb8 state = pax_string8_find_first_memory8(self,
        start, memory, length, &index);

    if (left != 0)
        *left = pax_string8_range(self, start, index);

    if (right != 0)
        *right = pax_string8_range(self, index + length, stop);

    if (state != 0) index += 1;

    return index;
}

paxb8
pax_string8_next(Pax_String8 self, paxiword index, paxiword* units, paxi32* value)
{
    if (index < 0 || index >= self.length)
        return 0;

    paxiword step = pax_utf8_read_forw(self.memory,
        self.length, index, value);

    if (step == 0) return 0;

    if (units != 0) *units = step;

    return 1;
}

paxb8
pax_string8_prev(Pax_String8 self, paxiword index, paxiword* units, paxi32* value)
{
    if (index < 0 || index >= self.length)
        return 0;

    paxiword step = pax_utf8_read_back(self.memory,
        self.length, index, value);

    if (step == 0) return 0;

    if (units != 0) *units = step;

    return 1;
}

#endif // PAX_CORE_STRING_STRING8_C
