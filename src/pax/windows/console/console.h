#ifndef PX_WINDOWS_CONSOLE_CONSOLE_H
#define PX_WINDOWS_CONSOLE_CONSOLE_H

#include "import.h"

typedef struct PxWindowsConsole PxWindowsConsole;

PxWindowsConsole*
pxWindowsConsoleCreate(PxArena* arena, pxiword length);

pxb8
pxWindowsConsoleModeDefault(PxWindowsConsole* self);

pxb8
pxWindowsConsoleModeEvent(PxWindowsConsole* self);

pxiword
pxWindowsConsoleWriteMemory(PxWindowsConsole* self, void* memory, pxiword amount, pxiword stride);

pxiword
pxWindowsConsoleReadMemory(PxWindowsConsole* self, void* memory, pxiword amount, pxiword stride);

PxConsoleEvent
pxWindowsConsoleReadEvent(PxWindowsConsole* self);

PxConsoleEvent
pxWindowsConsolePollEvent(PxWindowsConsole* self);

#endif // PX_WINDOWS_CONSOLE_CONSOLE_H
