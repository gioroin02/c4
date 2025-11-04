#ifndef PAX_ENCODING_JSON_TOKEN_C
#define PAX_ENCODING_JSON_TOKEN_C

#include "./token.h"

Pax_JSON_Token
pax_json_token_make(Pax_JSON_Token_Kind kind)
{
    return (Pax_JSON_Token) {.kind = kind};
}

Pax_JSON_Token
pax_json_token_error()
{
    return (Pax_JSON_Token) {
        .kind = PAX_JSON_TOKEN_KIND_ERROR,
    };
}

Pax_JSON_Token
pax_json_token_object_open()
{
    return (Pax_JSON_Token) {
        .kind = PAX_JSON_TOKEN_KIND_OBJECT_OPEN,
    };
}

Pax_JSON_Token
pax_json_token_object_close()
{
    return (Pax_JSON_Token) {
        .kind = PAX_JSON_TOKEN_KIND_OBJECT_CLOSE,
    };
}

Pax_JSON_Token
pax_json_token_array_open()
{
    return (Pax_JSON_Token) {
        .kind = PAX_JSON_TOKEN_KIND_ARRAY_OPEN,
    };
}

Pax_JSON_Token
pax_json_token_array_close()
{
    return (Pax_JSON_Token) {
        .kind = PAX_JSON_TOKEN_KIND_ARRAY_CLOSE,
    };
}

Pax_JSON_Token
pax_json_token_comma()
{
    return (Pax_JSON_Token) {
        .kind = PAX_JSON_TOKEN_KIND_COMMA,
    };
}

Pax_JSON_Token
pax_json_token_colon()
{
    return (Pax_JSON_Token) {
        .kind = PAX_JSON_TOKEN_KIND_COLON,
    };
}

Pax_JSON_Token
pax_json_token_string(Pax_String8 value)
{
    return (Pax_JSON_Token) {
        .kind = PAX_JSON_TOKEN_KIND_STRING,

        .value_string = value,
    };
}

Pax_JSON_Token
pax_json_token_unsigned(paxuword value)
{
    return (Pax_JSON_Token) {
        .kind = PAX_JSON_TOKEN_KIND_UNSIGNED,

        .value_unsigned = value,
    };
}

Pax_JSON_Token
pax_json_token_integer(paxiword value)
{
    return (Pax_JSON_Token) {
        .kind = PAX_JSON_TOKEN_KIND_INTEGER,

        .value_integer = value,
    };
}

Pax_JSON_Token
pax_json_token_floating(paxfword value)
{
    return (Pax_JSON_Token) {
        .kind = PAX_JSON_TOKEN_KIND_FLOATING,

        .value_floating = value,
    };
}

Pax_JSON_Token
pax_json_token_boolean(paxbword value)
{
    return (Pax_JSON_Token) {
        .kind = PAX_JSON_TOKEN_KIND_BOOLEAN,

        .value_boolean = value,
    };
}

Pax_JSON_Token
pax_json_token_null()
{
    return (Pax_JSON_Token) {
        .kind = PAX_JSON_TOKEN_KIND_NULL,
    };
}

Pax_JSON_Token
pax_json_token_end()
{
    return (Pax_JSON_Token) {
        .kind = PAX_JSON_TOKEN_KIND_END,
    };
}

#endif // PAX_ENCODING_JSON_TOKEN_C
