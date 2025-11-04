#ifndef PAX_CORE_STRING_STRING16_C
#define PAX_CORE_STRING_STRING16_C

#include "./string16.h"

Pax_String16
pax_string16_make(paxu16* memory, paxiword length)
{
    Pax_String16 result = {0};

    if (memory != 0 && length > 0) {
        result.memory = memory;
        result.length = length;
    }

    return result;
}

Pax_String16
pax_string16_from_memory(void* memory, paxiword length, paxiword stride)
{
    paxiword index = 0;

    if (stride != pax_size(paxu16)) return (Pax_String16) {0};

    while (index < length) {
        if (pax_as(paxu16*, memory)[index] == 0)
            break;

        index += 1;
    }

    return pax_string16_make(memory, index);
}

Pax_String16
pax_string16_copy(Pax_Arena* arena, Pax_String16 value)
{
    return pax_string16_copy_memory16(arena, value.memory, value.length);
}

Pax_String16
pax_string16_copy_memory16(Pax_Arena* arena, paxu16* memory, paxiword length)
{
    if (memory == 0 || length <= 0) return (Pax_String16) {0};

    paxiword     mark   = pax_arena_tell(arena);
    Pax_Buffer16 buffer = pax_buffer16_create(arena, length + 1);

    if (pax_buffer16_capacity(&buffer) > 0) {
        Pax_String16 string = {0};

        string.memory  = pax_as(paxu16*, buffer.memory);
        string.length += pax_buffer16_write_tail_memory16(&buffer, memory, length);

        if (string.length == length)
            return string;
    }

    pax_arena_rewind(arena, mark, 0);

    return (Pax_String16) {0};
}

Pax_String16
pax_string16_copy_unicode(Pax_Arena* arena, paxi32 value)
{
    Pax_UTF16 utf16 = {0};

    if (pax_utf16_encode(&utf16, value) > 0)
        return pax_string16_copy_memory16(arena, utf16.items, utf16.size);

    return (Pax_String16) {0};
}

Pax_String16
pax_string16_range(Pax_String16 self, paxiword start, paxiword stop)
{
    return pax_string16_range_length(self, start, stop - start);
}

Pax_String16
pax_string16_range_length(Pax_String16 self, paxiword index, paxiword length)
{
    index  = pax_between(index,  0, self.length - 1);
    length = pax_between(length, 0, self.length - index);

    if (length <= 0) return (Pax_String16) {0};

    paxu16* memory = self.memory + index;

    return pax_string16_make(memory, length);
}

Pax_String16
pax_string16_range_head(Pax_String16 self, paxiword head)
{
    return pax_string16_range(self, head, self.length);
}

Pax_String16
pax_string16_range_tail(Pax_String16 self, paxiword tail)
{
    return pax_string16_range(self, 0, tail);
}

paxiword
pax_string16_peek_memory16(Pax_String16 self, paxiword index, paxu16* memory, paxiword length)
{
    paxiword stride = pax_size(paxu16);

    index  = pax_between(index,  0, self.length - 1);
    length = pax_between(length, 0, self.length - index);

    Pax_Slice slice =
        pax_slice_make(self.memory, self.length, stride);

    Pax_Slice other = pax_slice_make(memory, length, stride);

    pax_slice_read(slice, index, other);

    return length;
}

paxu16
pax_string16_peek_or_none(Pax_String16 self, paxiword index)
{
    if (index < 0 || index >= self.length)
        return 0;

    return self.memory[index];
}

paxb8
pax_string16_is_equal(Pax_String16 self, Pax_String16 value)
{
    return pax_string16_is_equal_memory16(self, value.memory, value.length);
}

paxb8
pax_string16_is_equal_memory16(Pax_String16 self, paxu16* memory, paxiword length)
{
    paxiword stride = pax_size(paxu16);

    Pax_Slice slice =
        pax_slice_make(self.memory, self.length, stride);

    Pax_Slice other = pax_slice_make(memory, length, stride);

    return pax_slice_is_equal(slice, other);
}

