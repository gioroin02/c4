#ifndef PX_CORE_CONSOLE_COMMAND_H
#define PX_CORE_CONSOLE_COMMAND_H

#include "import.h"

#define PX_CONSOLE_COLOR_RGB_UNITS pxCast(pxiword, 3)

typedef enum PxConsoleCmdType
{
    PX_CONSOLE_CMD_NONE,

    PX_CONSOLE_CMD_STYLE_8_FRONT,
    PX_CONSOLE_CMD_STYLE_8_BACK,
    PX_CONSOLE_CMD_STYLE_256_FRONT,
    PX_CONSOLE_CMD_STYLE_256_BACK,
    PX_CONSOLE_CMD_STYLE_RGB_FRONT,
    PX_CONSOLE_CMD_STYLE_RGB_BACK,

    PX_CONSOLE_CMD_STYLE_CLEAR,

    PX_CONSOLE_CMD_CURSOR_SHOW,
    PX_CONSOLE_CMD_CURSOR_HIDE,
    PX_CONSOLE_CMD_CURSOR_UP,
    PX_CONSOLE_CMD_CURSOR_DOWN,
    PX_CONSOLE_CMD_CURSOR_RIGHT,
    PX_CONSOLE_CMD_CURSOR_LEFT,
    PX_CONSOLE_CMD_CURSOR_PLACE,

    PX_CONSOLE_CMD_UNICODE,

    PX_CONSOLE_CMD_STRING_8,
    PX_CONSOLE_CMD_STRING_16,
    PX_CONSOLE_CMD_STRING_32,

    PX_CONSOLE_CMD_RESET,
}
PxConsoleCmdType;

typedef pxu8 PxConsoleCmdStyle8;
typedef pxu8 PxConsoleCmdStyle256;

typedef union PxConsoleCmdStyleRGB
{
    struct
    {
        pxu8 r, g, b;
    };

    pxu8 items[PX_CONSOLE_COLOR_RGB_UNITS];
}
PxConsoleCmdStyleRGB;

typedef pxu8 PxConsoleCmdCursorMove;

typedef struct PxConsoleCmdCursorPlace
{
    pxu8 x, y;
}
PxConsoleCmdCursorPlace;

typedef pxi32 PxConsoleCmdUnicode;

typedef PxString8  PxConsoleCmdString8;
typedef PxString16 PxConsoleCmdString16;
typedef PxString32 PxConsoleCmdString32;

typedef struct PxConsoleCmd
{
    PxConsoleCmdType type;

    union
    {
        PxConsoleCmdStyle8   style_8;
        PxConsoleCmdStyle256 style_256;
        PxConsoleCmdStyleRGB style_rgb;

        PxConsoleCmdCursorMove  cursor_move;
        PxConsoleCmdCursorPlace cursor_place;

        PxConsoleCmdUnicode unicode;

        PxConsoleCmdString8  string_8;
        PxConsoleCmdString16 string_16;
        PxConsoleCmdString32 string_32;
    };
}
PxConsoleCmd;

PxConsoleCmd
pxConsoleCmdStyle8Front(pxu8 value);

PxConsoleCmd
pxConsoleCmdStyle256Front(pxu8 value);

PxConsoleCmd
pxConsoleCmdStyleRGBFront(pxu8 r, pxu8 g, pxu8 b);

PxConsoleCmd
pxConsoleCmdStyle8Back(pxu8 value);

PxConsoleCmd
pxConsoleCmdStyle256Back(pxu8 value);

PxConsoleCmd
pxConsoleCmdStyleRGBBack(pxu8 r, pxu8 g, pxu8 b);

PxConsoleCmd
pxConsoleCmdStyleClear();

PxConsoleCmd
pxConsoleCmdCursorShow();

PxConsoleCmd
pxConsoleCmdCursorHide();

PxConsoleCmd
pxConsoleCmdCursorUp(pxu8 value);

PxConsoleCmd
pxConsoleCmdCursorDown(pxu8 value);

PxConsoleCmd
pxConsoleCmdCursorRight(pxu8 value);

PxConsoleCmd
pxConsoleCmdCursorLeft(pxu8 value);

PxConsoleCmd
pxConsoleCmdCursorPlace(pxu8 x, pxu8 y);

PxConsoleCmd
pxConsoleCmdUnicode(pxi32 value);

PxConsoleCmd
pxConsoleCmdString8(PxString8 value);

PxConsoleCmd
pxConsoleCmdString16(PxString16 value);

PxConsoleCmd
pxConsoleCmdString32(PxString32 value);

PxConsoleCmd
pxConsoleCmdReset();

void
pxConsoleWriteCommand(PxWriter* writer, PxConsoleCmd value);

#endif // PX_CORE_CONSOLE_COMMAND_H
