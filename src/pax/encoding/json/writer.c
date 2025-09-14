#ifndef PX_ENCODING_JSON_WRITER_C
#define PX_ENCODING_JSON_WRITER_C

#include "writer.h"

PxJsonWriter
pxJsonWriterMake(PxArena* arena, pxiword length, PxWriter* writer)
{
    PxQueue stack =
        pxQueueReserve(arena, PxJsonLayerType, length);

    if (stack.length <= 0) return (PxJsonWriter) {0};

    return (PxJsonWriter) {
        .writer = writer,
        .stack  = stack,
    };
}

pxiword
pxJsonWriteChain(PxJsonWriter* self, PxArena* arena, pxiword start, pxiword stop, PxJsonMsg* list)
{
    if (start >= stop) return 0;

    pxiword diff = stop - start;

    for (pxiword i = start; i < stop; i += 1) {
        if (pxJsonWriteMessage(self, arena, list[i]) == 0)
            return i - start;
    }

    return diff;
}

pxb8
pxJsonWriteMessage(PxJsonWriter* self, PxArena* arena, PxJsonMsg message)
{
    PxJsonLayerType parent = PX_JSON_LAYER_NONE;

    pxQueueReadTail(&self->stack, PxJsonLayerType, &parent);

    switch (message.type) {
        case PX_JSON_MSG_OBJECT_OPEN: {
            pxWriterByte(self->writer, PX_ASCII_BRACE_LEFT);

            PxJsonLayerType layer = PX_JSON_LAYER_OBJECT;

            pxQueueInsertTail(&self->stack, PxJsonLayerType,
                &layer);

            self->comma = 0;
        } break;

        case PX_JSON_MSG_OBJECT_CLOSE: {
            pxWriterByte(self->writer,
                PX_ASCII_BRACE_RIGHT);

            pxQueueDropTail(&self->stack);

            self->comma = 1;
        } break;

        case PX_JSON_MSG_ARRAY_OPEN: {
            pxWriterByte(self->writer, PX_ASCII_SQUARE_LEFT);

            PxJsonLayerType layer = PX_JSON_LAYER_ARRAY;

            pxQueueInsertTail(&self->stack, PxJsonLayerType,
                &layer);

            self->comma = 0;
        } break;

        case PX_JSON_MSG_ARRAY_CLOSE: {
            pxWriterByte(self->writer,
                PX_ASCII_SQUARE_RIGHT);

            pxQueueDropTail(&self->stack);

            self->comma = 1;
        } break;

        case PX_JSON_MSG_NAME: {
            if (parent != PX_JSON_LAYER_OBJECT) return 0;

            if (self->comma != 0)
                pxWriterByte(self->writer, PX_ASCII_COMMA);

            pxWriterByte(self->writer, PX_ASCII_QUOTE);
            pxWriterString8(self->writer, message.name);
            pxWriterByte(self->writer, PX_ASCII_QUOTE);
            pxWriterByte(self->writer, PX_ASCII_COLON);
        } break;

        case PX_JSON_MSG_STRING: {
            if (self->comma != 0)
                pxWriterByte(self->writer, PX_ASCII_COMMA);

            if (parent == PX_JSON_LAYER_OBJECT) {
                if (message.name.length <= 0) return 0;

                pxWriterByte(self->writer, PX_ASCII_QUOTE);
                pxWriterString8(self->writer, message.name);
                pxWriterByte(self->writer, PX_ASCII_QUOTE);
                pxWriterByte(self->writer, PX_ASCII_COLON);
            }

            pxWriterByte(self->writer, PX_ASCII_QUOTE);
            pxWriterString8(self->writer, message.string_8);
            pxWriterByte(self->writer, PX_ASCII_QUOTE);

            self->comma = 1;
        } break;

        case PX_JSON_MSG_UNSIGNED: {
            if (self->comma != 0)
                pxWriterByte(self->writer, PX_ASCII_COMMA);

            if (parent == PX_JSON_LAYER_OBJECT) {
                if (message.name.length <= 0) return 0;

                pxWriterByte(self->writer, PX_ASCII_QUOTE);
                pxWriterString8(self->writer, message.name);
                pxWriterByte(self->writer, PX_ASCII_QUOTE);
                pxWriterByte(self->writer, PX_ASCII_COLON);
            }

            PxString8 string = pxString8FromUnsigned(arena, 10,
                PX_FORMAT_OPTION_NONE, message.unsigned_word);

            pxWriterString8(self->writer, string);

            self->comma = 1;
        } break;

        case PX_JSON_MSG_INTEGER: {
            if (self->comma != 0)
                pxWriterByte(self->writer, PX_ASCII_COMMA);

            if (parent == PX_JSON_LAYER_OBJECT) {
                if (message.name.length <= 0) return 0;

                pxWriterByte(self->writer, PX_ASCII_QUOTE);
                pxWriterString8(self->writer, message.name);
                pxWriterByte(self->writer, PX_ASCII_QUOTE);
                pxWriterByte(self->writer, PX_ASCII_COLON);
            }

            PxString8 string = pxString8FromInteger(arena, 10,
                PX_FORMAT_OPTION_NONE, message.integer_word);

            pxWriterString8(self->writer, string);

            self->comma = 1;
        } break;

        case PX_JSON_MSG_FLOATING: {
            return 0;
        } break;

        case PX_JSON_MSG_BOOLEAN: {
            if (self->comma != 0)
                pxWriterByte(self->writer, PX_ASCII_COMMA);

            if (parent == PX_JSON_LAYER_OBJECT) {
                if (message.name.length <= 0) return 0;

                pxWriterByte(self->writer, PX_ASCII_QUOTE);
                pxWriterString8(self->writer, message.name);
                pxWriterByte(self->writer, PX_ASCII_QUOTE);
                pxWriterByte(self->writer, PX_ASCII_COLON);
            }

            if (message.boolean_word != 0)
                pxWriterString8(self->writer, pxs8("true"));
            else
                pxWriterString8(self->writer, pxs8("false"));

            self->comma = 1;
        } break;

        case PX_JSON_MSG_NULL: {
            if (self->comma != 0)
                pxWriterByte(self->writer, PX_ASCII_COMMA);

            if (parent == PX_JSON_LAYER_OBJECT) {
                if (message.name.length <= 0) return 0;

                pxWriterByte(self->writer, PX_ASCII_QUOTE);
                pxWriterString8(self->writer, message.name);
                pxWriterByte(self->writer, PX_ASCII_QUOTE);
                pxWriterByte(self->writer, PX_ASCII_COLON);
            }

            pxWriterString8(self->writer, pxs8("null"));

            self->comma = 1;
        } break;

        default: return 0;
    }

    pxWriterFlush(self->writer);

    return 1;
}

#endif // PX_ENCODING_JSON_WRITER_C
