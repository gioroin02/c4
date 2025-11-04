#ifndef PAX_CORE_PROCESS_THREAD_H
#define PAX_CORE_PROCESS_THREAD_H

#include "./import.h"

typedef void* Pax_Thread;

Pax_Thread
pax_thread_start(Pax_Arena* arena, void* ctxt, void* proc);

void
pax_thread_wait(Pax_Thread self);

void
pax_thread_detach(Pax_Thread self);

#endif // PAX_CORE_PROCESS_THREAD_H
