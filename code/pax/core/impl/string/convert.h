#ifndef PAX_CORE_STRING_CONVERT_H
#define PAX_CORE_STRING_CONVERT_H

#include "./string8.h"
#include "./string16.h"
#include "./string32.h"

/* Buffer8 */

paxiword
pax_buffer8_write_head_string8(Pax_Buffer8* self, Pax_String8 value);

paxiword
pax_buffer8_write_tail_string8(Pax_Buffer8* self, Pax_String8 value);

Pax_String8
pax_buffer8_read_head_string8(Pax_Buffer8* self, Pax_Arena* arena, paxiword length);

Pax_String8
pax_buffer8_read_tail_string8(Pax_Buffer8* self, Pax_Arena* arena, paxiword length);

/* Buffer16 */

paxiword
pax_buffer16_write_head_string16(Pax_Buffer16* self, Pax_String16 value);

paxiword
pax_buffer16_write_tail_string16(Pax_Buffer16* self, Pax_String16 value);

Pax_String16
pax_buffer16_read_head_string16(Pax_Buffer16* self, Pax_Arena* arena, paxiword length);

Pax_String16
pax_buffer16_read_tail_string16(Pax_Buffer16* self, Pax_Arena* arena, paxiword length);

/* Buffer32 */

paxiword
pax_buffer32_write_head_string32(Pax_Buffer32* self, Pax_String32 value);

paxiword
pax_buffer32_write_tail_string32(Pax_Buffer32* self, Pax_String32 value);

Pax_String32
pax_buffer32_read_head_string32(Pax_Buffer32* self, Pax_Arena* arena, paxiword length);

Pax_String32
pax_buffer32_read_tail_string32(Pax_Buffer32* self, Pax_Arena* arena, paxiword length);

/* String8 */

Pax_String8
pax_string8_copy_memory16(Pax_Arena* arena, paxu16* memory, paxiword length);

Pax_String8
pax_string8_copy_string16(Pax_Arena* arena, Pax_String16 value);

Pax_String8
pax_string8_copy_memory32(Pax_Arena* arena, paxu32* memory, paxiword length);

Pax_String8
pax_string8_copy_string32(Pax_Arena* arena, Pax_String32 value);

/* String16 */

Pax_String16
pax_string16_copy_memory8(Pax_Arena* arena, paxu8* memory, paxiword length);

Pax_String16
pax_string16_copy_string8(Pax_Arena* arena, Pax_String8 value);

Pax_String16
pax_string16_copy_memory32(Pax_Arena* arena, paxu32* memory, paxiword length);

Pax_String16
pax_string16_copy_string32(Pax_Arena* arena, Pax_String32 value);

/* String32 */

Pax_String32
pax_string32_copy_memory8(Pax_Arena* arena, paxu8* memory, paxiword length);

Pax_String32
pax_string32_copy_string8(Pax_Arena* arena, Pax_String8 value);

Pax_String32
pax_string32_copy_memory16(Pax_Arena* arena, paxu16* memory, paxiword length);

Pax_String32
pax_string32_copy_string16(Pax_Arena* arena, Pax_String16 value);

#endif // PAX_CORE_STRING_CONVERT_H
