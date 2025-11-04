#ifndef PAX_WIN32_TIME_CLOCK_H
#define PAX_WIN32_TIME_CLOCK_H

#include "./import.h"

typedef struct Pax_Win32_Clock Pax_Win32_Clock;

Pax_Win32_Clock*
pax_win32_clock_create(Pax_Arena* arena);

paxf32
pax_win32_clock_elapsed(Pax_Win32_Clock* self);

#endif // PAX_WIN32_TIME_CLOCK_H
