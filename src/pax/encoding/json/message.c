#ifndef PX_ENCODING_JSON_MESSAGE_C
#define PX_ENCODING_JSON_MESSAGE_C

#include "message.h"

PxJsonMsg
pxJsonMsgNone()
{
    return (PxJsonMsg) {
        .type = PX_JSON_MSG_NONE,
    };
}

PxJsonMsg
pxJsonMsgError(PxString8 subject, PxString8 content)
{
    return (PxJsonMsg) {
        .type = PX_JSON_MSG_ERROR,

        .error = {
            .subject = subject,
            .content = content,
        },
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
pxJsonMsgString(PxString8 value, PxString8 name)
{
    return (PxJsonMsg) {
        .type     = PX_JSON_MSG_STRING,
        .string_8 = value,
        .name     = name,
    };
}

PxJsonMsg
pxJsonMsgUnsigned(pxuword value, PxString8 name)
{
    return (PxJsonMsg) {
        .type          = PX_JSON_MSG_UNSIGNED,
        .unsigned_word = value,
        .name          = name,
    };
}

PxJsonMsg
pxJsonMsgInteger(pxiword value, PxString8 name)
{
    return (PxJsonMsg) {
        .type         = PX_JSON_MSG_INTEGER,
        .integer_word = value,
        .name         = name,
    };
}

PxJsonMsg
pxJsonMsgFloating(pxfword value, PxString8 name)
{
    return (PxJsonMsg) {
        .type          = PX_JSON_MSG_FLOATING,
        .floating_word = value,
        .name          = name,
    };
}

PxJsonMsg
pxJsonMsgBoolean(pxbword value, PxString8 name)
{
    return (PxJsonMsg) {
        .type         = PX_JSON_MSG_BOOLEAN,
        .boolean_word = value,
        .name         = name,
    };
}

PxJsonMsg
pxJsonMsgNull(PxString8 name)
{
    return (PxJsonMsg) {
        .type = PX_JSON_MSG_NULL,
        .name = name,
    };
}

PxJsonMsg
pxJsonMsgCount()
{
    return (PxJsonMsg) {
        .type = PX_JSON_MSG_COUNT,
    };
}

#endif // PX_ENCODING_JSON_MESSAGE_C
