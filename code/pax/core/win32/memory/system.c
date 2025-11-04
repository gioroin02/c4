#ifndef PAX_WIN32_MEMORY_SYSTEM_C
#define PAX_WIN32_MEMORY_SYSTEM_C

#include "./system.h"

#define NOMINMAX
#define NOGDI
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

paxiword
pax_win32_memory_page_size()
{
    SYSTEM_INFO info = {0};

    GetSystemInfo(&info);

    return pax_as(paxiword, info.dwPageSize);
}

Pax_Arena
pax_win32_memory_reserve(paxiword amount)
{
    paxiword stride = pax_win32_memory_page_size();
    void*    result = 0;

    if (amount <= 0 || stride > PAX_U32_MAX / amount)
        return (Pax_Arena) {0};

    paxiword length = amount * stride;

    result = VirtualAlloc(0, pax_as(DWORD, length),
        MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

    if (result == 0) return (Pax_Arena) {0};

    return pax_arena_make(result, length);
}

void
pax_win32_memory_release(Pax_Arena* arena)
{
    if (arena == 0 || arena->memory == 0)
        return;

    VirtualFree(arena->memory, 0, MEM_RELEASE);

    arena->memory   = 0;
    arena->length   = 0;
    arena->capacity = 0;
}

#endif // PAX_WIN32_MEMORY_SYSTEM_C
