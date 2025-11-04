#ifndef PAX_LINUX_MEMORY_SYSTEM_H
#define PAX_LINUX_MEMORY_SYSTEM_H

#include "./import.h"

paxiword
pax_linux_memory_page_size();

Pax_Arena
pax_linux_memory_reserve(paxiword amount);

void
pax_linux_memory_release(Pax_Arena* arena);

#endif // PAX_LINUX_MEMORY_SYSTEM_H
