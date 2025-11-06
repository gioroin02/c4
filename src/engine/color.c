#ifndef C4_ENGINE_COLOR_C
#define C4_ENGINE_COLOR_C

#include "color.h"

pxb8
c4JsonWriteConsoleColor(PxConsoleColor* self, PxJsonWriter* writer, PxArena* arena)
{
    PxJsonMsg message = {0};

    pxJsonWriterObjectOpen(writer, arena);

    switch (self->type) {
        case PX_CONSOLE_COLOR_16: {
            message = pxJsonMsgPair(pxs8("color_16"),
                pxJsonMsgDelegate(&self->color_16, &c4JsonWriteConsoleColor16));
        } break;

        case PX_CONSOLE_COLOR_256: {
            message = pxJsonMsgPair(pxs8("color_256"),
                pxJsonMsgDelegate(&self->color_256, &c4JsonWriteConsoleColor256));
        } break;

        case PX_CONSOLE_COLOR_RGB: {
            message = pxJsonMsgPair(pxs8("color_rgb"),
                pxJsonMsgDelegate(&self->color_rgb, &c4JsonWriteConsoleColorRGB));
        } break;

        default: break;
    }

    pxJsonWriterMsg(writer, arena, message);

    pxJsonWriterObjectClose(writer, arena);

    return 1;
}

pxb8
c4JsonWriteConsoleColor16(PxConsoleColor16* self, PxJsonWriter* writer, PxArena* arena)
{
    pxJsonWriterObjectOpen(writer, arena);

    pxJsonWriterList(writer, arena, (PxJsonMsg[]) {
        pxJsonMsgPair(pxs8("index"), pxJsonMsgUnsigned(self->index)),
    }, 1);

    pxJsonWriterObjectClose(writer, arena);

    return 1;
}

pxb8
c4JsonWriteConsoleColor256(PxConsoleColor256* self, PxJsonWriter* writer, PxArena* arena)
{
    pxJsonWriterObjectOpen(writer, arena);

    pxJsonWriterList(writer, arena, (PxJsonMsg[]) {
        pxJsonMsgPair(pxs8("index"), pxJsonMsgUnsigned(self->index)),
    }, 1);

    pxJsonWriterObjectClose(writer, arena);

    return 1;
}

pxb8
c4JsonWriteConsoleColorRGB(PxConsoleColorRGB* self, PxJsonWriter* writer, PxArena* arena)
{
    pxJsonWriterObjectOpen(writer, arena);

    pxJsonWriterList(writer, arena, (PxJsonMsg[]) {
        pxJsonMsgPair(pxs8("r"), pxJsonMsgUnsigned(self->r)),
        pxJsonMsgPair(pxs8("g"), pxJsonMsgUnsigned(self->g)),
        pxJsonMsgPair(pxs8("b"), pxJsonMsgUnsigned(self->b)),
    }, 3);

    pxJsonWriterObjectClose(writer, arena);

    return 1;
}

pxb8
c4JsonReadConsoleColor(PxConsoleColor* self, PxJsonReader* reader, PxArena* arena)
{
    PxJsonMsg message = {0};

    if (pxJsonReaderObjectOpen(reader, arena, &message) == 0)
        return 0;

    while (pxJsonReaderObjectClose(reader, arena, &message) == 0) {
        switch (message.type) {
            case PX_JSON_MSG_NAME: {
                self->type = PX_CONSOLE_COLOR_NONE;

                if (pxString8IsEqual(message.name, pxs8("color_16")) != 0) {
                    self->type = PX_CONSOLE_COLOR_16;

                    c4JsonReadConsoleColor16(&self->color_16,
                        reader, arena);
                }

                if (pxString8IsEqual(message.name, pxs8("color_256")) != 0) {
                    self->type = PX_CONSOLE_COLOR_256;

                    c4JsonReadConsoleColor256(&self->color_256,
                        reader, arena);
                }

                if (pxString8IsEqual(message.name, pxs8("color_rgb")) != 0) {
                    self->type = PX_CONSOLE_COLOR_RGB;

                    c4JsonReadConsoleColorRGB(&self->color_rgb,
                        reader, arena);
                }
            } break;

            default: break;
        }
    }

    return 1;
}

pxb8
c4JsonReadConsoleColor16(PxConsoleColor16* self, PxJsonReader* reader, PxArena* arena)
{
    PxJsonMsg message = {0};

    if (pxJsonReaderObjectOpen(reader, arena, &message) == 0)
        return 0;

    while (pxJsonReaderObjectClose(reader, arena, &message) == 0) {
        switch (message.type) {
            case PX_JSON_MSG_UNSIGNED: {
                if (pxString8IsEqual(message.name, pxs8("index")) != 0)
                    self->index = message.unsigned_word;
            } break;

            default: break;
        }
    }

    return 1;
}

pxb8
c4JsonReadConsoleColor256(PxConsoleColor256* self, PxJsonReader* reader, PxArena* arena)
{
    PxJsonMsg message = {0};

    if (pxJsonReaderObjectOpen(reader, arena, &message) == 0)
        return 0;

    while (pxJsonReaderObjectClose(reader, arena, &message) == 0) {
        switch (message.type) {
            case PX_JSON_MSG_UNSIGNED: {
                if (pxString8IsEqual(message.name, pxs8("index")) != 0)
                    self->index = message.unsigned_word;
            } break;

            default: break;
        }
    }

    return 1;
}

pxb8
c4JsonReadConsoleColorRGB(PxConsoleColorRGB* self, PxJsonReader* reader, PxArena* arena)
{
    PxJsonMsg message = {0};

    if (pxJsonReaderObjectOpen(reader, arena, &message) == 0)
        return 0;

    while (pxJsonReaderObjectClose(reader, arena, &message) == 0) {
        switch (message.type) {
            case PX_JSON_MSG_UNSIGNED: {
                if (pxString8IsEqual(message.name, pxs8("r")) != 0)
                    self->r = message.unsigned_word;

                if (pxString8IsEqual(message.name, pxs8("g")) != 0)
                    self->g = message.unsigned_word;

                if (pxString8IsEqual(message.name, pxs8("b")) != 0)
                    self->b = message.unsigned_word;
            } break;

            default: break;
        }
    }

    return 1;
}

#endif // C4_ENGINE_COLOR_C
