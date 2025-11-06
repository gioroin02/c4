#ifndef PX_CORE_CONSOLE_MESSAGE_C
#define PX_CORE_CONSOLE_MESSAGE_C

#include "message.h"

PxConsoleMsg
pxConsoleMsgKeybdPress(pxiword button, pxuword modifs, pxi32 unicode)
{
    return (PxConsoleMsg) {
        .type = PX_CONSOLE_MSG_KEYBD_PRESS,

        .keybd_button = {
            .button  = button,
            .modifs  = modifs,
            .unicode = unicode,
        },
    };
}

PxConsoleMsg
pxConsoleMsgKeybdRelease(pxiword button, pxuword modifs, pxi32 unicode)
{
    return (PxConsoleMsg) {
        .type = PX_CONSOLE_MSG_KEYBD_RELEASE,

        .keybd_button = {
            .button  = button,
            .modifs  = modifs,
            .unicode = unicode,
        },
    };
}

PxConsoleMsg
pxConsoleMsgStyleText16(pxu8 index)
{
    return (PxConsoleMsg) {
        .type = PX_CONSOLE_MSG_STYLE_TEXT_16,

        .style_16 = {
            .index = index,
        },
    };
}

PxConsoleMsg
pxConsoleMsgStyleText256(pxu8 index)
{
    return (PxConsoleMsg) {
        .type = PX_CONSOLE_MSG_STYLE_TEXT_256,

        .style_256 = {
            .index = index,
        },
    };
}

PxConsoleMsg
pxConsoleMsgStyleTextRGB(pxu8 r, pxu8 g, pxu8 b)
{
    return (PxConsoleMsg) {
        .type = PX_CONSOLE_MSG_STYLE_TEXT_RGB,

        .style_rgb = {
            .r = r,
            .g = g,
            .b = b,
        },
    };
}

PxConsoleMsg
pxConsoleMsgStyleText(PxConsoleColor value)
{
    switch (value.type) {
        case PX_CONSOLE_COLOR_16:
            return pxConsoleMsgStyleText16(value.color_16.index);

        case PX_CONSOLE_COLOR_256:
            return pxConsoleMsgStyleText256(value.color_256.index);

        case PX_CONSOLE_COLOR_RGB:
            return pxConsoleMsgStyleTextRGB(value.color_rgb.r,
                value.color_rgb.g, value.color_rgb.b);

        default: break;
    }

    return (PxConsoleMsg) {0};
}

PxConsoleMsg
pxConsoleMsgStyleBack16(pxu8 index)
{
    return (PxConsoleMsg) {
        .type = PX_CONSOLE_MSG_STYLE_BACK_16,

        .style_16 = {
            .index = index,
        },
    };
}

PxConsoleMsg
pxConsoleMsgStyleBack256(pxu8 index)
{
    return (PxConsoleMsg) {
        .type = PX_CONSOLE_MSG_STYLE_BACK_256,

        .style_256 = {
            .index = index,
        },
    };
}

PxConsoleMsg
pxConsoleMsgStyleBackRGB(pxu8 r, pxu8 g, pxu8 b)
{
    return (PxConsoleMsg) {
        .type = PX_CONSOLE_MSG_STYLE_BACK_RGB,

        .style_rgb = {
            .r = r,
            .g = g,
            .b = b,
        },
    };
}

PxConsoleMsg
pxConsoleMsgStyleBack(PxConsoleColor value)
{
    switch (value.type) {
        case PX_CONSOLE_COLOR_16:
            return pxConsoleMsgStyleBack16(value.color_16.index);

        case PX_CONSOLE_COLOR_256:
            return pxConsoleMsgStyleBack256(value.color_256.index);

        case PX_CONSOLE_COLOR_RGB:
            return pxConsoleMsgStyleBackRGB(value.color_rgb.r,
                value.color_rgb.g, value.color_rgb.b);

        default: break;
    }

    return (PxConsoleMsg) {0};
}

PxConsoleMsg
pxConsoleMsgStyleClear()
{
    return (PxConsoleMsg) {
        .type = PX_CONSOLE_MSG_STYLE_CLEAR,
    };
}

PxConsoleMsg
pxConsoleMsgString8(PxString8 value)
{
    return (PxConsoleMsg) {
        .type     = PX_CONSOLE_MSG_STRING_8,
        .string_8 = value,
    };
}

