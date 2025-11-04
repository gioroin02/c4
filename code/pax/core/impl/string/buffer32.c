#ifndef PAX_CORE_STRING_BUFFER32_C
#define PAX_CORE_STRING_BUFFER32_C

#include "./buffer32.h"

Pax_Buffer32
pax_buffer32_make(paxu32* memory, paxiword length)
{
    return pax_array_make(paxu32, memory, length);
}

Pax_Buffer32
pax_buffer32_create(Pax_Arena* arena, paxiword length)
{
    return pax_array_create(arena, paxu32, length);
}

void
pax_buffer32_clear(Pax_Buffer32* self)
{
    pax_array_clear(self);
}

void
pax_buffer32_fill(Pax_Buffer32* self)
{
    pax_array_fill(self);
}

paxiword
pax_buffer32_elements(Pax_Buffer32* self)
{
    return pax_array_elements(self);
}

paxiword
pax_buffer32_capacity(Pax_Buffer32* self)
{
    return pax_array_capacity(self);
}

paxiword
pax_buffer32_head(Pax_Buffer32* self)
{
    return pax_array_head(self);
}

paxiword
pax_buffer32_tail(Pax_Buffer32* self)
{
    return pax_array_tail(self);
}

paxiword
pax_buffer32_drop_head(Pax_Buffer32* self, paxiword length)
{
    paxiword index = pax_array_head(self);

    return pax_array_remove(self, paxu32,
        index, 0, length);
}

paxiword
pax_buffer32_drop_tail(Pax_Buffer32* self, paxiword length)
{
    paxiword index = pax_array_tail(self);

    return pax_array_remove(self, paxu32,
        index - length, 0, length);
}

paxiword
pax_buffer32_write_head_memory32(Pax_Buffer32* self, paxu32* memory, paxiword length)
{
    paxiword index = pax_array_head(self);

    return pax_array_insert(self, paxu32,
        index, memory, length);
}

paxiword
pax_buffer32_write_head(Pax_Buffer32* self, paxu32 value)
{
    paxiword index = pax_array_head(self);

    return pax_array_insert(self, paxu32,
        index, &value, 1);
}

paxiword
pax_buffer32_write_head_unicode(Pax_Buffer32* self, paxi32 value)
{
    Pax_UTF32 utf32 = {0};

    if (pax_utf32_encode(&utf32, value) <= 0)
        return 0;

    paxiword index = pax_array_head(self);

    return pax_array_insert(self, paxu32,
        index, utf32.items, utf32.size);
}

paxiword
pax_buffer32_write_head_buffer32(Pax_Buffer32* self, Pax_Buffer32* value)
{
    paxu8*   memory = value->memory;
    paxiword length = value->length;

    paxiword size = pax_buffer32_write_head_memory32(self,
        pax_as(paxu32*, memory), length);

    pax_buffer32_drop_head(value, size);

    return size;
}

paxiword
pax_buffer32_write_tail_memory32(Pax_Buffer32* self, paxu32* memory, paxiword length)
{
    paxiword index = pax_array_tail(self) + 1;

    return pax_array_insert(self,
        paxu32, index, memory, length);
}

paxiword
pax_buffer32_write_tail(Pax_Buffer32* self, paxu32 value)
{
    paxiword index = pax_array_tail(self) + 1;

    return pax_array_insert(self, paxu32,
        index, &value, 1);
}

paxiword
pax_buffer32_write_tail_unicode(Pax_Buffer32* self, paxi32 value)
{
    Pax_UTF32 utf32 = {0};

    if (pax_utf32_encode(&utf32, value) <= 0)
        return 0;

    paxiword index = pax_array_tail(self) + 1;

    return pax_array_insert(self, paxu32,
        index, utf32.items, utf32.size);
}

