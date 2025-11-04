#ifndef PAX_CORE_MEMORY_ARRAY_H
#define PAX_CORE_MEMORY_ARRAY_H

#include "./arena.h"

#define pax_array_make(type, memory, length) \
    pax_array_make_pure(memory, length, pax_size(type))

#define pax_array_create(arena, type, length) \
    pax_array_create_pure(arena, length, pax_size(type))

#define pax_array_insert(self, type, index, value, length) \
    pax_array_insert_pure(self, index, value, length, pax_size(type))

#define pax_array_remove(self, type, index, value, length) \
    pax_array_remove_pure(self, index, value, length, pax_size(type))

#define pax_array_peek(self, type, index, value, length) \
    pax_array_peek_pure(self, index, value, length, pax_size(type))

#define pax_array_peek_or_fail(self, type, index) \
    *pax_as(type*, pax_array_peek_pure_or_null(self, index, pax_size(type)))

#define pax_array_update(self, type, index, value, length) \
    pax_array_update_pure(self, index, value, length, pax_size(type))

typedef struct Pax_Array
{
    paxu8*   memory;
    paxiword length;
    paxiword stride;
    paxiword capacity;
}
Pax_Array;

Pax_Array
pax_array_make_pure(void* memory, paxiword length, paxiword stride);

Pax_Array
pax_array_create_pure(Pax_Arena* arena, paxiword length, paxiword stride);

Pax_Array
pax_array_copy(Pax_Arena* arena, Pax_Array* value);

void
pax_array_clear(Pax_Array* self);

void
pax_array_fill(Pax_Array* self);

paxiword
pax_array_elements(Pax_Array* self);

paxiword
pax_array_capacity(Pax_Array* self);

paxiword
pax_array_head(Pax_Array* self);

paxiword
pax_array_tail(Pax_Array* self);

paxb8
pax_array_is_empty(Pax_Array* self);

paxb8
pax_array_is_full(Pax_Array* self);

paxiword
pax_array_insert_pure(Pax_Array* self, paxiword index, void* memory, paxiword length, paxiword stride);

paxiword
pax_array_remove_pure(Pax_Array* self, paxiword index, void* memory, paxiword length, paxiword stride);

paxiword
pax_array_peek_pure(Pax_Array* self, paxiword index, void* memory, paxiword length, paxiword stride);

void*
pax_array_peek_pure_or_null(Pax_Array* self, paxiword index, paxiword stride);

paxiword
pax_array_update_pure(Pax_Array* self, paxiword index, void* memory, paxiword length, paxiword stride);

#endif // PAX_CORE_MEMORY_ARRAY_H
