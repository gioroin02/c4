#ifndef PX_LINUX_CONSOLE_CONSOLE_H
#define PX_LINUX_CONSOLE_CONSOLE_H

#include "import.h"

typedef struct PxLinuxConsole PxLinuxConsole;

PxLinuxConsole*
pxLinuxConsoleCreate(PxArena* arena);

pxb8
pxLinuxConsoleModeDefault(PxLinuxConsole* self);

pxb8
pxLinuxConsoleModeEvent(PxLinuxConsole* self);

pxiword
pxLinuxConsoleWriteMemory(PxLinuxConsole* self, void* memory, pxiword amount, pxiword stride);

pxiword
pxLinuxConsoleReadMemory(PxLinuxConsole* self, void* memory, pxiword amount, pxiword stride);

#endif // PX_LINUX_CONSOLE_CONSOLE_H
