#ifndef PX_LINUX_PROCESS_LOCK_C
#define PX_LINUX_PROCESS_LOCK_C

#include "lock.h"

#include <pthread.h>

typedef pthread_mutex_t PThreadMutex;

struct PxLinuxLock
{
    PThreadMutex handle;
};

PxLinuxLock*
pxLinuxLockCreate(PxArena* arena)
{
    pxiword offset = pxArenaOffset(arena);

    PxLinuxLock* result =
        pxArenaReserve(arena, PxLinuxLock, 1);

    if (result != 0) {
        int state = pthread_mutex_init(&result->handle, 0);

        if (state == 0)
            return result;
    }

    pxArenaRewind(arena, offset);

    return 0;
}

void
pxLinuxLockDestroy(PxLinuxLock* self)
{
    if (self == 0) return;

    pthread_mutex_destroy(&self->handle);

    self->handle = (PThreadMutex) {0};
}

void
pxLinuxLockEnter(PxLinuxLock* self)
{
    if (self != 0) pthread_mutex_lock(&self->handle);
}

void
pxLinuxLockLeave(PxLinuxLock* self)
{
    if (self != 0) pthread_mutex_unlock(&self->handle);
}

#endif // PX_LINUX_PROCESS_LOCK_C
