#include "../export.h"
#include "../../structure/export.h"

typedef struct PxConsoleKeybdState
{
    pxb8 move_left  : 1;
    pxb8 move_right : 1;
    pxb8 move_up    : 1;
    pxb8 move_down  : 1;

}
PxConsoleKeybdState;

typedef enum PxConsoleColorType
{
    PX_CONSOLE_COLOR_NONE,
    PX_CONSOLE_COLOR_INDEX,
    PX_CONSOLE_COLOR_RGBA,
}
PxConsoleColorType;

typedef pxu8 PxConsoleColorIndex;

typedef union PxConsoleColorRGBA
{
    struct {
        pxu8 r;
        pxu8 g;
        pxu8 b;
        pxu8 a;
    };

    pxu8 items[4];
}
PxConsoleColorRGBA;

typedef struct PxConsoleColor
{
    PxConsoleColorType type;

    union
    {
        PxConsoleColorRGBA  color_rgba;
        PxConsoleColorIndex color_index;
    };
}
PxConsoleColor;

typedef struct PxConsoleCell
{
    pxi32          unicode;
    PxConsoleColor foreground;
    PxConsoleColor background;
}
PxConsoleCell;

typedef struct PxConsoleFrame
{
    PxArray items;

    pxiword width;
    pxiword height;
}
PxConsoleFrame;

typedef PxWriter PxConsoleWriter;

PxConsoleFrame
pxConsoleFrameMake(PxArena* arena, pxiword width, pxiword height)
{
    PxConsoleFrame result = {0};

    if (width <= 0 || height <= 0) return result;

    result.items = pxArrayReserve(arena,
        PxConsoleCell, width * height);

    if (result.items.length > 0) {
        pxArrayFill(&result.items);

        result.width  = width;
        result.height = height;
    }

    return result;
}

pxb8
pxConsoleFrameRead(PxConsoleFrame* self, pxiword x, pxiword y, PxConsoleCell* value)
{
    if (x < 0 || x >= self->width)  return 0;
    if (y < 0 || y >= self->height) return 0;

    pxiword index = x + self->width * y;

    return pxArrayRead(&self->items,
        index, PxConsoleCell, value);
}

PxConsoleCell
pxConsoleFrameReadOr(PxConsoleFrame* self, pxiword x, pxiword y, PxConsoleCell value)
{
    pxConsoleFrameRead(self, x, y, &value);

    return value;
}

pxb8
pxConsoleFrameUpdate(PxConsoleFrame* self, pxiword x, pxiword y, PxConsoleCell value)
{
    if (x < 0 || x >= self->width)  return 0;
    if (y < 0 || y >= self->height) return 0;

    pxiword index = x + self->width * y;

    return pxArrayUpdate(&self->items,
        index, PxConsoleCell, &value);
}

pxb8
pxConsoleFrameReset(PxConsoleFrame* self, pxi32 unicode, PxConsoleColor foreground, PxConsoleColor background)
{
    if (unicode < 32) unicode = 32;

    PxConsoleCell item = {
        .unicode    = unicode,
        .foreground = foreground,
        .background = background,
    };

    for (pxiword j = 0; j < self->height; j += 1) {
        for (pxiword i = 0; i < self->width; i += 1) {
            if (pxConsoleFrameUpdate(self, i, j, item) == 0)
                return 0;
        }
    }

    return 1;
}

pxb8
pxConsoleFramePaint(PxConsoleFrame* self, pxiword x, pxiword y, pxi32 unicode, PxConsoleColor foreground, PxConsoleColor background)
{
    if (unicode < 32) unicode = 32;

    PxConsoleCell item = {
        .unicode    = unicode,
        .foreground = foreground,
        .background = background,
    };

    return pxConsoleFrameUpdate(self, x, y, item);
}

PxConsoleWriter
pxConsoleWriterMake(PxConsole console, PxArena* arena, pxiword length)
{
    return pxConsoleWriter(console, arena, length);
}

void
pxConsoleWriterFlush(PxConsoleWriter* writer)
{
    pxWriterFlush(writer);
}

