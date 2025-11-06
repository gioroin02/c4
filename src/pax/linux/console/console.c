#ifndef PX_LINUX_CONSOLE_CONSOLE_C
#define PX_LINUX_CONSOLE_CONSOLE_C

#include "console.h"

#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#include <termios.h>

typedef struct termios PxTermIO;

struct PxLinuxConsole
{
    PxTermIO inout;
};

PxLinuxConsole*
pxLinuxConsoleCreate(PxArena* arena)
{
    pxiword offset = pxArenaOffset(arena);

    PxLinuxConsole* result =
        pxArenaReserve(arena, PxLinuxConsole, 1);

    if (result != 0) {
        int state = tcgetattr(STDIN_FILENO, &result->inout);

        if (state != -1)
            return result;
    }

    pxArenaRewind(arena, offset);

    return 0;
}

pxb8
pxLinuxConsoleModeDefault(PxLinuxConsole* self)
{
    int state = 0;

    do {
        state = tcsetattr(STDIN_FILENO, TCSANOW, &self->inout);
    } while (state == -1 && errno == EINTR);

    if (state == -1) return 0;

    return 1;
}

pxb8
pxLinuxConsoleModeMessage(PxLinuxConsole* self)
{
    PxTermIO inout = self->inout;

    inout.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    inout.c_oflag &= ~(OPOST);
    inout.c_cflag |= CS8;
    inout.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);

    inout.c_cc[VMIN]  = 0;
    inout.c_cc[VTIME] = 1;

    int state = 0;

    do {
        state = tcsetattr(STDIN_FILENO, TCSAFLUSH, &inout);
    } while (state == -1 && errno == EINTR);

    if (state == -1) return 0;

    return 1;
}

pxiword
pxLinuxConsoleWrite(PxLinuxConsole* self, pxu8* memory, pxiword length)
{
    pxiword temp = 0;

    for (pxiword i = 0; i < length;) {
        char* mem = px_as(char*, memory + i);
        int   len = px_as(int,   length - i);

        do {
            temp = write(STDOUT_FILENO, mem, len);
        } while (temp == -1 && errno == EINTR);

        if (temp > 0 && temp <= length - i)
            i += temp;
        else
            return i;
    }

    return length;
}

pxiword
pxLinuxConsoleRead(PxLinuxConsole* self, pxu8* memory, pxiword length)
{
    pxiword temp = 0;

    char* mem = px_as(char*, memory);
    int   len = px_as(int,   length);

    do {
        temp = read(STDIN_FILENO, mem, len);
    } while (temp == -1 && errno == EINTR);

    if (temp > 0 && temp <= length)
        return temp;

    return 0;
}

#endif // PX_LINUX_CONSOLE_CONSOLE_C
