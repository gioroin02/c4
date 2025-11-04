#ifndef PAX_CORE_MEMORY_ARENA_C
#define PAX_CORE_MEMORY_ARENA_C

#include "./arena.h"

static paxiword
pax_arena_align_forw(Pax_Arena* self, paxiword align)
{
    if (align <= 0) return self->length;

    paxiword diff = self->length % align;

    if (diff != 0)
        return self->length + align - diff;

    return self->length;
}

Pax_Arena
pax_arena_make(paxu8* memory, paxiword length)
{
    Pax_Arena result = {0};

    if (memory != 0 && length > 0) {
        result.memory   = memory;
        result.capacity = length;
    }

    return result;
}

Pax_Arena
pax_arena_create(Pax_Arena* arena, paxiword length)
{
    paxu8* memory =
        pax_arena_reserve(arena, paxu8, length);

    return pax_arena_make(memory, length);
}

Pax_Slice
pax_arena_reserve_slice(Pax_Arena* self, paxiword length, paxiword stride)
{
    Pax_Slice result = {0};

    result.memory =
        pax_arena_reserve_memory(self, length, stride);

    if (result.memory != 0) {
        result.length = length;
        result.stride = stride;
    }

    return result;
}

void*
pax_arena_reserve_memory(Pax_Arena* self, paxiword length, paxiword stride)
{
    if (length <= 0 || stride <= 0) return 0;

    paxiword index = pax_arena_align_forw(self, 16);
    paxiword size  = length * stride;

    if (size > PAX_IWORD_MAX - index) return 0;

    if (index < 0 || index + size > self->capacity)
        return 0;

    Pax_Slice slice =
        pax_slice_make(self->memory, self->capacity, 1);

    slice = pax_slice_range(slice, self->length, index + size);

    pax_slice_zero(slice);

    self->length = index + size;

    return self->memory + index;
}

Pax_Slice
pax_arena_clone_slice(Pax_Arena* self, void* memory, paxiword length, paxiword stride)
{
    Pax_Slice slice = pax_slice_make(memory, length, stride);

    Pax_Slice result =
        pax_arena_reserve_slice(self, slice.length, slice.stride);

    pax_slice_copy(result, slice);

    return result;
}

void*
pax_arena_clone_memory(Pax_Arena* self, void* memory, paxiword length, paxiword stride)
{
    return pax_arena_clone_slice(self, memory, length, stride).memory;
}

paxb8
pax_arena_release_slice(Pax_Arena* self, Pax_Slice slice)
{
    return pax_arena_release_memory(self, slice.memory);
}

paxb8
pax_arena_release_memory(Pax_Arena* self, void* memory)
{
    paxiword diff = self->memory - pax_as(paxu8*, memory);

    if (diff < 0 || diff >= self->capacity)
        return 0;

    self->length = diff;

    return 1;
}

void
pax_arena_clear(Pax_Arena* self)
{
    self->length = 0;
}

paxiword
pax_arena_tell(Pax_Arena* self)
{
    return pax_arena_align_forw(self, 16);
}

void
pax_arena_rewind(Pax_Arena* self, paxiword mark, paxiword offset)
{
    mark   = pax_between(mark,   0, self->capacity);
    offset = pax_between(offset, 0, self->capacity - mark);

    self->length = mark + offset;
}

#endif // PAX_CORE_MEMORY_ARENA_C
