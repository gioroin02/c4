#ifndef PX_CORE_CONSOLE_CONSOLE_C
#define PX_CORE_CONSOLE_CONSOLE_C

#include "console.h"

#if PX_SYSTEM == PX_SYSTEM_WINDOWS

    #include "../../windows/console/console.c"

    #define __pxConsoleCreate__      pxWindowsConsoleCreate
    #define __pxConsoleModeDefault__ pxWindowsConsoleModeDefault
    #define __pxConsoleModeMessage__ pxWindowsConsoleModeMessage
    #define __pxConsoleWrite__       pxWindowsConsoleWrite
    #define __pxConsoleRead__        pxWindowsConsoleRead

#elif PX_SYSTEM == PX_SYSTEM_LINUX

    #include "../../linux/console/console.c"

    #define __pxConsoleCreate__      pxLinuxConsoleCreate
    #define __pxConsoleModeDefault__ pxLinuxConsoleModeDefault
    #define __pxConsoleModeMessage__ pxLinuxConsoleModeMessage
    #define __pxConsoleWrite__       pxLinuxConsoleWrite
    #define __pxConsoleRead__        pxLinuxConsoleRead

#else

    #error "Unknown platform"

#endif

PxConsole
pxConsoleCreate(PxArena* arena)
{
    return __pxConsoleCreate__(arena);
}

pxb8
pxConsoleSetMode(PxConsole self, PxConsoleMode mode)
{
    switch (mode) {
        case PX_CONSOLE_MODE_DEFAULT:
            return __pxConsoleModeDefault__(self);

        case PX_CONSOLE_MODE_MESSAGE:
            return __pxConsoleModeMessage__(self);

        default: break;
    }

    return 0;
}

pxiword
pxConsoleWrite(PxConsole self, pxu8* memory, pxiword length)
{
    return __pxConsoleWrite__(self, memory, length);
}

pxiword
pxConsoleRead(PxConsole self, pxu8* memory, pxiword length)
{
    return __pxConsoleRead__(self, memory, length);
}

PxSource
pxSourceFromConsole(PxConsole self)
{
    PxSource result = {0};

    if (self == 0) return result;

    result.ctxt = self;
    result.proc = &pxConsoleRead;

    return result;
}

PxTarget
pxTargetFromConsole(PxConsole self)
{
    PxTarget result = {0};

    if (self == 0) return result;

    result.ctxt = self;
    result.proc = &pxConsoleWrite;

    return result;
}

#endif // PX_CORE_CONSOLE_CONSOLE_C
