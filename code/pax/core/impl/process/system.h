#ifndef PAX_CORE_PROCESS_SYSTEM_H
#define PAX_CORE_PROCESS_SYSTEM_H

#include "./import.h"

paxiword
pax_process_core_amount();

void
pax_current_thread_sleep(paxuword millis);

paxiword
pax_current_thread_ident();

#endif // PAX_CORE_PROCESS_SYSTEM_H
