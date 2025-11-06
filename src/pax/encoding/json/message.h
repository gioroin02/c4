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

    PX_JSON_MSG_DELEGATE,

    PX_JSON_MSG_COUNT,
}
PxJsonMsgType;

typedef struct PxJsonMsgDelegate
{
    void* ctxt;
    void* proc;
}
PxJsonMsgDelegate;

typedef struct PxJsonMsg
{
    PxJsonMsgType type;
    PxString8     name;

    union
    {
        PxString8 string_8;
        pxuword   unsigned_word;
        pxiword   integer_word;
        pxfword   floating_word;
        pxbword   boolean_word;

        PxJsonMsgDelegate delegate;
    };
}
PxJsonMsg;

PxJsonMsg
pxJsonMsgMake(PxJsonMsgType type);

PxJsonMsg
pxJsonMsgError();

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
pxJsonMsgString(PxString8 value);

PxJsonMsg
pxJsonMsgUnsigned(pxuword value);

PxJsonMsg
pxJsonMsgInteger(pxiword value);

PxJsonMsg
pxJsonMsgFloating(pxfword value);

PxJsonMsg
pxJsonMsgBoolean(pxbword value);

PxJsonMsg
pxJsonMsgNull();

PxJsonMsg
pxJsonMsgDelegate(void* ctxt, void* proc);

PxJsonMsg
pxJsonMsgCount();

PxJsonMsg
pxJsonMsgPair(PxString8 name, PxJsonMsg message);

#endif // PX_ENCODING_JSON_MESSAGE_H
