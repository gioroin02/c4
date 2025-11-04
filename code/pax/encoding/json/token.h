#ifndef PAX_ENCODING_JSON_TOKEN_H
#define PAX_ENCODING_JSON_TOKEN_H

#include "./import.h"

typedef enum Pax_JSON_Token_Kind
{
    PAX_JSON_TOKEN_KIND_NONE,

    PAX_JSON_TOKEN_KIND_ERROR,

    PAX_JSON_TOKEN_KIND_OBJECT_OPEN,
    PAX_JSON_TOKEN_KIND_OBJECT_CLOSE,
    PAX_JSON_TOKEN_KIND_ARRAY_OPEN,
    PAX_JSON_TOKEN_KIND_ARRAY_CLOSE,
    PAX_JSON_TOKEN_KIND_COMMA,
    PAX_JSON_TOKEN_KIND_COLON,

    PAX_JSON_TOKEN_KIND_STRING,
    PAX_JSON_TOKEN_KIND_UNSIGNED,
    PAX_JSON_TOKEN_KIND_INTEGER,
    PAX_JSON_TOKEN_KIND_FLOATING,
    PAX_JSON_TOKEN_KIND_BOOLEAN,
    PAX_JSON_TOKEN_KIND_NULL,

    PAX_JSON_TOKEN_KIND_END,
}
Pax_JSON_Token_Kind;

typedef struct Pax_JSON_Token
{
    Pax_JSON_Token_Kind kind;

    union
    {
        Pax_String8 value_string;
        paxuword    value_unsigned;
        paxiword    value_integer;
        paxfword    value_floating;
        paxbword    value_boolean;
    };
}
Pax_JSON_Token;

Pax_JSON_Token
pax_json_token_make(Pax_JSON_Token_Kind kind);

Pax_JSON_Token
pax_json_token_error();

Pax_JSON_Token
pax_json_token_object_open();

Pax_JSON_Token
pax_json_token_object_close();

Pax_JSON_Token
pax_json_token_array_open();

Pax_JSON_Token
pax_json_token_array_close();

Pax_JSON_Token
pax_json_token_comma();

Pax_JSON_Token
pax_json_token_colon();

Pax_JSON_Token
pax_json_token_string(Pax_String8 value);

Pax_JSON_Token
pax_json_token_unsigned(paxuword value);

Pax_JSON_Token
pax_json_token_integer(paxiword value);

Pax_JSON_Token
pax_json_token_floating(paxfword value);

Pax_JSON_Token
pax_json_token_boolean(paxbword value);

Pax_JSON_Token
pax_json_token_null();

Pax_JSON_Token
pax_json_token_end();

#endif // PAX_ENCODING_JSON_TOKEN_H
