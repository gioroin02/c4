#ifndef PAX_CORE_PROCESS_THREAD_C
#define PAX_CORE_PROCESS_THREAD_C

#include "./thread.h"

#if PAX_SYSTEM == PAX_SYSTEM_WINDOWS

    #include "../../win32/process/thread.c"

    #define __pax_thread_start__  pax_win32_thread_start
    #define __pax_thread_wait__   pax_win32_thread_wait
    #define __pax_thread_detach__ pax_win32_thread_detach

#elif PAX_SYSTEM == PAX_SYSTEM_LINUX

    #include "../../linux/process/thread.c"

    #define __pax_thread_start__  pax_linux_thread_start
    #define __pax_thread_wait__   pax_linux_thread_wait
    #define __pax_thread_detach__ pax_linux_thread_detach

#else

    #error "Unknown platform"

#endif

Pax_Thread
pax_thread_start(Pax_Arena* arena, void* ctxt, void* proc)
{
    return __pax_thread_start__(arena, ctxt, proc);
}

void
pax_thread_wait(Pax_Thread self)
{
    __pax_thread_wait__(self);
}

void
pax_thread_detach(Pax_Thread self)
{
    __pax_thread_detach__(self);
}

#endif // PAX_CORE_PROCESS_THREAD_C
