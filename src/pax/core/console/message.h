#ifndef PX_CORE_CONSOLE_MESSAGE_H
#define PX_CORE_CONSOLE_MESSAGE_H

#include "import.h"

typedef enum PxConsoleMsgType
{
    PX_CONSOLE_MSG_NONE,

    PX_CONSOLE_MSG_KEYBD_PRESS,
    PX_CONSOLE_MSG_KEYBD_RELEASE,

    PX_CONSOLE_MSG_MOUSE_PRESS,
    PX_CONSOLE_MSG_MOUSE_RELEASE,
    PX_CONSOLE_MSG_MOUSE_MOVE,
    PX_CONSOLE_MSG_MOUSE_SCROLL,
}
PxConsoleMsgType;

typedef enum PxConsoleKeybdModif
{
    PX_CONSOLE_MODIF_NONE  = 0x0,
    PX_CONSOLE_MODIF_CTRL  = 0x1,
    PX_CONSOLE_MODIF_ALT   = 0x2,
    PX_CONSOLE_MODIF_SHIFT = 0x4,
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

typedef struct PxConsoleMsgKeybdPress
{
    pxiword button;
    pxuword modifs;
    pxi32   unicode;
}
PxConsoleMsgKeybdPress;

typedef struct PxConsoleMsgKeybdRelease
{
    pxiword button;
    pxuword modifs;
    pxi32   unicode;
}
PxConsoleMsgKeybdRelease;

typedef struct PxConsoleMsgMousePress
{
    pxiword button;
    pxuword modifs;
}
PxConsoleMsgMousePress;

typedef struct PxConsoleMsgMouseRelease
{
    pxiword button;
    pxuword modifs;
}
PxConsoleMsgMouseRelease;

typedef struct PxConsoleMsgMouseMove
{
    pxiword x;
    pxiword y;
}
PxConsoleMsgMouseMove;

typedef struct PxConsoleMsgMouseScroll
{
    pxiword x;
    pxiword y;
}
PxConsoleMsgMouseScroll;

typedef struct PxConsoleMsg
{
    PxConsoleMsgType type;

    union
    {
        PxConsoleMsgKeybdPress   keybd_press;
        PxConsoleMsgKeybdRelease keybd_release;

        PxConsoleMsgMousePress   mouse_press;
        PxConsoleMsgMouseRelease mouse_release;
        PxConsoleMsgMouseMove    mouse_move;
        PxConsoleMsgMouseScroll  mouse_scroll;
    };
}
PxConsoleMsg;

PxConsoleMsg
pxConsoleMsgKeybdPress(pxiword button, pxuword modifs, pxi32 unicode);

PxConsoleMsg
pxConsoleMsgKeybdRelease(pxiword button, pxuword modifs, pxi32 unicode);

PxConsoleMsg
pxConsoleReadMessage(PxReader* reader);

PxConsoleMsg
pxConsolePollMessage(PxReader* reader);

#endif // PX_CORE_CONSOLE_MESSAGE_H
