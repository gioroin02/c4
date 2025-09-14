#ifndef PX_CORE_TIME_CLOCK_H
#define PX_CORE_TIME_CLOCK_H

#include "import.h"

typedef void* PxClock;

PxClock
pxClockCreate(PxArena* arena);

pxf32
pxClockElapsed(PxClock self);

#endif // PX_CORE_TIME_CLOCK_H
