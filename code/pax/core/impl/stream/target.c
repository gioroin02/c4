#ifndef PAX_CORE_STREAM_TARGET_C
#define PAX_CORE_STREAM_TARGET_C

#include "./target.h"

static paxiword
pax_target_write(Pax_Target* self, paxu8* memory, paxiword length)
{
    Pax_Target_Proc* proc = pax_as(Pax_Target_Proc*, self->proc);

    if (self->proc != 0)
        return proc(self->ctxt, memory, length);

    return 0;
}

Pax_Target*
pax_target_from_buffer8(Pax_Arena* arena, Pax_Buffer8* self)
{
    Pax_Target result = {0};

    if (self == 0) return 0;

    result.ctxt = self;
    result.proc = &pax_buffer8_write_tail_memory8;

    return pax_arena_clone(arena, Pax_Target, &result, 1);
}

paxiword
pax_target_write_memory8(Pax_Target* self, paxu8* memory, paxiword length)
{
    paxiword size = 0;
    paxiword temp = 1;

    for (; size < length && temp != 0; size += temp)
        temp = pax_target_write(self, memory + size, length - size);

    return size;
}

paxiword
pax_target_write_buffer8(Pax_Target* self, Pax_Buffer8* value)
{
    paxu8*   memory = value->memory;
    paxiword length = value->length;

    paxiword result =
        pax_target_write_memory8(self, memory, length);

    pax_buffer8_clear(value);

    return result;
}

paxiword
pax_target_write_byte(Pax_Target* self, paxu8 value)
{
    return pax_target_write_memory8(self, &value, 1);
}

paxiword
pax_target_write_string8(Pax_Target* self, Pax_String8 value)
{
    return pax_target_write_memory8(self, value.memory, value.length);
}

paxiword
pax_target_write_unicode(Pax_Target* self, paxi32 value)
{
    Pax_UTF8 utf8 = {0};

    if (pax_utf8_encode(&utf8, value) > 0)
        return pax_target_write_memory8(self, utf8.items, utf8.size);

    return 0;
}

#endif // PAX_CORE_STREAM_TARGET_C
