#ifndef PX_LINUX_PROCESS_LOCK_H
#define PX_LINUX_PROCESS_LOCK_H

#include "import.h"

typedef struct PxLinuxLock PxLinuxLock;

PxLinuxLock*
pxLinuxLockCreate(PxArena* arena);

void
pxLinuxLockDestroy(PxLinuxLock* self);

void
pxLinuxLockEnter(PxLinuxLock* self);

void
pxLinuxLockLeave(PxLinuxLock* self);

#endif // PX_LINUX_PROCESS_LOCK_H
