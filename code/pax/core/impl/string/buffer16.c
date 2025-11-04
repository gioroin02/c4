#ifndef PAX_CORE_STRING_BUFFER16_C
#define PAX_CORE_STRING_BUFFER16_C

#include "./buffer16.h"

Pax_Buffer16
pax_buffer16_make(paxu16* memory, paxiword length)
{
    return pax_array_make(paxu16, memory, length);
}

Pax_Buffer16
pax_buffer16_create(Pax_Arena* arena, paxiword length)
{
    return pax_array_create(arena, paxu16, length);
}

void
pax_buffer16_clear(Pax_Buffer16* self)
{
    pax_array_clear(self);
}

void
pax_buffer16_fill(Pax_Buffer16* self)
{
    pax_array_fill(self);
}

paxiword
pax_buffer16_elements(Pax_Buffer16* self)
{
    return pax_array_elements(self);
}

paxiword
pax_buffer16_capacity(Pax_Buffer16* self)
{
    return pax_array_capacity(self);
}

paxiword
pax_buffer16_head(Pax_Buffer16* self)
{
    return pax_array_head(self);
}

paxiword
pax_buffer16_tail(Pax_Buffer16* self)
{
    return pax_array_tail(self);
}

paxiword
pax_buffer16_drop_head(Pax_Buffer16* self, paxiword length)
{
    paxiword index = pax_array_head(self);

    return pax_array_remove(self, paxu16,
        index, 0, length);
}

paxiword
pax_buffer16_drop_tail(Pax_Buffer16* self, paxiword length)
{
    paxiword index = pax_array_tail(self);

    return pax_array_remove(self, paxu16,
        index - length, 0, length);
}

paxiword
pax_buffer16_write_head_memory16(Pax_Buffer16* self, paxu16* memory, paxiword length)
{
    paxiword index = pax_array_head(self);

    return pax_array_insert(self, paxu16,
        index, memory, length);
}

paxiword
pax_buffer16_write_head(Pax_Buffer16* self, paxu16 value)
{
    paxiword index = pax_array_head(self);

    return pax_array_insert(self, paxu16,
        index, &value, 1);
}

paxiword
pax_buffer16_write_head_unicode(Pax_Buffer16* self, paxi32 value)
{
    Pax_UTF16 utf16 = {0};

    if (pax_utf16_encode(&utf16, value) <= 0)
        return 0;

    paxiword index = pax_array_head(self);

    return pax_array_insert(self, paxu16,
        index, utf16.items, utf16.size);
}

paxiword
pax_buffer16_write_head_buffer16(Pax_Buffer16* self, Pax_Buffer16* value)
{
    paxu8*   memory = value->memory;
    paxiword length = value->length;

    paxiword size = pax_buffer16_write_head_memory16(self,
        pax_as(paxu16*, memory), length);

    pax_buffer16_drop_head(value, size);

    return size;
}

paxiword
pax_buffer16_write_tail_memory16(Pax_Buffer16* self, paxu16* memory, paxiword length)
{
    paxiword index = pax_array_tail(self) + 1;

    return pax_array_insert(self,
        paxu16, index, memory, length);
}

paxiword
pax_buffer16_write_tail(Pax_Buffer16* self, paxu16 value)
{
    paxiword index = pax_array_tail(self) + 1;

    return pax_array_insert(self, paxu16,
        index, &value, 1);
}

paxiword
pax_buffer16_write_tail_unicode(Pax_Buffer16* self, paxi32 value)
{
    Pax_UTF16 utf16 = {0};

    if (pax_utf16_encode(&utf16, value) <= 0)
        return 0;

    paxiword index = pax_array_tail(self) + 1;

    return pax_array_insert(self, paxu16,
        index, utf16.items, utf16.size);
}

