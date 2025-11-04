#ifndef PAX_CORE_STRING_STRING8_H
#define PAX_CORE_STRING_STRING8_H

#include "./buffer8.h"

#define pax_str8(x) (Pax_String8) {pax_as(paxu8*, x), pax_size_block(paxu8, x) - 1}

#define pax_str8_vargs(x, ...) \
    (Pax_String8) {pax_block_from_vargs(paxu8, x, __VA_ARGS__), pax_size_vargs(paxu8, x, __VA_ARGS__)}

typedef struct Pax_String8
{
    paxu8*   memory;
    paxiword length;
}
Pax_String8;

Pax_String8
pax_string8_make(paxu8* memory, paxiword length);

Pax_String8
pax_string8_from_memory(void* memory, paxiword length, paxiword stride);

Pax_String8
pax_string8_copy(Pax_Arena* arena, Pax_String8 value);

Pax_String8
pax_string8_copy_memory8(Pax_Arena* arena, paxu8* memory, paxiword length);

Pax_String8
pax_string8_copy_unicode(Pax_Arena* arena, paxi32 value);

/* Range */

Pax_String8
pax_string8_range(Pax_String8 self, paxiword start, paxiword stop);

Pax_String8
pax_string8_range_length(Pax_String8 self, paxiword index, paxiword length);

Pax_String8
pax_string8_range_head(Pax_String8 self, paxiword head);

Pax_String8
pax_string8_range_tail(Pax_String8 self, paxiword tail);

/* Content */

paxiword
pax_string8_peek_memory8(Pax_String8 self, paxiword index, paxu8* memory, paxiword length);

paxu8
pax_string8_peek_or_none(Pax_String8 self, paxiword index);

paxb8
pax_string8_is_equal(Pax_String8 self, Pax_String8 value);

paxb8
pax_string8_is_equal_memory8(Pax_String8 self, paxu8* memory, paxiword length);

paxb8
pax_string8_begins_with(Pax_String8 self, Pax_String8 value);

paxb8
pax_string8_begins_with_memory8(Pax_String8 self, paxu8* memory, paxiword length);

paxb8
pax_string8_ends_with(Pax_String8 self, Pax_String8 value);

paxb8
pax_string8_ends_with_memory8(Pax_String8 self, paxu8* memory, paxiword length);

paxiword
pax_string8_contains(Pax_String8 self, Pax_String8 value);

paxiword
pax_string8_contains_memory8(Pax_String8 self, paxu8* memory, paxiword length);

/* Trim */

Pax_String8
pax_string8_trim_spaces(Pax_String8 self);

Pax_String8
pax_string8_trim_spaces_head(Pax_String8 self);

Pax_String8
pax_string8_trim_spaces_tail(Pax_String8 self);

Pax_String8
pax_string8_trim_prefix(Pax_String8 self, Pax_String8 prefix);

Pax_String8
pax_string8_trim_prefix_memory8(Pax_String8 self, paxu8* memory, paxiword length);

Pax_String8
pax_string8_trim_suffix(Pax_String8 self, Pax_String8 suffix);

Pax_String8
pax_string8_trim_suffix_memory8(Pax_String8 self, paxu8* memory, paxiword length);

/* Find */

paxb8
pax_string8_find_first(Pax_String8 self, paxiword start, Pax_String8 value, paxiword* index);

paxb8
pax_string8_find_first_memory8(Pax_String8 self, paxiword start, paxu8* memory, paxiword length, paxiword* index);

paxb8
pax_string8_find_last(Pax_String8 self, paxiword start, Pax_String8 value, paxiword* index);

paxb8
pax_string8_find_last_memory8(Pax_String8 self, paxiword start, paxu8* memory, paxiword length, paxiword* index);

/* Split */

paxiword
pax_string8_split(Pax_String8 self, Pax_String8 pivot, Pax_String8* left, Pax_String8* right);

paxiword
pax_string8_split_memory8(Pax_String8 self, paxu8* memory, paxiword length, Pax_String8* left, Pax_String8* right);

/* Iterate */

paxb8
pax_string8_next(Pax_String8 self, paxiword index, paxiword* units, paxi32* value);

paxb8
pax_string8_prev(Pax_String8 self, paxiword index, paxiword* units, paxi32* value);

#endif // PAX_CORE_STRING_STRING8_H
