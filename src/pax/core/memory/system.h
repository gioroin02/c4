#ifndef PX_CORE_MEMORY_SYSTEM_H
#define PX_CORE_MEMORY_SYSTEM_H

#include "import.h"

pxiword
pxMemoryPageSize();

PxArena
pxMemoryReserve(pxiword amount);

void
pxMemoryRelease(PxArena* arena);

#endif // PX_CORE_MEMORY_SYSTEM_H
