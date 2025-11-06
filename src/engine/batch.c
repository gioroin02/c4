#ifndef C4_ENGINE_BATCH_C
#define C4_ENGINE_BATCH_C

#include "batch.h"

C4ConsoleBatch
c4ConsoleBatchReserve(PxArena* arena, pxiword width, pxiword height)
{
    C4ConsoleBatch result = {0};

    if (width <= 0 || height <= 0) return result;

    result.items =
        pxArrayReserve(arena, C4ConsoleCell, width * height);

    if (result.items.length > 0) {
        pxArrayFill(&result.items);

        result.width  = width;
        result.height = height;
    }

    return result;
}

pxb8
c4ConsoleBatchGet(C4ConsoleBatch* self, pxiword x, pxiword y, C4ConsoleCell* value)
{
    if (x < 0 || x >= self->width)  return 0;
    if (y < 0 || y >= self->height) return 0;

    pxiword index = x + self->width * y;

    return pxArrayGet(&self->items, index, C4ConsoleCell, value);
}

C4ConsoleCell
c4ConsoleBatchGetOr(C4ConsoleBatch* self, pxiword x, pxiword y, C4ConsoleCell value)
{
    C4ConsoleCell result = {0};

    if (c4ConsoleBatchGet(self, x, y, &result) == 0)
        return value;

    return result;
}

pxb8
c4ConsoleBatchUpdate(C4ConsoleBatch* self, pxiword x, pxiword y, C4ConsoleCell value)
{
    if (x < 0 || x >= self->width)  return 0;
    if (y < 0 || y >= self->height) return 0;

    pxiword index = x + self->width * y;

    return pxArrayUpdate(&self->items,
        index, C4ConsoleCell, &value);
}

pxb8
c4ConsoleBatchReset(C4ConsoleBatch* self, pxi32 unicode, PxConsoleColor text, PxConsoleColor back)
{
    if (pxUnicodeIsAsciiCntrl(unicode) != 0)
        unicode = PX_ASCII_SPACE;

    C4ConsoleCell item = {
        .unicode = unicode,
        .text    = text,
        .back    = back,
    };

    for (pxiword j = 0; j < self->height; j += 1) {
        for (pxiword i = 0; i < self->width; i += 1) {
            if (c4ConsoleBatchUpdate(self, i, j, item) == 0)
                return 0;
        }
    }

    return 1;
}

pxb8
c4ConsoleBatchPaintCell(C4ConsoleBatch* self, pxiword x, pxiword y, pxi32 unicode, PxConsoleColor text, PxConsoleColor back)
{
    if (pxUnicodeIsAsciiCntrl(unicode) != 0)
        unicode = PX_ASCII_SPACE;

    C4ConsoleCell item = {
        .unicode = unicode,
        .text    = text,
        .back    = back,
    };

    return c4ConsoleBatchUpdate(self, x, y, item);
}

pxb8
c4ConsoleBatchPaintRect(C4ConsoleBatch* self, pxiword x, pxiword y, pxiword w, pxiword h, pxi32 unicode, PxConsoleColor text, PxConsoleColor back)
{
    if (pxUnicodeIsAsciiCntrl(unicode) != 0)
        unicode = PX_ASCII_SPACE;

    C4ConsoleCell item = {
        .unicode = unicode,
        .text    = text,
        .back    = back,
    };

    for (pxiword j = 0; j < h; j += 1) {
        for (pxiword i = 0; i < w; i += 1) {
            if (c4ConsoleBatchUpdate(self, x + i, y + j, item) == 0)
                return 0;
        }
    }

    return 1;
}

#endif // C4_ENGINE_BATCH_C
