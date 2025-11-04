#ifndef PAX_LINUX_PROCESS_THREAD_H
#define PAX_LINUX_PROCESS_THREAD_H

#include "./import.h"

typedef struct Pax_Linux_Thread Pax_Linux_Thread;

Pax_Linux_Thread*
pax_linux_thread_start(Pax_Arena* arena, void* ctxt, void* proc);

void
pax_linux_thread_wait(Pax_Linux_Thread* self);

void
pax_linux_thread_detach(Pax_Linux_Thread* self);

#endif // PAX_LINUX_PROCESS_THREAD_H
