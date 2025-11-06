#ifndef PX_WINDOWS_PROCESS_SYSTEM_C
#define PX_WINDOWS_PROCESS_SYSTEM_C

#include "system.h"

#define NOMINMAX
#define NOGDI
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

pxiword
pxWindowsProcessCoreAmount()
{
    SYSTEM_INFO info = {};

    GetSystemInfo(&info);

    return px_as(pxiword, info.dwNumberOfProcessors);
}

void
pxWindowsCurrentThreadSleep(pxuword millis)
{
    Sleep(millis);
}

pxiword
pxWindowsCurrentThreadIdent()
{
    return px_as(pxiword, GetCurrentThreadId());
}

#endif // PX_WINDOWS_PROCESS_SYSTEM_C