PxConsoleMsg
pxConsoleMsgString16(PxString16 value)
{
    return (PxConsoleMsg) {
        .type      = PX_CONSOLE_MSG_STRING_16,
        .string_16 = value,
    };
}

PxConsoleMsg
pxConsoleMsgString32(PxString32 value)
{
    return (PxConsoleMsg) {
        .type      = PX_CONSOLE_MSG_STRING_32,
        .string_32 = value,
    };
}

PxConsoleMsg
pxConsoleMsgUnicode(pxi32 value)
{
    return (PxConsoleMsg) {
        .type    = PX_CONSOLE_MSG_UNICODE,
        .unicode = value,
    };
}

PxConsoleMsg
pxConsoleMsgCursorShow()
{
    return (PxConsoleMsg) {
        .type = PX_CONSOLE_MSG_CURSOR_SHOW,
    };
}

PxConsoleMsg
pxConsoleMsgCursorHide()
{
    return (PxConsoleMsg) {
        .type = PX_CONSOLE_MSG_CURSOR_HIDE,
    };
}

PxConsoleMsg
pxConsoleMsgCursorMove(pxiword x, pxiword y)
{
    return (PxConsoleMsg) {
        .type = PX_CONSOLE_MSG_CURSOR_MOVE,

        .cursor_move = {
            .x = x,
            .y = y,
        },
    };
}

PxConsoleMsg
pxConsoleMsgCursorMoveUp(pxiword y)
{
    return (PxConsoleMsg) {
        .type = PX_CONSOLE_MSG_CURSOR_MOVE_UP,

        .cursor_move = {
            .x = 0,
            .y = y,
        },
    };
}

PxConsoleMsg
pxConsoleMsgCursorMoveDown(pxiword y)
{
    return (PxConsoleMsg) {
        .type = PX_CONSOLE_MSG_CURSOR_MOVE_DOWN,

        .cursor_move = {
            .x = 0,
            .y = y,
        },
    };
}

PxConsoleMsg
pxConsoleMsgCursorMoveLeft(pxiword x)
{
    return (PxConsoleMsg) {
        .type = PX_CONSOLE_MSG_CURSOR_MOVE_LEFT,

        .cursor_move = {
            .x = x,
            .y = 0,
        },
    };
}

PxConsoleMsg
pxConsoleMsgCursorMoveRight(pxiword x)
{
    return (PxConsoleMsg) {
        .type = PX_CONSOLE_MSG_CURSOR_MOVE_RIGHT,

        .cursor_move = {
            .x = x,
            .y = 0,
        },
    };
}

PxConsoleMsg
pxConsoleMsgReset()
{
    return (PxConsoleMsg) {
        .type = PX_CONSOLE_MSG_RESET,
    };
}

PxConsoleQueue
pxConsoleQueueReserve(PxArena* arena, pxiword length)
{
    PxConsoleQueue result = {0};

    result.buffer = pxBuffer8Reserve(arena, length);

    return result;
}

