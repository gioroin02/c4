#ifndef PX_LINUX_MEMORY_SYSTEM_C
#define PX_LINUX_MEMORY_SYSTEM_C

#include "system.h"

#define _DEFAULT_SOURCE

#include <unistd.h>
#include <errno.h>

#include <sys/mman.h>

pxiword
pxLinuxMemoryPageSize()
{
    return px_as(pxiword, sysconf(_SC_PAGESIZE));
}

PxArena
pxLinuxMemoryReserve(pxiword amount)
{
    pxiword stride = pxLinuxMemoryPageSize();
    void*   result = 0;

    if (amount <= 0 || stride > PX_U32_MAX / amount)
        return (PxArena) {0};

    pxiword length = amount * stride;

    do {
        result = mmap(0, length, PROT_READ | PROT_WRITE,
            MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    } while (result == MAP_FAILED && errno == EINTR);

    if (result == MAP_FAILED) return (PxArena) {0};

    return pxArenaMake(result, length);
}

void
pxLinuxMemoryRelease(PxArena* arena)
{
    if (arena == 0 || arena->memory == 0)
        return;

    pxiword result = 0;

    do {
        result = munmap(arena->memory, arena->length);
    } while (result == -1 && errno == EINTR);

    arena->memory = 0;
    arena->length = 0;
    arena->offset = 0;
}

#endif // PX_LINUX_MEMORY_SYSTEM_C
