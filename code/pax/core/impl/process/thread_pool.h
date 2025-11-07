#ifndef PAX_CORE_PROCESS_THREAD_POOL_H
#define PAX_CORE_PROCESS_THREAD_POOL_H

#include "./channel.h"
#include "./thread.h"

typedef struct Pax_Thread_Pool
{
    Pax_Array   thread_list;
    Pax_Channel task_channel;
}
Pax_Thread_Pool;

typedef struct Pax_Worker_Data
{
    Pax_Arena arena;

    void* ctxt;
    void* proc;
}
Pax_Worker_Data;

typedef void (Pax_Worker_Proc) (void*, Pax_Arena);

Pax_Thread_Pool*
pax_thread_pool_create(Pax_Arena* arena, paxiword threads, paxiword tasks);

void
pax_thread_pool_destroy(Pax_Thread_Pool* self);

paxb8
pax_thread_pool_delegate(Pax_Thread_Pool* self, Pax_Worker_Data data);

paxb8
pax_thread_pool_try_delegate(Pax_Thread_Pool* self, Pax_Worker_Data);

#endif // PAX_CORE_PROCESS_THREAD_POOL_H