PxConsoleEscSeqnc
pxConsoleEscSeqncFromConsoleMsg(PxConsoleMsg value)
{
    PxConsoleEscSeqnc result = {0};

    switch (value.type) {
        case PX_CONSOLE_MSG_STYLE_TEXT_16: {
            pxu8 style = value.style_16.index;
            pxu8 index = 0;

            if (style >= 0 && style < 8)  index = (style % 8) + 30;
            if (style >= 8 && style < 16) index = (style % 8) + 90;

            result = pxConsoleEscSeqncMake((PxConsoleEscGroup[]) {
                pxConsoleEscGroupMake((pxuword[]) {index}, 1)
            }, 1);

            result.func  = PX_ASCII_LOWER_M;
            result.flags = PX_CONSOLE_ESC_FLAG_CSI;
        } break;

        case PX_CONSOLE_MSG_STYLE_TEXT_256: {
            result = pxConsoleEscSeqncMake((PxConsoleEscGroup[]) {
                pxConsoleEscGroupMake((pxuword[]) {38}, 1),
                pxConsoleEscGroupMake((pxuword[]) {5}, 1),
                pxConsoleEscGroupMake((pxuword[]) {value.style_256.index}, 1),
            }, 3);

            result.func  = PX_ASCII_LOWER_M;
            result.flags = PX_CONSOLE_ESC_FLAG_CSI;
        } break;

        case PX_CONSOLE_MSG_STYLE_TEXT_RGB: {
            result = pxConsoleEscSeqncMake((PxConsoleEscGroup[]) {
                pxConsoleEscGroupMake((pxuword[]) {38}, 1),
                pxConsoleEscGroupMake((pxuword[]) {2}, 1),
                pxConsoleEscGroupMake((pxuword[]) {value.style_rgb.r}, 1),
                pxConsoleEscGroupMake((pxuword[]) {value.style_rgb.g}, 1),
                pxConsoleEscGroupMake((pxuword[]) {value.style_rgb.b}, 1),
            }, 5);

            result.func  = PX_ASCII_LOWER_M;
            result.flags = PX_CONSOLE_ESC_FLAG_CSI;
        } break;

        case PX_CONSOLE_MSG_STYLE_BACK_16: {
            pxu8 style = value.style_16.index;
            pxu8 index = 0;

            if (style >= 0 && style < 8)  index = (style % 8) + 40;
            if (style >= 8 && style < 16) index = (style % 8) + 100;

            result = pxConsoleEscSeqncMake((PxConsoleEscGroup[]) {
                pxConsoleEscGroupMake((pxuword[]) {index}, 1)
            }, 1);

            result.func  = PX_ASCII_LOWER_M;
            result.flags = PX_CONSOLE_ESC_FLAG_CSI;
        } break;

        case PX_CONSOLE_MSG_STYLE_BACK_256: {
            result = pxConsoleEscSeqncMake((PxConsoleEscGroup[]) {
                pxConsoleEscGroupMake((pxuword[]) {48}, 1),
                pxConsoleEscGroupMake((pxuword[]) {5}, 1),
                pxConsoleEscGroupMake((pxuword[]) {value.style_256.index}, 1),
            }, 3);

            result.func  = PX_ASCII_LOWER_M;
            result.flags = PX_CONSOLE_ESC_FLAG_CSI;
        } break;

        case PX_CONSOLE_MSG_STYLE_BACK_RGB: {
            result = pxConsoleEscSeqncMake((PxConsoleEscGroup[]) {
                pxConsoleEscGroupMake((pxuword[]) {48}, 1),
                pxConsoleEscGroupMake((pxuword[]) {2}, 1),
                pxConsoleEscGroupMake((pxuword[]) {value.style_rgb.r}, 1),
                pxConsoleEscGroupMake((pxuword[]) {value.style_rgb.g}, 1),
                pxConsoleEscGroupMake((pxuword[]) {value.style_rgb.b}, 1),
            }, 5);

            result.func  = PX_ASCII_LOWER_M;
            result.flags = PX_CONSOLE_ESC_FLAG_CSI;
        } break;

        case PX_CONSOLE_MSG_STYLE_CLEAR: {
            result = pxConsoleEscSeqncMake((PxConsoleEscGroup[]) {
                pxConsoleEscGroupMake((pxuword[]) {0}, 1),
            }, 1);

            result.func  = PX_ASCII_LOWER_M;
            result.flags = PX_CONSOLE_ESC_FLAG_CSI;
        } break;

        case PX_CONSOLE_MSG_CURSOR_SHOW: {
            result = pxConsoleEscSeqncMake((PxConsoleEscGroup[]) {
                pxConsoleEscGroupMake((pxuword[]) {25}, 1),
            }, 1);

            result.func  = PX_ASCII_LOWER_H;
            result.flags = PX_CONSOLE_ESC_FLAG_CSI | PX_CONSOLE_ESC_FLAG_PRIV;
        } break;

        case PX_CONSOLE_MSG_CURSOR_HIDE: {
            result = pxConsoleEscSeqncMake((PxConsoleEscGroup[]) {
                pxConsoleEscGroupMake((pxuword[]) {25}, 1),
            }, 1);

            result.func  = PX_ASCII_LOWER_L;
            result.flags = PX_CONSOLE_ESC_FLAG_CSI | PX_CONSOLE_ESC_FLAG_PRIV;
        } break;

        case PX_CONSOLE_MSG_CURSOR_MOVE: {
            result = pxConsoleEscSeqncMake((PxConsoleEscGroup[]) {
                pxConsoleEscGroupMake((pxuword[]) {value.cursor_move.y + 1}, 1),
                pxConsoleEscGroupMake((pxuword[]) {value.cursor_move.x + 1}, 1),
            }, 2);

            result.func  = PX_ASCII_UPPER_H;
            result.flags = PX_CONSOLE_ESC_FLAG_CSI;
        } break;

        case PX_CONSOLE_MSG_CURSOR_MOVE_UP: {
            result.func  = PX_ASCII_UPPER_A;
            result.flags = PX_CONSOLE_ESC_FLAG_CSI;

            if (value.cursor_move.y > 0) {
                PxConsoleEscGroup group =
                    pxConsoleEscGroupMake((pxuword[]) {value.cursor_move.y}, 1);

                pxConsoleEscSeqncInsert(&result, group);
            }
        } break;

        case PX_CONSOLE_MSG_CURSOR_MOVE_DOWN: {
            result.func  = PX_ASCII_UPPER_B;
            result.flags = PX_CONSOLE_ESC_FLAG_CSI;

            if (value.cursor_move.y > 0) {
                PxConsoleEscGroup group =
                    pxConsoleEscGroupMake((pxuword[]) {value.cursor_move.y}, 1);

                pxConsoleEscSeqncInsert(&result, group);
            }
        } break;

        case PX_CONSOLE_MSG_CURSOR_MOVE_RIGHT: {
            result.func  = PX_ASCII_UPPER_C;
            result.flags = PX_CONSOLE_ESC_FLAG_CSI;

            if (value.cursor_move.x > 0) {
                PxConsoleEscGroup group =
                    pxConsoleEscGroupMake((pxuword[]) {value.cursor_move.x}, 1);

                pxConsoleEscSeqncInsert(&result, group);
            }
        } break;

        case PX_CONSOLE_MSG_CURSOR_MOVE_LEFT: {
            result.func  = PX_ASCII_UPPER_A;
            result.flags = PX_CONSOLE_ESC_FLAG_CSI;

            if (value.cursor_move.x > 0) {
                PxConsoleEscGroup group =
                    pxConsoleEscGroupMake((pxuword[]) {value.cursor_move.x}, 1);

                pxConsoleEscSeqncInsert(&result, group);
            }
        } break;

        case PX_CONSOLE_MSG_RESET: {
            result.func = PX_ASCII_LOWER_C;
        } break;

        default: break;
    }

    return result;
}

