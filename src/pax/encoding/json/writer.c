#ifndef PX_ENCODING_JSON_WRITER_C
#define PX_ENCODING_JSON_WRITER_C

#include "writer.h"

PxJsonWriter
pxJsonWriterReserve(PxTarget target, PxArena* arena, pxiword length)
{
    PxQueue stack =
        pxQueueReserve(arena, PxJsonLayerType, length);

    if (stack.length <= 0) return (PxJsonWriter) {0};

    return (PxJsonWriter) {
        .target = target,
        .stack  = stack,
    };
}

pxb8
pxJsonWriterMsg(PxJsonWriter* self, PxArena* arena, PxJsonMsg message)
{
    PxJsonLayerType parent = PX_JSON_LAYER_NONE;

    pxQueueGetTail(&self->stack, PxJsonLayerType, &parent);

    PxFormatRadix radix = PX_FORMAT_RADIX_10;
    PxFormatFlag  flags = PX_FORMAT_FLAG_NONE;

    switch (message.type) {
        case PX_JSON_MSG_OBJECT_OPEN: {
            pxTargetWriteByte(self->target, PX_ASCII_BRACE_LEFT);

            PxJsonLayerType layer = PX_JSON_LAYER_OBJECT;

            pxQueueInsertTail(&self->stack,
                PxJsonLayerType, &layer);

            self->flags &= ~PX_JSON_WRITER_COMMA;
        } break;

        case PX_JSON_MSG_OBJECT_CLOSE: {
            pxTargetWriteByte(self->target, PX_ASCII_BRACE_RIGHT);
            pxQueueDropTail(&self->stack);

            self->flags |= PX_JSON_WRITER_COMMA;
        } break;

        case PX_JSON_MSG_ARRAY_OPEN: {
            pxTargetWriteByte(self->target, PX_ASCII_SQUARE_LEFT);

            PxJsonLayerType layer = PX_JSON_LAYER_ARRAY;

            pxQueueInsertTail(&self->stack,
                PxJsonLayerType, &layer);

            self->flags &= ~PX_JSON_WRITER_COMMA;
        } break;

        case PX_JSON_MSG_ARRAY_CLOSE: {
            pxTargetWriteByte(self->target, PX_ASCII_SQUARE_RIGHT);
            pxQueueDropTail(&self->stack);

            self->flags |= PX_JSON_WRITER_COMMA;
        } break;

        case PX_JSON_MSG_NAME: {
            if (parent != PX_JSON_LAYER_OBJECT) return 0;

            if ((self->flags & PX_JSON_WRITER_COMMA) != 0)
                pxTargetWriteByte(self->target, PX_ASCII_COMMA);

            pxTargetWriteByte(self->target, PX_ASCII_QUOTE);
            pxTargetWriteString8(self->target, message.name);
            pxTargetWriteByte(self->target, PX_ASCII_QUOTE);
            pxTargetWriteByte(self->target, PX_ASCII_COLON);
        } break;

        case PX_JSON_MSG_STRING: {
            if ((self->flags & PX_JSON_WRITER_COMMA) != 0)
                pxTargetWriteByte(self->target, PX_ASCII_COMMA);

            if (parent == PX_JSON_LAYER_OBJECT) {
                if (message.name.length <= 0) return 0;

                pxTargetWriteByte(self->target, PX_ASCII_QUOTE);
                pxTargetWriteString8(self->target, message.name);
                pxTargetWriteByte(self->target, PX_ASCII_QUOTE);
                pxTargetWriteByte(self->target, PX_ASCII_COLON);
            }

            pxTargetWriteByte(self->target, PX_ASCII_QUOTE);
            pxTargetWriteString8(self->target, message.string_8);
            pxTargetWriteByte(self->target, PX_ASCII_QUOTE);

            self->flags |= PX_JSON_WRITER_COMMA;
        } break;

        case PX_JSON_MSG_UNSIGNED: {
            if ((self->flags & PX_JSON_WRITER_COMMA) != 0)
                pxTargetWriteByte(self->target, PX_ASCII_COMMA);

            if (parent == PX_JSON_LAYER_OBJECT) {
                if (message.name.length <= 0) return 0;

                pxTargetWriteByte(self->target, PX_ASCII_QUOTE);
                pxTargetWriteString8(self->target, message.name);
                pxTargetWriteByte(self->target, PX_ASCII_QUOTE);
                pxTargetWriteByte(self->target, PX_ASCII_COLON);
            }

            pxiword offset = pxArenaOffset(arena);

            PxString8 string = pxString8FromUnsigned(arena,
                message.unsigned_word, radix, flags);

            pxTargetWriteString8(self->target, string);

            pxArenaRewind(arena, offset);

            self->flags |= PX_JSON_WRITER_COMMA;
        } break;

        case PX_JSON_MSG_INTEGER: {
            if ((self->flags & PX_JSON_WRITER_COMMA) != 0)
                pxTargetWriteByte(self->target, PX_ASCII_COMMA);

            if (parent == PX_JSON_LAYER_OBJECT) {
                if (message.name.length <= 0) return 0;

                pxTargetWriteByte(self->target, PX_ASCII_QUOTE);
                pxTargetWriteString8(self->target, message.name);
                pxTargetWriteByte(self->target, PX_ASCII_QUOTE);
                pxTargetWriteByte(self->target, PX_ASCII_COLON);
            }

            pxiword offset = pxArenaOffset(arena);

            PxString8 string = pxString8FromInteger(arena,
                message.integer_word, radix, flags);

            pxTargetWriteString8(self->target, string);

            pxArenaRewind(arena, offset);

            self->flags |= PX_JSON_WRITER_COMMA;
        } break;

        case PX_JSON_MSG_FLOATING: {
            return 0;
        } break;

        case PX_JSON_MSG_BOOLEAN: {
            if ((self->flags & PX_JSON_WRITER_COMMA) != 0)
                pxTargetWriteByte(self->target, PX_ASCII_COMMA);

            if (parent == PX_JSON_LAYER_OBJECT) {
                if (message.name.length <= 0) return 0;

                pxTargetWriteByte(self->target, PX_ASCII_QUOTE);
                pxTargetWriteString8(self->target, message.name);
                pxTargetWriteByte(self->target, PX_ASCII_QUOTE);
                pxTargetWriteByte(self->target, PX_ASCII_COLON);
            }

            pxiword offset = pxArenaOffset(arena);

            PxString8 string = pxString8FromBoolean(arena,
                message.boolean_word, flags);

            pxTargetWriteString8(self->target, string);

            pxArenaRewind(arena, offset);

            self->flags |= PX_JSON_WRITER_COMMA;
        } break;

        case PX_JSON_MSG_NULL: {
            if ((self->flags & PX_JSON_WRITER_COMMA) != 0)
                pxTargetWriteByte(self->target, PX_ASCII_COMMA);

            if (parent == PX_JSON_LAYER_OBJECT) {
                if (message.name.length <= 0) return 0;

                pxTargetWriteByte(self->target, PX_ASCII_QUOTE);
                pxTargetWriteString8(self->target, message.name);
                pxTargetWriteByte(self->target, PX_ASCII_QUOTE);
                pxTargetWriteByte(self->target, PX_ASCII_COLON);
            }

            pxTargetWriteString8(self->target, pxs8("null"));

            self->flags |= PX_JSON_WRITER_COMMA;
        } break;

        case PX_JSON_MSG_DELEGATE: {
            PxJsonWriterProc* proc = px_as(PxJsonWriterProc*, message.delegate.proc);

            if ((self->flags & PX_JSON_WRITER_COMMA) != 0)
                pxTargetWriteByte(self->target, PX_ASCII_COMMA);

            if (parent == PX_JSON_LAYER_OBJECT) {
                if (message.name.length <= 0) return 0;

                pxTargetWriteByte(self->target, PX_ASCII_QUOTE);
                pxTargetWriteString8(self->target, message.name);
                pxTargetWriteByte(self->target, PX_ASCII_QUOTE);
                pxTargetWriteByte(self->target, PX_ASCII_COLON);
            }

            if (message.delegate.proc != 0)
                proc(message.delegate.ctxt, self, arena);
        } break;

        default: return 0;
    }

    pxTargetFlush(self->target);

    return 1;
}

