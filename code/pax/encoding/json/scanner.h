#ifndef PAX_ENCODING_JSON_SCANNER_H
#define PAX_ENCODING_JSON_SCANNER_H

#include "./token.h"

Pax_JSON_Token
pax_scanner_read_json_operator(Pax_Scanner* self, Pax_Arena* arena, paxiword length);

Pax_JSON_Token
pax_scanner_read_json_string(Pax_Scanner* self, Pax_Arena* arena, paxiword length);

Pax_JSON_Token
pax_scanner_read_json_number(Pax_Scanner* self, Pax_Arena* arena, paxiword length);

Pax_JSON_Token
pax_scanner_read_json_identifier(Pax_Scanner* self, Pax_Arena* arena, paxiword length);

Pax_JSON_Token
pax_scanner_read_json_token(Pax_Scanner* self, Pax_Arena* arena);

#endif // PAX_ENCODING_JSON_SCANNER_H
