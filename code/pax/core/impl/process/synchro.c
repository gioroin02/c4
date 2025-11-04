#ifndef PAX_CORE_PROCESS_SYNCHRO_C
#define PAX_CORE_PROCESS_SYNCHRO_C

#include "./synchro.h"

#if PAX_SYSTEM == PAX_SYSTEM_WINDOWS

    #include "../../win32/process/synchro.c"

    #define __pax_lock_create__  pax_win32_lock_create
    #define __pax_lock_destroy__ pax_win32_lock_destroy
    #define __pax_lock_enter__   pax_win32_lock_enter
    #define __pax_lock_leave__   pax_win32_lock_leave

    #define __pax_cond_create__    pax_win32_cond_create
    #define __pax_cond_destroy__   pax_win32_cond_destroy
    #define __pax_cond_sleep__     pax_win32_cond_sleep
    #define __pax_cond_wake__      pax_win32_cond_wake
    #define __pax_cond_wake_all__  pax_win32_cond_wake_all

#elif PAX_SYSTEM == PAX_SYSTEM_LINUX

    #include "../../linux/process/synchro.c"

    #define __pax_lock_create__  pax_linux_lock_create
    #define __pax_lock_destroy__ pax_linux_lock_destroy
    #define __pax_lock_enter__   pax_linux_lock_enter
    #define __pax_lock_leave__   pax_linux_lock_leave

    #define __pax_cond_create__    pax_linux_cond_create
    #define __pax_cond_destroy__   pax_linux_cond_destroy
    #define __pax_cond_sleep__     pax_linux_cond_sleep
    #define __pax_cond_wake__      pax_linux_cond_wake
    #define __pax_cond_wake_all__  pax_linux_cond_wake_all

#else

    #error "Unknown platform"

#endif

Pax_Lock
pax_lock_create(Pax_Arena* arena)
{
    return __pax_lock_create__(arena);
}

void
pax_lock_destroy(Pax_Lock self)
{
    __pax_lock_destroy__(self);
}

void
pax_lock_enter(Pax_Lock self)
{
    __pax_lock_enter__(self);
}

void
pax_lock_leave(Pax_Lock self)
{
    __pax_lock_leave__(self);
}

Pax_Cond
pax_cond_create(Pax_Arena* arena)
{
    return __pax_cond_create__(arena);
}

void
pax_cond_destroy(Pax_Cond self)
{
    __pax_cond_destroy__(self);
}

void
pax_cond_sleep(Pax_Cond self, Pax_Lock lock)
{
    __pax_cond_sleep__(self, lock);
}

void
pax_cond_wake(Pax_Cond self)
{
    __pax_cond_wake__(self);
}

void
pax_cond_wake_all(Pax_Cond self)
{
    __pax_cond_wake_all__(self);
}

#endif // PAX_CORE_PROCESS_SYNCHRO_C
