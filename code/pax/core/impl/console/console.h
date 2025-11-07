#ifndef PAX_CORE_CONSOLE_CONSOLE_H
#define PAX_CORE_CONSOLE_CONSOLE_H

#include "./mode.h"

typedef void* Pax_Console;

Pax_Console
pax_console_create(Pax_Arena* arena);

void
pax_console_destroy(Pax_Console self);

paxb8
pax_console_mode_apply(Pax_Console self, Pax_Console_Mode mode);

Pax_Console_Mode
pax_console_mode_query(Pax_Console self);

paxiword
pax_console_write(Pax_Console self, paxu8* memory, paxiword length);

paxiword
pax_console_read(Pax_Console self, paxu8* memory, paxiword length);

paxiword
pax_console_poll(Pax_Console self, paxu8* memory, paxiword length);

Pax_Source*
pax_source_from_console(Pax_Arena* arena, Pax_Console self);

Pax_Target*
pax_target_from_console(Pax_Arena* arena, Pax_Console self);

#endif // PAX_CORE_CONSOLE_CONSOLE_H
