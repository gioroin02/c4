#ifndef PAX_LINUX_PROCESS_SYNCHRO_C
#define PAX_LINUX_PROCESS_SYNCHRO_C

#include "./synchro.h"

#include <pthread.h>

struct Pax_Linux_Lock
{
    pthread_mutex_t handle;
};

struct Pax_Linux_Cond
{
    pthread_cond_t handle;
};

Pax_Linux_Lock*
pax_linux_lock_create(Pax_Arena* arena)
{
    paxiword mark = pax_arena_tell(arena);

    Pax_Linux_Lock* result =
        pax_arena_reserve(arena, Pax_Linux_Lock, 1);

    if (result != 0) {
        int state = pthread_mutex_init(&result->handle, 0);

        if (state == 0)
            return result;
    }

    pax_arena_rewind(arena, mark, 0);

    return 0;
}

void
pax_linux_lock_destroy(Pax_Linux_Lock* self)
{
    if (self == 0) return;

    pthread_mutex_destroy(&self->handle);

    self->handle = (pthread_mutex_t) {0};
}

void
pax_linux_lock_enter(Pax_Linux_Lock* self)
{
    pthread_mutex_lock(&self->handle);
}

void
pax_linux_lock_leave(Pax_Linux_Lock* self)
{
    pthread_mutex_unlock(&self->handle);
}

Pax_Linux_Cond*
pax_linux_cond_create(Pax_Arena* arena)
{
    paxiword mark = pax_arena_tell(arena);

    Pax_Linux_Cond* result =
        pax_arena_reserve(arena, Pax_Linux_Cond, 1);

    if (result != 0) {
        int state = pthread_cond_init(&result->handle, 0);

        if (state == 0)
            return result;
    }

    pax_arena_rewind(arena, mark, 0);

    return 0;
}

void
pax_linux_cond_destroy(Pax_Linux_Cond* self)
{
    if (self == 0) return;

    pthread_cond_destroy(&self->handle);

    self->handle = (pthread_cond_t) {0};
}

void
pax_linux_cond_sleep(Pax_Linux_Cond* self, Pax_Linux_Lock* lock)
{
    pthread_cond_wait(&self->handle, &lock->handle);
}

void
pax_linux_cond_wake(Pax_Linux_Cond* self)
{
    pthread_cond_signal(&self->handle);
}

void
pax_linux_cond_wake_all(Pax_Linux_Cond* self)
{
    pthread_cond_broadcast(&self->handle);
}

#endif // PAX_LINUX_PROCESS_SYNCHRO_C
