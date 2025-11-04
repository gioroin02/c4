#ifndef PAX_WIN32_PROCESS_SYSTEM_H
#define PAX_WIN32_PROCESS_SYSTEM_H

#include "./import.h"

paxiword
pax_win32_process_core_amount();

void
pax_win32_current_thread_sleep(paxuword millis);

paxiword
pax_win32_current_thread_ident();

#endif // PAX_WIN32_PROCESS_SYSTEM_H
