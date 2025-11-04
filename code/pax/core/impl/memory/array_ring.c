#ifndef PAX_CORE_MEMORY_ARRAY_RING_C
#define PAX_CORE_MEMORY_ARRAY_RING_C

#include "./array_ring.h"

Pax_Array_Ring
pax_array_ring_make_pure(void* memory, paxiword length, paxiword stride, paxiword offset)
{
    Pax_Array_Ring result = {0};

    offset = pax_between(offset, 0, length);

    if (memory != 0 && length > 0 && stride > 0) {
        result.memory   = memory;
        result.stride   = stride;
        result.capacity = length;
        result.offset   = offset;
    }

    return result;
}

Pax_Array_Ring
pax_array_ring_create_pure(Pax_Arena* arena, paxiword length, paxiword stride)
{
    Pax_Array_Ring result = {0};

    Pax_Slice slice =
        pax_arena_reserve_slice(arena, length, stride);

    result.memory   = slice.memory;
    result.stride   = slice.stride;
    result.capacity = slice.length;

    return result;
}

Pax_Array_Ring
pax_array_ring_copy(Pax_Arena* arena, Pax_Array_Ring* value)
{
    Pax_Array_Ring result =
        pax_array_ring_create_pure(arena, value->length, value->stride);

    if (result.capacity == 0) return result;

    Pax_Slice slice = pax_slice_make(result.memory, result.capacity, result.stride);
    Pax_Slice other = pax_slice_make(value->memory, value->capacity, result.stride);

    for (paxiword i = 0; i < value->length; i += 1) {
        paxiword j = (value->offset + i) % value->capacity;

        Pax_Slice left  = pax_slice_range_length(slice, i, 1);
        Pax_Slice right = pax_slice_range_length(other, j, 1);

        pax_slice_copy(left, right);
    }

    return result;
}

void
pax_array_ring_clear(Pax_Array_Ring* self)
{
    self->length = 0;
    self->offset = 0;
}

void
pax_array_ring_normalize(Pax_Array_Ring* self)
{
    Pax_Slice slice =
        pax_slice_make(self->memory, self->capacity, self->stride);

    paxiword head = self->offset;
    paxiword tail = (self->offset + self->length) % self->capacity;

    paxiword start = 0;
    paxiword stop  = self->capacity;

    if (head > tail) {
        Pax_Slice left = pax_slice_range(slice, head, stop);

        pax_slice_flip(left);

        Pax_Slice right =
            pax_slice_range(slice, start, tail);

        pax_slice_flip(right);

        pax_slice_flip(slice);
    }
}

void
pax_array_ring_fill(Pax_Array_Ring* self)
{
    Pax_Slice slice = pax_slice_make(self->memory,
        self->capacity, self->stride);

    paxiword size = self->capacity - self->length;

    for (paxiword i = self->length; i < self->capacity; i += 1) {
        paxiword j = (self->offset + i) % self->capacity;

        Pax_Slice range =
            pax_slice_range_length(slice, j, 1);

        pax_slice_zero(range);
    }

    self->length += size;
}

paxiword
pax_array_ring_elements(Pax_Array_Ring* self)
{
    return self->length;
}

paxiword
pax_array_ring_capacity(Pax_Array_Ring* self)
{
    return self->capacity;
}

paxiword
pax_array_ring_head(Pax_Array_Ring* self)
{
    return self->length > 0 ? 0 : -1;
}

paxiword
pax_array_ring_tail(Pax_Array_Ring* self)
{
    return self->length > 0 ? self->length - 1 : -1;
}

paxb8
pax_array_ring_is_empty(Pax_Array_Ring* self)
{
    return self->length <= 0 ? 1 : 0;
}

paxb8
pax_array_ring_is_full(Pax_Array_Ring* self)
{
    return self->length >= self->capacity ? 1 : 0;
}

paxiword
pax_array_ring_insert_head_pure(Pax_Array_Ring* self, void* memory, paxiword length, paxiword stride)
{
    length = pax_between(length, 0, self->capacity - self->length);

    if (self->stride != stride) return 0;

    Pax_Slice slice =
        pax_slice_make(self->memory, self->capacity, stride);

    Pax_Slice other = pax_slice_make(memory, length, stride);
    paxiword  index = 0;

    self->offset = (self->offset + self->capacity - length) % self->capacity;

    for (paxiword i = 0; i < length; i += 1) {
        paxiword j = (self->offset + index + i) % self->capacity;

        Pax_Slice left  = pax_slice_range_length(slice, j, 1);
        Pax_Slice right = pax_slice_range_length(other, i, 1);

        pax_slice_copy(left, right);
    }

    self->length += length;

    return length;
}

