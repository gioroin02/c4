#ifndef PAX_LINUX_PROCESS_THREAD_C
#define PAX_LINUX_PROCESS_THREAD_C

#include "./thread.h"

#include <pthread.h>

struct Pax_Linux_Thread
{
    pthread_t handle;
};

typedef void* (*Pax_Linux_Thread_Proc) (void*);

Pax_Linux_Thread*
pax_linux_thread_start(Pax_Arena* arena, void* ctxt, void* proc)
{
    paxiword mark = pax_arena_tell(arena);

    Pax_Linux_Thread* result =
        pax_arena_reserve(arena, Pax_Linux_Thread, 1);

    if (result != 0) {
        Pax_Linux_Thread_Proc routine =
            pax_as(Pax_Linux_Thread_Proc, proc);

        int state = pthread_create(&result->handle,
            0, routine, ctxt);

        if (state == 0) return result;
    }

    pax_arena_rewind(arena, mark, 0);

    return 0;
}

void
pax_linux_thread_wait(Pax_Linux_Thread* self)
{
    if (self == 0) return;

    pthread_join(self->handle, 0);

    self->handle = (pthread_t) {0};
}

void
pax_linux_thread_detach(Pax_Linux_Thread* self)
{
    if (self != 0)
        pthread_detach(self->handle);

    self->handle = (pthread_t) {0};
}

#endif // PAX_LINUX_PROCESS_THREAD_C
