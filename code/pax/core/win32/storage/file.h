#ifndef PAX_WIN32_STORAGE_FILE_H
#define PAX_WIN32_STORAGE_FILE_H

#include "./import.h"

typedef struct Pax_Win32_File Pax_Win32_File;

/* Defaults */

Pax_Win32_File*
pax_win32_default_input(Pax_Arena* arena);

Pax_Win32_File*
pax_win32_default_output(Pax_Arena* arena);

Pax_Win32_File*
pax_win32_default_error(Pax_Arena* arena);

/* File */

Pax_Win32_File*
pax_win32_file_create(Pax_Arena* arena, Pax_String8 base, Pax_String8 name, Pax_File_Mode mode);

Pax_Win32_File*
pax_win32_file_replace(Pax_Arena* arena, Pax_String8 base, Pax_String8 name, Pax_File_Mode mode);

Pax_Win32_File*
pax_win32_file_open(Pax_Arena* arena, Pax_String8 base, Pax_String8 name, Pax_File_Mode mode);

void
pax_win32_file_close(Pax_Win32_File* self);

paxb8
pax_win32_file_destroy(Pax_Arena* arena, Pax_String8 base, Pax_String8 name);

paxiword
pax_win32_file_write(Pax_Win32_File* self, paxu8* memory, paxiword length);

paxiword
pax_win32_file_read(Pax_Win32_File* self, paxu8* memory, paxiword length);

#endif // PAX_WIN32_STORAGE_FILE_H
