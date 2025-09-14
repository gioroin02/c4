#ifndef PX_WINDOWS_CONSOLE_CONSOLE_C
#define PX_WINDOWS_CONSOLE_CONSOLE_C

#include "console.h"

#define NOMINMAX
#define NOGDI
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

struct PxWindowsConsole
{
    DWORD input;
    DWORD output;
};

PxWindowsConsole*
pxWindowsConsoleCreate(PxArena* arena)
{
    pxiword offset = pxArenaOffset(arena);

    PxWindowsConsole* result =
        pxArenaReserve(arena, PxWindowsConsole, 1);

    if (result != 0) {
        HANDLE input  = GetStdHandle(STD_INPUT_HANDLE);
        HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);

        GetConsoleMode(input, &result->input);
        GetConsoleMode(output, &result->output);

        return result;
    }

    pxArenaRewind(arena, offset);

    return 0;
}

pxb8
pxWindowsConsoleModeDefault(PxWindowsConsole* self)
{
    HANDLE input  = GetStdHandle(STD_INPUT_HANDLE);
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleMode(input, self->input);
    SetConsoleMode(output, self->output);

    return 1;
}

pxb8
pxWindowsConsoleModeEvent(PxWindowsConsole* self)
{
    HANDLE input  = GetStdHandle(STD_INPUT_HANDLE);
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);

    DWORD mask = ENABLE_PROCESSED_INPUT |
        ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT;

    SetConsoleMode(input, self->input & ~mask);

    mask = ENABLE_VIRTUAL_TERMINAL_PROCESSING;

    SetConsoleMode(output, self->output | mask);

    return 1;
}

pxiword
pxWindowsConsoleWriteMemory(PxWindowsConsole* self, void* memory, pxiword amount, pxiword stride)
{
    pxiword length = amount * stride;
    DWORD   temp   = 0;

    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);

    for (pxiword i = 0; i < length;) {
        char* mem = pxCast(char*, memory + i);
        int   len = pxCast(int,   length - i);

        pxb32 state = WriteFile(output, mem, len, &temp, 0);

        if (state != 0 && temp > 0 && temp <= length - i)
            i += temp;
        else
            return i;
    }

    return length;
}

pxiword
pxWindowsConsoleReadMemory(PxWindowsConsole* self, void* memory, pxiword amount, pxiword stride)
{
    pxiword length = amount * stride;
    DWORD   temp   = 0;

    HANDLE input = GetStdHandle(STD_INPUT_HANDLE);

    char* mem = pxCast(char*, memory);
    int   len = pxCast(int,   length);

    pxb32 state = ReadFile(input, mem, len, &temp, 0);

    if (state != 0 && temp > 0 && temp <= length)
        return temp;

    return 0;
}

#endif // PX_WINDOWS_CONSOLE_CONSOLE_C
