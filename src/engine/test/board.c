#include "../export.h"

void
c4ConsoleBatchPaintTile(C4ConsoleBatch* batch, PxArena* arena, pxiword x, pxiword y, pxi32 unicode, PxConsoleColor text, PxConsoleColor back)
{
    c4ConsoleBatchPaintCell(batch, x + 0, y + 0, PX_ASCII_SHARP, text, back);
    c4ConsoleBatchPaintCell(batch, x + 4, y + 0, PX_ASCII_SHARP, text, back);
    c4ConsoleBatchPaintCell(batch, x + 0, y + 2, PX_ASCII_SHARP, text, back);
    c4ConsoleBatchPaintCell(batch, x + 4, y + 2, PX_ASCII_SHARP, text, back);

    for (pxiword i = 1; i < 4; i += 1)
        c4ConsoleBatchPaintCell(batch, x + i, y + 0, PX_ASCII_MINUS, text, back);

    for (pxiword i = 1; i < 4; i += 1)
        c4ConsoleBatchPaintCell(batch, x + i, y + 2, PX_ASCII_MINUS, text, back);

    for (pxiword i = 1; i < 2; i += 1)
        c4ConsoleBatchPaintCell(batch, x + 0, y + i, PX_ASCII_PIPE, text, back);

    for (pxiword i = 1; i < 2; i += 1)
        c4ConsoleBatchPaintCell(batch, x + 4, y + i, PX_ASCII_PIPE, text, back);

    if (unicode >= 32)
        c4ConsoleBatchPaintCell(batch, x + 2, y + 1, unicode, text, back);
}

void
c4ConsoleBatchPaintBoard(C4ConsoleBatch* batch, PxArena* arena, pxiword x, pxiword y, C4GameBoard* board)
{
    for (pxiword j = 0; j < board->height; j += 1) {
        for (pxiword i = 0; i < board->width; i += 1) {
            pxuword item    = c4GameBoardGetOr(board, i, board->height - j - 1, 0);
            pxi32   unicode = 0;

            if (item != 0) unicode = PX_ASCII_COMMERCIAL;

            c4ConsoleBatchPaintTile(batch, arena, x + i * 4, y + j * 2,
                unicode, C4_COLOR_16_WHITE, C4_COLOR_16_BLACK);
        }
    }
}

