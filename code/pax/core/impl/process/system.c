#ifndef PAX_CORE_PROCESS_SYSTEM_C
#define PAX_CORE_PROCESS_SYSTEM_C

#include "./system.h"

#if PAX_SYSTEM == PAX_SYSTEM_WINDOWS

    #include "../../win32/process/system.c"

    #define __pax_process_core_amount__  pax_win32_process_core_amount
    #define __pax_current_thread_sleep__ pax_win32_current_thread_sleep
    #define __pax_current_thread_ident__ pax_win32_current_thread_ident

#elif PAX_SYSTEM == PAX_SYSTEM_LINUX

    #include "../../linux/process/system.c"

    #define __pax_process_core_amount__  pax_linux_process_core_amount
    #define __pax_current_thread_sleep__ pax_linux_current_thread_sleep
    #define __pax_current_thread_ident__ pax_linux_current_thread_ident

#else

    #error "Unknown platform"

#endif

paxiword
pax_process_core_amount()
{
    return __pax_process_core_amount__();
}

void
pax_current_thread_sleep(paxuword millis)
{
    __pax_current_thread_sleep__(millis);
}

paxiword
pax_current_thread_ident()
{
    return __pax_current_thread_ident__();
}

#endif // PAX_CORE_PROCESS_SYSTEM_C
