#ifndef PAX_CORE_PROCESS_THREAD_POOL_C
#define PAX_CORE_PROCESS_THREAD_POOL_C

#include "./thread_pool.h"

typedef struct Pax_Thread_Delegate
{
    void* ctxt;
    void* proc;
}
Pax_Thread_Delegate;

static void
pax_worker_proc(Pax_Thread_Pool* pool)
{
    paxb8 active = 1;

    while (active != 0) {
        Pax_Thread_Delegate delegate = {0};

        pax_channel_remove(&pool->tasks, Pax_Thread_Delegate, &delegate);

        Pax_Thread_Delegate_Proc* proc =
            pax_as(Pax_Thread_Delegate_Proc*, delegate.proc);

        if (delegate.proc != 0)
            proc(delegate.ctxt);
        else
            active = 0;
    }
}

Pax_Thread_Pool*
pax_thread_pool_create(Pax_Arena *arena, paxiword threads, paxiword tasks)
{
    Pax_Thread_Pool temp = {
        .threads = pax_array_create(arena, Pax_Thread, threads),
        .tasks   = pax_channel_create(arena, Pax_Thread_Delegate, tasks),
    };

    Pax_Thread_Pool* result = pax_arena_clone(arena, Pax_Thread_Pool, &temp, 1);

    if (result == 0) return 0;

    for (paxiword i = 0; i < pax_array_capacity(&result->threads); i += 1) {
        Pax_Thread thread =
            pax_thread_start(arena, result, &pax_worker_proc);

        pax_array_insert(&result->threads, Pax_Thread,
            pax_array_tail(&result->threads) + 1, &thread, 1);
    }

    return result;
}

void
pax_thread_pool_destroy(Pax_Thread_Pool* self)
{
    if (self == 0) return;

    for (paxiword i = 0; i < pax_array_capacity(&self->threads); i += 1) {
        Pax_Thread_Delegate task = {0};

        pax_channel_insert(&self->tasks,
            Pax_Thread_Delegate, &task);
    }

    while (pax_array_elements(&self->threads) > 0) {
        Pax_Thread thread = 0;

        pax_array_remove(&self->threads, Pax_Thread,
            pax_array_tail(&self->threads), &thread, 1);

        pax_thread_wait(thread);
    }

    pax_channel_destroy(&self->tasks);
}

paxb8
pax_thread_pool_delegate(Pax_Thread_Pool* self, void* ctxt, void* proc)
{
    Pax_Thread_Delegate delegate = {
        .ctxt = ctxt,
        .proc = proc,
    };

    if (delegate.proc == 0) return 0;

    return pax_channel_insert(&self->tasks,
        Pax_Thread_Delegate, &delegate);
}

paxb8
pax_thread_pool_try_delegate(Pax_Thread_Pool* self, void* ctxt, void* proc)
{
    Pax_Thread_Delegate delegate = {
        .ctxt = ctxt,
        .proc = proc,
    };

    if (delegate.proc == 0) return 0;

    return pax_channel_try_insert(&self->tasks,
        Pax_Thread_Delegate, &delegate);
}

#endif // PAX_CORE_PROCESS_THREAD_POOL_C
