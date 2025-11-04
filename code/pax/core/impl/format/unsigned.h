#ifndef PAX_CORE_FORMAT_UNSIGNED_H
#define PAX_CORE_FORMAT_UNSIGNED_H

#include "./config.h"

paxiword
pax_unsigned_digits(paxuword value, Pax_Format_Radix radix, Pax_Format_Flag flags);

/* Memory */

paxiword
pax_memory8_write_unsigned(paxu8* memory, paxiword length, paxuword value, Pax_Format_Radix radix, Pax_Format_Flag flags);

paxiword
pax_memory8_read_unsigned(paxu8* memory, paxiword length, paxuword* value, Pax_Format_Radix radix, Pax_Format_Flag flags);

/* String */

Pax_String8
pax_string8_from_unsigned(Pax_Arena* arena, paxuword value, Pax_Format_Radix radix, Pax_Format_Flag flags);

paxb8
pax_unsigned_from_string8(Pax_String8 string, paxuword* value, Pax_Format_Radix radix, Pax_Format_Flag flags);

#endif // PAX_CORE_FORMAT_UNSIGNED_H
