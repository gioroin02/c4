#ifndef PAX_CORE_TIME_CLOCK_C
#define PAX_CORE_TIME_CLOCK_C

#include "./clock.h"

#if PAX_SYSTEM == PAX_SYSTEM_WINDOWS

    #include "../../win32/time/clock.c"

    #define __pax_clock_create__  pax_win32_clock_create
    #define __pax_clock_elapsed__ pax_win32_clock_elapsed

#elif PAX_SYSTEM == PAX_SYSTEM_LINUX

    #include "../../linux/time/clock.c"

    #define __pax_clock_create__  pax_linux_clock_create
    #define __pax_clock_elapsed__ pax_linux_clock_elapsed

#else

    #error "Unknown platform"

#endif

Pax_Clock
pax_clock_create(Pax_Arena* arena)
{
    return __pax_clock_create__(arena);
}

paxf32
pax_clock_elapsed(Pax_Clock self)
{
    return __pax_clock_elapsed__(self);
}

#endif // PAX_CORE_TIME_CLOCK_C
