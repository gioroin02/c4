#ifndef PX_CORE_CONSOLE_MESSAGE_H
#define PX_CORE_CONSOLE_MESSAGE_H

#include "escape.h"
#include "color.h"

#define PX_CONSOLE_STYLE_RGB_UNITS px_as(pxiword, 3)

typedef enum PxConsoleMsgType
{
    PX_CONSOLE_MSG_NONE,

    PX_CONSOLE_MSG_KEYBD_PRESS,
    PX_CONSOLE_MSG_KEYBD_RELEASE,

    PX_CONSOLE_MSG_MOUSE_PRESS,
    PX_CONSOLE_MSG_MOUSE_RELEASE,
    PX_CONSOLE_MSG_MOUSE_MOVE,
    PX_CONSOLE_MSG_MOUSE_SCROLL,

    PX_CONSOLE_MSG_STYLE_TEXT_16,
    PX_CONSOLE_MSG_STYLE_TEXT_256,
    PX_CONSOLE_MSG_STYLE_TEXT_RGB,
    PX_CONSOLE_MSG_STYLE_BACK_16,
    PX_CONSOLE_MSG_STYLE_BACK_256,
    PX_CONSOLE_MSG_STYLE_BACK_RGB,
    PX_CONSOLE_MSG_STYLE_CLEAR,

    PX_CONSOLE_MSG_STRING_8,
    PX_CONSOLE_MSG_STRING_16,
    PX_CONSOLE_MSG_STRING_32,

    PX_CONSOLE_MSG_UNICODE,

    PX_CONSOLE_MSG_CURSOR_SHOW,
    PX_CONSOLE_MSG_CURSOR_HIDE,
    PX_CONSOLE_MSG_CURSOR_MOVE,
    PX_CONSOLE_MSG_CURSOR_MOVE_UP,
    PX_CONSOLE_MSG_CURSOR_MOVE_DOWN,
    PX_CONSOLE_MSG_CURSOR_MOVE_LEFT,
    PX_CONSOLE_MSG_CURSOR_MOVE_RIGHT,

    PX_CONSOLE_MSG_RESET,
}
PxConsoleMsgType;

typedef enum PxConsoleKeybdModif
{
    PX_CONSOLE_MODIF_NONE  = 0,
    PX_CONSOLE_MODIF_CTRL  = 1 << 0,
    PX_CONSOLE_MODIF_ALT   = 1 << 1,
    PX_CONSOLE_MODIF_SHIFT = 1 << 2,
}
PxConsoleKeybdModif;

typedef enum PxConsoleKeybdButton
{
    PX_CONSOLE_KEYBD_NONE = 0,

    PX_CONSOLE_KEYBD_A,
    PX_CONSOLE_KEYBD_B,
    PX_CONSOLE_KEYBD_C,
    PX_CONSOLE_KEYBD_D,
    PX_CONSOLE_KEYBD_E,
    PX_CONSOLE_KEYBD_F,
    PX_CONSOLE_KEYBD_G,
    PX_CONSOLE_KEYBD_H,
    PX_CONSOLE_KEYBD_I,
    PX_CONSOLE_KEYBD_J,
    PX_CONSOLE_KEYBD_K,
    PX_CONSOLE_KEYBD_L,
    PX_CONSOLE_KEYBD_M,
    PX_CONSOLE_KEYBD_N,
    PX_CONSOLE_KEYBD_O,
    PX_CONSOLE_KEYBD_P,
    PX_CONSOLE_KEYBD_Q,
    PX_CONSOLE_KEYBD_R,
    PX_CONSOLE_KEYBD_S,
    PX_CONSOLE_KEYBD_T,
    PX_CONSOLE_KEYBD_U,
    PX_CONSOLE_KEYBD_V,
    PX_CONSOLE_KEYBD_W,
    PX_CONSOLE_KEYBD_X,
    PX_CONSOLE_KEYBD_Y,
    PX_CONSOLE_KEYBD_Z,

    PX_CONSOLE_KEYBD_ZERO,
    PX_CONSOLE_KEYBD_ONE,
    PX_CONSOLE_KEYBD_TWO,
    PX_CONSOLE_KEYBD_THREE,
    PX_CONSOLE_KEYBD_FOUR,
    PX_CONSOLE_KEYBD_FIVE,
    PX_CONSOLE_KEYBD_SIX,
    PX_CONSOLE_KEYBD_SEVEN,
    PX_CONSOLE_KEYBD_EIGHT,
    PX_CONSOLE_KEYBD_NINE,

    PX_CONSOLE_KEYBD_ENTER,
    PX_CONSOLE_KEYBD_ESCAPE,
    PX_CONSOLE_KEYBD_SPACE,
    PX_CONSOLE_KEYBD_BACK_SPACE,
    PX_CONSOLE_KEYBD_HORIZONTAL_TAB,
    PX_CONSOLE_KEYBD_ARROW_LEFT,
    PX_CONSOLE_KEYBD_ARROW_RIGHT,
    PX_CONSOLE_KEYBD_ARROW_UP,
    PX_CONSOLE_KEYBD_ARROW_DOWN,
    PX_CONSOLE_KEYBD_HOME,
    PX_CONSOLE_KEYBD_END,
    PX_CONSOLE_KEYBD_PAGE_UP,
    PX_CONSOLE_KEYBD_PAGE_DOWN,

    PX_CONSOLE_KEYBD_FUNC1,
    PX_CONSOLE_KEYBD_FUNC2,
    PX_CONSOLE_KEYBD_FUNC3,
    PX_CONSOLE_KEYBD_FUNC4,
    PX_CONSOLE_KEYBD_FUNC5,
    PX_CONSOLE_KEYBD_FUNC6,
    PX_CONSOLE_KEYBD_FUNC7,
    PX_CONSOLE_KEYBD_FUNC8,
    PX_CONSOLE_KEYBD_FUNC9,
    PX_CONSOLE_KEYBD_FUNC10,
    PX_CONSOLE_KEYBD_FUNC11,
    PX_CONSOLE_KEYBD_FUNC12,
}
PxConsoleKeybdButton;

