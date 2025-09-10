#ifndef PX_ENCODING_JSON_EVENT_C
#define PX_ENCODING_JSON_EVENT_C

#include "event.h"

PxJsonEvent
pxJsonEventNone()
{
    return (PxJsonEvent) {
        .type = PX_JSON_EVENT_NONE,
    };
}

PxJsonEvent
pxJsonEventError(PxString8 subject, PxString8 message)
{
    return (PxJsonEvent) {
        .type   = PX_JSON_EVENT_ERROR,
        .error  = {
            .message = message,
            .subject = subject,
        },
    };
}

PxJsonEvent
pxJsonEventObjectOpen()
{
    return (PxJsonEvent) {
        .type = PX_JSON_EVENT_OBJECT_OPEN,
    };
}

PxJsonEvent
pxJsonEventObjectClose()
{
    return (PxJsonEvent) {
        .type = PX_JSON_EVENT_OBJECT_CLOSE,
    };
}

PxJsonEvent
pxJsonEventArrayOpen()
{
    return (PxJsonEvent) {
        .type = PX_JSON_EVENT_ARRAY_OPEN,
    };
}

PxJsonEvent
pxJsonEventArrayClose()
{
    return (PxJsonEvent) {
        .type = PX_JSON_EVENT_ARRAY_CLOSE,
    };
}

PxJsonEvent
pxJsonEventName(PxString8 name)
{
    return (PxJsonEvent) {
        .type = PX_JSON_EVENT_NAME,
        .name = name,
    };
}

PxJsonEvent
pxJsonEventString(PxString8 value, PxString8 name)
{
    return (PxJsonEvent) {
        .type         = PX_JSON_EVENT_STRING,
        .value_string = value,
        .name         = name,
    };
}

PxJsonEvent
pxJsonEventUnsigned(pxuword value, PxString8 name)
{
    return (PxJsonEvent) {
        .type           = PX_JSON_EVENT_UNSIGNED,
        .value_unsigned = value,
        .name           = name,
    };
}

PxJsonEvent
pxJsonEventInteger(pxiword value, PxString8 name)
{
    return (PxJsonEvent) {
        .type          = PX_JSON_EVENT_INTEGER,
        .value_integer = value,
        .name          = name,
    };
}

PxJsonEvent
pxJsonEventFloating(pxfword value, PxString8 name)
{
    return (PxJsonEvent) {
        .type           = PX_JSON_EVENT_FLOATING,
        .value_floating = value,
        .name           = name,
    };
}

PxJsonEvent
pxJsonEventBoolean(pxbword value, PxString8 name)
{
    return (PxJsonEvent) {
        .type          = PX_JSON_EVENT_BOOLEAN,
        .value_boolean = value,
        .name          = name,
    };
}

PxJsonEvent
pxJsonEventNull(PxString8 name)
{
    return (PxJsonEvent) {
        .type = PX_JSON_EVENT_NULL,
        .name = name,
    };
}

PxJsonEvent
pxJsonEventCount()
{
    return (PxJsonEvent) {
        .type = PX_JSON_EVENT_COUNT,
    };
}

#endif // PX_ENCODING_JSON_EVENT_C
