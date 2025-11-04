#ifndef PAX_CORE_STRING_STRING32_H
#define PAX_CORE_STRING_STRING32_H

#include "./buffer32.h"

#define pax_str32(x) (Pax_String32) {pax_as(paxu32*, x), pax_size_block(paxu32, x) - 1}

#define pax_str32_vargs(x, ...) \
    (Pax_String32) {pax_block_from_vargs(paxu32, x, __VA_ARGS__), pax_size_vargs(paxu32, x, __VA_ARGS__)}

typedef struct Pax_String32
{
    paxu32*  memory;
    paxiword length;
}
Pax_String32;

Pax_String32
pax_string32_make(paxu32* memory, paxiword length);

Pax_String32
pax_string32_from_memory(void* memory, paxiword length, paxiword stride);

Pax_String32
pax_string32_copy(Pax_Arena* arena, Pax_String32 value);

Pax_String32
pax_string32_copy_memory32(Pax_Arena* arena, paxu32* memory, paxiword length);

Pax_String32
pax_string32_copy_unicode(Pax_Arena* arena, paxi32 value);

/* Range */

Pax_String32
pax_string32_range(Pax_String32 self, paxiword start, paxiword stop);

Pax_String32
pax_string32_range_length(Pax_String32 self, paxiword index, paxiword length);

Pax_String32
pax_string32_range_head(Pax_String32 self, paxiword head);

Pax_String32
pax_string32_range_tail(Pax_String32 self, paxiword tail);

/* Content */

paxiword
pax_string32_peek_memory32(Pax_String32 self, paxiword index, paxu32* memory, paxiword length);

paxu32
pax_string32_peek_or_none(Pax_String32 self, paxiword index);

paxb8
pax_string32_is_equal(Pax_String32 self, Pax_String32 value);

paxb8
pax_string32_is_equal_memory32(Pax_String32 self, paxu32* memory, paxiword length);

paxb8
pax_string32_begins_with(Pax_String32 self, Pax_String32 value);

paxb8
pax_string32_begins_with_memory32(Pax_String32 self, paxu32* memory, paxiword length);

paxb8
pax_string32_ends_with(Pax_String32 self, Pax_String32 value);

paxb8
pax_string32_ends_with_memory32(Pax_String32 self, paxu32* memory, paxiword length);

paxiword
pax_string32_contains(Pax_String32 self, Pax_String32 value);

paxiword
pax_string32_contains_memory32(Pax_String32 self, paxu32* memory, paxiword length);

/* Trim */

Pax_String32
pax_string32_trim_spaces(Pax_String32 self);

Pax_String32
pax_string32_trim_spaces_head(Pax_String32 self);

Pax_String32
pax_string32_trim_spaces_tail(Pax_String32 self);

Pax_String32
pax_string32_trim_prefix(Pax_String32 self, Pax_String32 prefix);

Pax_String32
pax_string32_trim_prefix_memory32(Pax_String32 self, paxu32* memory, paxiword length);

Pax_String32
pax_string32_trim_suffix(Pax_String32 self, Pax_String32 suffix);

Pax_String32
pax_string32_trim_suffix_memory32(Pax_String32 self, paxu32* memory, paxiword length);

/* Find */

paxb8
pax_string32_find_first(Pax_String32 self, paxiword start, Pax_String32 value, paxiword* index);

paxb8
pax_string32_find_first_memory32(Pax_String32 self, paxiword start, paxu32* memory, paxiword length, paxiword* index);

paxb8
pax_string32_find_last(Pax_String32 self, paxiword start, Pax_String32 value, paxiword* index);

paxb8
pax_string32_find_last_memory32(Pax_String32 self, paxiword start, paxu32* memory, paxiword length, paxiword* index);

/* Split */

paxiword
pax_string32_split(Pax_String32 self, Pax_String32 pivot, Pax_String32* left, Pax_String32* right);

paxiword
pax_string32_split_memory32(Pax_String32 self, paxu32* memory, paxiword length, Pax_String32* left, Pax_String32* right);

/* Iterate */

paxb8
pax_string32_next(Pax_String32 self, paxiword index, paxiword* units, paxi32* value);

paxb8
pax_string32_prev(Pax_String32 self, paxiword index, paxiword* units, paxi32* value);

#endif // PAX_CORE_STRING_STRING32_H
