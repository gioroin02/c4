#ifndef PX_ENCODING_JSON_READER_C
#define PX_ENCODING_JSON_READER_C

#include "reader.h"

PxJsonReader
pxJsonReaderReserve(PxSource source, PxArena* arena, pxiword length)
{
    PxQueue stack =
        pxQueueReserve(arena, PxJsonLayerType, length);

    if (stack.length <= 0) return (PxJsonReader) {0};

    return (PxJsonReader) {
        .source = source,
        .stack  = stack,
    };
}

PxJsonMsg
pxJsonReaderMsg(PxJsonReader* self, PxArena* arena)
{
    PxJsonMsg       result = pxJsonMsgCount();
    PxJsonLayerType parent = PX_JSON_LAYER_NONE;

    while (result.type == PX_JSON_MSG_COUNT) {
        if (pxQueueGetTail(&self->stack, PxJsonLayerType, &parent) == 0)
            parent = PX_JSON_LAYER_NONE;

        PxJsonToken token = self->token;

        if (token.type == PX_JSON_TOKEN_NONE)
            token = pxSourceReadJsonToken(self->source, arena);
        else
            self->token = (PxJsonToken) {0};

        if (token.type == PX_JSON_TOKEN_COUNT) break;

        switch (token.type) {
            case PX_JSON_TOKEN_ERROR: {
                result = pxJsonMsgError();
            } break;

            case PX_JSON_TOKEN_OBJECT_OPEN: {
                result = pxJsonMsgObjectOpen();

                PxJsonLayerType layer = PX_JSON_LAYER_OBJECT;

                pxQueueInsertTail(&self->stack,
                    PxJsonLayerType, &layer);

                self->name   = pxString8Make(0, 0);
                self->flags &= ~PX_JSON_READER_COMMA;
                self->flags &= ~PX_JSON_READER_COLON;
            } break;

            case PX_JSON_TOKEN_OBJECT_CLOSE: {
                result = pxJsonMsgObjectClose();

                pxQueueDropTail(&self->stack);

                self->name   = pxString8Make(0, 0);
                self->flags &= ~PX_JSON_READER_COMMA;
                self->flags &= ~PX_JSON_READER_COLON;
            } break;

            case PX_JSON_TOKEN_ARRAY_OPEN: {
                result = pxJsonMsgArrayOpen();

                PxJsonLayerType layer = PX_JSON_LAYER_ARRAY;

                pxQueueInsertTail(&self->stack,
                    PxJsonLayerType, &layer);

                self->name   = pxString8Make(0, 0);
                self->flags &= ~PX_JSON_READER_COMMA;
                self->flags &= ~PX_JSON_READER_COLON;
            } break;

            case PX_JSON_TOKEN_ARRAY_CLOSE: {
                result = pxJsonMsgArrayClose();

                pxQueueDropTail(&self->stack);

                self->name   = pxString8Make(0, 0);
                self->flags &= ~PX_JSON_READER_COMMA;
                self->flags &= ~PX_JSON_READER_COLON;
            } break;

            case PX_JSON_TOKEN_COLON: {
                if (parent == PX_JSON_LAYER_OBJECT) {
                    self->token = pxSourceReadJsonToken(self->source, arena);

                    switch (self->token.type) {
                        case PX_JSON_TOKEN_OBJECT_OPEN:
                        case PX_JSON_TOKEN_ARRAY_OPEN:
                            result = pxJsonMsgName(self->name);
                        break;

                        default: break;
                    }
                }

                self->flags |=  PX_JSON_READER_COLON;
                self->flags &= ~PX_JSON_READER_COMMA;
            } break;

            case PX_JSON_TOKEN_COMMA: {
                self->name   = pxString8Make(0, 0);
                self->flags &= ~PX_JSON_READER_COLON;
                self->flags |=  PX_JSON_READER_COMMA;
            } break;

            case PX_JSON_TOKEN_STRING: {
                pxb8 colon = (self->flags & PX_JSON_READER_COLON) != 0;

                if (parent != PX_JSON_LAYER_OBJECT || colon != 0) {
                    result = pxJsonMsgString(token.string_8);

                    if (self->name.length > 0)
                        result = pxJsonMsgPair(self->name, result);
                } else
                    self->name = token.string_8;

                self->flags &= ~PX_JSON_READER_COMMA;
                self->flags &= ~PX_JSON_READER_COLON;
            } break;

            case PX_JSON_TOKEN_UNSIGNED: {
                result = pxJsonMsgUnsigned(token.unsigned_word);

                if (self->name.length > 0)
                    result = pxJsonMsgPair(self->name, result);

                self->flags &= ~PX_JSON_READER_COMMA;
                self->flags &= ~PX_JSON_READER_COLON;
            } break;

            case PX_JSON_TOKEN_INTEGER: {
                result = pxJsonMsgInteger(token.integer_word);

                if (self->name.length > 0)
                    result = pxJsonMsgPair(self->name, result);

                self->flags &= ~PX_JSON_READER_COMMA;
                self->flags &= ~PX_JSON_READER_COLON;
            } break;

            case PX_JSON_TOKEN_FLOATING: {
                result = pxJsonMsgFloating(token.floating_word);

                if (self->name.length > 0)
                    result = pxJsonMsgPair(self->name, result);

                self->flags &= ~PX_JSON_READER_COMMA;
                self->flags &= ~PX_JSON_READER_COLON;
            } break;

            case PX_JSON_TOKEN_BOOLEAN: {
                result = pxJsonMsgBoolean(token.boolean_word);

                if (self->name.length > 0)
                    result = pxJsonMsgPair(self->name, result);

                self->flags &= ~PX_JSON_READER_COMMA;
                self->flags &= ~PX_JSON_READER_COLON;
            } break;

            case PX_JSON_TOKEN_NULL: {
                result = pxJsonMsgNull();

                if (self->name.length > 0)
                    result = pxJsonMsgPair(self->name, result);

                self->flags &= ~PX_JSON_READER_COMMA;
                self->flags &= ~PX_JSON_READER_COLON;
            } break;

            default: break;
        }
    }

    if (result.name.length > 0) self->name = pxString8Make(0, 0);

    return result;
}

pxb8
pxJsonReaderObjectOpen(PxJsonReader* self, PxArena* arena, PxJsonMsg* message)
{
    if (message == 0) return 0;

    *message = pxJsonReaderMsg(self, arena);

    if (message->type != PX_JSON_MSG_OBJECT_OPEN)
        return 0;

    return 1;
}

pxb8
pxJsonReaderObjectClose(PxJsonReader* self, PxArena* arena, PxJsonMsg* message)
{
    if (message == 0) return 0;

    *message = pxJsonReaderMsg(self, arena);

    if (message->type != PX_JSON_MSG_OBJECT_CLOSE)
        return 0;

    return 1;
}

pxb8
pxJsonReaderArrayOpen(PxJsonReader* self, PxArena* arena, PxJsonMsg* message)
{
    if (message == 0) return 0;

    *message = pxJsonReaderMsg(self, arena);

    if (message->type != PX_JSON_MSG_ARRAY_OPEN)
        return 0;

    return 1;
}

pxb8
pxJsonReaderArrayClose(PxJsonReader* self, PxArena* arena, PxJsonMsg* message)
{
    if (message == 0) return 0;

    *message = pxJsonReaderMsg(self, arena);

    if (message->type != PX_JSON_MSG_ARRAY_CLOSE)
        return 0;

    return 1;
}

#endif // PX_ENCODING_JSON_READER_C
