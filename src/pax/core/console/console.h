#ifndef PX_CORE_CONSOLE_CONSOLE_H
#define PX_CORE_CONSOLE_CONSOLE_H

#include "import.h"

typedef void* PxConsole;

typedef enum PxConsoleMode
{
    PX_CONSOLE_MODE_NONE,
    PX_CONSOLE_MODE_DEFAULT,
    PX_CONSOLE_MODE_MESSAGE,
}
PxConsoleMode;

PxConsole
pxConsoleCreate(PxArena* arena);

pxb8
pxConsoleSetMode(PxConsole self, PxConsoleMode mode);

pxiword
pxConsoleWrite(PxConsole self, pxu8* memory, pxiword length);

pxiword
pxConsoleRead(PxConsole self, pxu8* memory, pxiword length);

PxSource
pxSourceFromConsole(PxConsole self);

PxTarget
pxTargetFromConsole(PxConsole self);

#endif // PX_CORE_CONSOLE_CONSOLE_H
