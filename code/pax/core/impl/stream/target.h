#ifndef PAX_CORE_STREAM_TARGET_H
#define PAX_CORE_STREAM_TARGET_H

#include "./import.h"

typedef struct Pax_Target
{
    void* ctxt;
    void* proc;
}
Pax_Target;

typedef paxiword (Pax_Target_Proc) (void*, paxu8*, paxiword);

Pax_Target*
pax_target_from_buffer8(Pax_Arena* arena, Pax_Buffer8* self);

paxiword
pax_target_write_memory8(Pax_Target* self, paxu8* memory, paxiword length);

paxiword
pax_target_write_buffer8(Pax_Target* self, Pax_Buffer8* value);

paxiword
pax_target_write_byte(Pax_Target* self, paxu8 value);

paxiword
pax_target_write_string8(Pax_Target* self, Pax_String8 value);

paxiword
pax_target_write_unicode(Pax_Target* self, paxi32 value);

#endif // PAX_CORE_STREAM_TARGET_H
