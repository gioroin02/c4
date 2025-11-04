#ifndef PAX_CORE_STRING_BUFFER8_H
#define PAX_CORE_STRING_BUFFER8_H

#include "./unicode.h"

typedef Pax_Array Pax_Buffer8;

Pax_Buffer8
pax_buffer8_make(paxu8* memory, paxiword length);

Pax_Buffer8
pax_buffer8_create(Pax_Arena* arena, paxiword length);

void
pax_buffer8_clear(Pax_Buffer8* self);

void
pax_buffer8_fill(Pax_Buffer8* self);

paxiword
pax_buffer8_elements(Pax_Buffer8* self);

paxiword
pax_buffer8_capacity(Pax_Buffer8* self);

paxiword
pax_buffer8_head(Pax_Buffer8* self);

paxiword
pax_buffer8_tail(Pax_Buffer8* self);

/* Drop */

paxiword
pax_buffer8_drop_head(Pax_Buffer8* self, paxiword length);

paxiword
pax_buffer8_drop_tail(Pax_Buffer8* self, paxiword length);

/* Write head */

paxiword
pax_buffer8_write_head_memory8(Pax_Buffer8* self, paxu8* memory, paxiword length);

paxiword
pax_buffer8_write_head(Pax_Buffer8* self, paxu8 value);

paxiword
pax_buffer8_write_head_unicode(Pax_Buffer8* self, paxi32 value);

paxiword
pax_buffer8_write_head_buffer8(Pax_Buffer8* self, Pax_Buffer8* value);

/* Write tail */

paxiword
pax_buffer8_write_tail_memory8(Pax_Buffer8* self, paxu8* memory, paxiword length);

paxiword
pax_buffer8_write_tail(Pax_Buffer8* self, paxu8 value);

paxiword
pax_buffer8_write_tail_unicode(Pax_Buffer8* self, paxi32 value);

paxiword
pax_buffer8_write_tail_buffer8(Pax_Buffer8* self, Pax_Buffer8* value);

/* Read head */

paxiword
pax_buffer8_read_head_memory8(Pax_Buffer8* self, paxu8* memory, paxiword length);

paxiword
pax_buffer8_read_head(Pax_Buffer8* self, paxu8* value);

paxiword
pax_buffer8_read_head_unicode(Pax_Buffer8* self, paxi32* value);

paxiword
pax_buffer8_read_head_buffer8(Pax_Buffer8* self, Pax_Buffer8* value);

/* Read tail */

paxiword
pax_buffer8_read_tail_memory8(Pax_Buffer8* self, paxu8* memory, paxiword length);

paxiword
pax_buffer8_read_tail(Pax_Buffer8* self, paxu8* value);

paxiword
pax_buffer8_read_tail_unicode(Pax_Buffer8* self, paxi32* value);

paxiword
pax_buffer8_read_tail_buffer8(Pax_Buffer8* self, Pax_Buffer8* value);

/* Peek */

paxiword
pax_buffer8_peek_memory8(Pax_Buffer8* self, paxiword index, paxu8* memory, paxiword length);

paxiword
pax_buffer8_peek_buffer8(Pax_Buffer8* self, paxiword index, Pax_Buffer8* value);

paxu8
pax_buffer8_peek_or_none(Pax_Buffer8* self, paxiword index);

paxi32
pax_buffer8_peek_unicode_or_none(Pax_Buffer8* self, paxiword index);

#endif // PAX_CORE_STRING_BUFFER8_H