pxiword
pxConsoleWriterMoveUp(PxConsoleWriter* self, PxArena* arena, pxu8 amount)
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
pxConsoleWriterMoveDown(PxConsoleWriter* self, PxArena* arena, pxu8 amount)
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
pxConsoleWriterMoveLeft(PxConsoleWriter* self, PxArena* arena, pxu8 amount)
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
pxConsoleWriterMoveRight(PxConsoleWriter* self, PxArena* arena, pxu8 amount)
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
pxConsoleWriterMoveTo(PxConsoleWriter* self, PxArena* arena, pxiword x, pxiword y)
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
pxConsoleWriterShowCursor(PxConsoleWriter* self, pxb8 state)
{
    PxString8 string = pxs8("\x1b[?25l");

    if (state != 0)
        string = pxs8("\x1b[?25h");

    return pxWriterString8(self, string);
}

pxiword
pxConsoleWriterReset(PxConsoleWriter* self, pxb8 scroll)
{
    PxString8 string = pxs8("\x1b\x63");

    if (scroll != 0)
        string = pxs8("\x1b[2J");

    return pxWriterString8(self, string);
}

pxiword
pxConsoleWriterForegroundRGBA(PxConsoleWriter* self, PxArena* arena, PxConsoleColorRGBA color)
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
pxConsoleWriterForegroundIndex(PxConsoleWriter* self, PxArena* arena, PxConsoleColorIndex color)
{
    pxiword s0 = pxWriterString8(self, pxs8("\x1b[38;5;"));

    pxiword s1 = pxWriterUnsigned8(self, arena,
        10, PX_FORMAT_OPTION_NONE, color);

    pxiword s2 = pxWriterString8(self, pxs8("m"));

    return s0 + s1 + s2;
}

pxiword
pxConsoleWriterForeground(PxConsoleWriter* self, PxArena* arena, PxConsoleColor color)
{
    switch (color.type) {
        case PX_CONSOLE_COLOR_RGBA:
            return pxConsoleWriterForegroundRGBA(self, arena, color.color_rgba);

        case PX_CONSOLE_COLOR_INDEX:
            return pxConsoleWriterForegroundIndex(self, arena, color.color_index);

        default: break;
    }

    return 0;
}

pxiword
pxConsoleWriterBackgroundRGBA(PxConsoleWriter* self, PxArena* arena, PxConsoleColorRGBA color)
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
pxConsoleWriterBackgroundIndex(PxConsoleWriter* self, PxArena* arena, PxConsoleColorIndex color)
{
    pxiword s0 = pxWriterString8(self, pxs8("\x1b[48;5;"));

    pxiword s1 = pxWriterUnsigned8(self, arena,
        10, PX_FORMAT_OPTION_NONE, color);

    pxiword s2 = pxWriterString8(self, pxs8("m"));

    return s0 + s1 + s2;
}

pxiword
pxConsoleWriterBackground(PxConsoleWriter* self, PxArena* arena, PxConsoleColor color)
{
    switch (color.type) {
        case PX_CONSOLE_COLOR_RGBA:
            return pxConsoleWriterBackgroundRGBA(self, arena, color.color_rgba);

        case PX_CONSOLE_COLOR_INDEX:
            return pxConsoleWriterBackgroundIndex(self, arena, color.color_index);

        default: break;
    }

    return 0;
}

pxiword
pxConsoleWriterUnicode(PxConsoleWriter* self, PxArena* arena, pxi32 value)
{
    return pxWriterUnicode(self, arena, value);
}

void
pxConsoleWriterFrame(PxConsoleWriter* self, PxArena* arena, PxConsoleFrame* frame)
{
    for (pxiword j = 0; j < frame->height; j += 1) {
        for (pxiword i = 0; i < frame->width; i += 1) {
            PxConsoleCell item = pxConsoleFrameReadOr(frame,
                i, j, (PxConsoleCell) {0});

            pxConsoleWriterMoveTo(self, arena, i, j);

            pxConsoleWriterForeground(self, arena, item.foreground);
            pxConsoleWriterBackground(self, arena, item.background);

            pxConsoleWriterUnicode(self, arena, item.unicode);
        }

        pxConsoleWriterFlush(self);
    }
}

#define FRAMES 2

