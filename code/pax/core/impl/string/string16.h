#ifndef PAX_CORE_STRING_STRING16_H
#define PAX_CORE_STRING_STRING16_H

#include "./buffer16.h"

#define pax_str16(x) (Pax_String16) {pax_as(paxu16*, x), pax_size_block(paxu16, x) - 1}

#define pax_str16_vargs(x, ...) \
    (Pax_String16) {pax_block_from_vargs(paxu16, x, __VA_ARGS__), pax_size_vargs(paxu16, x, __VA_ARGS__)}

typedef struct Pax_String16
{
    paxu16*  memory;
    paxiword length;
}
Pax_String16;

Pax_String16
pax_string16_make(paxu16* memory, paxiword length);

Pax_String16
pax_string16_from_memory(void* memory, paxiword length, paxiword stride);

Pax_String16
pax_string16_copy(Pax_Arena* arena, Pax_String16 value);

Pax_String16
pax_string16_copy_memory16(Pax_Arena* arena, paxu16* memory, paxiword length);

Pax_String16
pax_string16_copy_unicode(Pax_Arena* arena, paxi32 value);

/* Range */

Pax_String16
pax_string16_range(Pax_String16 self, paxiword start, paxiword stop);

Pax_String16
pax_string16_range_length(Pax_String16 self, paxiword index, paxiword length);

Pax_String16
pax_string16_range_head(Pax_String16 self, paxiword head);

Pax_String16
pax_string16_range_tail(Pax_String16 self, paxiword tail);

/* Content */

paxiword
pax_string16_peek_memory16(Pax_String16 self, paxiword index, paxu16* memory, paxiword length);

paxu16
pax_string16_peek_or_none(Pax_String16 self, paxiword index);

paxb8
pax_string16_is_equal(Pax_String16 self, Pax_String16 value);

paxb8
pax_string16_is_equal_memory16(Pax_String16 self, paxu16* memory, paxiword length);

paxb8
pax_string16_begins_with(Pax_String16 self, Pax_String16 value);

paxb8
pax_string16_begins_with_memory16(Pax_String16 self, paxu16* memory, paxiword length);

paxb8
pax_string16_ends_with(Pax_String16 self, Pax_String16 value);

paxb8
pax_string16_ends_with_memory16(Pax_String16 self, paxu16* memory, paxiword length);

paxiword
pax_string16_contains(Pax_String16 self, Pax_String16 value);

paxiword
pax_string16_contains_memory16(Pax_String16 self, paxu16* memory, paxiword length);

/* Trim */

Pax_String16
pax_string16_trim_spaces(Pax_String16 self);

Pax_String16
pax_string16_trim_spaces_head(Pax_String16 self);

Pax_String16
pax_string16_trim_spaces_tail(Pax_String16 self);

Pax_String16
pax_string16_trim_prefix(Pax_String16 self, Pax_String16 prefix);

Pax_String16
pax_string16_trim_prefix_memory16(Pax_String16 self, paxu16* memory, paxiword length);

Pax_String16
pax_string16_trim_suffix(Pax_String16 self, Pax_String16 suffix);

Pax_String16
pax_string16_trim_suffix_memory16(Pax_String16 self, paxu16* memory, paxiword length);

/* Find */

paxb8
pax_string16_find_first(Pax_String16 self, paxiword start, Pax_String16 value, paxiword* index);

paxb8
pax_string16_find_first_memory16(Pax_String16 self, paxiword start, paxu16* memory, paxiword length, paxiword* index);

paxb8
pax_string16_find_last(Pax_String16 self, paxiword start, Pax_String16 value, paxiword* index);

paxb8
pax_string16_find_last_memory16(Pax_String16 self, paxiword start, paxu16* memory, paxiword length, paxiword* index);

/* Split */

paxiword
pax_string16_split(Pax_String16 self, Pax_String16 pivot, Pax_String16* left, Pax_String16* right);

paxiword
pax_string16_split_memory16(Pax_String16 self, paxu16* memory, paxiword length, Pax_String16* left, Pax_String16* right);

/* Iterate */

paxb8
pax_string16_next(Pax_String16 self, paxiword index, paxiword* units, paxi32* value);

paxb8
pax_string16_prev(Pax_String16 self, paxiword index, paxiword* units, paxi32* value);

#endif // PAX_CORE_STRING_STRING16_H
