#ifndef PX_ENCODING_JSON_TOKEN_C
#define PX_ENCODING_JSON_TOKEN_C

#include "token.h"

PxJsonToken
pxJsonTokenMake(PxJsonTokenType type)
{
    return (PxJsonToken) {.type = type};
}

PxJsonToken
pxJsonTokenError()
{
    return (PxJsonToken) {
        .type = PX_JSON_TOKEN_ERROR,
    };
}

PxJsonToken
pxJsonTokenObjectOpen()
{
    return (PxJsonToken) {
        .type = PX_JSON_TOKEN_OBJECT_OPEN,
    };
}

PxJsonToken
pxJsonTokenObjectClose()
{
    return (PxJsonToken) {
        .type = PX_JSON_TOKEN_OBJECT_CLOSE,
    };
}

PxJsonToken
pxJsonTokenArrayOpen()
{
    return (PxJsonToken) {
        .type = PX_JSON_TOKEN_ARRAY_OPEN,
    };
}

PxJsonToken
pxJsonTokenArrayClose()
{
    return (PxJsonToken) {
        .type = PX_JSON_TOKEN_ARRAY_CLOSE,
    };
}

PxJsonToken
pxJsonTokenColon()
{
    return (PxJsonToken) {
        .type = PX_JSON_TOKEN_COLON,
    };
}

PxJsonToken
pxJsonTokenComma()
{
    return (PxJsonToken) {
        .type = PX_JSON_TOKEN_COMMA,
    };
}

PxJsonToken
pxJsonTokenString(PxString8 string)
{
    return (PxJsonToken) {
        .type     = PX_JSON_TOKEN_STRING,
        .string_8 = string,
    };
}

PxJsonToken
pxJsonTokenUnsigned(pxuword value)
{
    return (PxJsonToken) {
        .type          = PX_JSON_TOKEN_UNSIGNED,
        .unsigned_word = value,
    };
}

PxJsonToken
pxJsonTokenInteger(pxiword value)
{
    return (PxJsonToken) {
        .type         = PX_JSON_TOKEN_INTEGER,
        .integer_word = value,
    };
}

PxJsonToken
pxJsonTokenFloating(pxfword value)
{
    return (PxJsonToken) {
        .type          = PX_JSON_TOKEN_FLOATING,
        .floating_word = value,
    };
}

PxJsonToken
pxJsonTokenBoolean(pxbword value)
{
    return (PxJsonToken) {
        .type         = PX_JSON_TOKEN_BOOLEAN,
        .boolean_word = value,
    };
}

PxJsonToken
pxJsonTokenNull()
{
    return (PxJsonToken) {
        .type = PX_JSON_TOKEN_NULL,
    };
}

PxJsonToken
pxJsonTokenCount()
{
    return (PxJsonToken) {
        .type = PX_JSON_TOKEN_COUNT,
    };
}

#endif // PX_ENCODING_JSON_TOKEN_C
