#ifndef PX_LINUX_TIME_CLOCK_H
#define PX_LINUX_TIME_CLOCK_H

#include "import.h"

typedef struct PxLinuxClock PxLinuxClock;

PxLinuxClock*
pxLinuxClockCreate(PxArena* arena);

pxf32
pxLinuxClockElapsed(PxLinuxClock* self);

#endif // PX_LINUX_TIME_CLOCK_H
