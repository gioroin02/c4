#ifndef PAX_CORE_STORAGE_DIRECTORY_H
#define PAX_CORE_STORAGE_DIRECTORY_H

#include "./path.h"

paxiword
pax_current_directory_memory8(Pax_Arena* arena, paxu8* memory, paxiword length);

Pax_String8
pax_current_directory(Pax_Arena* arena, paxiword length);

#endif // PAX_CORE_STORAGE_DIRECTORY_H
