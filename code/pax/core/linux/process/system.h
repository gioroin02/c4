#ifndef PAX_LINUX_PROCESS_SYSTEM_H
#define PAX_LINUX_PROCESS_SYSTEM_H

#include "./import.h"

paxiword
pax_linux_process_core_amount();

void
pax_linux_current_thread_sleep(paxuword millis);

paxiword
pax_linux_current_thread_ident();

#endif // PAX_LINUX_PROCESS_SYSTEM_H