paxb8
pax_string16_begins_with(Pax_String16 self, Pax_String16 value)
{
    return pax_string16_begins_with_memory16(self, value.memory, value.length);
}

paxb8
pax_string16_begins_with_memory16(Pax_String16 self, paxu16* memory, paxiword length)
{
    Pax_String16 slice =
        pax_string16_range_length(self, 0, length);

    if (length > self.length) return 0;

    return pax_string16_is_equal_memory16(slice, memory, length);
}

paxb8
pax_string16_ends_with(Pax_String16 self, Pax_String16 value)
{
    return pax_string16_ends_with_memory16(self, value.memory, value.length);
}

paxb8
pax_string16_ends_with_memory16(Pax_String16 self, paxu16* memory, paxiword length)
{
    Pax_String16 slice =
        pax_string16_range_length(self, self.length - length, length);

    if (length > self.length) return 0;

    return pax_string16_is_equal_memory16(slice, memory, length);
}

paxiword
pax_string16_contains(Pax_String16 self, Pax_String16 value)
{
    return pax_string16_contains_memory16(self, value.memory, value.length);
}

paxiword
pax_string16_contains_memory16(Pax_String16 self, paxu16* memory, paxiword length)
{
    paxiword result = 0;

    if (length > self.length) return result;

    for (paxiword i = 0; i < self.length - length + 1; i += 1) {
        Pax_String16 slice = pax_string16_range_length(self, i, length);

        if (pax_string16_is_equal_memory16(slice, memory, length) != 0)
            result += 1, i += length - 1;
    }

    return result;
}

Pax_String16
pax_string16_trim_spaces(Pax_String16 self)
{
    paxiword units = 0;
    paxiword start = 0;
    paxiword stop  = self.length;

    for (; start < stop; start += units) {
        paxi32 unicode = 0;

        units = pax_utf16_read_forw(self.memory,
            self.length, start, &unicode);

        if (units <= 0) return (Pax_String16) {0};

        if (pax_unicode_is_ascii_cntrl(unicode) == 0)
            break;
    }

    for (; start < stop; stop -= units) {
        paxi32 unicode = 0;

        units = pax_utf16_read_back(self.memory,
            self.length, stop - 1, &unicode);

        if (units <= 0) return (Pax_String16) {0};

        if (pax_unicode_is_ascii_cntrl(unicode) == 0)
            break;
    }

    return pax_string16_range(self, start, stop);
}

Pax_String16
pax_string16_trim_spaces_head(Pax_String16 self)
{
    paxiword units = 0;
    paxiword start = 0;
    paxiword stop  = self.length;

    for (; start < stop; start += units) {
        paxi32 unicode = 0;

        units = pax_utf16_read_forw(self.memory,
            self.length, start, &unicode);

        if (units <= 0) return (Pax_String16) {0};

        if (pax_unicode_is_ascii_cntrl(unicode) == 0)
            break;
    }

    return pax_string16_range(self, start, stop);
}

Pax_String16
pax_string16_trim_spaces_tail(Pax_String16 self)
{
    paxiword units = 0;
    paxiword start = 0;
    paxiword stop  = self.length;

    for (; start < stop; stop -= units) {
        paxi32 unicode = 0;

        units = pax_utf16_read_back(self.memory,
            self.length, stop - 1, &unicode);

        if (units <= 0) return (Pax_String16) {0};

        if (pax_unicode_is_ascii_cntrl(unicode) == 0)
            break;
    }

    return pax_string16_range(self, start, stop);
}

Pax_String16
pax_string16_trim_prefix(Pax_String16 self, Pax_String16 prefix)
{
    if (pax_string16_begins_with(self, prefix) != 0)
        return pax_string16_range(self, prefix.length, self.length);

    return pax_string16_range_length(self, 0, self.length);
}