PxConsoleMsg
pxConsoleMsgFromConsoleEscSeqnc(PxConsoleEscSeqnc value)
{
    PxConsoleMsg result = {0};

    switch (value.func) {
        case PX_ASCII_LOWER_M: {

        } break;

        case PX_ASCII_UPPER_A: {
            result = pxConsoleMsgCursorMoveUp(1);

            if (value.size >= 1)
                result.cursor_move.y = value.items[0].items[0];
        } break;

        case PX_ASCII_UPPER_B: {
            result = pxConsoleMsgCursorMoveDown(1);

            if (value.size >= 1)
                result.cursor_move.y = value.items[0].items[0];
        } break;

        case PX_ASCII_UPPER_C: {
            result = pxConsoleMsgCursorMoveRight(1);

            if (value.size >= 1)
                result.cursor_move.x = value.items[0].items[0];
        } break;

        case PX_ASCII_UPPER_D: {
            result = pxConsoleMsgCursorMoveLeft(1);

            if (value.size >= 1)
                result.cursor_move.x = value.items[0].items[0];
        } break;

        case PX_ASCII_UPPER_H: {
            result = pxConsoleMsgCursorMove(0, 0);

            if (value.size >= 2) {
                result.cursor_move.x = value.items[1].items[0];
                result.cursor_move.y = value.items[0].items[0];
            }
        };

        default: break;
    }

    return result;
}

