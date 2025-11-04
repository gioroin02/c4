#ifndef PAX_CORE_TIME_CLOCK_H
#define PAX_CORE_TIME_CLOCK_H

#include "./import.h"

typedef void* Pax_Clock;

Pax_Clock
pax_clock_create(Pax_Arena* arena);

paxf32
pax_clock_elapsed(Pax_Clock self);

#endif // PAX_CORE_TIME_CLOCK_H
