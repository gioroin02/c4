#ifndef PX_CORE_CONSOLE_COMMAND_C
#define PX_CORE_CONSOLE_COMMAND_C

#include "command.h"

#if PX_SYSTEM == PX_SYSTEM_WINDOWS

    #include "../../windows/console/command.c"

    #define __pxConsoleWriteCommand__ pxWindowsConsoleWriteCommand

#elif PX_SYSTEM == PX_SYSTEM_LINUX

    #include "../../linux/console/command.c"

    #define __pxConsoleWriteCommand__ pxLinuxConsoleWriteCommand

#else

    #error "Unknown platform"

#endif

PxConsoleCmd
pxConsoleCmdStyle8Front(pxu8 value)
{
    return (PxConsoleCmd) {
        .type    = PX_CONSOLE_CMD_STYLE_8_FRONT,
        .style_8 = value,
    };
}

PxConsoleCmd
pxConsoleCmdStyle256Front(pxu8 value)
{
    return (PxConsoleCmd) {
        .type      = PX_CONSOLE_CMD_STYLE_256_FRONT,
        .style_256 = value,
    };
}

PxConsoleCmd
pxConsoleCmdStyleRGBFront(pxu8 r, pxu8 g, pxu8 b)
{
    return (PxConsoleCmd) {
        .type = PX_CONSOLE_CMD_STYLE_RGB_FRONT,

        .style_rgb = {
            .r = r,
            .g = g,
            .b = b,
        },
    };
}

PxConsoleCmd
pxConsoleCmdStyle8Back(pxu8 value)
{
    return (PxConsoleCmd) {
        .type    = PX_CONSOLE_CMD_STYLE_8_BACK,
        .style_8 = value,
    };
}

PxConsoleCmd
pxConsoleCmdStyle256Back(pxu8 value)
{
    return (PxConsoleCmd) {
        .type      = PX_CONSOLE_CMD_STYLE_256_BACK,
        .style_256 = value,
    };
}

PxConsoleCmd
pxConsoleCmdStyleRGBBack(pxu8 r, pxu8 g, pxu8 b)
{
    return (PxConsoleCmd) {
        .type = PX_CONSOLE_CMD_STYLE_RGB_BACK,

        .style_rgb = {
            .r = r,
            .g = g,
            .b = b,
        },
    };
}

PxConsoleCmd
pxConsoleCmdStyleClear()
{
    return (PxConsoleCmd) {
        .type = PX_CONSOLE_CMD_STYLE_CLEAR,
    };
}

PxConsoleCmd
pxConsoleCmdCursorShow()
{
    return (PxConsoleCmd) {
        .type = PX_CONSOLE_CMD_CURSOR_SHOW,
    };
}

PxConsoleCmd
pxConsoleCmdCursorHide()
{
    return (PxConsoleCmd) {
        .type = PX_CONSOLE_CMD_CURSOR_HIDE,
    };
}

PxConsoleCmd
pxConsoleCmdCursorUp(pxu8 value)
{
    return (PxConsoleCmd) {
        .type        = PX_CONSOLE_CMD_CURSOR_UP,
        .cursor_move = value,
    };
}

PxConsoleCmd
pxConsoleCmdCursorDown(pxu8 value)
{
    return (PxConsoleCmd) {
        .type        = PX_CONSOLE_CMD_CURSOR_DOWN,
        .cursor_move = value,
    };
}

PxConsoleCmd
pxConsoleCmdCursorRight(pxu8 value)
{
    return (PxConsoleCmd) {
        .type        = PX_CONSOLE_CMD_CURSOR_RIGHT,
        .cursor_move = value,
    };
}

PxConsoleCmd
pxConsoleCmdCursorLeft(pxu8 value)
{
    return (PxConsoleCmd) {
        .type        = PX_CONSOLE_CMD_CURSOR_LEFT,
        .cursor_move = value,
    };
}

PxConsoleCmd
pxConsoleCmdCursorPlace(pxu8 x, pxu8 y)
{
    return (PxConsoleCmd) {
        .type = PX_CONSOLE_CMD_CURSOR_PLACE,

        .cursor_place = {
            .x = x,
            .y = y,
        }
    };
}

PxConsoleCmd
pxConsoleCmdUnicode(pxi32 value)
{
    return (PxConsoleCmd) {
        .type    = PX_CONSOLE_CMD_UNICODE,
        .unicode = value,
    };
}

PxConsoleCmd
pxConsoleCmdString8(PxString8 value)
{
    return (PxConsoleCmd) {
        .type     = PX_CONSOLE_CMD_STRING_8,
        .string_8 = value,
    };
}

PxConsoleCmd
pxConsoleCmdString16(PxString16 value)
{
    return (PxConsoleCmd) {
        .type      = PX_CONSOLE_CMD_STRING_16,
        .string_16 = value,
    };
}

PxConsoleCmd
pxConsoleCmdString32(PxString32 value)
{
    return (PxConsoleCmd) {
        .type      = PX_CONSOLE_CMD_STRING_32,
        .string_32 = value,
    };
}

PxConsoleCmd
pxConsoleCmdReset()
{
    return (PxConsoleCmd) {
        .type = PX_CONSOLE_CMD_RESET,
    };
}

void
pxConsoleWriteCommand(PxWriter* self, PxConsoleCmd value)
{
    __pxConsoleWriteCommand__(self, value);
}

#endif // PX_CORE_CONSOLE_COMMAND_C
