#ifndef PAX_CORE_MEMORY_ARENA_H
#define PAX_CORE_MEMORY_ARENA_H

#include "./slice.h"

#define pax_arena_from_block(memory) pax_arena_make(memory, pax_size(memory))

#define pax_arena_reserve(self, type, amount) \
    pax_as(type*, pax_arena_reserve_memory(self, amount, pax_size(type)))

#define pax_arena_clone(self, type, memory, amount) \
    pax_as(type*, pax_arena_clone_memory(self, memory, amount, pax_size(type)))

typedef struct Pax_Arena
{
    paxu8*   memory;
    paxiword length;
    paxiword capacity;
}
Pax_Arena;

Pax_Arena
pax_arena_make(paxu8* memory, paxiword length);

Pax_Arena
pax_arena_create(Pax_Arena* arena, paxiword length);

Pax_Slice
pax_arena_reserve_slice(Pax_Arena* self, paxiword length, paxiword stride);

void*
pax_arena_reserve_memory(Pax_Arena* self, paxiword length, paxiword stride);

paxb8
pax_arena_release_memory(Pax_Arena* self, void* memory);

Pax_Slice
pax_arena_clone_slice(Pax_Arena* self, void* memory, paxiword length, paxiword stride);

void*
pax_arena_clone_memory(Pax_Arena* self, void* memory, paxiword length, paxiword stride);

void
pax_arena_clear(Pax_Arena* self);

paxiword
pax_arena_tell(Pax_Arena* self);

void
pax_arena_rewind(Pax_Arena* self, paxiword mark, paxiword offset);

#endif // PAX_CORE_MEMORY_ARENA_H
