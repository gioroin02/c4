#include "../export.h"

#include "../../process/export.h"
#include "../../time/export.h"
#include "../../structure/export.h"

#include <math.h>

typedef struct PxConsoleValue
{
    pxi32 unicode;

    PxConsoleColor text;
    PxConsoleColor back;
}
PxConsoleValue;

typedef struct PxConsoleBatch
{
    PxArray items;

    pxiword width;
    pxiword height;

    pxb8 dirty;
}
PxConsoleBatch;

PxConsoleBatch
pxConsoleBatchReserve(PxArena* arena, pxiword width, pxiword height)
{
    PxConsoleBatch result = {0};

    if (width <= 0 || height <= 0) return result;

    result.items = pxArrayReserve(arena,
        PxConsoleValue, width * height);

    if (result.items.length > 0) {
        pxArrayFill(&result.items);

        result.width  = width;
        result.height = height;
    }

    return result;
}

pxb8
pxConsoleBatchIsDirty(PxConsoleBatch* self)
{
    return self->dirty != 0 ? 1 : 0;
}

pxb8
pxConsoleBatchGet(PxConsoleBatch* self, pxiword x, pxiword y, PxConsoleValue* value)
{
    if (x < 0 || x >= self->width)  return 0;
    if (y < 0 || y >= self->height) return 0;

    pxiword index = x + self->width * y;

    return pxArrayGet(&self->items,
        index, PxConsoleValue, value);
}

PxConsoleValue
pxConsoleBatchGetOr(PxConsoleBatch* self, pxiword x, pxiword y, PxConsoleValue value)
{
    PxConsoleValue result = {0};

    if (pxConsoleBatchRead(self, x, y, &result) == 0)
        return value;

    return result;
}

pxb8
pxConsoleBatchUpdate(PxConsoleBatch* self, pxiword x, pxiword y, PxConsoleValue value)
{
    if (x < 0 || x >= self->width)  return 0;
    if (y < 0 || y >= self->height) return 0;

    pxiword index = x + self->width * y;

    return pxArrayUpdate(&self->items,
        index, PxConsoleValue, &value);
}

pxb8
pxConsoleBatchReset(PxConsoleBatch* self, pxi32 unicode, PxConsoleColor text, PxConsoleColor back)
{
    if (unicode < 32) unicode = 32;

    PxConsoleValue item = {
        .unicode = unicode,
        .text    = text,
        .back    = back,
    };

    for (pxiword j = 0; j < self->height; j += 1) {
        for (pxiword i = 0; i < self->width; i += 1) {
            if (pxConsoleBatchUpdate(self, i, j, item) == 0)
                return 0;
        }
    }

    self->dirty = 0;

    return 1;
}

pxb8
pxConsoleBatchPaint(PxConsoleBatch* self, pxiword x, pxiword y, pxi32 unicode, PxConsoleColor text, PxConsoleColor back)
{
    if (unicode < 32) unicode = 32;

    PxConsoleValue item = {
        .unicode = unicode,
        .text    = text,
        .back    = back,
    };

    self->dirty = 1;

    return pxConsoleBatchUpdate(self, x, y, item);
}

void
pxConsoleQueueWriteBatch(PxConsoleQueue* self, PxConsoleBatch* batch)
{
    PxConsoleValue item = pxConsoleBatchGetOr(batch, 0, 0, (PxConsoleValue) {0});

    PxConsoleColor text = item.text;
    PxConsoleColor back = item.back;

    pxConsoleQueueWriteMsg(self, pxConsoleMsgCursorMove(0, 0));
    pxConsoleQueueWriteMsg(self, pxConsoleMsgStyleText(text));
    pxConsoleQueueWriteMsg(self, pxConsoleMsgStyleBack(back));

    for (pxiword j = 0; j < batch->height; j += 1) {
        for (pxiword i = 0; i < batch->width; i += 1) {
            item = pxConsoleBatchGetOr(batch, i, j, (PxConsoleValue) {0});

            if (pxConsoleColorIsEqual(text, item.text) == 0) {
                text = item.text;

                pxConsoleQueueWriteMsg(self,
                    pxConsoleMsgStyleText(text));
            }

            if (pxConsoleColorIsEqual(back, item.back) == 0) {
                back = item.back;

                pxConsoleQueueWriteMsg(self,
                    pxConsoleMsgStyleBack(back));
            }

            pxConsoleQueueWriteMsg(self,
                pxConsoleMsgUnicode(item.unicode));
        }

        pxConsoleQueueWriteMsg(self,
            pxConsoleMsgCursorMove(0, j + 1));
    }
}

typedef struct PollingThread
{
    PxSource  source;
    PxTarget  target;
    PxBuffer8 buffer;
}
PollingThread;

pxuword
mainPolling(PollingThread* self)
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

typedef struct Game
{
    PxConsole console;
    PxSource  con_source;
    PxTarget  con_target;

    PxChannel channel;
    PxSource  cnl_source;
    PxTarget  cnl_target;

    PxConsoleQueue input;
    PxConsoleQueue output;

    PxConsoleBatch batch;

    pxb8 active;

    pxu8 x, y;

    PxConsoleColor text;
    PxConsoleColor back;

    pxb8 move_left  : 1;
    pxb8 move_right : 1;
    pxb8 move_up    : 1;
    pxb8 move_down  : 1;
}
Game;

