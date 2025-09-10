#ifndef PX_CORE_CONSOLE_CONSOLE_H
#define PX_CORE_CONSOLE_CONSOLE_H

#include "event.h"

typedef void* PxConsole;

typedef enum PxConsoleMode
{
    PX_CONSOLE_MODE_NONE,
    PX_CONSOLE_MODE_DEFAULT,
    PX_CONSOLE_MODE_EVENT,
}
PxConsoleMode;

PxConsole
pxConsoleCreate(PxArena* arena, pxiword length);

pxb8
pxConsoleSetMode(PxConsole self, PxConsoleMode mode);

pxiword
pxConsoleWrite(PxConsole self, PxBuffer8* buffer);

pxiword
pxConsoleWriteMemory(PxConsole self, void* memory, pxiword amount, pxiword stride);

pxiword
pxConsoleRead(PxConsole self, PxBuffer8* buffer);

pxiword
pxConsoleReadMemory(PxConsole self, void* memory, pxiword amount, pxiword stride);

PxConsoleEvent
pxConsoleReadEvent(PxConsole self);

PxConsoleEvent
pxConsolePollEvent(PxConsole self);

PxWriter
pxConsoleWriter(PxConsole self, PxArena* arena, pxiword length);

PxReader
pxConsoleReader(PxConsole self, PxArena* arena, pxiword length);

#endif // PX_CORE_CONSOLE_CONSOLE_H
