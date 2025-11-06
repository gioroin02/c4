#ifndef PX_CORE_PROCESS_LOCK_H
#define PX_CORE_PROCESS_LOCK_H

#include "import.h"

typedef void* PxLock;

PxLock
pxLockCreate(PxArena* arena);

void
pxLockDestroy(PxLock self);

void
pxLockEnter(PxLock self);

void
pxLockLeave(PxLock self);

#endif // PX_CORE_PROCESS_LOCK_H
