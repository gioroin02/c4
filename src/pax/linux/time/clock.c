#ifndef PX_LINUX_TIME_CLOCK_C
#define PX_LINUX_TIME_CLOCK_C

#include "clock.h"

#define _POSIX_C_SOURCE 200809L

#include <unistd.h>
#include <time.h>

typedef struct timespec PxTimeSpec;

struct PxLinuxClock
{
    PxTimeSpec last;
    PxTimeSpec curr;
};

PxLinuxClock*
pxLinuxClockCreate(PxArena* arena)
{
    pxiword offset = pxArenaOffset(arena);

    PxLinuxClock* result =
        pxArenaReserve(arena, PxLinuxClock, 1);

    if (result != 0) {
        pxb8 state =
            clock_gettime(CLOCK_MONOTONIC, &result->curr);

        if (state != -1) return result;
    }

    pxArenaRewind(arena, offset);

    return 0;
}

pxf32
pxLinuxClockElapsed(PxLinuxClock* self)
{
    self->last = self->curr;

    clock_gettime(CLOCK_MONOTONIC, &self->curr);

    pxuword seconds  = self->curr.tv_sec  - self->last.tv_sec;
    pxuword nseconds = self->curr.tv_nsec - self->last.tv_nsec;

    return pxCast(pxf32, seconds + nseconds) / pxCast(pxf32, 1.0e9);
}

#endif // PX_LINUX_TIME_CLOCK_C
