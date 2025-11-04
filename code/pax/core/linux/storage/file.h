#ifndef PAX_LINUX_STORAGE_FILE_H
#define PAX_LINUX_STORAGE_FILE_H

#include "./import.h"

typedef struct Pax_Linux_File Pax_Linux_File;

/* Defaults */

Pax_Linux_File*
pax_linux_default_input(Pax_Arena* arena);

Pax_Linux_File*
pax_linux_default_output(Pax_Arena* arena);

Pax_Linux_File*
pax_linux_default_error(Pax_Arena* arena);

/* File */

Pax_Linux_File*
pax_linux_file_create(Pax_Arena* arena, Pax_String8 base, Pax_String8 name, Pax_File_Mode mode);

Pax_Linux_File*
pax_linux_file_replace(Pax_Arena* arena, Pax_String8 base, Pax_String8 name, Pax_File_Mode mode);

Pax_Linux_File*
pax_linux_file_open(Pax_Arena* arena, Pax_String8 base, Pax_String8 name, Pax_File_Mode mode);

void
pax_linux_file_close(Pax_Linux_File* self);

paxb8
pax_linux_file_destroy(Pax_Arena* arena, Pax_String8 base, Pax_String8 name);

paxiword
pax_linux_file_write(Pax_Linux_File* self, paxu8* memory, paxiword length);

paxiword
pax_linux_file_read(Pax_Linux_File* self, paxu8* memory, paxiword length);

#endif // PAX_LINUX_STORAGE_FILE_H
