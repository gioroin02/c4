#ifndef PAX_CORE_STRING_BUFFER32_H
#define PAX_CORE_STRING_BUFFER32_H

#include "./unicode.h"

typedef Pax_Array Pax_Buffer32;

Pax_Buffer32
pax_buffer32_make(paxu32* memory, paxiword length);

Pax_Buffer32
pax_buffer32_create(Pax_Arena* arena, paxiword length);

void
pax_buffer32_clear(Pax_Buffer32* self);

void
pax_buffer32_fill(Pax_Buffer32* self);

paxiword
pax_buffer32_elements(Pax_Buffer32* self);

paxiword
pax_buffer32_capacity(Pax_Buffer32* self);

paxiword
pax_buffer32_head(Pax_Buffer32* self);

paxiword
pax_buffer32_tail(Pax_Buffer32* self);

/* Drop */

paxiword
pax_buffer32_drop_head(Pax_Buffer32* self, paxiword length);

paxiword
pax_buffer32_drop_tail(Pax_Buffer32* self, paxiword length);

/* Write head */

paxiword
pax_buffer32_write_head_memory32(Pax_Buffer32* self, paxu32* memory, paxiword length);

paxiword
pax_buffer32_write_head(Pax_Buffer32* self, paxu32 value);

paxiword
pax_buffer32_write_head_unicode(Pax_Buffer32* self, paxi32 value);

paxiword
pax_buffer32_write_head_buffer32(Pax_Buffer32* self, Pax_Buffer32* value);

/* Write tail */

paxiword
pax_buffer32_write_tail_memory32(Pax_Buffer32* self, paxu32* memory, paxiword length);

paxiword
pax_buffer32_write_tail(Pax_Buffer32* self, paxu32 value);

paxiword
pax_buffer32_write_tail_unicode(Pax_Buffer32* self, paxi32 value);

paxiword
pax_buffer32_write_tail_buffer32(Pax_Buffer32* self, Pax_Buffer32* value);

/* Read head */

paxiword
pax_buffer32_read_head_memory32(Pax_Buffer32* self, paxu32* memory, paxiword length);

paxiword
pax_buffer32_read_head(Pax_Buffer32* self, paxu32* value);

paxiword
pax_buffer32_read_head_unicode(Pax_Buffer32* self, paxi32* value);

paxiword
pax_buffer32_read_head_buffer32(Pax_Buffer32* self, Pax_Buffer32* value);

/* Read tail */

paxiword
pax_buffer32_read_tail_memory32(Pax_Buffer32* self, paxu32* memory, paxiword length);

paxiword
pax_buffer32_read_tail(Pax_Buffer32* self, paxu32* value);

paxiword
pax_buffer32_read_tail_unicode(Pax_Buffer32* self, paxi32* value);

paxiword
pax_buffer32_read_tail_buffer32(Pax_Buffer32* self, Pax_Buffer32* value);

/* Peek */

paxiword
pax_buffer32_peek_memory32(Pax_Buffer32* self, paxiword index, paxu32* memory, paxiword length);

paxiword
pax_buffer32_peek_buffer32(Pax_Buffer32* self, paxiword index, Pax_Buffer32* value);

paxu32
pax_buffer32_peek_or_none(Pax_Buffer32* self, paxiword index);

paxi32
pax_buffer32_peek_unicode_or_none(Pax_Buffer32* self, paxiword index);

#endif // PAX_CORE_STRING_BUFFER32_H
