#ifndef PAX_CORE_NETWORK_SYSTEM_C
#define PAX_CORE_NETWORK_SYSTEM_C

#include "./system.h"

#if PAX_SYSTEM == PAX_SYSTEM_WINDOWS

    #include "../../win32/network/system.c"

    #define __pax_network_load__   pax_win32_network_load
    #define __pax_network_unload__ pax_win32_network_unload

#elif PAX_SYSTEM == PAX_SYSTEM_LINUX

    #include "../../linux/network/system.c"

    #define __pax_network_load__   pax_linux_network_load
    #define __pax_network_unload__ pax_linux_network_unload

#else

    #error "Unknown platform"

#endif

paxb8
pax_network_load()
{
    return __pax_network_load__();
}

void
pax_network_unload()
{
    __pax_network_unload__();
}

#endif // PAX_CORE_NETWORK_SYSTEM_C
