#ifndef PX_WINDOWS_PROCESS_THREAD_C
#define PX_WINDOWS_PROCESS_THREAD_C

#include "thread.h"

#define NOMINMAX
#define NOGDI
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

struct PxWindowsThread
{
    HANDLE handle;
    DWORD  ident;
};

typedef LPTHREAD_START_ROUTINE PxWindowsThreadProc;

PxWindowsThread*
pxWindowsThreadCreate(PxArena* arena, void* ctxt, void* proc)
{
    pxiword offset = pxArenaOffset(arena);

    PxWindowsThread* result =
        pxArenaReserve(arena, PxWindowsThread, 1);

    if (result != 0) {
        PxWindowsThreadProc routine = px_as(PxWindowsThreadProc, proc);

        result->handle = CreateThread(0, 0,
            routine, ctxt, 0, &result->ident);

        if (result->handle != 0)
            return result;
    }

    pxArenaRewind(arena, offset);

    return 0;
}

void
pxWindowsThreadDestroy(PxWindowsThread* self)
{
    DWORD state = 0;

    if (self == 0) return;

    if (self->handle != 0) {
        GetExitCodeThread(self->handle, &state);

        if (state == STILL_ACTIVE)
            TerminateThread(self->handle, 0);

        CloseHandle(self->handle);
    }

    self->handle = 0;
    self->ident  = 0;
}

void
pxWindowsThreadJoin(PxWindowsThread* self)
{
    WaitForSingleObject(self->handle, INFINITE);
}

void
pxWindowsThreadDetach(PxWindowsThread* self)
{
    if (self->handle != 0)
        CloseHandle(self->handle);

    self->handle = 0;
}

#endif // PX_WINDOWS_PROCESS_THREAD_C
