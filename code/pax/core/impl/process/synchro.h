#ifndef PAX_CORE_PROCESS_SYNCHRO_H
#define PAX_CORE_PROCESS_SYNCHRO_H

#include "./import.h"

typedef void* Pax_Lock;
typedef void* Pax_Cond;

/* Lock */

Pax_Lock
pax_lock_create(Pax_Arena* arena);

void
pax_lock_destroy(Pax_Lock self);

void
pax_lock_enter(Pax_Lock self);

void
pax_lock_leave(Pax_Lock self);

/* Cond */

Pax_Cond
pax_cond_create(Pax_Arena* arena);

void
pax_cond_destroy(Pax_Cond self);

void
pax_cond_sleep(Pax_Cond self, Pax_Lock lock);

void
pax_cond_wake(Pax_Cond self);

void
pax_cond_wake_all(Pax_Cond self);

#endif // PAX_CORE_PROCESS_SYNCHRO_H
