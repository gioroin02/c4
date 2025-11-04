#ifndef PAX_ENCODING_JSON_READER_C
#define PAX_ENCODING_JSON_READER_C

#include "./reader.h"
#include "message.h"
#include "scanner.c"

Pax_JSON_Reader
pax_json_reader_create(Pax_Arena* arena, paxiword length, Pax_Scanner scanner)
{
    return (Pax_JSON_Reader) {
        .stack   = pax_array_ring_create(arena, Pax_JSON_Layer_Kind, length),
        .scanner = scanner,
    };
}

Pax_JSON_Message
pax_json_reader_message(Pax_JSON_Reader* self, Pax_Arena* arena)
{
    Pax_JSON_Message    result = pax_json_message_end();
    Pax_JSON_Layer_Kind parent = PAX_JSON_LAYER_KIND_NONE;

    while (result.kind == PAX_JSON_MESSAGE_KIND_END) {
        paxiword index = pax_array_ring_tail(&self->stack);

        pax_array_ring_peek(&self->stack, Pax_JSON_Layer_Kind, index, &parent, 1);

        Pax_JSON_Token token = self->token;

        self->token = (Pax_JSON_Token) {0};

        if (token.kind == PAX_JSON_TOKEN_KIND_NONE)
            token = pax_scanner_read_json_token(&self->scanner, arena);

        if (token.kind == PAX_JSON_TOKEN_KIND_END) break;

        switch (token.kind) {
            case PAX_JSON_TOKEN_KIND_ERROR: {
                result = pax_json_message_error();
            } break;

            case PAX_JSON_TOKEN_KIND_OBJECT_OPEN: {
                result = pax_json_message_object_open();

                Pax_JSON_Layer_Kind layer = PAX_JSON_LAYER_KIND_OBJECT;

                pax_array_ring_insert_tail(&self->stack,
                    Pax_JSON_Layer_Kind, &layer, 1);

                self->name   = (Pax_String8) {0};
                self->flags &= ~PAX_JSON_READER_COMMA;
                self->flags &= ~PAX_JSON_READER_COLON;
            } break;

            case PAX_JSON_TOKEN_KIND_OBJECT_CLOSE: {
                result = pax_json_message_object_close();

                pax_array_ring_remove_tail(&self->stack,
                    Pax_JSON_Layer_Kind, 0, 1);

                self->name   = (Pax_String8) {0};
                self->flags &= ~PAX_JSON_READER_COMMA;
                self->flags &= ~PAX_JSON_READER_COLON;
            } break;

            case PAX_JSON_TOKEN_KIND_ARRAY_OPEN: {
                result = pax_json_message_array_open();

                Pax_JSON_Layer_Kind layer = PAX_JSON_LAYER_KIND_ARRAY;

                pax_array_ring_insert_tail(&self->stack,
                    Pax_JSON_Layer_Kind, &layer, 1);

                self->name   = (Pax_String8) {0};
                self->flags &= ~PAX_JSON_READER_COMMA;
                self->flags &= ~PAX_JSON_READER_COLON;
            } break;

            case PAX_JSON_TOKEN_KIND_ARRAY_CLOSE: {
                result = pax_json_message_array_close();

                pax_array_ring_remove_tail(&self->stack,
                    Pax_JSON_Layer_Kind, 0, 1);

                self->name   = (Pax_String8) {0};
                self->flags &= ~PAX_JSON_READER_COMMA;
                self->flags &= ~PAX_JSON_READER_COLON;
            } break;

            case PAX_JSON_TOKEN_KIND_COLON: {
                if (parent == PAX_JSON_LAYER_KIND_ARRAY)
                    result = pax_json_message_error();

                if (parent == PAX_JSON_LAYER_KIND_OBJECT) {
                    self->token = pax_scanner_read_json_token(&self->scanner, arena);

                    switch (self->token.kind) {
                        case PAX_JSON_TOKEN_KIND_OBJECT_OPEN:
                        case PAX_JSON_TOKEN_KIND_ARRAY_OPEN:
                            result = pax_json_message_name(self->name);
                        break;

                        default: break;
                    }
                }

                self->flags |=  PAX_JSON_READER_COLON;
                self->flags &= ~PAX_JSON_READER_COMMA;
            } break;

            case PAX_JSON_TOKEN_KIND_COMMA: {
                self->name   = (Pax_String8) {0};
                self->flags &= ~PAX_JSON_READER_COLON;
                self->flags |=  PAX_JSON_READER_COMMA;
            } break;

            case PAX_JSON_TOKEN_KIND_STRING: {
                paxb8 colon = (self->flags & PAX_JSON_READER_COLON) != 0;

                if (parent != PAX_JSON_LAYER_KIND_OBJECT || colon != 0) {
                    result = pax_json_message_string(token.value_string);

                    if (self->name.length > 0)
                        result = pax_json_message_pair(self->name, result);
                } else
                    self->name = token.value_string;

                self->flags &= ~PAX_JSON_READER_COMMA;
                self->flags &= ~PAX_JSON_READER_COLON;
            } break;

            case PAX_JSON_TOKEN_KIND_UNSIGNED: {
                result = pax_json_message_unsigned(token.value_unsigned);

                if (self->name.length > 0)
                    result = pax_json_message_pair(self->name, result);

                self->flags &= ~PAX_JSON_READER_COMMA;
                self->flags &= ~PAX_JSON_READER_COLON;
            } break;

            case PAX_JSON_TOKEN_KIND_INTEGER: {
                result = pax_json_message_integer(token.value_integer);

                if (self->name.length > 0)
                    result = pax_json_message_pair(self->name, result);

                self->flags &= ~PAX_JSON_READER_COMMA;
                self->flags &= ~PAX_JSON_READER_COLON;
            } break;

            case PAX_JSON_TOKEN_KIND_FLOATING: {
                result = pax_json_message_floating(token.value_floating);

                if (self->name.length > 0)
                    result = pax_json_message_pair(self->name, result);

                self->flags &= ~PAX_JSON_READER_COMMA;
                self->flags &= ~PAX_JSON_READER_COLON;
            } break;

            case PAX_JSON_TOKEN_KIND_BOOLEAN: {
                result = pax_json_message_boolean(token.value_boolean);

                if (self->name.length > 0)
                    result = pax_json_message_pair(self->name, result);

                self->flags &= ~PAX_JSON_READER_COMMA;
                self->flags &= ~PAX_JSON_READER_COLON;
            } break;

            case PAX_JSON_TOKEN_KIND_NULL: {
                result = pax_json_message_null();

                if (self->name.length > 0)
                    result = pax_json_message_pair(self->name, result);

                self->flags &= ~PAX_JSON_READER_COMMA;
                self->flags &= ~PAX_JSON_READER_COLON;
            } break;

            default: break;
        }
    }

    if (result.name.length > 0)
        self->name = (Pax_String8) {0};

    return result;
}

