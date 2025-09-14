#ifndef PX_CORE_TIME_CLOCK_C
#define PX_CORE_TIME_CLOCK_C

#include "clock.h"

#if PX_SYSTEM == PX_SYSTEM_WINDOWS

    #include "../../windows/time/clock.c"

    #define __pxClockCreate__  pxWindowsClockCreate
    #define __pxClockElapsed__ pxWindowsClockElapsed

#elif PX_SYSTEM == PX_SYSTEM_LINUX

    #include "../../linux/time/clock.c"

    #define __pxClockCreate__  pxLinuxClockCreate
    #define __pxClockElapsed__ pxLinuxClockElapsed

#else

    #error "Unknown platform"

#endif

PxClock
pxClockCreate(PxArena* arena)
{
    return __pxClockCreate__(arena);
}

pxf32
pxClockElapsed(PxClock self)
{
    return __pxClockElapsed__(self);
}

#endif // PX_CORE_TIME_CLOCK_C
