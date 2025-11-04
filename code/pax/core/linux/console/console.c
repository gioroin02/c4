#ifndef PAX_LINUX_CONSOLE_CONSOLE_C
#define PAX_LINUX_CONSOLE_CONSOLE_C

#include "./console.h"

#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#include <termios.h>

typedef struct termios Pax_Term_IO;

struct Pax_Linux_Console
{
    Pax_Console_Mode mode;

    Pax_Term_IO termio;
};

static paxb8
pax_linux_console_mode_default(Pax_Linux_Console* self)
{
    if (self->mode == PAX_CONSOLE_MODE_DEFAULT)
        return 1;

    int state = 0;

    do {
        state = tcsetattr(STDIN_FILENO, TCSANOW, &self->termio);
    } while (state == -1 && errno == EINTR);

    if (state == -1) return 0;

    self->mode = PAX_CONSOLE_MODE_DEFAULT;

    return 1;
}

static paxb8
pax_linux_console_mode_raw(Pax_Linux_Console* self)
{
    Pax_Term_IO termio = self->termio;

    if (self->mode == PAX_CONSOLE_MODE_RAW)
        return 1;

    termio.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    termio.c_oflag &= ~(OPOST);
    termio.c_cflag |= CS8;
    termio.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);

    termio.c_cc[VMIN]  = 1;
    termio.c_cc[VTIME] = 0;

    int state = 0;

    do {
        state = tcsetattr(STDIN_FILENO, TCSAFLUSH, &termio);
    } while (state == -1 && errno == EINTR);

    if (state == -1) return 0;

    self->mode = PAX_CONSOLE_MODE_RAW;

    return 1;
}

Pax_Linux_Console*
pax_linux_console_create(Pax_Arena* arena)
{
    paxiword mark = pax_arena_tell(arena);

    Pax_Linux_Console* result =
        pax_arena_reserve(arena, Pax_Linux_Console, 1);

    if (result != 0) {
        int state = tcgetattr(STDIN_FILENO, &result->termio);

        if (state != -1)
            return result;
    }

    pax_arena_rewind(arena, mark, 0);

    return 0;
}

void
pax_linux_console_destroy(Pax_Linux_Console* self)
{
    pax_linux_console_mode_default(self);
}

paxb8
pax_linux_console_mode_apply(Pax_Linux_Console* self, Pax_Console_Mode mode)
{
    switch (mode) {
        case PAX_CONSOLE_MODE_DEFAULT:
            return pax_linux_console_mode_default(self);

        case PAX_CONSOLE_MODE_RAW:
            return pax_linux_console_mode_raw(self);

        default: break;
    }

    return 0;
}

Pax_Console_Mode
pax_linux_console_mode_query(Pax_Linux_Console* self)
{
    return self->mode;
}

paxiword
pax_linux_console_write(Pax_Linux_Console* self, paxu8* memory, paxiword length)
{
    paxiword temp = 0;

    for (paxiword i = 0; i < length;) {
        char* mem = pax_as(char*, memory + i);
        int   len = pax_as(int,   length - i);

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

paxiword
pax_linux_console_read(Pax_Linux_Console* self, paxu8* memory, paxiword length)
{
    paxiword temp = 0;

    char* mem = pax_as(char*, memory);
    int   len = pax_as(int,   length);

    do {
        temp = read(STDIN_FILENO, mem, len);
    } while (temp == -1 && errno == EINTR);

    if (temp > 0 && temp <= length)
        return temp;

    return 0;
}

#endif // PAX_LINUX_CONSOLE_CONSOLE_C
