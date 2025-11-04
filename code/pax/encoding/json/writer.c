#ifndef PAX_ENCODING_JSON_WRITER_C
#define PAX_ENCODING_JSON_WRITER_C

#include "./writer.h"
#include "message.h"

Pax_JSON_Writer
pax_json_writer_create(Pax_Arena* arena, paxiword length, Pax_Target* target)
{
    return (Pax_JSON_Writer) {
        .stack  = pax_array_ring_create(arena, Pax_JSON_Layer_Kind, length),
        .target = target,
    };
}

paxb8
pax_json_writer_message(Pax_JSON_Writer* self, Pax_Arena* arena, Pax_JSON_Message message)
{
    Pax_JSON_Layer_Kind parent = PAX_JSON_LAYER_KIND_NONE;
    paxiword            index  = pax_array_ring_tail(&self->stack);

    pax_array_ring_peek(&self->stack, Pax_JSON_Layer_Kind, index, &parent, 1);

    switch (message.kind) {
        case PAX_JSON_MESSAGE_KIND_OBJECT_OPEN: {
            pax_target_write_byte(self->target, PAX_ASCII_BRACE_LEFT);

            Pax_JSON_Layer_Kind layer = PAX_JSON_LAYER_KIND_OBJECT;

            pax_array_ring_insert_tail(&self->stack,
                Pax_JSON_Layer_Kind, &layer, 1);

            self->flags &= ~PAX_JSON_WRITER_COMMA;
        } break;

        case PAX_JSON_MESSAGE_KIND_OBJECT_CLOSE: {
            pax_target_write_byte(self->target, PAX_ASCII_BRACE_RIGHT);

            pax_array_ring_remove_tail(&self->stack,
                Pax_JSON_Layer_Kind, 0, 1);

            self->flags |= PAX_JSON_WRITER_COMMA;
        } break;

        case PAX_JSON_MESSAGE_KIND_ARRAY_OPEN: {
            pax_target_write_byte(self->target, PAX_ASCII_SQUARE_LEFT);

            Pax_JSON_Layer_Kind layer = PAX_JSON_LAYER_KIND_ARRAY;

            pax_array_ring_insert_tail(&self->stack,
                Pax_JSON_Layer_Kind, &layer, 1);

            self->flags &= ~PAX_JSON_WRITER_COMMA;
        } break;

        case PAX_JSON_MESSAGE_KIND_ARRAY_CLOSE: {
            pax_target_write_byte(self->target, PAX_ASCII_SQUARE_RIGHT);

            pax_array_ring_remove_tail(&self->stack,
                Pax_JSON_Layer_Kind, 0, 1);

            self->flags |= PAX_JSON_WRITER_COMMA;
        } break;

        case PAX_JSON_MESSAGE_KIND_NAME: {
            if (parent != PAX_JSON_LAYER_KIND_OBJECT) return 0;

            if ((self->flags & PAX_JSON_WRITER_COMMA) != 0)
                pax_target_write_byte(self->target, PAX_ASCII_COMMA);

            pax_target_write_byte(self->target, PAX_ASCII_QUOTE);
            pax_target_write_string8(self->target, message.name);
            pax_target_write_byte(self->target, PAX_ASCII_QUOTE);
            pax_target_write_byte(self->target, PAX_ASCII_COLON);
        } break;

        case PAX_JSON_MESSAGE_KIND_STRING: {
            if ((self->flags & PAX_JSON_WRITER_COMMA) != 0)
                pax_target_write_byte(self->target, PAX_ASCII_COMMA);

            if (parent == PAX_JSON_LAYER_KIND_OBJECT) {
                if (message.name.length <= 0) return 0;

                pax_target_write_byte(self->target, PAX_ASCII_QUOTE);
                pax_target_write_string8(self->target, message.name);
                pax_target_write_byte(self->target, PAX_ASCII_QUOTE);
                pax_target_write_byte(self->target, PAX_ASCII_COLON);
            }

            pax_target_write_byte(self->target, PAX_ASCII_QUOTE);
            pax_target_write_string8(self->target, message.value_string);
            pax_target_write_byte(self->target, PAX_ASCII_QUOTE);

            self->flags |= PAX_JSON_WRITER_COMMA;
        } break;

        case PAX_JSON_MESSAGE_KIND_UNSIGNED: {
            if ((self->flags & PAX_JSON_WRITER_COMMA) != 0)
                pax_target_write_byte(self->target, PAX_ASCII_COMMA);

            if (parent == PAX_JSON_LAYER_KIND_OBJECT) {
                if (message.name.length <= 0) return 0;

                pax_target_write_byte(self->target, PAX_ASCII_QUOTE);
                pax_target_write_string8(self->target, message.name);
                pax_target_write_byte(self->target, PAX_ASCII_QUOTE);
                pax_target_write_byte(self->target, PAX_ASCII_COLON);
            }

            paxiword mark = pax_arena_tell(arena);

            Pax_Format_Radix radix = PAX_FORMAT_RADIX_10;
            Pax_Format_Flag  flags = PAX_FORMAT_FLAG_NONE;

            Pax_String8 string = pax_string8_from_unsigned(arena,
                message.value_unsigned, radix, flags);

            pax_target_write_string8(self->target, string);

            pax_arena_rewind(arena, mark, 0);

            self->flags |= PAX_JSON_WRITER_COMMA;
        } break;

        case PAX_JSON_MESSAGE_KIND_INTEGER: {
            if ((self->flags & PAX_JSON_WRITER_COMMA) != 0)
                pax_target_write_byte(self->target, PAX_ASCII_COMMA);

            if (parent == PAX_JSON_LAYER_KIND_OBJECT) {
                if (message.name.length <= 0) return 0;

                pax_target_write_byte(self->target, PAX_ASCII_QUOTE);
                pax_target_write_string8(self->target, message.name);
                pax_target_write_byte(self->target, PAX_ASCII_QUOTE);
                pax_target_write_byte(self->target, PAX_ASCII_COLON);
            }

            paxiword mark = pax_arena_tell(arena);

            Pax_Format_Radix radix = PAX_FORMAT_RADIX_10;
            Pax_Format_Flag  flags = PAX_FORMAT_FLAG_NONE;

            Pax_String8 string = pax_string8_from_integer(arena,
                message.value_integer, radix, flags);

            pax_target_write_string8(self->target, string);

            pax_arena_rewind(arena, mark, 0);

            self->flags |= PAX_JSON_WRITER_COMMA;
        } break;

        case PAX_JSON_MESSAGE_KIND_FLOATING: {
            return 0;
        } break;

        case PAX_JSON_MESSAGE_KIND_BOOLEAN: {
            if ((self->flags & PAX_JSON_WRITER_COMMA) != 0)
                pax_target_write_byte(self->target, PAX_ASCII_COMMA);

            if (parent == PAX_JSON_LAYER_KIND_OBJECT) {
                if (message.name.length <= 0) return 0;

                pax_target_write_byte(self->target, PAX_ASCII_QUOTE);
                pax_target_write_string8(self->target, message.name);
                pax_target_write_byte(self->target, PAX_ASCII_QUOTE);
                pax_target_write_byte(self->target, PAX_ASCII_COLON);
            }

            paxiword mark = pax_arena_tell(arena);

            Pax_Format_Flag flags = PAX_FORMAT_FLAG_NONE;

            Pax_String8 string = pax_string8_from_boolean(arena,
                message.value_boolean, flags);

            pax_target_write_string8(self->target, string);

            pax_arena_rewind(arena, mark, 0);

            self->flags |= PAX_JSON_WRITER_COMMA;
        } break;

        case PAX_JSON_MESSAGE_KIND_NULL: {
            if ((self->flags & PAX_JSON_WRITER_COMMA) != 0)
                pax_target_write_byte(self->target, PAX_ASCII_COMMA);

            if (parent == PAX_JSON_LAYER_KIND_OBJECT) {
                if (message.name.length <= 0) return 0;

                pax_target_write_byte(self->target, PAX_ASCII_QUOTE);
                pax_target_write_string8(self->target, message.name);
                pax_target_write_byte(self->target, PAX_ASCII_QUOTE);
                pax_target_write_byte(self->target, PAX_ASCII_COLON);
            }

            pax_target_write_string8(self->target, pax_str8("null"));

            self->flags |= PAX_JSON_WRITER_COMMA;
        } break;

        case PAX_JSON_MESSAGE_KIND_DELEGATE: {
            Pax_JSON_Writer_Proc* proc =
                pax_as(Pax_JSON_Writer_Proc*, message.delegate.proc);

            if ((self->flags & PAX_JSON_WRITER_COMMA) != 0)
                pax_target_write_byte(self->target, PAX_ASCII_COMMA);

            if (parent == PAX_JSON_LAYER_KIND_OBJECT) {
                if (message.name.length <= 0) return 0;

                pax_target_write_byte(self->target, PAX_ASCII_QUOTE);
                pax_target_write_string8(self->target, message.name);
                pax_target_write_byte(self->target, PAX_ASCII_QUOTE);
                pax_target_write_byte(self->target, PAX_ASCII_COLON);
            }

            if (message.delegate.proc != 0)
                proc(message.delegate.ctxt, self, arena);
        } break;

        default: return 0;
    }

    return 1;
}

