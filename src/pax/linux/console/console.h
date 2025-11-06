#ifndef PX_LINUX_CONSOLE_CONSOLE_H
#define PX_LINUX_CONSOLE_CONSOLE_H

#include "import.h"

typedef struct PxLinuxConsole PxLinuxConsole;

PxLinuxConsole*
pxLinuxConsoleCreate(PxArena* arena);

pxb8
pxLinuxConsoleModeDefault(PxLinuxConsole* self);

pxb8
pxLinuxConsoleModeMessage(PxLinuxConsole* self);

pxiword
pxLinuxConsoleWrite(PxLinuxConsole* self, pxu8* memory, pxiword length);

pxiword
pxLinuxConsoleRead(PxLinuxConsole* self, pxu8* memory, pxiword length);

#endif // PX_LINUX_CONSOLE_CONSOLE_H