paxb8
pax_json_reader_record(Pax_JSON_Reader* self, Pax_Arena* arena, paxiword* size, Pax_JSON_Message* values, paxiword length)
{
    Pax_JSON_Message message = pax_json_reader_message(self, arena);
    paxiword         temp    = 0;

    if (message.kind != PAX_JSON_MESSAGE_KIND_OBJECT_OPEN) return 0;

    message = pax_json_reader_message(self, arena);

    while (message.kind != PAX_JSON_MESSAGE_KIND_OBJECT_CLOSE) {
        if (message.kind == PAX_JSON_MESSAGE_KIND_END) break;

        for (paxiword i = 0; i < length; i += 1) {
            switch (message.kind) {
                case PAX_JSON_MESSAGE_KIND_NAME: {
                    if (values[i].kind != PAX_JSON_MESSAGE_KIND_DELEGATE) break;

                    Pax_JSON_Reader_Proc* proc =
                        pax_as(Pax_JSON_Reader_Proc*, values[i].delegate.proc);

                    if (values[i].delegate.proc == 0) break;

                    if (pax_string8_is_equal(message.name, values[i].name) != 0) {
                        paxb8 state =
                            proc(values[i].delegate.ctxt, self, arena);

                        if (state != 0) temp += 1;
                    }
                } break;

                case PAX_JSON_MESSAGE_KIND_STRING:
                case PAX_JSON_MESSAGE_KIND_UNSIGNED:
                case PAX_JSON_MESSAGE_KIND_INTEGER:
                case PAX_JSON_MESSAGE_KIND_FLOATING:
                case PAX_JSON_MESSAGE_KIND_BOOLEAN:
                case PAX_JSON_MESSAGE_KIND_NULL: {
                    if (values[i].kind != message.kind) break;

                    if (pax_string8_is_equal(message.name, values[i].name) != 0) {
                        values[i]  = message;
                        temp      += 1;
                    }
                } break;

                default: break;
            }
        }

        message = pax_json_reader_message(self, arena);
    }

    if (size != 0) *size = temp;

    return 1;
}

