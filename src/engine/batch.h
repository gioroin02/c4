#ifndef C4_ENGINE_BATCH_H
#define C4_ENGINE_BATCH_H

#include "import.h"

typedef struct C4ConsoleCell
{
    pxi32 unicode;

    PxConsoleColor text;
    PxConsoleColor back;
}
C4ConsoleCell;

typedef struct C4ConsoleBatch
{
    PxArray items;

    pxiword width;
    pxiword height;
}
C4ConsoleBatch;

C4ConsoleBatch
c4ConsoleBatchReserve(PxArena* arena, pxiword width, pxiword height);

pxb8
c4ConsoleBatchGet(C4ConsoleBatch* self, pxiword x, pxiword y, C4ConsoleCell* value);

C4ConsoleCell
c4ConsoleBatchGetOr(C4ConsoleBatch* self, pxiword x, pxiword y, C4ConsoleCell value);

pxb8
c4ConsoleBatchUpdate(C4ConsoleBatch* self, pxiword x, pxiword y, C4ConsoleCell value);

pxb8
c4ConsoleBatchReset(C4ConsoleBatch* self, pxi32 unicode, PxConsoleColor text, PxConsoleColor back);

pxb8
c4ConsoleBatchPaintCell(C4ConsoleBatch* self, pxiword x, pxiword y, pxi32 unicode, PxConsoleColor text, PxConsoleColor back);

pxb8
c4ConsoleBatchPaintRect(C4ConsoleBatch* self, pxiword x, pxiword y, pxiword w, pxiword h, pxi32 unicode, PxConsoleColor text, PxConsoleColor back);

#endif // C4_ENGINE_BATCH_H
