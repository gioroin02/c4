#ifndef PAX_LINUX_CONSOLE_CONSOLE_H
#define PAX_LINUX_CONSOLE_CONSOLE_H

#include "./import.h"

typedef struct Pax_Linux_Console Pax_Linux_Console;

Pax_Linux_Console*
pax_linux_console_create(Pax_Arena* arena);

void
pax_linux_console_destroy(Pax_Linux_Console* self);

paxb8
pax_linux_console_mode_apply(Pax_Linux_Console* self, Pax_Console_Mode mode);

Pax_Console_Mode
pax_linux_console_mode_query(Pax_Linux_Console* self);

paxiword
pax_linux_console_write(Pax_Linux_Console* self, paxu8* memory, paxiword length);

paxiword
pax_linux_console_read(Pax_Linux_Console* self, paxu8* memory, paxiword length);

#endif // PAX_LINUX_CONSOLE_CONSOLE_H