paxb8
pax_json_writer_record(Pax_JSON_Writer* self, Pax_Arena* arena, paxiword* size, Pax_JSON_Message* values, paxiword length)
{
    paxiword temp = 0;

    pax_json_writer_message(self, arena, pax_json_message_object_open());

    for (paxiword i = 0; i < length; i += 1) {
        if (pax_json_writer_message(self, arena, values[i]) != 0)
            temp += 1;
    }

    pax_json_writer_message(self, arena, pax_json_message_object_close());

    if (size != 0) *size = temp;

    return 1;
}

paxb8
pax_json_writer_union(Pax_JSON_Writer* self, Pax_Arena* arena, paxiword index, Pax_JSON_Message* values, paxiword length)
{
    paxb8 state = 1;

    if (index < 0 || index >= length)
        return 0;

    pax_json_writer_message(self, arena, pax_json_message_object_open());

    if (pax_json_writer_message(self, arena, values[index]) == 0)
        state = 0;

    pax_json_writer_message(self, arena, pax_json_message_object_close());

    return state;
}

paxb8
pax_json_writer_array(Pax_JSON_Writer* self, Pax_Arena* arena, paxiword* size, Pax_JSON_Message* values, paxiword length)
{
    paxiword temp = 0;

    pax_json_writer_message(self, arena, pax_json_message_array_open());

    for (paxiword i = 0; i < length; i += 1) {
        if (pax_json_writer_message(self, arena, values[i]) != 0)
            temp += 1;
    }

    pax_json_writer_message(self, arena, pax_json_message_array_close());

    if (size != 0) *size = temp;

    return 1;
}

#endif // PAX_ENCODING_JSON_WRITER_C
