#ifndef PAX_CORE_STRING_BUFFER16_H
#define PAX_CORE_STRING_BUFFER16_H

#include "./unicode.h"

typedef Pax_Array Pax_Buffer16;

Pax_Buffer16
pax_buffer16_make(paxu16* memory, paxiword length);

Pax_Buffer16
pax_buffer16_create(Pax_Arena* arena, paxiword length);

void
pax_buffer16_clear(Pax_Buffer16* self);

void
pax_buffer16_fill(Pax_Buffer16* self);

paxiword
pax_buffer16_elements(Pax_Buffer16* self);

paxiword
pax_buffer16_capacity(Pax_Buffer16* self);

paxiword
pax_buffer16_head(Pax_Buffer16* self);

paxiword
pax_buffer16_tail(Pax_Buffer16* self);

/* Drop */

paxiword
pax_buffer16_drop_head(Pax_Buffer16* self, paxiword length);

paxiword
pax_buffer16_drop_tail(Pax_Buffer16* self, paxiword length);

/* Write head */

paxiword
pax_buffer16_write_head_memory16(Pax_Buffer16* self, paxu16* memory, paxiword length);

paxiword
pax_buffer16_write_head(Pax_Buffer16* self, paxu16 value);

paxiword
pax_buffer16_write_head_unicode(Pax_Buffer16* self, paxi32 value);

paxiword
pax_buffer16_write_head_buffer16(Pax_Buffer16* self, Pax_Buffer16* value);

/* Write tail */

paxiword
pax_buffer16_write_tail_memory16(Pax_Buffer16* self, paxu16* memory, paxiword length);

paxiword
pax_buffer16_write_tail(Pax_Buffer16* self, paxu16 value);

paxiword
pax_buffer16_write_tail_unicode(Pax_Buffer16* self, paxi32 value);

paxiword
pax_buffer16_write_tail_buffer16(Pax_Buffer16* self, Pax_Buffer16* value);

/* Read head */

paxiword
pax_buffer16_read_head_memory16(Pax_Buffer16* self, paxu16* memory, paxiword length);

paxiword
pax_buffer16_read_head(Pax_Buffer16* self, paxu16* value);

paxiword
pax_buffer16_read_head_unicode(Pax_Buffer16* self, paxi32* value);

paxiword
pax_buffer16_read_head_buffer16(Pax_Buffer16* self, Pax_Buffer16* value);

/* Read tail */

paxiword
pax_buffer16_read_tail_memory16(Pax_Buffer16* self, paxu16* memory, paxiword length);

paxiword
pax_buffer16_read_tail(Pax_Buffer16* self, paxu16* value);

paxiword
pax_buffer16_read_tail_unicode(Pax_Buffer16* self, paxi32* value);

paxiword
pax_buffer16_read_tail_buffer16(Pax_Buffer16* self, Pax_Buffer16* value);

/* Peek */

paxiword
pax_buffer16_peek_memory16(Pax_Buffer16* self, paxiword index, paxu16* memory, paxiword length);

paxiword
pax_buffer16_peek_buffer16(Pax_Buffer16* self, paxiword index, Pax_Buffer16* value);

paxu16
pax_buffer16_peek_or_none(Pax_Buffer16* self, paxiword index);

paxi32
pax_buffer16_peek_unicode_or_none(Pax_Buffer16* self, paxiword index);

#endif // PAX_CORE_STRING_BUFFER16_H
