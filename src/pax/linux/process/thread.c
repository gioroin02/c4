#ifndef PX_LINUX_PROCESS_THREAD_C
#define PX_LINUX_PROCESS_THREAD_C

#include "thread.h"

#include <pthread.h>

struct PxLinuxThread
{
    pthread_t handle;
};

typedef void* (*PxLinuxThreadProc) (void*);

PxLinuxThread*
pxLinuxThreadCreate(PxArena* arena, void* ctxt, void* proc)
{
    pxiword offset = pxArenaOffset(arena);

    PxLinuxThread* result =
        pxArenaReserve(arena, PxLinuxThread, 1);

    if (result != 0) {
        PxLinuxThreadProc routine = px_as(PxLinuxThreadProc, proc);

        int state = pthread_create(
            &result->handle, 0, routine, ctxt);

        if (state == 0) return result;
    }

    pxArenaRewind(arena, offset);

    return 0;
}

void
pxLinuxThreadDestroy(PxLinuxThread* self)
{
    if (self == 0) return;

    pthread_cancel(self->handle);
    pthread_join(self->handle, 0);

    self->handle = (pthread_t) {0};
}

void
pxLinuxThreadJoin(PxLinuxThread* self)
{
    if (self != 0) pthread_join(self->handle, 0);
}

void
pxLinuxThreadDetach(PxLinuxThread* self)
{
    if (self != 0)
        pthread_detach(self->handle);

    self->handle = (pthread_t) {0};
}

#endif // PX_LINUX_PROCESS_THREAD_C
