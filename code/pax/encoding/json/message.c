#ifndef PAX_ENCODING_JSON_MESSAGE_C
#define PAX_ENCODING_JSON_MESSAGE_C

#include "./message.h"

Pax_JSON_Message
pax_json_message_make(Pax_JSON_Message_Kind kind)
{
    return (Pax_JSON_Message) {.kind = kind};
}

Pax_JSON_Message
pax_json_message_error()
{
    return (Pax_JSON_Message) {
        .kind = PAX_JSON_MESSAGE_KIND_ERROR,
    };
}

Pax_JSON_Message
pax_json_message_object_open()
{
    return (Pax_JSON_Message) {
        .kind = PAX_JSON_MESSAGE_KIND_OBJECT_OPEN,
    };
}

Pax_JSON_Message
pax_json_message_object_close()
{
    return (Pax_JSON_Message) {
        .kind = PAX_JSON_MESSAGE_KIND_OBJECT_CLOSE,
    };
}

Pax_JSON_Message
pax_json_message_array_open()
{
    return (Pax_JSON_Message) {
        .kind = PAX_JSON_MESSAGE_KIND_ARRAY_OPEN,
    };
}

Pax_JSON_Message
pax_json_message_array_close()
{
    return (Pax_JSON_Message) {
        .kind = PAX_JSON_MESSAGE_KIND_ARRAY_CLOSE,
    };
}

Pax_JSON_Message
pax_json_message_name(Pax_String8 name)
{
    return (Pax_JSON_Message) {
        .kind = PAX_JSON_MESSAGE_KIND_NAME,
        .name = name,
    };
}

Pax_JSON_Message
pax_json_message_string(Pax_String8 value)
{
    return (Pax_JSON_Message) {
        .kind = PAX_JSON_MESSAGE_KIND_STRING,

        .value_string = value,
    };
}

Pax_JSON_Message
pax_json_message_unsigned(paxuword value)
{
    return (Pax_JSON_Message) {
        .kind = PAX_JSON_MESSAGE_KIND_UNSIGNED,

        .value_unsigned = value,
    };
}

Pax_JSON_Message
pax_json_message_integer(paxiword value)
{
    return (Pax_JSON_Message) {
        .kind = PAX_JSON_MESSAGE_KIND_INTEGER,

        .value_integer = value,
    };
}

Pax_JSON_Message
pax_json_message_floating(paxfword value)
{
    return (Pax_JSON_Message) {
        .kind = PAX_JSON_MESSAGE_KIND_FLOATING,

        .value_floating = value,
    };
}

Pax_JSON_Message
pax_json_message_boolean(paxbword value)
{
    return (Pax_JSON_Message) {
        .kind = PAX_JSON_MESSAGE_KIND_BOOLEAN,

        .value_boolean = value,
    };
}

Pax_JSON_Message
pax_json_message_null()
{
    return (Pax_JSON_Message) {
        .kind = PAX_JSON_MESSAGE_KIND_NULL,
    };
}

Pax_JSON_Message
pax_json_message_delegate(void* ctxt, void* proc)
{
    return (Pax_JSON_Message) {
        .kind = PAX_JSON_MESSAGE_KIND_DELEGATE,

        .delegate = {
            .ctxt = ctxt,
            .proc = proc,
        },
    };
}

Pax_JSON_Message
pax_json_message_end()
{
    return (Pax_JSON_Message) {
        .kind = PAX_JSON_MESSAGE_KIND_END,
    };
}

Pax_JSON_Message
pax_json_message_pair(Pax_String8 name, Pax_JSON_Message value)
{
    value.name = name;

    return value;
}

#endif // PAX_ENCODING_JSON_MESSAGE_C