void
c4ConsoleBatchPaintRange(C4ConsoleBatch* batch, PxArena* arena, pxiword x, pxiword y, pxiword dx, pxiword dy, pxiword start, pxiword stop)
{
    pxiword offset = pxArenaOffset(arena);

    PxFormatRadix radix = PX_FORMAT_RADIX_10;
    PxFormatFlag  flags = PX_FORMAT_FLAG_NONE;

    for (pxiword i = start; i < stop; i += 1) {
        PxString8 string = pxString8FromInteger(arena, i, radix, flags);

        for (pxiword j = 0; j < string.length; j += 1) {
            pxi32 unicode = string.memory[j];

            c4ConsoleBatchPaintCell(batch, x + 2 + j, y + 1,
                unicode, C4_COLOR_16_WHITE, C4_COLOR_16_BLACK);
        }

        x += dx * 4;
        y += dy * 2;

        pxArenaRewind(arena, offset);
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

typedef struct ReaderThread
{
    PxSource  source;
    PxTarget  target;
    PxBuffer8 buffer;
}
ReaderThread;

pxuword
mainReader(ReaderThread* self)
{
    if (self == 0) return 0;

    while (1) {
        pxiword size = pxSourceReadBuffer8(self->source, &self->buffer);

        if (size > 0)
            size = pxTargetWriteBuffer8(self->target, &self->buffer);

        if (size <= 0) break;
    }

    return 1;
}

typedef struct C4Game
{
    PxConsole console;
    PxSource  con_source;
    PxTarget  con_target;

    PxChannel channel;
    PxSource  chl_source;
    PxTarget  chl_target;

    PxConsoleQueue queue_in;
    PxConsoleQueue queue_out;

    C4GameBoard board;

    C4ConsoleBatch batch;

    pxb8 active;

    pxiword column;

    pxb8 insert;
    pxb8 move_left;
    pxb8 move_right;
}
C4Game;

void
c4GameStart(C4Game* self, PxArena* arena)
{
    self->console    = pxConsoleCreate(arena);
    self->con_source = pxSourceFromConsole(self->console);
    self->con_target = pxTargetFromConsole(self->console);

    self->channel    = pxChannelOpen(arena, PX_MEMORY_KIB);
    self->chl_source = pxSourceFromChannel(&self->channel);
    self->chl_target = pxTargetFromChannel(&self->channel);

    self->queue_in  = pxConsoleQueueReserve(arena, PX_MEMORY_KIB);
    self->queue_out = pxConsoleQueueReserve(arena, PX_MEMORY_KIB * 16);

    self->board = c4GameBoardReserve(arena, 5, 5);

    self->batch = c4ConsoleBatchReserve(arena, 60, 20);

    pxConsoleSetMode(self->console, PX_CONSOLE_MODE_MESSAGE);

    pxConsoleQueueWriteList(&self->queue_out, (PxConsoleMsg[]) {
        pxConsoleMsgReset(), pxConsoleMsgCursorHide(),
    }, 2);

    pxTargetWriteBuffer8(self->con_target,
        pxConsoleQueueBuffer8(&self->queue_out));

    ReaderThread* reader =
        pxArenaReserve(arena, ReaderThread, 1);

    reader->source = self->con_source;
    reader->target = self->chl_target;
    reader->buffer = pxBuffer8Reserve(arena, PX_MEMORY_KIB);

    PxThread thread = pxThreadCreate(arena, reader, &mainReader);

    pxThreadDetach(thread);

    self->active = 1;
}

void
c4GameStop(C4Game* self)
{
    pxConsoleQueueWriteList(&self->queue_out, (PxConsoleMsg[]) {
        pxConsoleMsgReset(),
    }, 1);

    pxTargetWriteBuffer8(self->con_target,
        pxConsoleQueueBuffer8(&self->queue_out));

    pxConsoleSetMode(self->console, PX_CONSOLE_MODE_DEFAULT);
}

void
c4GameInput(C4Game* self, PxArena* arena)
{
    PxConsoleMsg message = {0};

    pxSourceReadBuffer8(self->chl_source,
        pxConsoleQueueBuffer8(&self->queue_in));

    self->active     = 1;
    self->insert     = 0;
    self->move_left  = 0;
    self->move_right = 0;

    while (pxConsoleQueueReadMsg(&self->queue_in, arena, &message) != 0) {
        switch (message.type) {
            case PX_CONSOLE_MSG_UNICODE: {
                if (message.unicode == PX_ASCII_LOWER_Q) self->active     = 0;
                if (message.unicode == PX_ASCII_LOWER_S) self->insert     = 1;
                if (message.unicode == PX_ASCII_LOWER_A) self->move_left  = 1;
                if (message.unicode == PX_ASCII_LOWER_D) self->move_right = 1;
            } break;

            default: break;
        }
    }
}

void
c4GameTick(C4Game* self, PxArena* arena, pxf32 total, pxf32 slice)
{

}

void
c4GameStep(C4Game* self, PxArena* arena, pxf32 total)
{
    pxiword movement = self->move_right - self->move_left;

    self->column = px_between(self->column + movement, 0, self->board.width - 1);

    if (self->insert != 0)
        c4GameBoardInsert(&self->board, self->column, 1);
}

void
c4GamePaint(C4Game* self, PxArena* arena)
{
    c4BatchReset(&self->batch, 0, C4_COLOR_16_WHITE, C4_COLOR_16_BLACK);

    pxiword width  = self->board.width;
    pxiword height = self->board.height;

    pxiword xpad = 3;
    pxiword ypad = 1;

    pxiword wrange = 4 * width + 1;
    pxiword hrange = 3;

    pxiword wboard = 4 * width + 1;
    pxiword hboard = 2 * height + 1;

    pxiword wrect = 4 * 1 + 1;
    pxiword hrect = hboard + 2 * hrange;

    pxiword xrect = xpad + self->column * (wrect - 1);
    pxiword yrect = ypad;

    pxiword xrange0 = xpad;
    pxiword yrange0 = ypad;
    pxiword xboard  = xpad;
    pxiword yboard  = ypad + hrange;
    pxiword xrange1 = xpad;
    pxiword yrange1 = ypad + hrange + hboard;

    c4ConsoleBatchPaintRect(&self->batch, xrect, yrect, wrect, hrect,
        PX_ASCII_SHARP, C4_COLOR_16_MAGENTA_DARK, C4_COLOR_16_BLACK);

    c4ConsoleBatchPaintRange(&self->batch, arena, xrange0, yrange0,
        1, 0, 1, self->board.width + 1);

    c4ConsoleBatchPaintBoard(&self->batch, arena, xboard, yboard, &self->board);

    c4ConsoleBatchPaintRange(&self->batch, arena, xrange1, yrange1,
        1, 0, 1, self->board.width + 1);

    c4ConsoleQueueWriteBatch(&self->queue_out, &self->batch);

    pxTargetWriteBuffer8(self->con_target,
        pxConsoleQueueBuffer8(&self->queue_out));
}

void
c4GameLoop(C4Game* self, PxArena* arena, pxuword steps)
{
    PxClock clock = pxClockCreate(arena);

    c4GameStart(self, arena);

    pxf32 time_total = 0;
    pxf32 time_slice = 1.0 / px_as(pxf32, steps);
    pxf32 time_simul = 0;

    while (self->active != 0) {
        pxf32 time_elapsed = pxClockElapsed(clock);

        time_simul += time_elapsed;

        c4GameInput(self, arena);

        while (time_simul >= time_slice) {
            c4GameTick(self, arena, time_total, time_slice);

            time_simul -= time_slice;
            time_total += time_slice;
        }

        c4GameStep(self, arena, time_total);
        c4GamePaint(self, arena);

        pxCurrentThreadSleep(10);
    }

    c4GameStop(self);
}

int
main(int argc, char** argv)
{
    C4Game game = {0};

    PxArena arena = pxMemoryReserve(32);

    c4GameLoop(&game, &arena, 48);
}
