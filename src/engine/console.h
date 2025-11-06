#ifndef C4_ENGINE_CONSOLE_H
#define C4_ENGINE_CONSOLE_H

#include "batch.h"

typedef struct C4ConsoleReaderCtxt
{
    PxArena  arena;
    PxQueue* queue;

    PxLock lock;

    PxSource source;
}
C4ConsoleReaderCtxt;

pxuword
c4ConsoleReaderProc(C4ConsoleReaderCtxt* self);

typedef struct C4Console
{
    PxConsole console;

    PxLock  input_lock;
    PxQueue input_queue;

    PxConsoleQueue output_queue;
}
C4Console;

C4Console
c4ConsoleCreate(PxArena* arena, pxiword length);

pxb8
c4ConsoleReadMsg(C4Console* self, PxConsoleMsg* value);

pxb8
c4ConsoleWriteMsg(C4Console* self, PxConsoleMsg value);

pxb8
c4ConsoleWriteBatch(C4Console* self, C4ConsoleBatch* value);

pxb8
c4ConsoleFlush(C4Console* self);

C4ConsoleReaderCtxt*
c4ConsoleReaderCtxt(C4Console* self, PxArena* arena, pxiword length);

#endif // C4_ENGINE_CONSOLE_H
