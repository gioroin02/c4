#ifndef PX_CORE_CONSOLE_CONSOLE_C
#define PX_CORE_CONSOLE_CONSOLE_C

#include "console.h"

#if PX_SYSTEM == PX_SYSTEM_WINDOWS

    #include "../../windows/console/console.c"

    #define __pxConsoleCreate__      pxWindowsConsoleCreate
    #define __pxConsoleModeDefault__ pxWindowsConsoleModeDefault
    #define __pxConsoleModeEvent__   pxWindowsConsoleModeEvent
    #define __pxConsoleWriteMemory__ pxWindowsConsoleWriteMemory
    #define __pxConsoleReadMemory__  pxWindowsConsoleReadMemory
    #define __pxConsoleReadEvent__   pxWindowsConsoleReadEvent
    #define __pxConsolePollEvent__   pxWindowsConsolePollEvent

#elif PX_SYSTEM == PX_SYSTEM_LINUX

    #include "../../linux/console/console.c"

    #define __pxConsoleCreate__      pxLinuxConsoleCreate
    #define __pxConsoleModeDefault__ pxLinuxConsoleModeDefault
    #define __pxConsoleModeEvent__   pxLinuxConsoleModeEvent
    #define __pxConsoleWriteMemory__ pxLinuxConsoleWriteMemory
    #define __pxConsoleReadMemory__  pxLinuxConsoleReadMemory
    #define __pxConsoleReadEvent__   pxLinuxConsoleReadEvent
    #define __pxConsolePollEvent__   pxLinuxConsolePollEvent

#else

    #error "Unknown platform"

#endif

PxConsole
pxConsoleCreate(PxArena* arena, pxiword length)
{
    return __pxConsoleCreate__(arena, length);
}

pxb8
pxConsoleSetMode(PxConsole self, PxConsoleMode mode)
{
    switch (mode) {
        case PX_CONSOLE_MODE_DEFAULT:
            return __pxConsoleModeDefault__(self);

        case PX_CONSOLE_MODE_EVENT:
            return __pxConsoleModeEvent__(self);

        default: break;
    }

    return 0;
}

pxiword
pxConsoleWrite(PxConsole self, PxBuffer8* buffer)
{
    pxBuffer8Normalize(buffer);

    pxu8*   memory = buffer->memory;
    pxiword size   = buffer->size;

    if (size <= 0) return 0;

    pxiword temp = pxConsoleWriteMemory(self, memory, size, 1);

    buffer->size -= temp;
    buffer->head  = (buffer->head + temp) % buffer->length;

    return temp;
}

pxiword
pxConsoleWriteMemory(PxConsole self, void* memory, pxiword amount, pxiword stride)
{
    return __pxConsoleWriteMemory__(self, memory, amount, stride);
}

pxiword
pxConsoleRead(PxConsole self, PxBuffer8* buffer)
{
    pxBuffer8Normalize(buffer);

    pxu8*   memory = buffer->memory + buffer->size;
    pxiword size   = buffer->length - buffer->size;

    if (size <= 0) return 0;

    pxiword temp = pxConsoleReadMemory(self, memory, size, 1);

    buffer->size += temp;
    buffer->tail  = (buffer->tail + temp) % buffer->length;

    return temp;
}

pxiword
pxConsoleReadMemory(PxConsole self, void* memory, pxiword amount, pxiword stride)
{
    return __pxConsoleReadMemory__(self, memory, amount, stride);
}

PxConsoleEvent
pxConsoleReadEvent(PxConsole self)
{
    return __pxConsoleReadEvent__(self);
}

PxConsoleEvent
pxConsolePollEvent(PxConsole self)
{
    return __pxConsolePollEvent__(self);
}

PxWriter
pxConsoleWriter(PxConsole self, PxArena* arena, pxiword length)
{
    PxWriter result = {0};

    if (self == 0 || length <= 0) return result;

    result.buffer = pxBuffer8Reserve(arena, length);

    if (result.buffer.length > 0) {
        result.ctxt = self;
        result.proc = &pxConsoleWrite;
    }

    return result;
}

PxReader
pxConsoleReader(PxConsole self, PxArena* arena, pxiword length)
{
    PxReader result = {0};

    if (self == 0 || length <= 0) return result;

    result.buffer = pxBuffer8Reserve(arena, length);

    if (result.buffer.length > 0) {
        result.ctxt = self;
        result.proc = &pxConsoleRead;
    }

    return result;
}

#endif // PX_CORE_CONSOLE_CONSOLE_C
