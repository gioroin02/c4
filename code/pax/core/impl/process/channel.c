#ifndef PAX_CORE_PROCESS_CHANNEL_C
#define PAX_CORE_PROCESS_CHANNEL_C

#include "./channel.h"

Pax_Channel
pax_channel_create_pure(Pax_Arena* arena, paxiword amount, paxiword stride)
{
    Pax_Channel result = {
        .cond_full  = pax_cond_create(arena),
        .cond_empty = pax_cond_create(arena),
        .lock       = pax_lock_create(arena),

        .items = pax_array_ring_create_pure(arena, amount, stride),
    };

    return result;
}

void
pax_channel_destroy(Pax_Channel* self)
{
    if (self == 0) return;

    if (self->cond_full  != 0) pax_cond_destroy(self->cond_full);
    if (self->cond_empty != 0) pax_cond_destroy(self->cond_empty);

    if (self->lock != 0) pax_lock_destroy(self->lock);
}

paxb8
pax_channel_try_insert_pure(Pax_Channel* self, void* memory, paxiword stride)
{
    paxb8 state = 0;

    pax_lock_enter(self->lock);

    if (pax_array_ring_is_full(&self->items) == 0) {
        state = pax_array_ring_insert_tail_pure(
            &self->items, memory, 1, stride);
    }

    pax_lock_leave(self->lock);

    if (state != 0)
        pax_cond_wake(self->cond_empty);

    return state;
}

paxb8
pax_channel_insert_pure(Pax_Channel* self, void* memory, paxiword stride)
{
    paxb8 state = 0;

    pax_lock_enter(self->lock);

    while (pax_array_ring_is_full(&self->items) != 0)
        pax_cond_sleep(self->cond_full, self->lock);

    state = pax_array_ring_insert_tail_pure(
        &self->items, memory, 1, stride);

    pax_lock_leave(self->lock);

    if (state != 0)
        pax_cond_wake(self->cond_empty);

    return state;
}

paxb8
pax_channel_try_remove_pure(Pax_Channel* self, void* memory, paxiword stride)
{
    paxb8 state = 0;

    pax_lock_enter(self->lock);

    if (pax_array_ring_is_empty(&self->items) == 0) {
        state = pax_array_ring_remove_head_pure(
            &self->items, memory, 1, stride);
    }

    pax_lock_leave(self->lock);

    if (state != 0)
        pax_cond_wake(self->cond_full);

    return state;
}

paxb8
pax_channel_remove_pure(Pax_Channel* self, void* memory, paxiword stride)
{
    paxb8 state = 0;

    pax_lock_enter(self->lock);

    while (pax_array_ring_is_empty(&self->items) != 0)
        pax_cond_sleep(self->cond_empty, self->lock);

    state = pax_array_ring_remove_head_pure(
        &self->items, memory, 1, stride);

    pax_lock_leave(self->lock);

    if (state != 0)
        pax_cond_wake(self->cond_full);

    return state;
}

#endif // PAX_CORE_PROCESS_CHANNEL_C
