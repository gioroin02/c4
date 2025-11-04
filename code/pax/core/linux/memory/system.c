#ifndef PAX_LINUX_MEMORY_SYSTEM_C
#define PAX_LINUX_MEMORY_SYSTEM_C

#include "./system.h"

#define _DEFAULT_SOURCE

#include <unistd.h>
#include <errno.h>

#include <sys/mman.h>

paxiword
pax_linux_memory_page_size()
{
    return pax_as(paxiword, sysconf(_SC_PAGESIZE));
}

Pax_Arena
pax_linux_memory_reserve(paxiword amount)
{
    paxiword stride = pax_linux_memory_page_size();
    void*   result = 0;

    if (amount <= 0 || stride > PAX_U32_MAX / amount)
        return (Pax_Arena) {0};

    paxiword length = amount * stride;

    do {
        result = mmap(0, length, PROT_READ | PROT_WRITE,
            MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    } while (result == MAP_FAILED && errno == EINTR);

    if (result == MAP_FAILED) return (Pax_Arena) {0};

    return pax_arena_make(result, length);
}

void
pax_linux_memory_release(Pax_Arena* arena)
{
    if (arena == 0 || arena->memory == 0)
        return;

    paxiword result = 0;

    do {
        result = munmap(arena->memory, arena->length);
    } while (result == -1 && errno == EINTR);

    arena->memory   = 0;
    arena->length   = 0;
    arena->capacity = 0;
}

#endif // PAX_LINUX_MEMORY_SYSTEM_C
