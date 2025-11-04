#ifndef PAX_WIN32_PROCESS_THREAD_H
#define PAX_WIN32_PROCESS_THREAD_H

#include "./import.h"

typedef struct Pax_Win32_Thread Pax_Win32_Thread;

Pax_Win32_Thread*
pax_win32_thread_start(Pax_Arena* arena, void* ctxt, void* proc);

void
pax_win32_thread_wait(Pax_Win32_Thread* self);

void
pax_win32_thread_detach(Pax_Win32_Thread* self);

#endif // PAX_WIN32_PROCESS_THREAD_H