Pax_String16
pax_string16_trim_prefix_memory16(Pax_String16 self, paxu16* memory, paxiword length)
{
    if (pax_string16_begins_with_memory16(self, memory, length) != 0)
        return pax_string16_range(self, length, self.length);

    return pax_string16_range_length(self, 0, self.length);
}

Pax_String16
pax_string16_trim_suffix(Pax_String16 self, Pax_String16 suffix)
{
    if (pax_string16_ends_with(self, suffix) != 0)
        return pax_string16_range(self, 0, self.length - suffix.length);

    return pax_string16_range_length(self, 0, self.length);
}

Pax_String16
pax_string16_trim_suffix_memory16(Pax_String16 self, paxu16* memory, paxiword length)
{
    if (pax_string16_ends_with_memory16(self, memory, length) != 0)
        return pax_string16_range(self, 0, self.length - length);

    return pax_string16_range_length(self, 0, self.length);
}

paxb8
pax_string16_find_first(Pax_String16 self, paxiword start, Pax_String16 value, paxiword* index)
{
    return pax_string16_find_first_memory16(self, start, value.memory, value.length, index);
}

paxb8
pax_string16_find_first_memory16(Pax_String16 self, paxiword start, paxu16* memory, paxiword length, paxiword* index)
{
    paxb8 state = 0;

    start = pax_between(start, 0, self.length);

    for (paxiword i = start; i < self.length; i += 1) {
        Pax_String16 slice =
            pax_string16_range_length(self, i, length);

        state = pax_string16_is_equal_memory16(slice, memory, length);

        if (state == 0) continue;
        if (index != 0) *index = i;

        return 1;
    }

    return 0;
}

paxb8
pax_string16_find_last(Pax_String16 self, paxiword start, Pax_String16 value, paxiword* index)
{
    return pax_string16_find_last_memory16(self, start, value.memory, value.length, index);
}

paxb8
pax_string16_find_last_memory16(Pax_String16 self, paxiword start, paxu16* memory, paxiword length, paxiword* index)
{
    paxb8 state = 0;

    start = pax_between(start, 0, self.length);

    for (paxiword i = start; i > 0; i -= 1) {
        Pax_String16 slice =
            pax_string16_range_length(self, i - length, length);

        state = pax_string16_is_equal_memory16(slice, memory, length);

        if (state == 0) continue;
        if (index != 0) *index = i - length;

        return 1;
    }

    return 0;
}

paxiword
pax_string16_split(Pax_String16 self, Pax_String16 pivot, Pax_String16* left, Pax_String16* right)
{
    return pax_string16_split_memory16(self, pivot.memory, pivot.length, left, right);
}

paxiword
pax_string16_split_memory16(Pax_String16 self, paxu16* memory, paxiword length, Pax_String16* left, Pax_String16* right)
{
    paxiword start = 0;
    paxiword stop  = self.length;
    paxiword index = self.length;

    paxb8 state = pax_string16_find_first_memory16(self,
        start, memory, length, &index);

    if (left != 0)
        *left = pax_string16_range(self, start, index);

    if (right != 0)
        *right = pax_string16_range(self, index + length, stop);

    if (state != 0) index += 1;

    return index;
}

paxb8
pax_string16_next(Pax_String16 self, paxiword index, paxiword* units, paxi32* value)
{
    if (index < 0 || index >= self.length)
        return 0;

    paxiword step = pax_utf16_read_forw(self.memory,
        self.length, index, value);

    if (step == 0) return 0;

    if (units != 0) *units = step;

    return 1;
}

paxb8
pax_string16_prev(Pax_String16 self, paxiword index, paxiword* units, paxi32* value)
{
    if (index < 0 || index >= self.length)
        return 0;

    paxiword step = pax_utf16_read_back(self.memory,
        self.length, index, value);

    if (step == 0) return 0;

    if (units != 0) *units = step;

    return 1;
}

#endif // PAX_CORE_STRING_STRING16_C
