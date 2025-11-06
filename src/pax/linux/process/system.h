#ifndef PX_LINUX_PROCESS_SYSTEM_H
#define PX_LINUX_PROCESS_SYSTEM_H

#include "import.h"

pxiword
pxLinuxProcessCoreAmount();

void
pxLinuxCurrentThreadSleep(pxuword millis);

pxiword
pxLinuxCurrentThreadIdent();

#endif // PX_LINUX_PROCESS_SYSTEM_H
