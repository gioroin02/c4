#ifndef PX_WINDOWS_PROCESS_THREAD_H
#define PX_WINDOWS_PROCESS_THREAD_H

#include "import.h"

typedef struct PxWindowsThread PxWindowsThread;

PxWindowsThread*
pxWindowsThreadCreate(PxArena* arena, void* ctxt, void* proc);

void
pxWindowsThreadDestroy(PxWindowsThread* self);

void
pxWindowsThreadJoin(PxWindowsThread* self);

void
pxWindowsThreadDetach(PxWindowsThread* self);

#endif // PX_WINDOWS_PROCESS_THREAD_H
