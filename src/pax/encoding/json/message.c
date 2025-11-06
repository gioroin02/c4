#ifndef PX_ENCODING_JSON_MESSAGE_C
#define PX_ENCODING_JSON_MESSAGE_C

#include "message.h"

PxJsonMsg
pxJsonMsgMake(PxJsonMsgType type)
{
    return (PxJsonMsg) {.type = type};
}

PxJsonMsg
pxJsonMsgError()
{
    return (PxJsonMsg) {
        .type = PX_JSON_MSG_ERROR,
    };
}

PxJsonMsg
pxJsonMsgObjectOpen()
{
    return (PxJsonMsg) {
        .type = PX_JSON_MSG_OBJECT_OPEN,
    };
}

PxJsonMsg
pxJsonMsgObjectClose()
{
    return (PxJsonMsg) {
        .type = PX_JSON_MSG_OBJECT_CLOSE,
    };
}

PxJsonMsg
pxJsonMsgArrayOpen()
{
    return (PxJsonMsg) {
        .type = PX_JSON_MSG_ARRAY_OPEN,
    };
}

PxJsonMsg
pxJsonMsgArrayClose()
{
    return (PxJsonMsg) {
        .type = PX_JSON_MSG_ARRAY_CLOSE,
    };
}

PxJsonMsg
pxJsonMsgName(PxString8 name)
{
    return (PxJsonMsg) {
        .type = PX_JSON_MSG_NAME,
        .name = name,
    };
}

PxJsonMsg
pxJsonMsgString(PxString8 value)
{
    return (PxJsonMsg) {
        .type     = PX_JSON_MSG_STRING,
        .string_8 = value,
    };
}

PxJsonMsg
pxJsonMsgUnsigned(pxuword value)
{
    return (PxJsonMsg) {
        .type          = PX_JSON_MSG_UNSIGNED,
        .unsigned_word = value,
    };
}

PxJsonMsg
pxJsonMsgInteger(pxiword value)
{
    return (PxJsonMsg) {
        .type         = PX_JSON_MSG_INTEGER,
        .integer_word = value,
    };
}

PxJsonMsg
pxJsonMsgFloating(pxfword value)
{
    return (PxJsonMsg) {
        .type          = PX_JSON_MSG_FLOATING,
        .floating_word = value,
    };
}

PxJsonMsg
pxJsonMsgBoolean(pxbword value)
{
    return (PxJsonMsg) {
        .type         = PX_JSON_MSG_BOOLEAN,
        .boolean_word = value,
    };
}

PxJsonMsg
pxJsonMsgNull()
{
    return (PxJsonMsg) {
        .type = PX_JSON_MSG_NULL,
    };
}

PxJsonMsg
pxJsonMsgDelegate(void* ctxt, void* proc)
{
    return (PxJsonMsg) {
        .type = PX_JSON_MSG_DELEGATE,

        .delegate = {
            .ctxt = ctxt,
            .proc = proc,
        },
    };
}

PxJsonMsg
pxJsonMsgCount()
{
    return (PxJsonMsg) {
        .type = PX_JSON_MSG_COUNT,
    };
}

PxJsonMsg
pxJsonMsgPair(PxString8 name, PxJsonMsg value)
{
    value.name = name;

    return value;
}

#endif // PX_ENCODING_JSON_MESSAGE_C
