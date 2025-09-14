#ifndef PX_ENCODING_JSON_MESSAGE_H
#define PX_ENCODING_JSON_MESSAGE_H

#include "import.h"

typedef enum PxJsonLayerType
{
    PX_JSON_LAYER_NONE,
    PX_JSON_LAYER_OBJECT,
    PX_JSON_LAYER_ARRAY,
}
PxJsonLayerType;

typedef enum PxJsonMsgType
{
    PX_JSON_MSG_NONE,

    PX_JSON_MSG_ERROR,

    PX_JSON_MSG_OBJECT_OPEN,
    PX_JSON_MSG_OBJECT_CLOSE,
    PX_JSON_MSG_ARRAY_OPEN,
    PX_JSON_MSG_ARRAY_CLOSE,

    PX_JSON_MSG_NAME,

    PX_JSON_MSG_STRING,
    PX_JSON_MSG_UNSIGNED,
    PX_JSON_MSG_INTEGER,
    PX_JSON_MSG_FLOATING,
    PX_JSON_MSG_BOOLEAN,
    PX_JSON_MSG_NULL,

    PX_JSON_MSG_COUNT,
}
PxJsonMsgType;

typedef struct PxJsonMsgError
{
    PxString8 subject;
    PxString8 content;
}
PxJsonMsgError;

typedef struct PxJsonMsg
{
    PxJsonMsgType type;
    PxString8     name;

    union
    {
        PxJsonMsgError error;

        PxString8 string_8;
        pxuword   unsigned_word;
        pxiword   integer_word;
        pxfword   floating_word;
        pxbword   boolean_word;
    };
}
PxJsonMsg;

PxJsonMsg
pxJsonMsgNone();

PxJsonMsg
pxJsonMsgError(PxString8 subject, PxString8 message);

PxJsonMsg
pxJsonMsgObjectOpen();

PxJsonMsg
pxJsonMsgObjectClose();

PxJsonMsg
pxJsonMsgArrayOpen();

PxJsonMsg
pxJsonMsgArrayClose();

PxJsonMsg
pxJsonMsgName(PxString8 name);

PxJsonMsg
pxJsonMsgString(PxString8 value, PxString8 name);

PxJsonMsg
pxJsonMsgUnsigned(pxuword value, PxString8 name);

PxJsonMsg
pxJsonMsgInteger(pxiword value, PxString8 name);

PxJsonMsg
pxJsonMsgFloating(pxfword value, PxString8 name);

PxJsonMsg
pxJsonMsgBoolean(pxbword value, PxString8 name);

PxJsonMsg
pxJsonMsgNull(PxString8 name);

PxJsonMsg
pxJsonMsgCount();

#endif // PX_ENCODING_JSON_MESSAGE_H