typedef enum PxConsoleMouseBtn
{
    PX_CONSOLE_MOUSE_NONE,
    PX_CONSOLE_MOUSE_LEFT,
    PX_CONSOLE_MOUSE_RIGHT,
    PX_CONSOLE_MOUSE_MIDDLE,
}
PxConsoleMouseBtn;

typedef struct PxConsoleMsgKeybdButton
{
    pxiword button;
    pxuword modifs;
    pxi32   unicode;
}
PxConsoleMsgKeybdButton;

typedef struct PxConsoleMsgMouseButton
{
    pxiword button;
    pxuword modifs;
}
PxConsoleMsgMouseButton;

typedef struct PxConsoleMsgMouseMove
{
    pxiword x, y;
}
PxConsoleMsgMouseMove;

typedef struct PxConsoleMsgMouseScroll
{
    pxiword x, y;
}
PxConsoleMsgMouseScroll;

typedef struct PxConsoleMsgStyle16
{
    pxu8 index;
}
PxConsoleMsgStyle16;

typedef struct PxConsoleMsgStyle256
{
    pxu8 index;
}
PxConsoleMsgStyle256;

typedef union PxConsoleMsgStyleRGB
{
    struct
    {
        pxu8 r, g, b;
    };

    pxu8 items[PX_CONSOLE_STYLE_RGB_UNITS];
}
PxConsoleMsgStyleRGB;

typedef struct PxConsoleMsgCursorMove
{
    pxiword x, y;
}
PxConsoleMsgCursorMove;

typedef struct PxConsoleMsg
{
    PxConsoleMsgType type;

    union
    {
        PxConsoleMsgKeybdButton keybd_button;

        PxConsoleMsgMouseButton  mouse_button;
        PxConsoleMsgMouseMove    mouse_move;
        PxConsoleMsgMouseScroll  mouse_scroll;

        PxConsoleMsgStyle16  style_16;
        PxConsoleMsgStyle256 style_256;
        PxConsoleMsgStyleRGB style_rgb;

        PxString8  string_8;
        PxString16 string_16;
        PxString32 string_32;

        pxi32 unicode;

        PxConsoleMsgCursorMove cursor_move;
    };
}
PxConsoleMsg;

typedef struct PxConsoleQueue
{
    PxBuffer8 buffer;
}
PxConsoleQueue;

PxConsoleMsg
pxConsoleMsgKeybdPress(pxiword button, pxuword modifs, pxi32 unicode);

PxConsoleMsg
pxConsoleMsgKeybdRelease(pxiword button, pxuword modifs, pxi32 unicode);

PxConsoleMsg
pxConsoleMsgStyleText16(pxu8 index);

PxConsoleMsg
pxConsoleMsgStyleText256(pxu8 index);

PxConsoleMsg
pxConsoleMsgStyleTextRGB(pxu8 r, pxu8 g, pxu8 b);

PxConsoleMsg
pxConsoleMsgStyleText(PxConsoleColor value);

PxConsoleMsg
pxConsoleMsgStyleBack16(pxu8 index);

PxConsoleMsg
pxConsoleMsgStyleBack256(pxu8 index);

PxConsoleMsg
pxConsoleMsgStyleBackRGB(pxu8 r, pxu8 g, pxu8 b);

PxConsoleMsg
pxConsoleMsgStyleBack(PxConsoleColor value);

PxConsoleMsg
pxConsoleMsgStyleClear();

PxConsoleMsg
pxConsoleMsgString8(PxString8 value);

PxConsoleMsg
pxConsoleMsgString16(PxString16 value);

PxConsoleMsg
pxConsoleMsgString32(PxString32 value);

PxConsoleMsg
pxConsoleMsgUnicode(pxi32 unicode);

PxConsoleMsg
pxConsoleMsgCursorShow();

PxConsoleMsg
pxConsoleMsgCursorHide();

PxConsoleMsg
pxConsoleMsgCursorMove(pxiword x, pxiword y);

PxConsoleMsg
pxConsoleMsgCursorMoveUp(pxiword y);

PxConsoleMsg
pxConsoleMsgCursorMoveDown(pxiword y);

PxConsoleMsg
pxConsoleMsgCursorMoveLeft(pxiword x);

PxConsoleMsg
pxConsoleMsgCursorMoveRight(pxiword x);

PxConsoleMsg
pxConsoleMsgReset();

PxConsoleEscSeqnc
pxConsoleEscSeqncFromConsoleMsg(PxConsoleMsg value);

PxConsoleMsg
pxConsoleMsgFromConsoleEscSeqnc(PxConsoleEscSeqnc value);

/* Message Queue */

PxConsoleQueue
pxConsoleQueueReserve(PxArena* arena, pxiword length);

pxb8
pxConsoleQueueWriteMsg(PxConsoleQueue* self,  PxConsoleMsg value);

pxb8
pxConsoleQueueWriteList(PxConsoleQueue* self, PxConsoleMsg* values, pxiword length);

pxb8
pxConsoleQueueReadMsg(PxConsoleQueue* self, PxArena* arena, PxConsoleMsg* value);

PxBuffer8*
pxConsoleQueueBuffer8(PxConsoleQueue* self);

#endif // PX_CORE_CONSOLE_MESSAGE_H
