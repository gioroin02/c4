#ifndef PAX_CORE_MEMORY_SLICE_H
#define PAX_CORE_MEMORY_SLICE_H

#include "./import.h"

#define pax_slice_from_block(type, memory) \
    pax_slice_make(memory, pax_size_block(type, memory), pax_size(type))

#define pax_slice_peek(self, type, index, value) \
    pax_slice_peek_pure(self, index, value, pax_size(type))

#define pax_slice_peek_or_fail(self, type, index) \
    *pax_as(type*, pax_slice_peek_pure_or_null(self, index, pax_size(type)))

#define pax_slice_update(self, type, index, value) \
    pax_slice_update_pure(self, index, value, pax_size(type))

typedef struct Pax_Slice
{
    paxu8*   memory;
    paxiword length;
    paxiword stride;
}
Pax_Slice;

Pax_Slice
pax_slice_make(void* memory, paxiword length, paxiword stride);

Pax_Slice
pax_slice_range(Pax_Slice self, paxiword start, paxiword stop);

Pax_Slice
pax_slice_range_length(Pax_Slice self, paxiword index, paxiword length);

void*
pax_slice_zero(Pax_Slice self);

void*
pax_slice_flip(Pax_Slice self);

void*
pax_slice_copy(Pax_Slice self, Pax_Slice value);

void*
pax_slice_copy_flipped(Pax_Slice self, Pax_Slice value);

void*
pax_slice_shift(Pax_Slice self, paxiword index, paxiword length, paxiword about);

void*
pax_slice_shift_forw(Pax_Slice self, paxiword index, paxiword length, paxiword about);

void*
pax_slice_shift_back(Pax_Slice self, paxiword index, paxiword length, paxiword about);

paxb8
pax_slice_is_equal(Pax_Slice self, Pax_Slice value);

paxiword
pax_slice_length(Pax_Slice self);

paxb8
pax_slice_peek_pure(Pax_Slice self, paxiword index, void* memory, paxiword stride);

void*
pax_slice_peek_pure_or_null(Pax_Slice self, paxiword index, paxiword stride);

paxb8
pax_slice_update_pure(Pax_Slice self, paxiword index, void* memory, paxiword stride);

paxb8
pax_slice_write(Pax_Slice self, paxiword index, Pax_Slice slice);

paxb8
pax_slice_read(Pax_Slice self, paxiword index, Pax_Slice slice);

#endif // PAX_CORE_MEMORY_SLICE_H
