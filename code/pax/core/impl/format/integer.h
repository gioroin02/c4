#ifndef PAX_CORE_FORMAT_INTEGER_H
#define PAX_CORE_FORMAT_INTEGER_H

#include "./config.h"

paxiword
pax_integer_digits(paxiword value, Pax_Format_Radix radix, Pax_Format_Flag flags);

/* Memory */

paxiword
pax_memory8_write_integer(paxu8* memory, paxiword length, paxiword value, Pax_Format_Radix radix, Pax_Format_Flag flags);

paxiword
pax_memory8_read_integer(paxu8* memory, paxiword length, paxiword* value, Pax_Format_Radix radix, Pax_Format_Flag flags);

/* String */

Pax_String8
pax_string8_from_integer(Pax_Arena* arena, paxiword value, Pax_Format_Radix radix, Pax_Format_Flag flags);

paxb8
pax_integer_from_string8(Pax_String8 string, paxiword* value, Pax_Format_Radix radix, Pax_Format_Flag flags);

#endif // PAX_CORE_FORMAT_INTEGER_H
