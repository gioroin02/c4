#ifndef PX_WINDOWS_PROCESS_SYSTEM_H
#define PX_WINDOWS_PROCESS_SYSTEM_H

#include "import.h"

pxiword
pxWindowsProcessCoreAmount();

void
pxWindowsCurrentThreadSleep(pxuword millis);

pxiword
pxWindowsCurrentThreadIdent();

#endif // PX_WINDOWS_PROCESS_SYSTEM_H