pxiword
pxJsonWriterList(PxJsonWriter* self, PxArena* arena, PxJsonMsg* values, pxiword length)
{
    for (pxiword i = 0; i < length; i += 1) {
        if (pxJsonWriterMsg(self, arena, values[i]) == 0)
            return i;
    }

    return length;
}

pxb8
pxJsonWriterObjectItem(PxJsonWriter* self, PxArena* arena, void* ctxt, void* proc, PxString8 name)
{
    PxJsonWriterProc* temp = px_as(PxJsonWriterProc*, proc);

    pxJsonWriterMsg(self, arena, pxJsonMsgName(name));

    if (proc != 0)
        return temp(ctxt, self, arena);

    return 0;
}

pxb8
pxJsonWriterObjectOpen(PxJsonWriter* self, PxArena* arena)
{
    return pxJsonWriterMsg(self, arena, pxJsonMsgObjectOpen());
}

pxb8
pxJsonWriterObjectClose(PxJsonWriter* self, PxArena* arena)
{
    return pxJsonWriterMsg(self, arena, pxJsonMsgObjectClose());
}

pxb8
pxJsonWriterArrayItem(PxJsonWriter* self, PxArena* arena, void* ctxt, void* proc)
{
    PxJsonWriterProc* temp = px_as(PxJsonWriterProc*, proc);

    if (proc != 0)
        return temp(ctxt, self, arena);

    return 0;
}

pxb8
pxJsonWriterArrayOpen(PxJsonWriter* self, PxArena* arena)
{
    return pxJsonWriterMsg(self, arena, pxJsonMsgArrayOpen());
}

pxb8
pxJsonWriterArrayClose(PxJsonWriter* self, PxArena* arena)
{
    return pxJsonWriterMsg(self, arena, pxJsonMsgArrayClose());
}

#endif // PX_ENCODING_JSON_WRITER_C