void
gameStart(Game* self, PxArena* arena)
{
    self->text = pxConsoleColor16(9);
    self->back = pxConsoleColorRGB(0, 0, 0);

    self->console    = pxConsoleCreate(arena);
    self->con_source = pxSourceFromConsole(self->console);
    self->con_target = pxTargetFromConsole(self->console);

    self->channel    = pxChannelOpen(arena, PX_MEMORY_KIB);
    self->cnl_source = pxSourceFromChannel(&self->channel);
    self->cnl_target = pxTargetFromChannel(&self->channel);

    self->input  = pxConsoleQueueReserve(arena, PX_MEMORY_KIB);
    self->output = pxConsoleQueueReserve(arena, PX_MEMORY_KIB * 16);

    self->batch = pxConsoleBatchReserve(arena, 50, 15);

    pxConsoleSetMode(self->console, PX_CONSOLE_MODE_MESSAGE);

    pxConsoleQueueWriteMsg(&self->output, pxConsoleMsgReset());
    pxConsoleQueueWriteMsg(&self->output, pxConsoleMsgCursorHide());

    pxTargetWriteBuffer8(self->con_target, pxConsoleQueueBuffer8(&self->output));

    PollingThread polling = {
        .source = self->con_source,
        .target = self->cnl_target,
        .buffer = pxBuffer8Reserve(arena, PX_MEMORY_KIB),
    };

    PxThread thread = pxThreadCreate(arena,
        pxArenaCopy(arena, &polling, PollingThread, 1), &mainPolling);

    pxThreadDetach(thread);

    self->active = 1;
}

void
gameStop(Game* self, PxArena* arena)
{
    pxConsoleQueueWriteMsg(&self->output, pxConsoleMsgReset());

    pxTargetWriteBuffer8(self->con_target, pxConsoleQueueBuffer8(&self->output));

    pxConsoleSetMode(self->console, PX_CONSOLE_MODE_DEFAULT);
}

void
gameInput(Game* self, PxArena* arena)
{
    PxConsoleMsg message = {0};

    pxSourceReadBuffer8(self->cnl_source, pxConsoleQueueBuffer8(&self->input));

    self->move_up    = 0;
    self->move_down  = 0;
    self->move_left  = 0;
    self->move_right = 0;

    while (pxConsoleQueueReadMsg(&self->input, arena, &message) != 0) {
        switch (message.type) {
            case PX_CONSOLE_MSG_UNICODE: {
                if (message.unicode == PX_ASCII_LOWER_Q) self->active = 0;

                if (message.unicode == PX_ASCII_LOWER_W) self->move_up    = 1;
                if (message.unicode == PX_ASCII_LOWER_S) self->move_down  = 1;
                if (message.unicode == PX_ASCII_LOWER_A) self->move_left  = 1;
                if (message.unicode == PX_ASCII_LOWER_D) self->move_right = 1;
            } break;

            default: break;
        }
    }
}

void
gameStep(Game* self, PxArena* arena, pxf32 total, pxf32 slice)
{
    pxu8 x = self->x + self->move_right - self->move_left;
    pxu8 y = self->y + self->move_down  - self->move_up;

    if (x >= 0 && x < self->batch.width)  self->x = x;
    if (y >= 0 && y < self->batch.height) self->y = y;

    pxf32 comp_r = px_between((1 + sin(total + 0)) * 128, 1, 255);
    pxf32 comp_g = px_between((1 + sin(total + 1)) * 128, 1, 255);
    pxf32 comp_b = px_between((1 + sin(total + 2)) * 128, 1, 255);

    self->text = pxConsoleColor16((self->text.color_16.index + 8) % 16);

    self->back = pxConsoleColorRGB(
        px_as(pxu8, comp_r), px_as(pxu8, comp_g), px_as(pxu8, comp_b));
}

void
gamePaint(Game* self, PxArena* arena)
{
    pxConsoleBatchReset(&self->batch, 0, self->text, self->back);

    pxConsoleBatchPaint(&self->batch, self->x, self->y,
        PX_ASCII_SHARP, (PxConsoleColor) {0}, self->back);

    if (pxConsoleBatchIsDirty(&self->batch) != 0)
        pxConsoleQueueWriteBatch(&self->output, &self->batch);

    pxTargetWriteBuffer8(self->con_target, pxConsoleQueueBuffer8(&self->output));
}

void
gameLoop(Game* self, PxArena* arena, pxuword steps)
{
    PxClock clock = pxClockCreate(arena);

    gameStart(self, arena);

    pxf32 time_total = 0;
    pxf32 time_slice = 1.0 / px_as(pxf32, steps);
    pxf32 time_simul = 0;

    while (self->active != 0) {
        pxf32 time_elapsed = pxClockElapsed(clock);

        time_simul += time_elapsed;

        gameInput(self, arena);

        while (time_simul >= time_slice) {
            gameStep(self, arena, time_total, time_slice);

            time_simul -= time_slice;
            time_total += time_slice;
        }

        gamePaint(self, arena);

        pxCurrentThreadSleep(10);
    }

    gameStop(self, arena);
}

int
main(int argc, char** argv)
{
    PxArena arena = pxMemoryReserve(32);
    Game    game  = {0};

    gameLoop(&game, &arena, 60);
}
