#ifndef PAX_WIN32_PROCESS_SYNCHRO_H
#define PAX_WIN32_PROCESS_SYNCHRO_H

#include "./import.h"

typedef struct Pax_Win32_Lock Pax_Win32_Lock;
typedef struct Pax_Win32_Cond Pax_Win32_Cond;

/* Windows Lock */

Pax_Win32_Lock*
pax_win32_lock_create(Pax_Arena* arena);

void
pax_win32_lock_destroy(Pax_Win32_Lock* self);

void
pax_win32_lock_enter(Pax_Win32_Lock* self);

void
pax_win32_lock_leave(Pax_Win32_Lock* self);

/* Windows Cond */

Pax_Win32_Cond*
pax_win32_cond_create(Pax_Arena* arena);

void
pax_win32_cond_destroy(Pax_Win32_Cond* self);

void
pax_win32_cond_sleep(Pax_Win32_Cond* self, Pax_Win32_Lock* lock);

void
pax_win32_cond_wake(Pax_Win32_Cond* self);

void
pax_win32_cond_wake_all(Pax_Win32_Cond* self);

#endif // PAX_WIN32_PROCESS_SYNCHRO_H
