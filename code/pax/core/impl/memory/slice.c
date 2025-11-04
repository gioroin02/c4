#ifndef PAX_CORE_MEMORY_SLICE_C
#define PAX_CORE_MEMORY_SLICE_C

#include "./slice.h"

Pax_Slice
pax_slice_make(void* memory, paxiword length, paxiword stride)
{
    Pax_Slice result = {0};

    if (memory != 0 && length > 0 && stride > 0) {
        result.memory = memory;
        result.length = length;
        result.stride = stride;
    }

    return result;
}

Pax_Slice
pax_slice_range(Pax_Slice self, paxiword start, paxiword stop)
{
    return pax_slice_range_length(self, start, stop - start);
}

Pax_Slice
pax_slice_range_length(Pax_Slice self, paxiword index, paxiword length)
{
    index  = pax_between(index,  0, self.length - 1);
    length = pax_between(length, 0, self.length - index);

    if (length <= 0) return pax_slice_make(0, 0, 0);

    paxu8* memory = self.memory + self.stride * index;

    return pax_slice_make(memory, length, self.stride);
}

void*
pax_slice_zero(Pax_Slice self)
{
    for (paxiword i = 0; i < self.length * self.stride; i += 1)
        self.memory[i] = 0;

    return self.memory;
}

void*
pax_slice_flip(Pax_Slice self)
{
    paxiword head = 0;
    paxiword tail = self.length - 1;

    while (head < tail) {
        for (paxiword i = 0; i < self.stride; i += 1) {
            paxu8 left  = self.memory[head * self.stride + i];
            paxu8 right = self.memory[tail * self.stride + i];

            self.memory[head * self.stride + i] = right;
            self.memory[tail * self.stride + i] = left;
        }

        head += 1;
        tail -= 1;
    }

    return self.memory;
}

void*
pax_slice_copy(Pax_Slice self, Pax_Slice value)
{
    if (self.length != value.length || self.stride != value.stride)
        return 0;

    for (paxiword i = 0; i < self.length * self.stride; i += 1)
        self.memory[i] = value.memory[i];

    return self.memory;
}

void*
pax_slice_copy_flipped(Pax_Slice self, Pax_Slice value)
{
    if (pax_slice_copy(self, value) == 0)
        return 0;

    return pax_slice_flip(self);
}

void*
pax_slice_shift(Pax_Slice self, paxiword index, paxiword length, paxiword about)
{
    paxuword value = pax_magn_integer(about);

    switch (pax_sign_integer(about)) {
        case +1:
            return pax_slice_shift_forw(self, index, length, about);

        case -1:
            return pax_slice_shift_back(self, index, length, about);

        default: break;
    }

    return self.memory;
}

void*
pax_slice_shift_forw(Pax_Slice self, paxiword index, paxiword length, paxiword about)
{
    index  = pax_between(index,  0, self.length - 1);
    length = pax_between(length, 0, self.length - index);

    if (about < 0 || index + length + about > self.length) return 0;

    for (paxiword i = length; i > 0; i -= 1) {
        paxiword left  = i - 1;
        paxiword right = i - 1 + about;

        for (paxiword j = 0; j < self.stride; j += 1) {
            paxu8 value = self.memory[self.stride * left + j];

            self.memory[self.stride * right + j] = value;
            self.memory[self.stride * left  + j] = 0;
        }
    }

    return self.memory;
}

void*
pax_slice_shift_back(Pax_Slice self, paxiword index, paxiword length, paxiword about)
{
    index  = pax_between(index,  0, self.length - 1);
    length = pax_between(length, 0, self.length - index);

    if (about < 0 || index - about < 0) return 0;

    for (paxiword i = 0; i < length; i += 1) {
        paxiword left  = i;
        paxiword right = i + about;

        for (paxiword j = 0; j < self.stride; j += 1) {
            paxu8 value = self.memory[self.stride * right + j];

            self.memory[self.stride * left  + j] = value;
            self.memory[self.stride * right + j] = 0;
        }
    }

    return self.memory;
}

paxb8
pax_slice_is_equal(Pax_Slice self, Pax_Slice value)
{
    if (self.length != value.length || self.stride != value.stride)
        return 0;

    for (paxiword i = 0; i < self.length * self.stride; i += 1) {
        if (self.memory[i] != value.memory[i])
            return 0;
    }

    return 1;
}

paxiword
pax_slice_length(Pax_Slice self)
{
    return self.length;
}

paxb8
pax_slice_peek_pure(Pax_Slice self, paxiword index, void* memory, paxiword stride)
{
    if (index < 0 || index >= self.length || stride != self.stride)
        return 0;

    if (memory == 0) return 1;

    for (paxiword i = 0; i < self.stride; i += 1) {
        paxu8 value =
            self.memory[self.stride * index + i];

        pax_as(paxu8*, memory)[i] = value;
    }

    return 1;
}

void*
pax_slice_peek_pure_or_null(Pax_Slice self, paxiword index, paxiword stride)
{
    if (self.stride != stride) return 0;

    if (index < 0 || index >= self.length)
        return 0;

    return &self.memory[self.stride * index];
}

paxb8
pax_slice_update_pure(Pax_Slice self, paxiword index, void* memory, paxiword stride)
{
    if (index < 0 || index >= self.length || stride != self.stride)
        return 0;

    if (memory == 0) {
        for (paxiword i = 0; i < self.stride; i += 1)
            self.memory[self.stride * index + i] = 0;

        return 1;
    }

    for (paxiword i = 0; i < self.stride; i += 1) {
        paxu8 value = pax_as(paxu8*, memory)[i];

        self.memory[self.stride * index + i] =
            value;
    }

    return 1;
}

paxb8
pax_slice_write(Pax_Slice self, paxiword index, Pax_Slice value)
{
    if (self.stride != value.stride) return 0;

    if (index < 0 || index + value.length > self.length)
        return 0;

    Pax_Slice slice =
        pax_slice_range_length(self, index, value.length);

    pax_slice_copy(slice, value);

    return 1;
}

paxb8
pax_slice_read(Pax_Slice self, paxiword index, Pax_Slice value)
{
    if (self.stride != value.stride) return 0;

    if (index < 0 || index + value.length > self.length)
        return 0;

    Pax_Slice slice =
        pax_slice_range_length(self, index, value.length);

    pax_slice_copy(value, slice);

    return 1;
}

#endif // PAX_CORE_MEMORY_SLICE_C
