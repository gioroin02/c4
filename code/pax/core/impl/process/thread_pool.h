#ifndef PAX_CORE_PROCESS_THREAD_POOL_H
#define PAX_CORE_PROCESS_THREAD_POOL_H

#include "./channel.h"
#include "./thread.h"

typedef struct Pax_Thread_Pool
{
    Pax_Array   threads;
    Pax_Channel tasks;
    Pax_Channel results;
}
Pax_Thread_Pool;

typedef void (Pax_Thread_Delegate_Proc) (void*);

Pax_Thread_Pool*
pax_thread_pool_create(Pax_Arena* arena, paxiword threads, paxiword tasks);

void
pax_thread_pool_destroy(Pax_Thread_Pool* self);

paxb8
pax_thread_pool_delegate(Pax_Thread_Pool* self, void* ctxt, void* proc);

paxb8
pax_thread_pool_try_delegate(Pax_Thread_Pool* self, void* ctxt, void* proc);

#endif // PAX_CORE_PROCESS_THREAD_POOL_H
