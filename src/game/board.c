#ifndef C4_GAME_BOARD_C
#define C4_GAME_BOARD_C

#include "board.h"

C4GameBoard
c4GameBoardReserve(PxArena* arena, pxiword width, pxiword height)
{
    C4GameBoard result = {0};

    if (width <= 0 || height <= 0) return result;

    result.grid = pxArrayReserve(arena, pxuword, width * height);

    if (result.grid.length != 0) {
        pxArrayFill(&result.grid);

        result.width  = width;
        result.height = height;
    }

    return result;
}

pxiword
c4GameBoardSize(C4GameBoard* self)
{
    return self->grid.size;
}

pxiword
c4GameBoardLength(C4GameBoard* self)
{
    return self->grid.length;
}

pxb8
c4GameBoardIsFull(C4GameBoard* self)
{
    pxiword count = 0;

    for (pxiword i = 0; i < self->width; i += 1) {
        for (pxiword j = 0; j < self->height; j += 1) {
            pxiword index = self->width * i + j;
            pxuword item  = 0;

            pxArrayRead(&self->grid, index,
                pxuword, &item);

            if (item != 0) count += 1;
        }
    }

    if (count >= self->grid.length)
        return 1;

    return 0;
}

pxiword
c4GameBoardHeight(C4GameBoard* self, pxiword column)
{
    if (column < 0 || column >= self->width) return 0;

    for (pxiword i = 0; i < self->height; i += 1) {
        pxiword index = self->height * column + i;
        pxiword other = 0;

        pxArrayRead(&self->grid, index, pxiword, &other);

        if (other == 0) return i;
    }

    return -1;
}

void
c4GameBoardClear(C4GameBoard* self)
{
    pxArrayClear(&self->grid);
    pxArrayFill(&self->grid);
}

pxb8
c4GameBoardInsert(C4GameBoard* self, pxiword column, pxuword value)
{
    if (column < 0 || column >= self->width) return 0;

    if (value <= 0) return 0;

    pxiword height = c4GameBoardHeight(self, column);

    if (height >= 0) {
        pxiword index = self->height * column + height;

        return pxArrayUpdate(&self->grid, index,
            pxuword, &value);
    }

    return 0;
}

pxb8
c4GameBoardRead(C4GameBoard* self, pxiword x, pxiword y, pxuword* value)
{
    if (c4GameBoardContainsPoint(self, x, y, value) != 0)
        return 1;

    return 0;
}

pxuword
c4GameBoardReadOr(C4GameBoard* self, pxiword x, pxiword y, pxuword value)
{
    pxuword result = 0;

    if (c4GameBoardContainsPoint(self, x, y, &result) == 0)
        return value;

    return result;
}

pxiword
c4GameBoardContainsPoint(C4GameBoard* self, pxiword x, pxiword y, pxuword* value)
{
    if (x < 0 || x >=  self->width) return 0;
    if (y < 0 || y >= self->height) return 0;

    if (value != 0) {
        pxiword index = x * self->height + y;

        pxArrayRead(&self->grid, index,
            pxuword, value);
    }

    return 1;
}

pxiword
c4GameBoardContainsLine(C4GameBoard* self, pxiword x, pxiword y, pxiword dx, pxiword dy, pxuword* value)
{
    pxuword temp   = 0;
    pxuword other  = 0;
    pxiword result = c4GameBoardContainsPoint(self, x, y, &other);

    if (dx == 0 && dy == 0) return result;

    x += pxDirectionInteger(dx);
    y += pxDirectionInteger(dy);

    while (c4GameBoardContainsPoint(self, x, y, &temp) != 0) {
        if (temp != other) break;

        result += 1;

        x += pxDirectionInteger(dx);
        y += pxDirectionInteger(dy);
    }

    if (value != 0) *value = other;

    return result;
}

#endif // C4_GAME_BOARD_C
