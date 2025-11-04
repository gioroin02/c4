#ifndef PAX_LINUX_PROCESS_SYNCHRO_H
#define PAX_LINUX_PROCESS_SYNCHRO_H

#include "./import.h"

typedef struct Pax_Linux_Lock Pax_Linux_Lock;
typedef struct Pax_Linux_Cond Pax_Linux_Cond;

/* Linux Lock */

Pax_Linux_Lock*
pax_linux_lock_create(Pax_Arena* arena);

void
pax_linux_lock_destroy(Pax_Linux_Lock* self);

void
pax_linux_lock_enter(Pax_Linux_Lock* self);

void
pax_linux_lock_leave(Pax_Linux_Lock* self);

/* Linux Cond */

Pax_Linux_Cond*
pax_linux_cond_create(Pax_Arena* arena);

void
pax_linux_cond_destroy(Pax_Linux_Cond* self);

void
pax_linux_cond_sleep(Pax_Linux_Cond* self, Pax_Linux_Lock* lock);

void
pax_linux_cond_wake(Pax_Linux_Cond* self);

void
pax_linux_cond_wake_all(Pax_Linux_Cond* self);

#endif // PAX_LINUX_PROCESS_SYNCHRO_H
