#ifndef PAX_CORE_MEMORY_SYSTEM_C
#define PAX_CORE_MEMORY_SYSTEM_C

#include "./system.h"

#if PAX_SYSTEM == PAX_SYSTEM_WINDOWS

    #include "../../win32/memory/system.c"

    #define __pax_memory_page_size__ pax_win32_memory_page_size
    #define __pax_memory_reserve__   pax_win32_memory_reserve
    #define __pax_memory_release__   pax_win32_memory_release

#elif PAX_SYSTEM == PAX_SYSTEM_LINUX

    #include "../../linux/memory/system.c"

    #define __pax_memory_page_size__ pax_linux_memory_page_size
    #define __pax_memory_reserve__   pax_linux_memory_reserve
    #define __pax_memory_release__   pax_linux_memory_release

#else

    #error "Unknown platform"

#endif

paxiword
pax_memory_page_size()
{
    return __pax_memory_page_size__();
}

Pax_Arena
pax_memory_reserve(paxiword amount)
{
    return __pax_memory_reserve__(amount);
}

void
pax_memory_release(Pax_Arena* arena)
{
    __pax_memory_release__(arena);
}

#endif // PAX_CORE_MEMORY_SYSTEM_C
