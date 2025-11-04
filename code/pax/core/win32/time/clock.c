#ifndef PAX_WIN32_TIME_CLOCK_C
#define PAX_WIN32_TIME_CLOCK_C

#include "./clock.h"

#define NOMINMAX
#define NOGDI
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

struct Pax_Win32_Clock
{
    LARGE_INTEGER freq;

    LARGE_INTEGER last;
    LARGE_INTEGER curr;
};

Pax_Win32_Clock*
pax_win32_clock_create(Pax_Arena* arena)
{
    paxiword mark = pax_arena_tell(arena);

    Pax_Win32_Clock* result =
        pax_arena_reserve(arena, Pax_Win32_Clock, 1);

    if (result != 0) {
        paxb8 state = QueryPerformanceFrequency(&result->freq);

        if (state != 0)
            state = QueryPerformanceCounter(&result->curr);

        if (state != 0) return result;
    }

    pax_arena_rewind(arena, mark, 0);

    return 0;
}

paxf32
pax_win32_clock_elapsed(Pax_Win32_Clock* self)
{
    self->last = self->curr;

    QueryPerformanceCounter(&self->curr);

    paxuword diff = self->curr.QuadPart - self->last.QuadPart;
    paxuword freq = self->freq.QuadPart;

    return pax_as(paxf32, diff) / pax_as(paxf32, freq);
}

#endif // PAX_WIN32_TIME_CLOCK_C
