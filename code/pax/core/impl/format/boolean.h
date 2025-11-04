#ifndef PAX_CORE_FORMAT_BOOLEAN_H
#define PAX_CORE_FORMAT_BOOLEAN_H

#include "./config.h"

paxiword
pax_boolean_digits(paxbword value, Pax_Format_Flag flags);

/* Memory */

paxiword
pax_memory8_write_boolean(paxu8* memory, paxiword length, paxbword value, Pax_Format_Flag flags);

paxiword
pax_memory8_read_boolean(paxu8* memory, paxiword length, paxbword* value, Pax_Format_Flag flags);

/* String */

Pax_String8
pax_string8_from_boolean(Pax_Arena* arena, paxbword value, Pax_Format_Flag flags);

paxb8
pax_boolean_from_string8(Pax_String8 string, paxbword* value, Pax_Format_Flag flags);

#endif // PAX_CORE_FORMAT_BOOLEAN_H
