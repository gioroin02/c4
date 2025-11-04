#ifndef PAX_CORE_STREAM_SOURCE_C
#define PAX_CORE_STREAM_SOURCE_C

#include "./source.h"

static paxiword
pax_source_read(Pax_Source* self, paxu8* memory, paxiword length)
{
    Pax_Source_Proc* proc = pax_as(Pax_Source_Proc*, self->proc);

    if (self->proc != 0)
        return proc(self->ctxt, memory, length);

    return 0;
}

Pax_Source*
pax_source_from_buffer8(Pax_Arena* arena, Pax_Buffer8* self)
{
    Pax_Source result = {0};

    if (self == 0) return 0;

    result.ctxt = self;
    result.proc = &pax_buffer8_read_head_memory8;

    return pax_arena_clone(arena, Pax_Source, &result, 1);
}

paxiword
pax_source_read_memory8(Pax_Source* self, paxu8* memory, paxiword length)
{
    return pax_source_read(self, memory, length);
}

paxiword
pax_source_read_buffer8(Pax_Source* self, Pax_Buffer8* value)
{
    paxu8*   memory = value->memory   + value->length;
    paxiword length = value->capacity - value->length;

    paxiword size = pax_source_read_memory8(self, memory, length);

    value->length += size;

    return size;
}

paxu8
pax_source_read_byte(Pax_Source* self)
{
    paxu8 result = 0;

    if (pax_source_read_memory8(self, &result, 1) <= 0)
        return 0;

    return result;
}

Pax_String8
pax_source_read_string8(Pax_Source* self, Pax_Arena* arena, paxiword length)
{
    paxiword mark   = pax_arena_tell(arena);
    paxu8*   memory = pax_arena_reserve(arena, paxu8, length + 1);

    paxiword size = pax_source_read_memory8(self, memory, length);

    if (size > 0 && size < length)
        pax_arena_rewind(arena, mark, size + 1);
    else
        pax_arena_rewind(arena, mark, 0);

    return pax_string8_make(memory, size);
}

paxiword
pax_source_read_unicode(Pax_Source* self, paxi32* value)
{
    Pax_UTF8 utf8 = {0};

    utf8.a    = pax_source_read_byte(self);
    utf8.size = pax_utf8_units_to_read(utf8.a);

    pax_source_read_memory8(self,
        utf8.items + 1, utf8.size - 1);

    pax_utf8_decode(&utf8, value);

    return utf8.size;
}

#endif // PAX_CORE_STREAM_SOURCE_C
