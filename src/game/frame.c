#ifndef C4_GAME_FRAME_C
#define C4_GAME_FRAME_C

#include "frame.h"

C4FrameBuffer
c4FrameBufferMake(PxArena* arena, pxiword width, pxiword height)
{
    C4FrameBuffer result = {0};

    if (width <= 0 || height <= 0) return result;

    result.items =
        pxArrayReserve(arena, C4FrameElement, width * height);

    if (result.items.length > 0) {
        pxArrayFill(&result.items);

        result.width  = width;
        result.height = height;
    }

    return result;
}

pxb8
c4FrameBufferRead(C4FrameBuffer* self, pxiword x, pxiword y, C4FrameElement* value)
{
    if (x < 0 || x >= self->width)  return 0;
    if (y < 0 || y >= self->height) return 0;

    pxiword index = x + self->width * y;

    return pxArrayRead(&self->items,
        index, C4FrameElement, value);
}

C4FrameElement
c4FrameBufferReadOr(C4FrameBuffer* self, pxiword x, pxiword y, C4FrameElement value)
{
    c4FrameBufferRead(self, x, y, &value);

    return value;
}

pxb8
c4FrameBufferUpdate(C4FrameBuffer* self, pxiword x, pxiword y, C4FrameElement value)
{
    if (x < 0 || x >= self->width)  return 0;
    if (y < 0 || y >= self->height) return 0;

    pxiword index = x + self->width * y;

    return pxArrayUpdate(&self->items,
        index, C4FrameElement, &value);
}

pxb8
c4FrameBufferReset(C4FrameBuffer* self, PxString8 text, C4Color front, C4Color back)
{
    if (text.length <= 0) text = pxs8(" ");

    C4FrameElement item = {
        .text  = text,
        .front = front,
        .back  = back,
    };

    for (pxiword j = 0; j < self->height; j += 1) {
        for (pxiword i = 0; i < self->width; i += 1) {
            if (c4FrameBufferUpdate(self, i, j, item) == 0)
                return 0;
        }
    }

    return 1;
}

pxb8
c4FrameBufferPaintCell(C4FrameBuffer* self, pxiword x, pxiword y, PxString8 text, C4Color front, C4Color back)
{
    if (text.length <= 0) text = pxs8(" ");

    C4FrameElement item = {
        .text  = text,
        .front = front,
        .back  = back,
    };

    return c4FrameBufferUpdate(self, x, y, item);
}

pxb8
c4FrameBufferPaintRect(C4FrameBuffer* self, pxiword x, pxiword y, pxiword w, pxiword h, PxString8 text, C4Color front, C4Color back)
{
    if (text.length <= 0) text = pxs8(" ");

    C4FrameElement item = {
        .text  = text,
        .front = front,
        .back  = back,
    };

    for (pxiword j = 0; j < h; j += 1) {
        for (pxiword i = 0; i < w; i += 1) {
            if (c4FrameBufferUpdate(self, x + i, y + j, item) == 0)
                return 0;
        }
    }

    return 1;
}

PxConsoleCmd
c4ConsoleCmdColorFront(C4Color value)
{
    switch (value.type) {
        case C4_COLOR_8:
            return (PxConsoleCmd) {
                .type   = PX_CONSOLE_CMD_STYLE_8_FRONT,
                .style_8 = value.color_8,
            };

        case C4_COLOR_256:
            return (PxConsoleCmd) {
                .type     = PX_CONSOLE_CMD_STYLE_256_FRONT,
                .style_256 = value.color_256,
            };

        case C4_COLOR_RGB:
            return (PxConsoleCmd) {
                .type = PX_CONSOLE_CMD_STYLE_RGB_FRONT,

                .style_rgb = {
                    .r = value.color_rgb.r,
                    .g = value.color_rgb.g,
                    .b = value.color_rgb.b,
                },
            };

        default: break;
    }

    return (PxConsoleCmd) {0};
}

PxConsoleCmd
c4ConsoleCmdColorBack(C4Color value)
{
    switch (value.type) {
        case C4_COLOR_8:
            return (PxConsoleCmd) {
                .type   = PX_CONSOLE_CMD_STYLE_8_BACK,
                .style_8 = value.color_8,
            };

        case C4_COLOR_256:
            return (PxConsoleCmd) {
                .type     = PX_CONSOLE_CMD_STYLE_256_BACK,
                .style_256 = value.color_256,
            };

        case C4_COLOR_RGB:
            return (PxConsoleCmd) {
                .type = PX_CONSOLE_CMD_STYLE_RGB_BACK,

                .style_rgb = {
                    .r = value.color_rgb.r,
                    .g = value.color_rgb.g,
                    .b = value.color_rgb.b,
                },
            };

        default: break;
    }

    return (PxConsoleCmd) {0};
}

void
c4WriterFrame(PxWriter* self, C4FrameBuffer* frame)
{
    C4FrameElement item = c4FrameBufferReadOr(frame,
        0, 0, (C4FrameElement) {0});

    pxConsoleWriteCommand(self, pxConsoleCmdCursorPlace(0, 0));

    C4Color front = item.front;
    C4Color back  = item.back;

    pxConsoleWriteCommand(self, c4ConsoleCmdColorFront(front));
    pxConsoleWriteCommand(self, c4ConsoleCmdColorBack(back));

    for (pxiword j = 0; j < frame->height; j += 1) {
        for (pxiword i = 0; i < frame->width; i += 1) {
            item = c4FrameBufferReadOr(frame, i, j, (C4FrameElement) {0});

            if (c4ColorIsEqual(front, item.front) == 0) {
                front = item.front;

                pxConsoleWriteCommand(self,
                    c4ConsoleCmdColorFront(item.front));
            }

            if (c4ColorIsEqual(back, item.back) == 0) {
                back = item.back;

                pxConsoleWriteCommand(self,
                    c4ConsoleCmdColorFront(item.back));
            }

            pxConsoleWriteCommand(self, pxConsoleCmdString8(item.text));
        }

        if (j + 1 < frame->height) {
            PxConsoleCmd command =
                pxConsoleCmdCursorPlace(0, j + 1);

            pxConsoleWriteCommand(self, command);
        }
    }
}

#endif // C4_GAME_FRAME_C
