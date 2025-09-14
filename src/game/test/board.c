#include "../export.h"

void
c4FrameBufferPaintTile(C4FrameBuffer* frame, PxArena* arena, pxiword x, pxiword y, PxString8 text, C4Color front, C4Color back)
{
    c4FrameBufferPaintCell(frame, x + 0, y + 0, pxs8("#"), front, back);
    c4FrameBufferPaintCell(frame, x + 4, y + 0, pxs8("#"), front, back);
    c4FrameBufferPaintCell(frame, x + 0, y + 2, pxs8("#"), front, back);
    c4FrameBufferPaintCell(frame, x + 4, y + 2, pxs8("#"), front, back);

    for (pxiword i = 1; i < 4; i += 1)
        c4FrameBufferPaintCell(frame, x + i, y + 0, pxs8("-"), front, back);

    for (pxiword i = 1; i < 4; i += 1)
        c4FrameBufferPaintCell(frame, x + i, y + 2, pxs8("-"), front, back);

    for (pxiword i = 1; i < 2; i += 1)
        c4FrameBufferPaintCell(frame, x + 0, y + i, pxs8("|"), front, back);

    for (pxiword i = 1; i < 2; i += 1)
        c4FrameBufferPaintCell(frame, x + 4, y + i, pxs8("|"), front, back);

    if (text.length > 0)
        c4FrameBufferPaintCell(frame, x + 2, y + 1, text, front, back);
}

void
c4FrameBufferPaintBoard(C4FrameBuffer* frame, PxArena* arena, pxiword x, pxiword y, C4GameBoard* board)
{
    for (pxiword j = 0; j < board->height; j += 1) {
        for (pxiword i = 0; i < board->width; i += 1) {
            pxuword   item = c4GameBoardReadOr(board, i, board->height - j - 1, 0);
            PxString8 text = pxs8("");

            if (item != 0) text = pxs8("@");

            c4FrameBufferPaintTile(frame, arena, x + i * 4, y + j * 2,
                text, C4_COLOR_8_WHITE, C4_COLOR_8_BLACK);
        }
    }
}

void
c4FrameBufferPaintRange(C4FrameBuffer* frame, PxArena* arena, pxiword x, pxiword y, pxiword dx, pxiword dy, pxiword start, pxiword stop)
{
    for (pxiword i = start; i < stop; i += 1) {
        PxString8 text = pxString8FromInteger(arena,
            10, PX_FORMAT_OPTION_NONE, i);

        c4FrameBufferPaintCell(frame, x + 2, y + 1,
            text, C4_COLOR_8_WHITE, C4_COLOR_8_BLACK);

        x += dx * 4;
        y += dy * 2;
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

    PxConsole console = pxConsoleCreate(&arena);
    PxReader  reader  = pxConsoleReader(console, &arena, 4 * PX_MEMORY_KIB);
    PxWriter  writer  = pxConsoleWriter(console, &arena, 4 * PX_MEMORY_KIB);

    PxConsoleMsg message = {0};

    PxClock clock = pxClockCreate(&arena);

    pxf32   elapsed = 0;
    pxf32   step    = 1 / 64.0f;
    pxb8    active  = 1;
    pxiword column  = 0;

    C4FrameBuffer frame = c4FrameBufferMake(&arena, 100, 30);

    if (pxConsoleSetMode(console, PX_CONSOLE_MODE_MESSAGE) == 0)
        return 1;

    pxConsoleWriteCommand(&writer, pxConsoleCmdReset());
    pxConsoleWriteCommand(&writer, pxConsoleCmdCursorHide());
    pxWriterFlush(&writer);

    pxuword total  = 2;
    pxuword player = 0;

    pxiword offset = pxArenaOffset(&arena);

    while (active != 0) {
        elapsed += pxClockElapsed(&clock);
        message  = pxConsolePollMessage(&reader);

        pxb8 move_left  = 0;
        pxb8 move_right = 0;
        pxb8 action     = 0;

        switch (message.type) {
            case PX_CONSOLE_MSG_KEYBD_PRESS: {
                switch (message.keybd_press.button) {
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

                    case PX_CONSOLE_KEYBD_ENTER:
                        action = 1;
                    break;

                    default: break;
                }
            }

            default: break;
        }

        column = pxClamp(column + move_right - move_left,
            1, board.width);

        if (action != 0) {
            c4GameBoardInsert(&board, column - 1, player + 1);

            player = (player + 1) % total;
        }

        for (pxiword i = 0; i < 10 && step <= elapsed; i += 1) {
            c4FrameBufferReset(&frame, pxs8(""), C4_COLOR_8_WHITE, C4_COLOR_8_BLACK);

            pxiword width  = board.width;
            pxiword height = board.height;

            pxiword xpad = 3;
            pxiword ypad = 1;

            pxiword wrange = 4 * width + 1;
            pxiword hrange = 3;

            pxiword wboard = 4 * width + 1;
            pxiword hboard = 2 * height + 1;

            pxiword wrect = 4 * 1 + 1;
            pxiword hrect = hboard + 2 * hrange;

            pxiword xrect = xpad + (column - 1) * (wrect - 1);
            pxiword yrect = ypad;

            pxiword xrange0 = xpad;
            pxiword yrange0 = ypad;
            pxiword xboard  = xpad;
            pxiword yboard  = ypad + hrange;
            pxiword xrange1 = xpad;
            pxiword yrange1 = ypad + hrange + hboard;

            c4FrameBufferPaintRect(&frame, xrect, yrect, wrect, hrect,
                pxs8("/"), c4ColorRGB(0xff, 0, 0), C4_COLOR_8_BLACK);

            c4FrameBufferPaintRange(&frame, &arena, xrange0, yrange0,
                1, 0, 1, board.width + 1);

            c4FrameBufferPaintBoard(&frame, &arena, xboard, yboard, &board);

            c4FrameBufferPaintRange(&frame, &arena, xrange1, yrange1,
                1, 0, 1, board.width + 1);

            c4WriterFrame(&writer, &frame);
            pxWriterFlush(&writer);

            elapsed -= step;

            pxArenaRewind(&arena, offset);
        }
    }

    pxConsoleWriteCommand(&writer, pxConsoleCmdReset());
    pxWriterFlush(&writer);

    pxConsoleSetMode(console, PX_CONSOLE_MODE_DEFAULT);
}
