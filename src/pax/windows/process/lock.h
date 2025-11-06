#ifndef PX_WINDOWS_PROCESS_LOCK_H
#define PX_WINDOWS_PROCESS_LOCK_H

#include "import.h"

typedef struct PxWindowsLock PxWindowsLock;

PxWindowsLock*
pxWindowsLockCreate(PxArena* arena);

void
pxWindowsLockDestroy(PxWindowsLock* self);

void
pxWindowsLockEnter(PxWindowsLock* self);

void
pxWindowsLockLeave(PxWindowsLock* self);

#endif // PX_WINDOWS_PROCESS_LOCK_H
