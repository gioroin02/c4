#ifndef PX_WINDOWS_MEMORY_SYSTEM_C
#define PX_WINDOWS_MEMORY_SYSTEM_C

#include "system.h"

#define NOMINMAX
#define NOGDI
#define WIN32_LEAN_AND_MEAN

#include  <windows.h>

pxiword
pxWindowsMemoryPageSize()
{
    SYSTEM_INFO info = {0};

    GetSystemInfo(&info);

    return px_as(pxiword, info.dwPageSize);
}

PxArena
pxWindowsMemoryReserve(pxiword amount)
{
    pxiword stride = pxWindowsMemoryPageSize();
    void*   result = 0;

    if (amount <= 0 || stride > PX_U32_MAX / amount)
        return (PxArena) {0};

    pxiword length = amount * stride;

    result = VirtualAlloc(0, px_as(DWORD, length),
        MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

    if (result == 0) return (PxArena) {0};

    return pxArenaMake(result, length);
}

void
pxWindowsMemoryRelease(PxArena* arena)
{
    if (arena == 0 || arena->memory == 0)
        return;

    VirtualFree(arena->memory, 0, MEM_RELEASE);

    arena->memory = 0;
    arena->length = 0;
    arena->offset = 0;
}

#endif // PX_WINDOWS_MEMORY_SYSTEM_C
