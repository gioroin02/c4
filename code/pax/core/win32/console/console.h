#ifndef PAX_WIN32_CONSOLE_CONSOLE_H
#define PAX_WIN32_CONSOLE_CONSOLE_H

#include "./import.h"

typedef struct Pax_Win32_Console Pax_Win32_Console;

Pax_Win32_Console*
pax_win32_console_create(Pax_Arena* arena);

void
pax_win32_console_destroy(Pax_Win32_Console* self);

paxb8
pax_win32_console_mode_apply(Pax_Win32_Console* self, Pax_Console_Mode mode);

Pax_Console_Mode
pax_win32_console_mode_query(Pax_Win32_Console* self);

paxiword
pax_win32_console_write(Pax_Win32_Console* self, paxu8* memory, paxiword length);

paxiword
pax_win32_console_read(Pax_Win32_Console* self, paxu8* memory, paxiword length);

#endif // PAX_WIN32_CONSOLE_CONSOLE_H
