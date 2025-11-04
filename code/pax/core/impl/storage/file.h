#ifndef PAX_CORE_STORAGE_FILE_H
#define PAX_CORE_STORAGE_FILE_H

#include "./attrib.h"

typedef void* Pax_File;

/* Defaults */

Pax_File
pax_default_input(Pax_Arena* arena);

Pax_File
pax_default_output(Pax_Arena* arena);

Pax_File
pax_default_error(Pax_Arena* arena);

/* File */

Pax_File
pax_file_create(Pax_Arena* arena, Pax_String8 base, Pax_String8 name, Pax_File_Mode mode);

Pax_File
pax_file_replace(Pax_Arena* arena, Pax_String8 base, Pax_String8 name, Pax_File_Mode mode);

Pax_File
pax_file_open(Pax_Arena* arena, Pax_String8 base, Pax_String8 name, Pax_File_Mode mode);

void
pax_file_close(Pax_File self);

paxb8
pax_file_destroy(Pax_Arena* arena, Pax_String8 base, Pax_String8 name);

paxiword
pax_file_write(Pax_File self, paxu8* memory, paxiword length);

paxiword
pax_file_read(Pax_File self, paxu8* memory, paxiword length);

Pax_Source*
pax_source_from_file(Pax_Arena* arena, Pax_File self);

Pax_Target*
pax_target_from_file(Pax_Arena* arena, Pax_File self);

#endif // PAX_CORE_STORAGE_FILE_H
