#ifndef PAX_CORE_MEMORY_ARRAY_C
#define PAX_CORE_MEMORY_ARRAY_C

#include "./array.h"

static Pax_Slice
pax_array_range_length(Pax_Array* self, paxiword index, paxiword length)
{
    Pax_Slice slice = pax_slice_make(self->memory,
        self->capacity, self->stride);

    return pax_slice_range_length(slice, index, length);
}

static Pax_Slice
pax_array_range(Pax_Array* self, paxiword start, paxiword stop)
{
    return pax_array_range_length(self, start, stop - start);
}

Pax_Array
pax_array_make_pure(void* memory, paxiword length, paxiword stride)
{
    Pax_Array result = {0};

    if (memory != 0 && length > 0 && stride > 0) {
        result.memory   = memory;
        result.stride   = stride;
        result.capacity = length;
    }

    return result;
}

Pax_Array
pax_array_create_pure(Pax_Arena* arena, paxiword length, paxiword stride)
{
    Pax_Array result = {0};

    Pax_Slice slice =
        pax_arena_reserve_slice(arena, length, stride);

    result.memory   = slice.memory;
    result.stride   = slice.stride;
    result.capacity = slice.length;

    return result;
}

Pax_Array
pax_array_copy(Pax_Arena* arena, Pax_Array* value)
{
    Pax_Array result =
        pax_array_create_pure(arena, value->length, value->stride);

    if (result.capacity == 0) return result;

    Pax_Slice left  = pax_array_range(&result, 0, result.capacity);
    Pax_Slice right = pax_array_range(value,   0, result.capacity);

    pax_slice_copy(left, right);

    return result;
}

void
pax_array_clear(Pax_Array* self)
{
    self->length = 0;
}

void
pax_array_fill(Pax_Array* self)
{
    Pax_Slice slice = pax_array_range(self,
        self->length, self->capacity);

    pax_slice_zero(slice);

    self->length = self->capacity;
}

paxiword
pax_array_elements(Pax_Array* self)
{
    return self->length;
}

paxiword
pax_array_capacity(Pax_Array* self)
{
    return self->capacity;
}

paxiword
pax_array_head(Pax_Array* self)
{
    return self->length > 0 ? 0 : -1;
}

paxiword
pax_array_tail(Pax_Array* self)
{
    return self->length > 0 ? self->length - 1 : -1;
}

paxb8
pax_array_is_empty(Pax_Array* self)
{
    return self->length <= 0 ? 1 : 0;
}

paxb8
pax_array_is_full(Pax_Array* self)
{
    return self->length >= self->capacity ? 1 : 0;
}

paxiword
pax_array_insert_pure(Pax_Array* self, paxiword index, void* memory, paxiword length, paxiword stride)
{
    index  = pax_between(index,  0, self->length);
    length = pax_between(length, 0, self->capacity - index);

    if (self->stride != stride) return 0;

    Pax_Slice slice = pax_array_range(self, 0, self->capacity);
    Pax_Slice other = pax_slice_make(memory, length, stride);

    if (index < self->length)
        pax_slice_shift_forw(slice, index, self->length - index, length);

    self->length += length;

    pax_slice_write(slice, index, other);

    return length;
}

paxiword
pax_array_remove_pure(Pax_Array* self, paxiword index, void* memory, paxiword length, paxiword stride)
{
    index  = pax_between(index,  0, self->length - 1);
    length = pax_between(length, 0, self->length - index);

    if (self->stride != stride) return 0;

    Pax_Slice slice = pax_array_range(self, 0, self->capacity);
    Pax_Slice other = pax_slice_make(memory, length, stride);

    pax_slice_read(slice, index, other);

    paxiword temp = index + length;

    if (temp < self->length)
        pax_slice_shift_back(slice, temp, self->length - temp, length);

    self->length -= length;

    return length;
}

paxiword
pax_array_peek_pure(Pax_Array* self, paxiword index, void* memory, paxiword length, paxiword stride)
{
    index  = pax_between(index,  0, self->length - 1);
    length = pax_between(length, 0, self->length - index);

    if (self->stride != stride) return 0;

    Pax_Slice slice = pax_array_range(self, 0, self->length);
    Pax_Slice other = pax_slice_make(memory, length, stride);

    pax_slice_read(slice, index, other);

    return length;
}

void*
pax_array_peek_pure_or_null(Pax_Array* self, paxiword index, paxiword stride)
{
    if (self->stride != stride) return 0;

    if (index < 0 || index >= self->length)
        return 0;

    return &self->memory[index * self->stride];
}

paxiword
pax_array_update_pure(Pax_Array* self, paxiword index, void* memory, paxiword length, paxiword stride)
{
    index  = pax_between(index,  0, self->length - 1);
    length = pax_between(length, 0, self->length - index);

    if (self->stride != stride) return 0;

    Pax_Slice slice = pax_array_range(self, 0, self->length);
    Pax_Slice other = pax_slice_make(memory, length, stride);

    pax_slice_write(slice, index, other);

    return length;
}

#endif // PAX_CORE_MEMORY_ARRAY_C
