#ifndef PAX_WIN32_CONSOLE_CONSOLE_C
#define PAX_WIN32_CONSOLE_CONSOLE_C

#include "./console.h"

#define NOMINMAX
#define NOGDI
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

struct Pax_Win32_Console
{
    Pax_Console_Mode mode;

    DWORD input;
    DWORD output;
};

static paxb8
pax_win32_console_mode_default(Pax_Win32_Console* self)
{
    HANDLE stdin  = GetStdHandle(STD_INPUT_HANDLE);
    HANDLE stdout = GetStdHandle(STD_OUTPUT_HANDLE);

    if (self->mode != PAX_CONSOLE_MODE_DEFAULT) {
        SetConsoleMode(stdin, self->input);
        SetConsoleMode(stdout, self->output);
    }

    self->mode = PAX_CONSOLE_MODE_DEFAULT;

    return 1;
}

static paxb8
pax_win32_console_mode_raw(Pax_Win32_Console* self)
{
    HANDLE stdin  = GetStdHandle(STD_INPUT_HANDLE);
    HANDLE stdout = GetStdHandle(STD_OUTPUT_HANDLE);

    if (self->mode != PAX_CONSOLE_MODE_RAW) {
        DWORD mask = ENABLE_PROCESSED_INPUT |
            ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT;

        SetConsoleMode(stdin, self->input & ~mask);

        mask = ENABLE_VIRTUAL_TERMINAL_PROCESSING;

        SetConsoleMode(stdout, self->output | mask);
    }

    self->mode = PAX_CONSOLE_MODE_RAW;

    return 1;
}

Pax_Win32_Console*
pax_win32_console_create(Pax_Arena* arena)
{
    paxiword mark = pax_arena_tell(arena);

    Pax_Win32_Console* result =
        pax_arena_reserve(arena, Pax_Win32_Console, 1);

    HANDLE stdin  = GetStdHandle(STD_INPUT_HANDLE);
    HANDLE stdout = GetStdHandle(STD_OUTPUT_HANDLE);

    if (result != 0) {
        GetConsoleMode(stdin, &result->input);
        GetConsoleMode(stdout, &result->output);

        return result;
    }

    pax_arena_rewind(arena, mark, 0);

    return 0;
}

void
pax_win32_console_destroy(Pax_Win32_Console* self)
{
    pax_win32_console_mode_default(self);
}

paxb8
pax_win32_console_mode_apply(Pax_Win32_Console* self, Pax_Console_Mode mode)
{
    switch (mode) {
        case PAX_CONSOLE_MODE_DEFAULT:
            return pax_win32_console_mode_default(self);

        case PAX_CONSOLE_MODE_RAW:
            return pax_win32_console_mode_raw(self);

        default: break;
    }

    return 0;
}

Pax_Console_Mode
pax_win32_console_mode_query(Pax_Win32_Console* self)
{
    return self->mode;
}

paxiword
pax_win32_console_write(Pax_Win32_Console* self, paxu8* memory, paxiword length)
{
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD  temp   = 0;

    for (paxiword i = 0; i < length;) {
        char* mem = pax_as(char*, memory + i);
        int   len = pax_as(int,   length - i);

        paxb32 state = WriteFile(output, mem, len, &temp, 0);

        if (state != 0 && temp > 0 && temp <= length - i)
            i += temp;
        else
            return i;
    }

    return length;
}

paxiword
pax_win32_console_read(Pax_Win32_Console* self, paxu8* memory, paxiword length)
{
    HANDLE input = GetStdHandle(STD_INPUT_HANDLE);
    DWORD  temp  = 0;

    char* mem = pax_as(char*, memory);
    int   len = pax_as(int,   length);

    paxb32 state = ReadFile(input, mem, len, &temp, 0);

    if (state != 0 && temp > 0 && temp <= length)
        return temp;

    return 0;
}

paxiword
pax_win32_console_poll(Pax_Win32_Console* self, paxu8* memory, paxiword length)
{
    HANDLE   input = GetStdHandle(STD_INPUT_HANDLE);
    paxiword size  = 0;

    GetNumberOfConsoleInputEvents(input, pax_as(DWORD*, &size));

    if (size < 0) return 0;

    return pax_win32_console_read(self,
        memory, pax_min(length, size));
}

#endif // PAX_WIN32_CONSOLE_CONSOLE_C
