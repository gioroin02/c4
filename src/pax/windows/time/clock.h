#ifndef PX_WINDOWS_TIME_CLOCK_H
#define PX_WINDOWS_TIME_CLOCK_H

#include "import.h"

typedef struct PxWindowsClock PxWindowsClock;

PxWindowsClock*
pxWindowsClockCreate(PxArena* arena);

pxf32
pxWindowsClockElapsed(PxWindowsClock* self);

#endif // PX_WINDOWS_TIME_CLOCK_H
