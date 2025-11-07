#ifndef PAX_CORE_PROCESS_THREAD_POOL_C
#define PAX_CORE_PROCESS_THREAD_POOL_C

#include "./thread_pool.h"

static void
pax_worker_proc(Pax_Thread_Pool* pool)
{
    paxb8 active = 1;

    while (active != 0) {
        Pax_Worker_Data data = {0};

        pax_channel_remove(&pool->task_channel,
            Pax_Worker_Data, &data);

        Pax_Worker_Proc* proc =
            pax_as(Pax_Worker_Proc*, data.proc);

        if (data.proc != 0)
            proc(data.ctxt, data.arena);
        else
            active = 0;
    }
}

Pax_Thread_Pool*
pax_thread_pool_create(Pax_Arena *arena, paxiword threads, paxiword tasks)
{
    Pax_Thread_Pool temp = {
        .thread_list  = pax_array_create(arena, Pax_Thread, threads),
        .task_channel = pax_channel_create(arena, Pax_Worker_Data, tasks),
    };

    Pax_Thread_Pool* result = pax_arena_clone(arena, Pax_Thread_Pool, &temp, 1);

    if (result == 0) return 0;

    for (paxiword i = 0; i < pax_array_capacity(&result->thread_list); i += 1) {
        Pax_Thread thread =
            pax_thread_start(arena, result, &pax_worker_proc);

        pax_array_insert(&result->thread_list, Pax_Thread,
            pax_array_tail(&result->thread_list) + 1, &thread, 1);
    }

    return result;
}

void
pax_thread_pool_destroy(Pax_Thread_Pool* self)
{
    if (self == 0) return;

    for (paxiword i = 0; i < pax_array_capacity(&self->thread_list); i += 1) {
        Pax_Worker_Data task = {0};

        pax_channel_insert(&self->task_channel,
            Pax_Worker_Data, &task);
    }

    while (pax_array_elements(&self->thread_list) > 0) {
        Pax_Thread thread = 0;

        pax_array_remove(&self->thread_list, Pax_Thread,
            pax_array_tail(&self->thread_list), &thread, 1);

        pax_thread_wait(thread);
    }

    pax_channel_destroy(&self->task_channel);
}

paxb8
pax_thread_pool_delegate(Pax_Thread_Pool* self, Pax_Worker_Data data)
{
    if (data.proc == 0) return 0;

    return pax_channel_insert(&self->task_channel,
        Pax_Worker_Data, &data);
}

paxb8
pax_thread_pool_try_delegate(Pax_Thread_Pool* self, Pax_Worker_Data data)
{
    if (data.proc == 0) return 0;

    return pax_channel_try_insert(&self->task_channel,
        Pax_Worker_Data, &data);
}

#endif // PAX_CORE_PROCESS_THREAD_POOL_C
