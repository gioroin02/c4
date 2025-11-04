#ifndef PAX_LINUX_TIME_CLOCK_C
#define PAX_LINUX_TIME_CLOCK_C

#if !defined(_POSIX_C_SOURCE)

    #define _POSIX_C_SOURCE 200809L

#endif

#include "./clock.h"

#include <linux/time.h>

#include <unistd.h>

typedef struct timespec Pax_Time_Spec;

struct Pax_Linux_Clock
{
    Pax_Time_Spec last;
    Pax_Time_Spec curr;
};

Pax_Linux_Clock*
pax_linux_clock_create(Pax_Arena* arena)
{
    paxiword mark = pax_arena_tell(arena);

    Pax_Linux_Clock* result =
        pax_arena_reserve(arena, Pax_Linux_Clock, 1);

    if (result != 0) {
        paxiword state =
            clock_gettime(CLOCK_MONOTONIC, &result->curr);

        if (state != -1) return result;
    }

    pax_arena_rewind(arena, mark, 0);

    return 0;
}

paxf32
pax_linux_clock_elapsed(Pax_Linux_Clock* self)
{
    self->last = self->curr;

    clock_gettime(CLOCK_MONOTONIC, &self->curr);

    paxuword seconds  = self->curr.tv_sec  - self->last.tv_sec;
    paxuword nseconds = self->curr.tv_nsec - self->last.tv_nsec;

    return pax_as(paxf32, seconds + nseconds) / pax_as(paxf32, 1.0e9);
}

#endif // PAX_LINUX_TIME_CLOCK_C
