#ifndef PX_CORE_PROCESS_SYSTEM_H
#define PX_CORE_PROCESS_SYSTEM_H

#include "import.h"

pxiword
pxProcessCoreAmount();

void
pxCurrentThreadSleep(pxuword millis);

pxiword
pxCurrentThreadIdent();

#endif // PX_CORE_PROCESS_SYSTEM_H