paxiword
pax_buffer32_write_tail_buffer32(Pax_Buffer32* self, Pax_Buffer32* value)
{
    paxu8*   memory = value->memory;
    paxiword length = value->length;

    paxiword size = pax_buffer32_write_tail_memory32(self,
        pax_as(paxu32*, memory), length);

    pax_buffer32_drop_head(value, size);

    return size;
}

paxiword
pax_buffer32_read_head_memory32(Pax_Buffer32* self, paxu32* memory, paxiword length)
{
    paxiword index = pax_array_head(self);

    return pax_array_remove(self,
        paxu32, index, memory, length);
}

paxiword
pax_buffer32_read_head(Pax_Buffer32* self, paxu32* value)
{
    paxiword index = pax_array_head(self);

    return pax_array_remove(self,
        paxu32, index, &value, 1);
}

paxiword
pax_buffer32_read_head_unicode(Pax_Buffer32* self, paxi32* value)
{
    paxu8*   memory = self->memory;
    paxiword length = self->length;
    paxiword index  = pax_array_head(self);

    paxiword result = pax_utf32_read_forw(
        pax_as(paxu32*, memory), length, index, value);

    pax_array_remove(self, paxu32, index, 0, result);

    return result;
}

paxiword
pax_buffer32_read_head_buffer32(Pax_Buffer32* self, Pax_Buffer32* value)
{
    paxu8*   memory = value->memory   + value->length;
    paxiword length = value->capacity - value->length;

    paxiword size = pax_buffer32_read_head_memory32(self,
        pax_as(paxu32*, memory), length);

    value->length += size;

    return size;
}

paxiword
pax_buffer32_read_tail_memory32(Pax_Buffer32* self, paxu32* memory, paxiword length)
{
    paxiword index = pax_array_tail(self);

    return pax_array_remove(self,
        paxu32, index - length, memory, length);
}

paxiword
pax_buffer32_read_tail(Pax_Buffer32* self, paxu32* value)
{
    paxiword index = pax_array_tail(self);

    return pax_array_remove(self,
        paxu32, index, &value, 1);
}

paxiword
pax_buffer32_read_tail_unicode(Pax_Buffer32* self, paxi32* value)
{
    paxu8*   memory = self->memory;
    paxiword length = self->length;
    paxiword index  = pax_array_tail(self);

    paxiword result = pax_utf32_read_back(
        pax_as(paxu32*, memory), length, index, value);

    pax_array_remove(self, paxu32, index, 0, result);

    return result;
}

paxiword
pax_buffer32_read_tail_buffer32(Pax_Buffer32* self, Pax_Buffer32* value)
{
    paxu8*   memory = value->memory   + value->length;
    paxiword length = value->capacity - value->length;

    paxiword size = pax_buffer32_read_tail_memory32(self,
        pax_as(paxu32*, memory), length);

    value->length += size;

    return size;
}

paxiword
pax_buffer32_peek_memory32(Pax_Buffer32* self, paxiword index, paxu32* memory, paxiword length)
{
    return pax_array_peek(self, paxu32, index, memory, length);
}

paxiword
pax_buffer32_peek_buffer32(Pax_Buffer32* self, paxiword index, Pax_Buffer32* value)
{
    paxu8*   memory = value->memory   + value->length;
    paxiword length = value->capacity - value->length;

    paxiword size = pax_buffer32_peek_memory32(self, index,
        pax_as(paxu32*, memory), length);

    value->length += size;

    return size;
}

paxu32
pax_buffer32_peek_or_none(Pax_Buffer32* self, paxiword index)
{
    paxu32 result = 0;

    if (pax_array_peek(self, paxu32, index, &result, 1) != 0)
        return result;

    return 0;
}

paxi32
pax_buffer32_peek_unicode_or_none(Pax_Buffer32* self, paxiword index)
{
    paxu8*   memory = self->memory;
    paxiword length = self->length;
    paxi32   result = 0;

    pax_utf32_read_forw(pax_as(paxu32*, memory), length,
        index, &result);

    return result;
}

#endif // PAX_CORE_STRING_BUFFER32_C
