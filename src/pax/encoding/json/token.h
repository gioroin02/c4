#ifndef PX_ENCODING_JSON_TOKEN_H
#define PX_ENCODING_JSON_TOKEN_H

#include "import.h"

typedef enum PxJsonTokenType
{
    PX_JSON_TOKEN_NONE,

    PX_JSON_TOKEN_ERROR,

    PX_JSON_TOKEN_OBJECT_OPEN,
    PX_JSON_TOKEN_OBJECT_CLOSE,
    PX_JSON_TOKEN_ARRAY_OPEN,
    PX_JSON_TOKEN_ARRAY_CLOSE,
    PX_JSON_TOKEN_COLON,
    PX_JSON_TOKEN_COMMA,

    PX_JSON_TOKEN_STRING,
    PX_JSON_TOKEN_UNSIGNED,
    PX_JSON_TOKEN_INTEGER,
    PX_JSON_TOKEN_FLOATING,
    PX_JSON_TOKEN_BOOLEAN,
    PX_JSON_TOKEN_NULL,

    PX_JSON_TOKEN_COUNT,
}
PxJsonTokenType;

typedef struct PxJsonToken
{
    PxJsonTokenType type;

    union
    {
        PxString8 string_8;
        pxuword   unsigned_word;
        pxiword   integer_word;
        pxfword   floating_word;
        pxbword   boolean_word;
    };
}
PxJsonToken;

PxJsonToken
pxJsonTokenMake(PxJsonTokenType type);

PxJsonToken
pxJsonTokenError();

PxJsonToken
pxJsonTokenObjectOpen();

PxJsonToken
pxJsonTokenObjectClose();

PxJsonToken
pxJsonTokenArrayOpen();

PxJsonToken
pxJsonTokenArrayClose();

PxJsonToken
pxJsonTokenColon();

PxJsonToken
pxJsonTokenComma();

PxJsonToken
pxJsonTokenString(PxString8 string);

PxJsonToken
pxJsonTokenUnsigned(pxuword value);

PxJsonToken
pxJsonTokenInteger(pxiword value);

PxJsonToken
pxJsonTokenFloating(pxfword value);

PxJsonToken
pxJsonTokenBoolean(pxbword value);

PxJsonToken
pxJsonTokenNull();

PxJsonToken
pxJsonTokenCount();

#endif // PX_ENCODING_JSON_TOKEN_H
