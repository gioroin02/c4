#ifndef C4_GAME_RENDERER_C
#define C4_GAME_RENDERER_C

#include "renderer.h"

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
c4FrameBufferReset(C4FrameBuffer* self, pxi32 unicode, C4Color foreground, C4Color background)
{
    if (unicode < 32) unicode = 32;

    C4FrameElement item = {
        .unicode    = unicode,
        .foreground = foreground,
        .background = background,
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
c4FrameBufferPaint(C4FrameBuffer* self, pxiword x, pxiword y, pxi32 unicode, C4Color foreground, C4Color background)
{
    if (unicode < 32) unicode = 32;

    C4FrameElement item = {
        .unicode    = unicode,
        .foreground = foreground,
        .background = background,
    };

    return c4FrameBufferUpdate(self, x, y, item);
}

C4Renderer
c4RendererMake(PxConsole console, PxArena* arena, pxiword length)
{
    return pxConsoleWriter(console, arena, length);
}

void
c4RendererFlush(C4Renderer* writer)
{
    pxWriterFlush(writer);
}

pxiword
c4RendererMoveUp(C4Renderer* self, PxArena* arena, pxu8 amount)
{
    if (amount <= 0) return 0;

    pxiword s0 = pxWriterString8(self, pxs8("\x1b["));
    pxiword s1 = 0;

    if (amount > 1) {
        s1 = pxWriterUnsigned8(self, arena,
            10, PX_FORMAT_OPTION_NONE, amount);
    }

    pxiword s2 = pxWriterString8(self, pxs8("A"));

    return s0 + s1 + s2;
}

pxiword
c4RendererMoveDown(C4Renderer* self, PxArena* arena, pxu8 amount)
{
    if (amount <= 0) return 0;

    pxiword s0 = pxWriterString8(self, pxs8("\x1b["));
    pxiword s1 = 0;

    if (amount > 1) {
        s1 = pxWriterUnsigned8(self, arena,
            10, PX_FORMAT_OPTION_NONE, amount);
    }

    pxiword s2 = pxWriterString8(self, pxs8("B"));

    return s0 + s1 + s2;
}

pxiword
c4RendererMoveLeft(C4Renderer* self, PxArena* arena, pxu8 amount)
{
    if (amount <= 0) return 0;

    pxiword s0 = pxWriterString8(self, pxs8("\x1b["));
    pxiword s1 = 0;

    if (amount > 1) {
        s1 = pxWriterUnsigned8(self, arena,
            10, PX_FORMAT_OPTION_NONE, amount);
    }

    pxiword s2 = pxWriterString8(self, pxs8("D"));

    return s0 + s1 + s2;
}

pxiword
c4RendererMoveRight(C4Renderer* self, PxArena* arena, pxu8 amount)
{
    if (amount <= 0) return 0;

    pxiword s0 = pxWriterString8(self, pxs8("\x1b["));
    pxiword s1 = 0;

    if (amount > 1) {
        s1 = pxWriterUnsigned8(self, arena,
            10, PX_FORMAT_OPTION_NONE, amount);
    }

    pxiword s2 = pxWriterString8(self, pxs8("C"));

    return s0 + s1 + s2;
}

pxiword
c4RendererMoveTo(C4Renderer* self, PxArena* arena, pxiword x, pxiword y)
{
    if (x < 0 || y < 0) return 0;

    pxiword s0 = pxWriterString8(self, pxs8("\x1b["));

    pxiword s1 = 0;
    pxiword s2 = 0;
    pxiword s3 = 0;

    if (x != 0 || y != 0) {
        s1 = pxWriterUnsigned8(self, arena,
            10, PX_FORMAT_OPTION_NONE, y + 1);

        s2 = pxWriterString8(self, pxs8(";"));

        s3 = pxWriterUnsigned8(self, arena,
            10, PX_FORMAT_OPTION_NONE, x + 1);
    }

    pxiword s4 = pxWriterString8(self, pxs8("H"));

    return s0 + s1 + s2 + s3 + s4;
}

pxiword
c4RendererShowCursor(C4Renderer* self, pxb8 state)
{
    PxString8 string = pxs8("\x1b[?25l");

    if (state != 0)
        string = pxs8("\x1b[?25h");

    return pxWriterString8(self, string);
}

pxiword
c4RendererReset(C4Renderer* self, pxb8 scroll)
{
    PxString8 string = pxs8("\x1b\x63");

    if (scroll != 0)
        string = pxs8("\x1b[2J");

    return pxWriterString8(self, string);
}

pxiword
c4RendererForeground(C4Renderer* self, PxArena* arena, C4Color color)
{
    switch (color.type) {
        case PX_CONSOLE_COLOR_INDEX:
            return c4RendererForegroundIndex(self, arena, color.color_index);

        case PX_CONSOLE_COLOR_RGBA:
            return c4RendererForegroundRGBA(self, arena, color.color_rgba);

        default: break;
    }

    return 0;
}

pxiword
c4RendererForegroundIndex(C4Renderer* self, PxArena* arena, C4ColorIndex color)
{
    pxiword s0 = pxWriterString8(self, pxs8("\x1b[38;5;"));

    pxiword s1 = pxWriterUnsigned8(self, arena,
        10, PX_FORMAT_OPTION_NONE, color);

    pxiword s2 = pxWriterString8(self, pxs8("m"));

    return s0 + s1 + s2;
}

pxiword
c4RendererForegroundRGBA(C4Renderer* self, PxArena* arena, C4ColorRGBA color)
{
    pxiword s0 = pxWriterString8(self, pxs8("\x1b[38;2;"));

    pxiword s1 = pxWriterUnsigned8(self, arena,
        10, PX_FORMAT_OPTION_NONE, color.r);

    pxiword s2 = pxWriterString8(self, pxs8(";"));

    pxiword s3 = pxWriterUnsigned8(self, arena,
        10, PX_FORMAT_OPTION_NONE, color.g);

    pxiword s4 = pxWriterString8(self, pxs8(";"));

    pxiword s5 = pxWriterUnsigned8(self, arena,
        10, PX_FORMAT_OPTION_NONE, color.b);

    pxiword s6 = pxWriterString8(self, pxs8("m"));

    return s0 + s1 + s2 + s3 + s4 + s5 + s6;
}

pxiword
c4RendererBackground(C4Renderer* self, PxArena* arena, C4Color color)
{
    switch (color.type) {
        case PX_CONSOLE_COLOR_INDEX:
            return c4RendererBackgroundIndex(self, arena, color.color_index);

        case PX_CONSOLE_COLOR_RGBA:
            return c4RendererBackgroundRGBA(self, arena, color.color_rgba);

        default: break;
    }

    return 0;
}

pxiword
c4RendererBackgroundIndex(C4Renderer* self, PxArena* arena, C4ColorIndex color)
{
    pxiword s0 = pxWriterString8(self, pxs8("\x1b[48;5;"));

    pxiword s1 = pxWriterUnsigned8(self, arena,
        10, PX_FORMAT_OPTION_NONE, color);

    pxiword s2 = pxWriterString8(self, pxs8("m"));

    return s0 + s1 + s2;
}

pxiword
c4RendererBackgroundRGBA(C4Renderer* self, PxArena* arena, C4ColorRGBA color)
{
    pxiword s0 = pxWriterString8(self, pxs8("\x1b[48;2;"));

    pxiword s1 = pxWriterUnsigned8(self, arena,
        10, PX_FORMAT_OPTION_NONE, color.r);

    pxiword s2 = pxWriterString8(self, pxs8(";"));

    pxiword s3 = pxWriterUnsigned8(self, arena,
        10, PX_FORMAT_OPTION_NONE, color.g);

    pxiword s4 = pxWriterString8(self, pxs8(";"));

    pxiword s5 = pxWriterUnsigned8(self, arena,
        10, PX_FORMAT_OPTION_NONE, color.b);

    pxiword s6 = pxWriterString8(self, pxs8("m"));

    return s0 + s1 + s2 + s3 + s4 + s5 + s6;
}

pxiword
c4RendererUnicode(C4Renderer* self, PxArena* arena, pxi32 value)
{
    return pxWriterUnicode(self, arena, value);
}

void
c4RendererFrame(C4Renderer* self, PxArena* arena, C4FrameBuffer* frame)
{
    C4FrameElement item = {0};

    for (pxiword j = 0; j < frame->height; j += 1) {
        for (pxiword i = 0; i < frame->width; i += 1) {
            item = c4FrameBufferReadOr(frame, i, j, item);

            c4RendererMoveTo(self, arena, i, j);

            c4RendererForeground(self, arena, item.foreground);
            c4RendererBackground(self, arena, item.background);

            c4RendererUnicode(self, arena, item.unicode);
        }

        c4RendererFlush(self);
    }
}

#endif // C4_GAME_RENDERER_C
