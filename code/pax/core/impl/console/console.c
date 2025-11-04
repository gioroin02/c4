#ifndef PAX_CORE_CONSOLE_CONSOLE_C
#define PAX_CORE_CONSOLE_CONSOLE_C

#include "./console.h"

#if PAX_SYSTEM == PAX_SYSTEM_WINDOWS

    #include "../../win32/console/console.c"

    #define __pax_console_create__     pax_win32_console_create
    #define __pax_console_destroy__    pax_win32_console_destroy
    #define __pax_console_mode_apply__ pax_win32_console_mode_apply
    #define __pax_console_mode_query__ pax_win32_console_mode_query
    #define __pax_console_write__      pax_win32_console_write
    #define __pax_console_read__       pax_win32_console_read

#elif PAX_SYSTEM == PAX_SYSTEM_LINUX

    #include "../../linux/console/console.c"

    #define __pax_console_create__     pax_linux_console_create
    #define __pax_console_destroy__    pax_linux_console_destroy
    #define __pax_console_mode_apply__ pax_linux_console_mode_apply
    #define __pax_console_mode_query__ pax_linux_console_mode_query
    #define __pax_console_write__      pax_linux_console_write
    #define __pax_console_read__       pax_linux_console_read

#else

    #error "Unknown platform"

#endif

Pax_Console
pax_console_create(Pax_Arena* arena)
{
    return __pax_console_create__(arena);
}

void
pax_console_destroy(Pax_Console self)
{
    __pax_console_destroy__(self);
}

paxb8
pax_console_mode_apply(Pax_Console self, Pax_Console_Mode mode)
{
    return __pax_console_mode_apply__(self, mode);
}

Pax_Console_Mode
pax_console_mode_query(Pax_Console self)
{
    return __pax_console_mode_query__(self);
}

paxiword
pax_console_write(Pax_Console self, paxu8* memory, paxiword length)
{
    return __pax_console_write__(self, memory, length);
}

paxiword
pax_console_read(Pax_Console self, paxu8* memory, paxiword length)
{
    return __pax_console_read__(self, memory, length);
}

Pax_Source*
pax_source_from_console(Pax_Arena* arena, Pax_Console self)
{
    Pax_Source result = {0};

    if (self == 0) return 0;

    result.ctxt = self;
    result.proc = &pax_console_read;

    return pax_arena_clone(arena, Pax_Source, &result, 1);
}

Pax_Target*
pax_target_from_console(Pax_Arena* arena, Pax_Console self)
{
    Pax_Target result = {0};

    if (self == 0) return 0;

    result.ctxt = self;
    result.proc = &pax_console_write;

    return pax_arena_clone(arena, Pax_Target, &result, 1);
}

#endif // PAX_CORE_CONSOLE_CONSOLE_C