pxb8
pxConsoleQueueWriteMsg(PxConsoleQueue* self, PxConsoleMsg value)
{
    PxTarget target = pxTargetFromBuffer8(&self->buffer);

    switch (value.type) {
        case PX_CONSOLE_MSG_NONE: break;

        case PX_CONSOLE_MSG_STRING_8: {
            pxTargetWriteString8(target, value.string_8);
        } break;

        case PX_CONSOLE_MSG_STRING_16:{
            pxTargetWriteString16(target, value.string_16);
        } break;

        case PX_CONSOLE_MSG_STRING_32:{
            pxTargetWriteString32(target, value.string_32);
        } break;

        case PX_CONSOLE_MSG_UNICODE: {
            pxTargetWriteUnicode(target, value.unicode);
        } break;

        default: {
            PxConsoleEscSeqnc escape = pxConsoleEscSeqncFromConsoleMsg(value);

            PxFormatRadix radix = PX_FORMAT_RADIX_10;
            PxFormatFlag  flags = PX_FORMAT_FLAG_NONE;

            pxTargetWriteString8(target, pxs8("\x1b"));

            if ((escape.flags & PX_CONSOLE_ESC_FLAG_CSI) != 0)
                pxTargetWriteString8(target, pxs8("["));

            if ((escape.flags & PX_CONSOLE_ESC_FLAG_PRIV) != 0)
                pxTargetWriteString8(target, pxs8("?"));

            for (pxiword j = 0; j < escape.size; j += 1) {
                PxConsoleEscGroup* group = &escape.items[j];

                for (pxiword i = 0; i < group->size; i += 1) {
                    pxTargetPrintUnsigned(target, group->items[i], radix, flags);

                    if (i + 1 < group->size)
                        pxTargetWriteString8(target, pxs8(":"));
                }

                if (j + 1 < escape.size)
                    pxTargetWriteString8(target, pxs8(";"));
            }

            pxTargetWriteUnicode(target, escape.func);
        } break;
    }

    pxTargetFlush(target);

    return 1;
}

pxb8
pxConsoleQueueWriteList(PxConsoleQueue* self, PxConsoleMsg* values, pxiword length)
{
    PxBuffer8* buffer = &self->buffer;
    pxiword    size   = buffer->size;
    pxb8       state  = 0;

    for (pxiword i = 0; i < length; i += 1) {
        state =
            pxConsoleQueueWriteMsg(self, values[i]);

        if (state == 0) break;
    }

    if (state == 0)
        pxBuffer8DropTail(buffer, buffer->size - size);

    return state;
}

pxb8
pxConsoleQueueReadMsg(PxConsoleQueue* self, PxArena* arena, PxConsoleMsg* value)
{
    PxConsoleMsg result = {0};

    pxu8 byte = 0;

    if (pxBuffer8GetForw(&self->buffer, 0, &byte) == 0)
        return 0;

    if (byte == PX_ASCII_ESCAPE) {
        byte = pxBuffer8GetForwOr(&self->buffer, 1, 0);

        switch (byte) {
            case PX_ASCII_SQUARE_LEFT: {
                for (pxiword i = 2; i < self->buffer.size; i += 1) {
                    pxu8 byte = pxBuffer8GetForwOr(&self->buffer, i, 0);

                    switch (byte) {
                        case PX_ASCII_TILDE:
                        case PX_ASCII_UPPER_A:
                        case PX_ASCII_UPPER_B:
                        case PX_ASCII_UPPER_C:
                        case PX_ASCII_UPPER_D:
                        case PX_ASCII_UPPER_F:
                        case PX_ASCII_UPPER_H:
                        case PX_ASCII_LOWER_H:
                        case PX_ASCII_LOWER_L:
                        case PX_ASCII_LOWER_M:
                        case PX_ASCII_LOWER_U: {
                            PxConsoleEscSeqnc escape = {0};

                            PxString8 string = pxBuffer8ReadString8Head(
                                &self->buffer, arena, i + 1);

                            pxConsoleEscSeqncFromString8(string, &escape);

                            if (value != 0)
                                pxConsoleMsgFromConsoleEscSeqnc(escape);

                            return 1;
                        } break;

                        default: break;
                    }
                }
            } break;

            default: {
                PxConsoleMsg message = pxConsoleMsgKeybdPress(
                    PX_CONSOLE_KEYBD_ESCAPE, 0, byte);

                pxBuffer8DropHead(&self->buffer, 1);

                if (value != 0) *value = message;

                return 1;
            } break;
        }
    }

    pxBuffer8DropHead(&self->buffer, 1);

    if (value != 0)
        *value = pxConsoleMsgUnicode(byte);

    return 1;
}

PxBuffer8*
pxConsoleQueueBuffer8(PxConsoleQueue* self)
{
    return &self->buffer;
}

#endif // PX_CORE_CONSOLE_MESSAGE_C
