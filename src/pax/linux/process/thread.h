#ifndef PX_LINUX_PROCESS_THREAD_H
#define PX_LINUX_PROCESS_THREAD_H

#include "import.h"

typedef struct PxLinuxThread PxLinuxThread;

PxLinuxThread*
pxLinuxThreadCreate(PxArena* arena, void* ctxt, void* proc);

void
pxLinuxThreadDestroy(PxLinuxThread* self);

void
pxLinuxThreadJoin(PxLinuxThread* self);

void
pxLinuxThreadDetach(PxLinuxThread* self);

#endif // PX_LINUX_PROCESS_THREAD_H
