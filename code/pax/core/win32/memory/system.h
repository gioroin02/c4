#ifndef PAX_WIN32_MEMORY_SYSTEM_H
#define PAX_WIN32_MEMORY_SYSTEM_H

#include "./import.h"

paxiword
pax_win32_memory_page_size();

Pax_Arena
pax_win32_memory_reserve(paxiword amount);

void
pax_win32_memory_release(Pax_Arena* arena);

#endif // PAX_WIN32_MEMORY_SYSTEM_H