paxb8
pax_json_reader_union(Pax_JSON_Reader* self, Pax_Arena* arena, paxiword* index, Pax_JSON_Message* values, paxiword length)
{
    Pax_JSON_Message message = pax_json_reader_message(self, arena);
    paxiword         temp    = length;

    if (message.kind != PAX_JSON_MESSAGE_KIND_OBJECT_OPEN) return 0;

    message = pax_json_reader_message(self, arena);

    while (message.kind != PAX_JSON_MESSAGE_KIND_OBJECT_CLOSE) {
        if (message.kind == PAX_JSON_MESSAGE_KIND_END) break;

        for (paxiword i = 0; i < length && temp == length; i += 1) {
            switch (message.kind) {
                case PAX_JSON_MESSAGE_KIND_NAME: {
                    if (values[i].kind != PAX_JSON_MESSAGE_KIND_DELEGATE) break;

                    Pax_JSON_Reader_Proc* proc =
                        pax_as(Pax_JSON_Reader_Proc*, values[i].delegate.proc);

                    if (values[i].delegate.proc == 0) break;

                    if (pax_string8_is_equal(message.name, values[i].name) != 0) {
                        paxb8 state =
                            proc(values[i].delegate.ctxt, self, arena);

                        if (state != 0) temp = i;
                    }
                } break;

                case PAX_JSON_MESSAGE_KIND_STRING:
                case PAX_JSON_MESSAGE_KIND_UNSIGNED:
                case PAX_JSON_MESSAGE_KIND_INTEGER:
                case PAX_JSON_MESSAGE_KIND_FLOATING:
                case PAX_JSON_MESSAGE_KIND_BOOLEAN:
                case PAX_JSON_MESSAGE_KIND_NULL: {
                    if (values[i].kind != message.kind) break;

                    if (pax_string8_is_equal(message.name, values[i].name) != 0) {
                        values[i] = message;
                        temp      = i;
                    }
                } break;

                default: break;
            }
        }

        message = pax_json_reader_message(self, arena);
    }

    if (index != 0) *index = temp;

    return 1;
}

paxb8
pax_json_reader_array(Pax_JSON_Reader* self, Pax_Arena* arena, paxiword* size, Pax_JSON_Message* values, paxiword length)
{
    Pax_JSON_Message message = pax_json_reader_message(self, arena);
    Pax_JSON_Message sentry  = {0};
    paxiword         temp    = 0;

    if (length > 0) sentry = values[0];

    if (message.kind != PAX_JSON_MESSAGE_KIND_ARRAY_OPEN) return 0;

    message = pax_json_reader_message(self, arena);

    while (message.kind != PAX_JSON_MESSAGE_KIND_ARRAY_CLOSE) {
        if (message.kind == PAX_JSON_MESSAGE_KIND_END) break;

        if (temp < length) {
            switch (message.kind) {
                case PAX_JSON_MESSAGE_KIND_NAME: {
                    if (sentry.kind != PAX_JSON_MESSAGE_KIND_DELEGATE) break;

                    Pax_JSON_Reader_Proc* proc =
                        pax_as(Pax_JSON_Reader_Proc*, sentry.delegate.proc);

                    if (sentry.delegate.proc != 0) {
                        paxb8 state =
                            proc(sentry.delegate.ctxt, self, arena);

                        if (state != 0) temp += 1;
                    }
                } break;

                case PAX_JSON_MESSAGE_KIND_STRING:
                case PAX_JSON_MESSAGE_KIND_UNSIGNED:
                case PAX_JSON_MESSAGE_KIND_INTEGER:
                case PAX_JSON_MESSAGE_KIND_FLOATING:
                case PAX_JSON_MESSAGE_KIND_BOOLEAN:
                case PAX_JSON_MESSAGE_KIND_NULL: {
                    if (sentry.kind == message.kind) {
                        values[temp]  = message;
                        temp         += 1;
                    }
                } break;

                default: break;
            }
        }

        message = pax_json_reader_message(self, arena);
    }

    if (size != 0) *size = temp;

    return 1;
}

#endif // PAX_ENCODING_JSON_READER_C
