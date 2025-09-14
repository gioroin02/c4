#ifndef PX_WINDOWS_TIME_CLOCK_C
#define PX_WINDOWS_TIME_CLOCK_C

#include "clock.h"

#define NOMINMAX
#define NOGDI
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

struct PxWindowsClock
{
    LARGE_INTEGER freq;

    LARGE_INTEGER last;
    LARGE_INTEGER curr;
};

PxWindowsClock*
pxWindowsClockCreate(PxArena* arena)
{
    pxiword offset = pxArenaOffset(arena);

    PxWindowsClock* result =
        pxArenaReserve(arena, PxWindowsClock, 1);

    if (result != 0) {
        pxb8 state = QueryPerformanceFrequency(&result->freq);

        if (state != 0)
            state = QueryPerformanceCounter(&result->curr);

        if (state != 0) return result;
    }

    pxArenaRewind(arena, offset);

    return 0;
}

pxf32
pxWindowsClockElapsed(PxWindowsClock* self)
{
    self->last = self->curr;

    QueryPerformanceCounter(&self->curr);

    pxuword diff = self->curr.QuadPart - self->last.QuadPart;
    pxuword freq = self->freq.QuadPart;

    return pxCast(pxf32, diff) / pxCast(pxf32, freq);
}

#endif // PX_WINDOWS_TIME_CLOCK_C
