#ifndef PAX_CORE_STREAM_SOURCE_H
#define PAX_CORE_STREAM_SOURCE_H

#include "./import.h"

typedef struct Pax_Source
{
    void* ctxt;
    void* proc;
}
Pax_Source;

typedef paxiword (Pax_Source_Proc) (void*, paxu8*, paxiword);

Pax_Source*
pax_source_from_buffer8(Pax_Arena* arena, Pax_Buffer8* self);

paxiword
pax_source_read_memory8(Pax_Source* self, paxu8* memory, paxiword length);

paxiword
pax_source_read_buffer8(Pax_Source* self, Pax_Buffer8* buffer);

paxu8
pax_source_read_byte(Pax_Source* self);

Pax_String8
pax_source_read_string8(Pax_Source* self, Pax_Arena* arena, paxiword length);

paxiword
pax_source_read_unicode(Pax_Source* self, paxi32* value);

#endif // PAX_CORE_STREAM_SOURCE_H
