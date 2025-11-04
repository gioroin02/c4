#ifndef PAX_CORE_FORMAT_SCANNER_H
#define PAX_CORE_FORMAT_SCANNER_H

#include "./import.h"
#include "./config.h"

typedef struct Pax_Scanner
{
    Pax_Buffer8 buffer;
    Pax_Source* source;
}
Pax_Scanner;

Pax_Scanner
pax_scanner_create(Pax_Arena* arena, paxiword length, Pax_Source* source);

paxiword
pax_scanner_peek_memory8(Pax_Scanner* self, paxiword offset, paxu8* memory, paxiword length);

paxiword
pax_scanner_peek_byte(Pax_Scanner* self, paxiword offset, paxu8* value);

paxiword
pax_scanner_peek_unicode(Pax_Scanner* self, paxiword offset, paxi32* value);

paxiword
pax_scanner_read_memory8(Pax_Scanner* self, paxiword offset, paxu8* memory, paxiword length);

paxiword
pax_scanner_read_byte(Pax_Scanner* self, paxiword offset, paxu8* value);

paxiword
pax_scanner_read_unicode(Pax_Scanner* self, paxiword offset, paxi32* value);

paxiword
pax_scanner_drop(Pax_Scanner* self, paxiword length);

paxiword
pax_scanner_drop_cntrls(Pax_Scanner* self);

#endif // PAX_CORE_FORMAT_SCANNER_H
