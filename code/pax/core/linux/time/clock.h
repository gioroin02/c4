#ifndef PAX_LINUX_TIME_CLOCK_H
#define PAX_LINUX_TIME_CLOCK_H

#include "./import.h"

typedef struct Pax_Linux_Clock Pax_Linux_Clock;

Pax_Linux_Clock*
pax_linux_clock_create(Pax_Arena* arena);

paxf32
pax_linux_clock_elapsed(Pax_Linux_Clock* self);

#endif // PAX_LINUX_TIME_CLOCK_H
