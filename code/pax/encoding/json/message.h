#ifndef PAX_ENCODING_JSON_MESSAGE_H
#define PAX_ENCODING_JSON_MESSAGE_H

#include "./import.h"

typedef enum Pax_JSON_Layer_Kind
{
    PAX_JSON_LAYER_KIND_NONE,
    PAX_JSON_LAYER_KIND_OBJECT,
    PAX_JSON_LAYER_KIND_ARRAY,
}
Pax_JSON_Layer_Kind;

typedef enum Pax_JSON_Message_Kind
{
    PAX_JSON_MESSAGE_KIND_NONE,

    PAX_JSON_MESSAGE_KIND_ERROR,

    PAX_JSON_MESSAGE_KIND_OBJECT_OPEN,
    PAX_JSON_MESSAGE_KIND_OBJECT_CLOSE,
    PAX_JSON_MESSAGE_KIND_ARRAY_OPEN,
    PAX_JSON_MESSAGE_KIND_ARRAY_CLOSE,

    PAX_JSON_MESSAGE_KIND_NAME,

    PAX_JSON_MESSAGE_KIND_STRING,
    PAX_JSON_MESSAGE_KIND_UNSIGNED,
    PAX_JSON_MESSAGE_KIND_INTEGER,
    PAX_JSON_MESSAGE_KIND_FLOATING,
    PAX_JSON_MESSAGE_KIND_BOOLEAN,
    PAX_JSON_MESSAGE_KIND_NULL,

    PAX_JSON_MESSAGE_KIND_DELEGATE,

    PAX_JSON_MESSAGE_KIND_END,
}
Pax_JSON_Message_Kind;

typedef struct Pax_JSON_Delegate
{
    void* ctxt;
    void* proc;
}
Pax_JSON_Delegate;

typedef struct Pax_JSON_Message
{
    Pax_JSON_Message_Kind kind;

    Pax_String8 name;

    union
    {
        Pax_String8 value_string;
        paxuword    value_unsigned;
        paxiword    value_integer;
        paxfword    value_floating;
        paxbword    value_boolean;

        Pax_JSON_Delegate delegate;
    };
}
Pax_JSON_Message;

Pax_JSON_Message
pax_json_message_make(Pax_JSON_Message_Kind kind);

Pax_JSON_Message
pax_json_message_error();

Pax_JSON_Message
pax_json_message_object_open();

Pax_JSON_Message
pax_json_message_object_close();

Pax_JSON_Message
pax_json_message_array_open();

Pax_JSON_Message
pax_json_message_array_close();

Pax_JSON_Message
pax_json_message_name(Pax_String8 name);

Pax_JSON_Message
pax_json_message_string(Pax_String8 value);

Pax_JSON_Message
pax_json_message_unsigned(paxuword value);

Pax_JSON_Message
pax_json_message_integer(paxiword value);

Pax_JSON_Message
pax_json_message_floating(paxfword value);

Pax_JSON_Message
pax_json_message_boolean(paxbword value);

Pax_JSON_Message
pax_json_message_null();

Pax_JSON_Message
pax_json_message_delegate(void* ctxt, void* proc);

Pax_JSON_Message
pax_json_message_end();

Pax_JSON_Message
pax_json_message_pair(Pax_String8 name, Pax_JSON_Message message);

#endif // PAX_ENCODING_JSON_MESSAGE_H