int
main(int argc, char** argv)
{
    PxArena arena = pxMemoryReserve(32);

    PxConsoleFrame frames[FRAMES] = {
        pxConsoleFrameMake(&arena, 50, 15),
        pxConsoleFrameMake(&arena, 50, 15),
    };

    pxiword frame = 0;

    pxu8 x = 1;
    pxu8 y = 1;

    PxConsole console = pxConsoleCreate(&arena, PX_MEMORY_KIB);

    PxConsoleWriter writer = pxConsoleWriterMake(
        console, &arena, 4 * PX_MEMORY_KIB);

    pxConsoleSetMode(console, PX_CONSOLE_MODE_EVENT);

    PxConsoleKeybdState keybd = {0};

    pxConsoleWriterReset(&writer, 0);
    pxConsoleWriterShowCursor(&writer, 0);

    pxConsoleWriterFlush(&writer);

    pxb8 active = 1;

    PxConsoleColor fground = {
        .type = PX_CONSOLE_COLOR_INDEX, .color_index = 0,
    };

    PxConsoleColor bground = {0};

    for (pxiword i = 0; active != 0; i += 1) {
        PxConsoleEvent event = pxConsolePollEvent(console);

        switch (event.type) {
            case PX_CONSOLE_EVENT_KEYBD_PRESS: {
                switch (event.keybd_press.button) {
                    case PX_CONSOLE_KEYBD_A: keybd.move_left  = 1; break;
                    case PX_CONSOLE_KEYBD_D: keybd.move_right = 1; break;
                    case PX_CONSOLE_KEYBD_W: keybd.move_up    = 1; break;
                    case PX_CONSOLE_KEYBD_S: keybd.move_down  = 1; break;

                    case PX_CONSOLE_KEYBD_ARROW_LEFT:  keybd.move_left  = 1; break;
                    case PX_CONSOLE_KEYBD_ARROW_RIGHT: keybd.move_right = 1; break;
                    case PX_CONSOLE_KEYBD_ARROW_UP:    keybd.move_up    = 1; break;
                    case PX_CONSOLE_KEYBD_ARROW_DOWN:  keybd.move_down  = 1; break;

                    default: break;
                }
            } break;

            case PX_CONSOLE_EVENT_KEYBD_RELEASE: {
                if (event.keybd_release.button == PX_CONSOLE_KEYBD_ESCAPE)
                    active = 0;

                switch (event.keybd_release.button) {
                    case PX_CONSOLE_KEYBD_A: keybd.move_left  = 0; break;
                    case PX_CONSOLE_KEYBD_D: keybd.move_right = 0; break;
                    case PX_CONSOLE_KEYBD_W: keybd.move_up    = 0; break;
                    case PX_CONSOLE_KEYBD_S: keybd.move_down  = 0; break;

                    case PX_CONSOLE_KEYBD_ARROW_LEFT:  keybd.move_left  = 0; break;
                    case PX_CONSOLE_KEYBD_ARROW_RIGHT: keybd.move_right = 0; break;
                    case PX_CONSOLE_KEYBD_ARROW_UP:    keybd.move_up    = 0; break;
                    case PX_CONSOLE_KEYBD_ARROW_DOWN:  keybd.move_down  = 0; break;

                    default: break;
                }
            } break;

            default: break;
        }

        if (i % 250 == 0) {
            pxi8 dx = keybd.move_right - keybd.move_left;
            pxi8 dy = keybd.move_down  - keybd.move_up;

            if (dx != 0 || dy != 0) {
                x = pxClamp(x + dx, 1, frames[frame].width);
                y = pxClamp(y + dy, 1, frames[frame].height);
            }

            bground.type = PX_CONSOLE_COLOR_RGBA;

            bground.color_rgba.r = (bground.color_rgba.r + 1) % 256;
            bground.color_rgba.g = (bground.color_rgba.g + 2) % 256;
            bground.color_rgba.b = (bground.color_rgba.b + 3) % 256;

            pxConsoleFrameReset(&frames[frame], PX_ASCII_SPACE,
                fground, bground);

            pxConsoleFramePaint(&frames[frame], x - 1, y - 1,
                PX_ASCII_SHARP, fground, bground);

            pxConsoleWriterFrame(&writer, &arena, &frames[frame]);
            pxConsoleWriterFlush(&writer);

            frame = (frame + 1) % FRAMES;
        }
    }

    pxConsoleWriterReset(&writer, 0);
    pxConsoleWriterFlush(&writer);

    pxConsoleSetMode(console, PX_CONSOLE_MODE_DEFAULT);
}
