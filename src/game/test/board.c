#include "../export.h"

#define FGROUND ((C4Color) \
    {.type = PX_CONSOLE_COLOR_RGBA, .color_rgba = {255, 255, 255, 0}})

#define BGROUND ((C4Color) \
    {.type = PX_CONSOLE_COLOR_RGBA, .color_rgba = { 50,  50,  50, 0}})

void
c4PaintBoard(C4FrameBuffer* buffer, C4GameBoard* self)
{
    for (pxiword j = 0; j < self->height; j += 1) {
        for (pxiword i = 0; i < self->width; i += 1) {
            pxuword item = c4GameBoardReadOr(self, i, j, 0);

            if (item != 0) {
                pxi32 unicode = PX_ASCII_UPPER_A + item + 1;

                c4FrameBufferPaint(buffer, i, j,
                    unicode, FGROUND, BGROUND);
            }
        }
    }
}

pxuword
playerHasWon(C4GameBoard* self, pxiword x, pxiword y, pxiword length)
{
    #define DIRS 8

    pxiword xs[DIRS] = {+1, +1,  0, -1, -1, -1,  0, +1};
    pxiword ys[DIRS] = { 0, +1, +1, +1,  0, -1, -1, -1};

    pxuword value = 0;

    for (pxiword i = 0; i < DIRS; i += 1) {
        pxiword line = c4GameBoardContainsLine(self,
            x, y, xs[i], ys[i], &value);

        if (line >= length) return value;
    }

    return 0;
}

int
main(int argc, char** argv)
{
    PxArena     arena = pxMemoryReserve(32);
    C4GameBoard board = c4GameBoardReserve(&arena, 7, 5);

    PxConsole  console  = pxConsoleCreate(&arena, 0);
    C4Renderer renderer = c4RendererMake(console, &arena, 4 * PX_MEMORY_KIB);

    pxb8    active = 1;
    pxiword column = 0;

    C4FrameBuffer frame = c4FrameBufferMake(&arena, 100, 30);

    if (pxConsoleSetMode(console, PX_CONSOLE_MODE_EVENT) == 0)
        return 1;

    c4RendererReset(&renderer, 0);
    c4RendererShowCursor(&renderer, 0);

    c4RendererFlush(&renderer);

    for (pxiword i = 0; active != 0; i += 1) {
        PxConsoleEvent event = pxConsolePollEvent(console);

        pxb8 move_left  = 0;
        pxb8 move_right = 0;

        switch (event.type) {
            case PX_CONSOLE_EVENT_KEYBD_PRESS: {
                switch (event.keybd_press.button) {
                    case PX_CONSOLE_KEYBD_A:
                    case PX_CONSOLE_KEYBD_ARROW_LEFT:
                        move_left = 1;
                    break;

                    case PX_CONSOLE_KEYBD_D:
                    case PX_CONSOLE_KEYBD_ARROW_RIGHT:
                        move_right = 1;
                    break;

                    case PX_CONSOLE_KEYBD_ESCAPE:
                        active = 0;
                    break;

                    default: break;
                }
            }

            default: break;
        }

        c4FrameBufferReset(&frame,
            PX_ASCII_COMMERCIAL, FGROUND, BGROUND);

        c4PaintBoard(&frame, &board);

        c4RendererFrame(&renderer, &arena, &frame);
        c4RendererFlush(&renderer);
    }

    c4RendererReset(&renderer, 0);
    c4RendererFlush(&renderer);

    pxConsoleSetMode(console, PX_CONSOLE_MODE_DEFAULT);
}