paxiword
pax_buffer16_write_tail_buffer16(Pax_Buffer16* self, Pax_Buffer16* value)
{
    paxu8*   memory = value->memory;
    paxiword length = value->length;

    paxiword size = pax_buffer16_write_tail_memory16(self,
        pax_as(paxu16*, memory), length);

    pax_buffer16_drop_head(value, size);

    return size;
}

paxiword
pax_buffer16_read_head_memory16(Pax_Buffer16* self, paxu16* memory, paxiword length)
{
    paxiword index = pax_array_head(self);

    return pax_array_remove(self,
        paxu16, index, memory, length);
}

paxiword
pax_buffer16_read_head(Pax_Buffer16* self, paxu16* value)
{
    paxiword index = pax_array_head(self);

    return pax_array_remove(self,
        paxu16, index, &value, 1);
}

paxiword
pax_buffer16_read_head_unicode(Pax_Buffer16* self, paxi32* value)
{
    paxu8*   memory = self->memory;
    paxiword length = self->length;
    paxiword index  = pax_array_head(self);

    paxiword result = pax_utf16_read_forw(
        pax_as(paxu16*, memory), length, index, value);

    pax_array_remove(self, paxu16, index, 0, result);

    return result;
}

paxiword
pax_buffer16_read_head_buffer16(Pax_Buffer16* self, Pax_Buffer16* value)
{
    paxu8*   memory = value->memory   + value->length;
    paxiword length = value->capacity - value->length;

    paxiword size = pax_buffer16_read_head_memory16(self,
        pax_as(paxu16*, memory), length);

    value->length += size;

    return size;
}

paxiword
pax_buffer16_read_tail_memory16(Pax_Buffer16* self, paxu16* memory, paxiword length)
{
    paxiword index = pax_array_tail(self);

    return pax_array_remove(self,
        paxu16, index - length, memory, length);
}

paxiword
pax_buffer16_read_tail(Pax_Buffer16* self, paxu16* value)
{
    paxiword index = pax_array_tail(self);

    return pax_array_remove(self,
        paxu16, index, &value, 1);
}

paxiword
pax_buffer16_read_tail_unicode(Pax_Buffer16* self, paxi32* value)
{
    paxu8*   memory = self->memory;
    paxiword length = self->length;
    paxiword index  = pax_array_tail(self);

    paxiword result = pax_utf16_read_back(
        pax_as(paxu16*, memory), length, index, value);

    pax_array_remove(self, paxu16, index, 0, result);

    return result;
}

paxiword
pax_buffer16_read_tail_buffer16(Pax_Buffer16* self, Pax_Buffer16* value)
{
    paxu8*   memory = value->memory   + value->length;
    paxiword length = value->capacity - value->length;

    paxiword size = pax_buffer16_read_tail_memory16(self,
        pax_as(paxu16*, memory), length);

    value->length += size;

    return size;
}

paxiword
pax_buffer16_peek_memory16(Pax_Buffer16* self, paxiword index, paxu16* memory, paxiword length)
{
    return pax_array_peek(self, paxu16, index, memory, length);
}

paxiword
pax_buffer16_peek_buffer16(Pax_Buffer16* self, paxiword index, Pax_Buffer16* value)
{
    paxu8*   memory = value->memory   + value->length;
    paxiword length = value->capacity - value->length;

    paxiword size = pax_buffer16_peek_memory16(self, index,
        pax_as(paxu16*, memory), length);

    value->length += size;

    return size;
}

paxu16
pax_buffer16_peek_or_none(Pax_Buffer16* self, paxiword index)
{
    paxu16 result = 0;

    if (pax_array_peek(self, paxu16, index, &result, 1) != 0)
        return result;

    return 0;
}

paxi32
pax_buffer16_peek_unicode_or_none(Pax_Buffer16* self, paxiword index)
{
    paxu8*   memory = self->memory;
    paxiword length = self->length;
    paxi32   result = 0;

    pax_utf16_read_forw(pax_as(paxu16*, memory), length,
        index, &result);

    return result;
}

#endif // PAX_CORE_STRING_BUFFER16_C
