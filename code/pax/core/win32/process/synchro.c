#ifndef PAX_WIN32_PROCESS_SYNCHRO_C
#define PAX_WIN32_PROCESS_SYNCHRO_C

#include "./synchro.h"

#define NOMINMAX
#define NOGDI
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

struct Pax_Win32_Lock
{
    CRITICAL_SECTION handle;
};

struct Pax_Win32_Cond
{
    CONDITION_VARIABLE handle;
};

Pax_Win32_Lock*
pax_win32_lock_create(Pax_Arena* arena)
{
    Pax_Win32_Lock* result =
        pax_arena_reserve(arena, Pax_Win32_Lock, 1);

    if (result != 0)
        InitializeCriticalSection(&result->handle);

    return result;
}

void
pax_win32_lock_destroy(Pax_Win32_Lock* self)
{
    if (self != 0)
        DeleteCriticalSection(&self->handle);
}

void
pax_win32_lock_enter(Pax_Win32_Lock* self)
{
    EnterCriticalSection(&self->handle);
}

void
pax_win32_lock_leave(Pax_Win32_Lock* self)
{
    LeaveCriticalSection(&self->handle);
}

Pax_Win32_Cond*
pax_win32_cond_create(Pax_Arena* arena)
{
    Pax_Win32_Cond* result =
        pax_arena_reserve(arena, Pax_Win32_Cond, 1);

    if (result != 0)
        InitializeConditionVariable(&result->handle);

    return result;
}

void
pax_win32_cond_destroy(Pax_Win32_Cond* self)
{
    // Empty...
}

void
pax_win32_cond_sleep(Pax_Win32_Cond* self, Pax_Win32_Lock* lock)
{
    SleepConditionVariableCS(&self->handle, &lock->handle, INFINITE);
}

void
pax_win32_cond_wake(Pax_Win32_Cond* self)
{
    WakeConditionVariable(&self->handle);
}

void
pax_win32_cond_wake_all(Pax_Win32_Cond* self)
{
    WakeAllConditionVariable(&self->handle);
}

#endif // PAX_WIN32_PROCESS_SYNCHRO_C
