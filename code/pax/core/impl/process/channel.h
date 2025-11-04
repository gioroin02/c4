#ifndef PAX_CORE_PROCESS_CHANNEL_H
#define PAX_CORE_PROCESS_CHANNEL_H

#include "./synchro.h"

#define pax_channel_create(arena, type, amount) \
    pax_channel_create_pure(arena, amount, pax_size(type))

#define pax_channel_try_insert(self, type, value) \
    pax_channel_try_insert_pure(self, value, pax_size(type))

#define pax_channel_insert(self, type, value) \
    pax_channel_insert_pure(self, value, pax_size(type))

#define pax_channel_try_remove(self, type, value) \
    pax_channel_try_remove_pure(self, value, pax_size(type))

#define pax_channel_remove(self, type, value) \
    pax_channel_remove_pure(self, value, pax_size(type))

typedef struct Pax_Channel
{
    Pax_Cond cond_full;
    Pax_Cond cond_empty;

    Pax_Lock lock;

    Pax_Array_Ring items;
}
Pax_Channel;

Pax_Channel
pax_channel_create_pure(Pax_Arena* arena, paxiword amount, paxiword stride);

void
pax_channel_destroy(Pax_Channel* self);

paxb8
pax_channel_try_insert_pure(Pax_Channel* self, void* memory, paxiword stride);

paxb8
pax_channel_insert_pure(Pax_Channel* self, void* memory, paxiword stride);

paxb8
pax_channel_try_remove_pure(Pax_Channel* self, void* memory, paxiword stride);

paxb8
pax_channel_remove_pure(Pax_Channel* self, void* memory, paxiword stride);

#endif // PAX_CORE_PROCESS_CHANNEL_H
