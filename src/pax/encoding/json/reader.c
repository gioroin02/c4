#ifndef PX_ENCODING_JSON_READER_C
#define PX_ENCODING_JSON_READER_C

#include "reader.h"

PxJsonReader
pxJsonReaderMake(PxArena* arena, pxiword length, PxReader* reader)
{
    PxQueue stack =
        pxQueueReserve(arena, PxJsonLayerType, length);

    if (stack.length <= 0) return (PxJsonReader) {0};

    return (PxJsonReader) {
        .reader = reader,
        .stack  = stack,
    };
}

PxJsonMsg
pxJsonReadMessage(PxJsonReader* self, PxArena* arena)
{
    PxJsonMsg     result = pxJsonMsgCount();
    PxJsonLayerType parent = PX_JSON_LAYER_NONE;

    while (result.type == PX_JSON_MSG_COUNT) {
        if (pxQueueReadTail(&self->stack, PxJsonLayerType, &parent) == 0)
            parent = PX_JSON_LAYER_NONE;

        PxJsonToken token = pxJsonNext(self->reader, arena);

        if (token.type == PX_JSON_TOKEN_COUNT) break;

        switch (token.type) {
            case PX_JSON_TOKEN_ERROR: {
                result = pxJsonMsgError(token.error.subject,
                    token.error.content);
            } break;

            case PX_JSON_TOKEN_OBJECT_OPEN: {
                result = pxJsonMsgObjectOpen();

                PxJsonLayerType layer = PX_JSON_LAYER_OBJECT;

                pxQueueInsertTail(&self->stack, PxJsonLayerType,
                    &layer);

                self->name  = (PxString8) {0};
                self->colon = 0;
                self->comma = 0;
            } break;

            case PX_JSON_TOKEN_OBJECT_CLOSE: {
                result = pxJsonMsgObjectClose();

                pxQueueDropTail(&self->stack);

                self->name  = (PxString8) {0};
                self->colon = 0;
                self->comma = 0;
            } break;

            case PX_JSON_TOKEN_ARRAY_OPEN: {
                result = pxJsonMsgArrayOpen();

                PxJsonLayerType layer = PX_JSON_LAYER_ARRAY;

                pxQueueInsertTail(&self->stack, PxJsonLayerType,
                    &layer);

                self->name  = (PxString8) {0};
                self->colon = 0;
                self->comma = 0;
            } break;

            case PX_JSON_TOKEN_ARRAY_CLOSE: {
                result = pxJsonMsgArrayClose();

                pxQueueDropTail(&self->stack);

                self->name  = (PxString8) {0};
                self->colon = 0;
                self->comma = 0;
            } break;

            case PX_JSON_TOKEN_COLON: {
                if (parent == PX_JSON_LAYER_OBJECT) {
                    token = pxJsonPeek(self->reader, arena);

                    switch (token.type) {
                        case PX_JSON_TOKEN_OBJECT_OPEN:
                        case PX_JSON_TOKEN_ARRAY_OPEN:
                            result = pxJsonMsgName(self->name);
                        break;

                        default: break;
                    }
                }

                self->colon = 1;
                self->comma = 0;
            } break;

            case PX_JSON_TOKEN_COMMA: {
                self->name  = (PxString8) {0};
                self->colon = 0;
                self->comma = 1;
            } break;

            case PX_JSON_TOKEN_STRING: {
                if (parent != PX_JSON_LAYER_OBJECT || self->colon != 0) {
                    result = pxJsonMsgString(
                        token.string_8, self->name);
                } else
                    self->name = token.string_8;

                self->colon = 0;
                self->comma = 0;
            } break;

            case PX_JSON_TOKEN_UNSIGNED: {
                result = pxJsonMsgUnsigned(
                    token.unsigned_word, self->name);

                self->colon = 0;
                self->comma = 0;
            } break;

            case PX_JSON_TOKEN_INTEGER: {
                result = pxJsonMsgInteger(
                    token.integer_word, self->name);

                self->colon = 0;
                self->comma = 0;
            } break;

            case PX_JSON_TOKEN_FLOATING: {
                result = pxJsonMsgFloating(
                    token.floating_word, self->name);

                self->colon = 0;
                self->comma = 0;
            } break;

            case PX_JSON_TOKEN_BOOLEAN: {
                result = pxJsonMsgBoolean(
                    token.boolean_word, self->name);

                self->colon = 0;
                self->comma = 0;
            } break;

            case PX_JSON_TOKEN_NULL: {
                result = pxJsonMsgNull(self->name);

                self->colon = 0;
                self->comma = 0;
            } break;

            default: break;
        }
    }

    return result;
}

pxb8
pxJsonExpectMessage(PxJsonReader* self, PxArena* arena, PxJsonMsgType type)
{
    PxJsonMsg result = pxJsonReadMessage(self, arena);

    if (result.type != type)
        return 0;

    return 1;
}

#endif // PX_ENCODING_JSON_READER_C
