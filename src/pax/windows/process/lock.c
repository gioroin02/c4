#ifndef PX_WINDOWS_PROCESS_LOCK_C
#define PX_WINDOWS_PROCESS_LOCK_C

#include "lock.h"

#define NOMINMAX
#define NOGDI
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

struct PxWindowsLock
{
    HANDLE handle;
};

PxWindowsLock*
pxWindowsLockCreate(PxArena* arena)
{
    pxiword offset = pxArenaOffset(arena);

    PxWindowsLock* result =
        pxArenaReserve(arena, PxWindowsLock, 1);

    if (result != 0) {
        result->handle = CreateMutex(0, 0, 0);

        if (result->handle != 0)
            return result;
    }

    pxArenaRewind(arena, offset);

    return 0;
}

void
pxWindowsLockDestroy(PxWindowsLock* self)
{
    if (self == 0) return;

    if (self->handle != 0)
        CloseHandle(self->handle);

    self->handle = 0;
}

void
pxWindowsLockEnter(PxWindowsLock* self)
{
    if (self != 0) WaitForSingleObject(self->handle, INFINITE);
}

void
pxWindowsLockLeave(PxWindowsLock* self)
{
    if (self != 0) ReleaseMutex(self->handle);
}

#endif // PX_WINDOWS_PROCESS_LOCK_C
