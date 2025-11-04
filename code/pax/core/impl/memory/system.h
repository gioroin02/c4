#ifndef PAX_CORE_MEMORY_SYSTEM_H
#define PAX_CORE_MEMORY_SYSTEM_H

#include "./arena.h"

paxiword
pax_memory_page_size();

Pax_Arena
pax_memory_reserve(paxiword amount);

void
pax_memory_release(Pax_Arena* arena);

#endif // PAX_CORE_MEMORY_SYSTEM_H
