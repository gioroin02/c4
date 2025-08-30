#ifndef C4_GAME_BOARD_H
#define C4_GAME_BOARD_H

#include "import.h"

typedef struct C4GameBoard
{
    PxArray grid;

    pxiword width;
    pxiword height;
}
C4GameBoard;

C4GameBoard
c4GameBoardReserve(PxArena* arena, pxiword width, pxiword height);

pxiword
c4GameBoardSize(C4GameBoard* self);

pxiword
c4GameBoardLength(C4GameBoard* self);

pxiword
c4GameBoardHeight(C4GameBoard* self, pxiword column);

pxb8
c4GameBoardIsFull(C4GameBoard* self);

void
c4GameBoardClear(C4GameBoard* self);

pxb8
c4GameBoardInsert(C4GameBoard* self, pxiword column, pxuword value);

pxb8
c4GameBoardRead(C4GameBoard* self, pxiword col, pxiword row, pxuword* value);

pxuword
c4GameBoardReadOr(C4GameBoard* self, pxiword col, pxiword row, pxuword value);

pxiword
c4GameBoardContainsPoint(C4GameBoard* self, pxiword col, pxiword row, pxuword* value);

pxiword
c4GameBoardContainsLine(C4GameBoard* self, pxiword col, pxiword row, pxiword dcol, pxiword drow, pxuword* value);

#endif // C4_GAME_BOARD_H
