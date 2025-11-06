#ifndef PAX_CORE_PROCESS_THREAD_POOL_H
#define PAX_CORE_PROCESS_THREAD_POOL_H

#include "thread.h"
#include "lock.h"

typedef struct Pax_Thread_Pool
{
    Pax_Thread* items;
}
Pax_Thread_Pool;

#endif // PAX_CORE_PROCESS_THREAD_POOL_H
