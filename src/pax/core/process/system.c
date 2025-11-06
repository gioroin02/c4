#ifndef PX_CORE_PROCESS_SYSTEM_C
#define PX_CORE_PROCESS_SYSTEM_C

#include "system.h"

#if PX_SYSTEM == PX_SYSTEM_WINDOWS

    #include "../../windows/process/system.c"

    #define __pxProcessCoreAmount__  pxWindowsProcessCoreAmount
    #define __pxCurrentThreadSleep__ pxWindowsCurrentThreadSleep
    #define __pxCurrentThreadIdent__ pxWindowsCurrentThreadIdent

#elif PX_SYSTEM == PX_SYSTEM_LINUX

    #include "../../linux/process/system.c"

    #define __pxProcessCoreAmount__  pxLinuxProcessCoreAmount
    #define __pxCurrentThreadSleep__ pxLinuxCurrentThreadSleep
    #define __pxCurrentThreadIdent__ pxLinuxCurrentThreadIdent

#else

    #error "Unknown platform"

#endif

pxiword
pxProcessCoreAmount()
{
    return __pxProcessCoreAmount__();
}

void
pxCurrentThreadSleep(pxuword millis)
{
    __pxCurrentThreadSleep__(millis);
}

pxiword
pxCurrentThreadIdent()
{
    return __pxCurrentThreadIdent__();
}

#endif // PX_CORE_PROCESS_SYSTEM_C
