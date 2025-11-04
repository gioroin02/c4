#ifndef PAX_CORE_STORAGE_PATH_H
#define PAX_CORE_STORAGE_PATH_H

#include "./import.h"

typedef Pax_Buffer8 Pax_Path;

Pax_Path
pax_path_create(Pax_Arena* arena, paxiword length);

paxiword
pax_path_insert_memory8(Pax_Path* self, paxu8* memory, paxiword length, Pax_String8 delim);

paxiword
pax_path_insert_string8(Pax_Path* self, Pax_String8 value, Pax_String8 delim);

paxiword
pax_path_remove_memory8(Pax_Path* self, paxu8* memory, paxiword length);

Pax_String8
pax_path_remove_string8(Pax_Path* self, Pax_Arena* arena);

Pax_String8
pax_string8_from_path(Pax_Arena* arena, Pax_Path* path, paxi32 delim);

Pax_String16
pax_string16_from_path(Pax_Arena* arena, Pax_Path* path, paxi32 delim);

Pax_String32
pax_string32_from_path(Pax_Arena* arena, Pax_Path* path, paxi32 delim);

#endif // PAX_CORE_STORAGE_PATH_H