paxiword
pax_array_ring_insert_tail_pure(Pax_Array_Ring* self, void* memory, paxiword length, paxiword stride)
{
    length = pax_between(length, 0, self->capacity - self->length);

    if (self->stride != stride) return 0;

    Pax_Slice slice =
        pax_slice_make(self->memory, self->capacity, stride);

    Pax_Slice other = pax_slice_make(memory, length, stride);
    paxiword  index = self->length;

    for (paxiword i = 0; i < length; i += 1) {
        paxiword j = (self->offset + index + i) % self->capacity;

        Pax_Slice left  = pax_slice_range_length(slice, j, 1);
        Pax_Slice right = pax_slice_range_length(other, i, 1);

        pax_slice_copy(left, right);
    }

    self->length += length;

    return length;
}

paxiword
pax_array_ring_remove_head_pure(Pax_Array_Ring* self, void* memory, paxiword length, paxiword stride)
{
    length = pax_between(length, 0, self->length);

    if (self->stride != stride) return 0;

    Pax_Slice slice =
        pax_slice_make(self->memory, self->capacity, stride);

    Pax_Slice other = pax_slice_make(memory, length, stride);
    paxiword  index = 0;

    for (paxiword i = 0; i < length; i += 1) {
        paxiword j = (self->offset + index + i) % self->capacity;

        Pax_Slice left  = pax_slice_range_length(slice, j, 1);
        Pax_Slice right = pax_slice_range_length(other, i, 1);

        pax_slice_copy(right, left);
    }

    self->length -= length;
    self->offset  = (self->offset + length) % self->capacity;

    return length;
}

paxiword
pax_array_ring_remove_tail_pure(Pax_Array_Ring* self, void* memory, paxiword length, paxiword stride)
{
    length = pax_between(length, 0, self->length);

    if (self->stride != stride) return 0;

    Pax_Slice slice =
        pax_slice_make(self->memory, self->capacity, stride);

    Pax_Slice other = pax_slice_make(memory, length, stride);
    paxiword  index = self->length - length;

    for (paxiword i = 0; i < length; i += 1) {
        paxiword j = (self->offset + index + i) % self->capacity;

        Pax_Slice left  = pax_slice_range_length(slice, j, 1);
        Pax_Slice right = pax_slice_range_length(other, i, 1);

        pax_slice_copy(right, left);
    }

    self->length -= length;

    return length;
}

paxiword
pax_array_ring_peek_pure(Pax_Array_Ring* self, paxiword index, void* memory, paxiword length, paxiword stride)
{
    index  = pax_between(index,  0, self->length - 1);
    length = pax_between(length, 0, self->length - index);

    if (self->stride != stride) return 0;

    Pax_Slice slice =
        pax_slice_make(self->memory, self->capacity, stride);

    Pax_Slice other = pax_slice_make(memory, length, stride);

    for (paxiword i = 0; i < length; i += 1) {
        paxiword j = (self->offset + index + i) % self->capacity;

        Pax_Slice left  = pax_slice_range_length(slice, j, 1);
        Pax_Slice right = pax_slice_range_length(other, i, 1);

        pax_slice_copy(right, left);
    }

    return length;
}

void*
pax_array_ring_peek_pure_or_null(Pax_Array_Ring* self, paxiword index, paxiword stride)
{
    if (self->stride != stride) return 0;

    if (index < 0 || index >= self->length)
        return 0;

    paxiword other = (self->offset + index) % self->capacity;

    return &self->memory[other * self->stride];
}

paxiword
pax_array_ring_update_pure(Pax_Array_Ring* self, paxiword index, void* memory, paxiword length, paxiword stride)
{
    index  = pax_between(index,  0, self->length - 1);
    length = pax_between(length, 0, self->length - index);

    if (self->stride != stride) return 0;

    Pax_Slice slice =
        pax_slice_make(self->memory, self->capacity, stride);

    Pax_Slice other = pax_slice_make(memory, length, stride);

    for (paxiword i = 0; i < length; i += 1) {
        paxiword j = (self->offset + index + i) % self->capacity;

        Pax_Slice left  = pax_slice_range_length(slice, j, 1);
        Pax_Slice right = pax_slice_range_length(other, i, 1);

        pax_slice_copy(left, right);
    }

    return length;
}

#endif // PAX_CORE_MEMORY_ARRAY_RING_C
