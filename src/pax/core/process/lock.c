#ifndef PX_CORE_PROCESS_LOCK_C
#define PX_CORE_PROCESS_LOCK_C

#include "lock.h"

#if PX_SYSTEM == PX_SYSTEM_WINDOWS

    #include "../../windows/process/lock.c"

    #define __pxLockCreate__  pxWindowsLockCreate
    #define __pxLockDestroy__ pxWindowsLockDestroy
    #define __pxLockEnter__   pxWindowsLockEnter
    #define __pxLockLeave__   pxWindowsLockLeave

#elif PX_SYSTEM == PX_SYSTEM_LINUX

    #include "../../linux/process/lock.c"

    #define __pxLockCreate__  pxLinuxLockCreate
    #define __pxLockDestroy__ pxLinuxLockDestroy
    #define __pxLockEnter__   pxLinuxLockEnter
    #define __pxLockLeave__   pxLinuxLockLeave

#else

    #error "Unknown platform"

#endif

PxLock
pxLockCreate(PxArena* arena)
{
    return __pxLockCreate__(arena);
}

void
pxLockDestroy(PxLock self)
{
    __pxLockDestroy__(self);
}

void
pxLockEnter(PxLock self)
{
    return __pxLockEnter__(self);
}

void
pxLockLeave(PxLock self)
{
    return __pxLockLeave__(self);
}

#endif // PX_CORE_PROCESS_LOCK_C
