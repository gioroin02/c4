#ifndef PX_CORE_PROCESS_THREAD_H
#define PX_CORE_PROCESS_THREAD_H

#include "import.h"

typedef void* PxThread;

typedef pxiword (PxThreadProc) (void*);

PxThread
pxThreadCreate(PxArena* arena, void* ctxt, void* proc);

void
pxThreadDestroy(PxThread self);

void
pxThreadJoin(PxThread self);

void
pxThreadDetach(PxThread self);

#endif // PX_CORE_PROCESS_THREAD_H
