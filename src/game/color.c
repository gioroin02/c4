#ifndef C4_GAME_COLOR_C
#define C4_GAME_COLOR_C

#include "color.h"

C4Color
c4Color8(pxu8 value)
{
    return (C4Color) {
        .type    = C4_COLOR_8,
        .color_8 = value,
    };
}

C4Color
c4Color256(pxu8 value)
{
    return (C4Color) {
        .type      = C4_COLOR_256,
        .color_256 = value,
    };
}

C4Color
c4ColorRGB(pxu8 r, pxu8 g, pxu8 b)
{
    return (C4Color) {
        .type = C4_COLOR_RGB,

        .color_rgb = {
            .r = r,
            .g = g,
            .b = b,
        },
    };
}

pxb8
c4ColorIsEqual(C4Color self, C4Color value)
{
    if (self.type != value.type) return 0;

    switch (self.type) {
        case C4_COLOR_8:
            return c4Color8IsEqual(self.color_8, value.color_8);

        case C4_COLOR_256:
            return c4Color256IsEqual(self.color_256, value.color_256);

        case C4_COLOR_RGB:
            return c4ColorRGBIsEqual(self.color_rgb, value.color_rgb);

        default: break;
    }

    return 0;
}

pxb8
c4Color8IsEqual(C4Color8 self, C4Color8 value)
{
    return self == value ? 1 : 0;
}

pxb8
c4Color256IsEqual(C4Color256 self, C4Color256 value)
{
    return self == value ? 1 : 0;
}

pxb8
c4ColorRGBIsEqual(C4ColorRGB self, C4ColorRGB value)
{
    if (self.r != value.r) return 0;
    if (self.g != value.g) return 0;
    if (self.b != value.b) return 0;

    return 1;
}

pxb8
c4JsonWriteColor(C4Color* self, PxJsonWriter* writer, PxArena* arena)
{
    pxJsonWriteMessage(writer, arena, pxJsonMsgObjectOpen());

    switch (self->type) {
        case C4_COLOR_8: {
            pxJsonWriteMessage(writer, arena,
                pxJsonMsgUnsigned(self->color_8, pxs8("color_8")));
        } break;

        case C4_COLOR_256: {
            pxJsonWriteMessage(writer, arena,
                pxJsonMsgUnsigned(self->color_256, pxs8("color_256")));
        } break;

        case C4_COLOR_RGB: {
            pxJsonWriteMessage(writer, arena,
                pxJsonMsgName(pxs8("color_rgb")));

            c4JsonWriteColorRGB(&self->color_rgb,
                writer, arena);
        } break;

        default: break;
    }

    pxJsonWriteMessage(writer, arena, pxJsonMsgObjectClose());

    return 1;
}

pxb8
c4JsonWriteColorRGB(C4ColorRGB* self, PxJsonWriter* writer, PxArena* arena)
{
    pxJsonWriteMessage(writer, arena, pxJsonMsgObjectOpen());

    pxJsonWriteMessage(writer, arena,
        pxJsonMsgUnsigned(self->r, pxs8("r")));

    pxJsonWriteMessage(writer, arena,
        pxJsonMsgUnsigned(self->g, pxs8("g")));

    pxJsonWriteMessage(writer, arena,
        pxJsonMsgUnsigned(self->b, pxs8("b")));

    pxJsonWriteMessage(writer, arena, pxJsonMsgObjectClose());

    return 1;
}

pxb8
c4JsonReadColor(C4Color* self, PxJsonReader* reader, PxArena* arena)
{
    if (pxJsonExpectMessage(reader, arena, PX_JSON_MSG_OBJECT_OPEN) == 0)
        return 0;

    PxJsonMsg message = pxJsonReadMessage(reader, arena);

    while (message.type != PX_JSON_MSG_OBJECT_CLOSE) {
        switch (message.type) {
            case PX_JSON_MSG_COUNT: return 0;

            case PX_JSON_MSG_NAME: {
                self->type = C4_COLOR_NONE;

                if (pxString8IsEqual(message.name, pxs8("color_rgb")) != 0) {
                    self->type = C4_COLOR_RGB;

                    c4JsonReadColorRGB(&self->color_rgb,
                        reader, arena);
                }
            } break;

            case PX_JSON_MSG_UNSIGNED: {
                self->type = C4_COLOR_NONE;

                if (pxString8IsEqual(message.name, pxs8("color_8")) != 0)
                    *self = c4Color8(message.unsigned_word);

                if (pxString8IsEqual(message.name, pxs8("color_256")) != 0)
                    *self = c4Color256(message.unsigned_word);
            } break;

            default: break;
        }

        message = pxJsonReadMessage(reader, arena);
    }

    return 1;
}

pxb8
c4JsonReadColorRGB(C4ColorRGB* self, PxJsonReader* reader, PxArena* arena)
{
    if (pxJsonExpectMessage(reader, arena, PX_JSON_MSG_OBJECT_OPEN) == 0)
        return 0;

    PxJsonMsg message = pxJsonReadMessage(reader, arena);

    while (message.type != PX_JSON_MSG_OBJECT_CLOSE) {
        switch (message.type) {
            case PX_JSON_MSG_COUNT: return 0;

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

        message = pxJsonReadMessage(reader, arena);
    }

    return 1;
}

pxiword
c4FormatProcColor(C4Color* self, PxBuilder* builder)
{
    switch (self->type) {
        case C4_COLOR_8:
            return c4FormatProcColor8(&self->color_8, builder);

        case C4_COLOR_256:
            return c4FormatProcColor256(&self->color_256, builder);

        case C4_COLOR_RGB:
            return c4FormatProcColorRGB(&self->color_rgb, builder);

        default: break;
    }

    return 0;
}

pxiword
c4FormatProcColor8(C4Color8* self, PxBuilder* builder)
{
    pxu8 format[] = "Color8 = ${0}";

    PxFormatCmd list[] = {
        pxFormatCmdUnsigned8(10, PX_FORMAT_OPTION_NONE, *self),
    };

    return pxBuilderFormat(builder, pxs8(format),
        0, pxSizeArray(PxFormatCmd, list), list);
}

pxiword
c4FormatProcColor256(C4Color256* self, PxBuilder* builder)
{
    pxu8 format[] = "Color256 = ${0}";

    PxFormatCmd list[] = {
        pxFormatCmdUnsigned8(10, PX_FORMAT_OPTION_NONE, *self),
    };

    return pxBuilderFormat(builder, pxs8(format),
        0, pxSizeArray(PxFormatCmd, list), list);
}

pxiword
c4FormatProcColorRGB(C4ColorRGB* self, PxBuilder* builder)
{
    pxu8 format[] = "ColorRGB = [${0}, ${1}, ${2}]";

    PxFormatCmd list[] = {
        pxFormatCmdUnsigned8(10, PX_FORMAT_OPTION_NONE, self->r),
        pxFormatCmdUnsigned8(10, PX_FORMAT_OPTION_NONE, self->g),
        pxFormatCmdUnsigned8(10, PX_FORMAT_OPTION_NONE, self->b),
    };

    return pxBuilderFormat(builder, pxs8(format),
        0, pxSizeArray(PxFormatCmd, list), list);
}

#endif // C4_GAME_COLOR_C
