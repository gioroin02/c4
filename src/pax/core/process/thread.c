#ifndef PX_CORE_PROCESS_THREAD_C
#define PX_CORE_PROCESS_THREAD_C

#include "thread.h"

#if PX_SYSTEM == PX_SYSTEM_WINDOWS

    #include "../../windows/process/thread.c"

    #define __pxThreadCreate__  pxWindowsThreadCreate
    #define __pxThreadDestroy__ pxWindowsThreadDestroy
    #define __pxThreadJoin__    pxWindowsThreadJoin
    #define __pxThreadDetach__  pxWindowsThreadDetach

#elif PX_SYSTEM == PX_SYSTEM_LINUX

    #include "../../linux/process/thread.c"

    #define __pxThreadCreate__  pxLinuxThreadCreate
    #define __pxThreadDestroy__ pxLinuxThreadDestroy
    #define __pxThreadJoin__    pxLinuxThreadJoin
    #define __pxThreadDetach__  pxLinuxThreadDetach

#else

    #error "Unknown platform"

#endif


PxThread
pxThreadCreate(PxArena* arena, void* ctxt, void* proc)
{
    return __pxThreadCreate__(arena, ctxt, proc);
}

void
pxThreadDestroy(PxThread self)
{
    __pxThreadDestroy__(self);
}

void
pxThreadJoin(PxThread self)
{
    __pxThreadJoin__(self);
}

void
pxThreadDetach(PxThread self)
{
    __pxThreadDetach__(self);
}

#endif // PX_CORE_PROCESS_THREAD_C
