#include "../export.h"
#include "../../time/export.h"
#include "../../structure/export.h"

#include <stdlib.h>
#include <time.h>

#define PX_COLOR_RGB_UNITS pxCast(pxiword, 3)

typedef union PxColorRGB
{
    struct
    {
        pxu8 r, g, b;
    };

    pxu8 items[PX_COLOR_RGB_UNITS];
}
PxColorRGB;

pxb8
pxColorRGBIsEqual(PxColorRGB* self, PxColorRGB* value)
{
    if (self == 0 || value == 0)
        return 0;

    if (self->r != value->r) return 0;
    if (self->g != value->g) return 0;
    if (self->b != value->b) return 0;

    return 1;
}

typedef struct PxConsoleCell
{
    pxi32      unicode;
    PxColorRGB front;
    PxColorRGB back;
}
PxConsoleCell;

typedef struct PxConsoleFrame
{
    PxArray items;

    pxiword width;
    pxiword height;
    pxb8    dirty;
}
PxConsoleFrame;

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
pxConsoleFrameIsDirty(PxConsoleFrame* self)
{
    return self->dirty != 0 ? 1 : 0;
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

    self->dirty = 1;

    return pxArrayUpdate(&self->items,
        index, PxConsoleCell, &value);
}

pxb8
pxConsoleFrameReset(PxConsoleFrame* self, pxi32 unicode, PxColorRGB front, PxColorRGB back)
{
    if (unicode < 32) unicode = 32;

    PxConsoleCell item = {
        .unicode = unicode,
        .front   = front,
        .back    = back,
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
pxConsoleFramePaint(PxConsoleFrame* self, pxiword x, pxiword y, pxi32 unicode, PxColorRGB front, PxColorRGB back)
{
    if (unicode < 32) unicode = 32;

    PxConsoleCell item = {
        .unicode = unicode,
        .front   = front,
        .back    = back,
    };

    return pxConsoleFrameUpdate(self, x, y, item);
}

void
pxConsoleWriteFrame(PxWriter* self, PxConsoleFrame* frame)
{
    PxConsoleCell item = {0};

    pxConsoleWriteCommand(self, pxConsoleCmdCursorPlace(0, 0));

    PxColorRGB front = {0};
    PxColorRGB back  = {0};

    for (pxiword j = 0; j < frame->height; j += 1) {
        for (pxiword i = 0; i < frame->width; i += 1) {
            item = pxConsoleFrameReadOr(frame, i, j, (PxConsoleCell) {0});

            if ((i == 0 && j == 0) || pxColorRGBIsEqual(&front, &item.front) == 0) {
                front = item.front;

                pxConsoleWriteCommand(self, pxConsoleCmdStyleRGBFront(
                    item.front.r, item.front.g, item.front.b));
            }

            if ((i == 0 && j == 0) || pxColorRGBIsEqual(&back, &item.back) == 0) {
                back = item.back;

                pxConsoleWriteCommand(self, pxConsoleCmdStyleRGBBack(
                    item.back.r, item.back.g, item.back.b));
            }

            pxConsoleWriteCommand(self, pxConsoleCmdUnicode(item.unicode));
        }

        pxConsoleWriteCommand(self, pxConsoleCmdCursorPlace(0, j + 1));
    }
}

typedef struct GameState
{
    pxu8 x, y;

    PxColorRGB front;
    PxColorRGB back;

    pxb8 move_left  : 1;
    pxb8 move_right : 1;
    pxb8 move_up    : 1;
    pxb8 move_down  : 1;

}
GameState;

int
main(int argc, char** argv)
{
    #define PX_CONSOLE_FRAMES pxCast(pxiword, 2)

    PxArena arena = pxMemoryReserve(32);

    srand(time(0));

    PxConsole console = pxConsoleCreate(&arena);
    PxReader  reader  = pxConsoleReader(console, &arena, 4 * PX_MEMORY_KIB);
    PxWriter  writer  = pxConsoleWriter(console, &arena, 8 * PX_MEMORY_KIB);

    PxConsoleMsg message = {0};

    PxConsoleFrame frames[PX_CONSOLE_FRAMES] = {
        pxConsoleFrameMake(&arena, 100, 50),
        pxConsoleFrameMake(&arena, 100, 50),
    };

    pxiword frame = 0;

    pxConsoleSetMode(console, PX_CONSOLE_MODE_MESSAGE);

    GameState game = {
        .front = {.r = 128, .g = 128, .b = 128},
    };

    pxConsoleWriteCommand(&writer, pxConsoleCmdReset());
    pxConsoleWriteCommand(&writer, pxConsoleCmdCursorHide());
    pxWriterFlush(&writer);

    pxb8 active = 1;

    PxClock clock = pxClockCreate(&arena);

    pxf32 slice   = 1.0 / 64.0;
    pxf32 elapsed = 0;

    while (active != 0) {
        elapsed += pxClockElapsed(clock);
        message  = pxConsolePollMessage(&reader);

        switch (message.type) {
            case PX_CONSOLE_MSG_KEYBD_PRESS: {
                if (message.keybd_press.button == PX_CONSOLE_KEYBD_ESCAPE)
                    active = 0;

                switch (message.keybd_press.button) {
                    case PX_CONSOLE_KEYBD_A: game.move_left  = 1; break;
                    case PX_CONSOLE_KEYBD_D: game.move_right = 1; break;
                    case PX_CONSOLE_KEYBD_W: game.move_up    = 1; break;
                    case PX_CONSOLE_KEYBD_S: game.move_down  = 1; break;

                    case PX_CONSOLE_KEYBD_ARROW_LEFT:  game.move_left  = 1; break;
                    case PX_CONSOLE_KEYBD_ARROW_RIGHT: game.move_right = 1; break;
                    case PX_CONSOLE_KEYBD_ARROW_UP:    game.move_up    = 1; break;
                    case PX_CONSOLE_KEYBD_ARROW_DOWN:  game.move_down  = 1; break;

                    default: break;
                }
            } break;

            case PX_CONSOLE_MSG_KEYBD_RELEASE: {
                switch (message.keybd_release.button) {
                    case PX_CONSOLE_KEYBD_A: game.move_left  = 0; break;
                    case PX_CONSOLE_KEYBD_D: game.move_right = 0; break;
                    case PX_CONSOLE_KEYBD_W: game.move_up    = 0; break;
                    case PX_CONSOLE_KEYBD_S: game.move_down  = 0; break;

                    case PX_CONSOLE_KEYBD_ARROW_LEFT:  game.move_left  = 0; break;
                    case PX_CONSOLE_KEYBD_ARROW_RIGHT: game.move_right = 0; break;
                    case PX_CONSOLE_KEYBD_ARROW_UP:    game.move_up    = 0; break;
                    case PX_CONSOLE_KEYBD_ARROW_DOWN:  game.move_down  = 0; break;

                    default: break;
                }
            } break;

            default: break;
        }

        for (pxiword i = 0; i < 64 && slice <= elapsed; i += 1) {
            pxu8 x = game.x + game.move_right - game.move_left;
            pxu8 y = game.y + game.move_down  - game.move_up;

            if (x >= 0 && x < frames[frame].width)  game.x = x;
            if (y >= 0 && y < frames[frame].height) game.y = y;

            game.back.r = game.back.r + (128 + rand() % 5 - 2);
            game.back.g = game.back.g + (128 + rand() % 5 - 2);
            game.back.b = game.back.b + (128 + rand() % 5 - 2);

            pxConsoleFrameReset(&frames[frame],
                0, game.front, game.back);

            pxConsoleFramePaint(&frames[frame], game.x, game.y,
                PX_ASCII_SHARP, (PxColorRGB) {0}, game.back);

            pxConsoleWriteFrame(&writer, &frames[frame]);
            pxWriterFlush(&writer);

            frame    = (frame + 1) % PX_CONSOLE_FRAMES;
            elapsed -= slice;
        }
    }

    pxConsoleWriteCommand(&writer, pxConsoleCmdReset());
    pxWriterFlush(&writer);

    pxConsoleSetMode(console, PX_CONSOLE_MODE_DEFAULT);
}
