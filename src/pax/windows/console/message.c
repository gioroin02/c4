#ifndef PX_WINDOWS_CONSOLE_MESSAGE_C
#define PX_WINDOWS_CONSOLE_MESSAGE_C

#include "message.h"

#define NOMINMAX
#define NOGDI
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

pxuword
pxWindowsMapConsoleKeybdModifs(pxuword value)
{
    pxuword result = 0;

    if ((value & LEFT_CTRL_PRESSED) != 0)
        result |= PX_CONSOLE_MODIF_CTRL;

    if ((value & RIGHT_CTRL_PRESSED) != 0)
        result |= PX_CONSOLE_MODIF_CTRL;

    if ((value & LEFT_ALT_PRESSED) != 0)
        result |= PX_CONSOLE_MODIF_ALT;

    if ((value & RIGHT_ALT_PRESSED) != 0)
        result |= PX_CONSOLE_MODIF_ALT;

    if ((value & SHIFT_PRESSED) != 0)
        result |= PX_CONSOLE_MODIF_SHIFT;

    return result;
}

pxiword
pxWindowsMapConsoleKeybdButton(pxiword button)
{
    switch (button) {
        case PX_ASCII_UPPER_A: return PX_CONSOLE_KEYBD_A;
        case PX_ASCII_UPPER_B: return PX_CONSOLE_KEYBD_B;
        case PX_ASCII_UPPER_C: return PX_CONSOLE_KEYBD_C;
        case PX_ASCII_UPPER_D: return PX_CONSOLE_KEYBD_D;
        case PX_ASCII_UPPER_E: return PX_CONSOLE_KEYBD_E;
        case PX_ASCII_UPPER_F: return PX_CONSOLE_KEYBD_F;
        case PX_ASCII_UPPER_G: return PX_CONSOLE_KEYBD_G;
        case PX_ASCII_UPPER_H: return PX_CONSOLE_KEYBD_H;
        case PX_ASCII_UPPER_I: return PX_CONSOLE_KEYBD_I;
        case PX_ASCII_UPPER_J: return PX_CONSOLE_KEYBD_J;
        case PX_ASCII_UPPER_K: return PX_CONSOLE_KEYBD_K;
        case PX_ASCII_UPPER_L: return PX_CONSOLE_KEYBD_L;
        case PX_ASCII_UPPER_M: return PX_CONSOLE_KEYBD_M;
        case PX_ASCII_UPPER_N: return PX_CONSOLE_KEYBD_N;
        case PX_ASCII_UPPER_O: return PX_CONSOLE_KEYBD_O;
        case PX_ASCII_UPPER_P: return PX_CONSOLE_KEYBD_P;
        case PX_ASCII_UPPER_Q: return PX_CONSOLE_KEYBD_Q;
        case PX_ASCII_UPPER_R: return PX_CONSOLE_KEYBD_R;
        case PX_ASCII_UPPER_S: return PX_CONSOLE_KEYBD_S;
        case PX_ASCII_UPPER_T: return PX_CONSOLE_KEYBD_T;
        case PX_ASCII_UPPER_U: return PX_CONSOLE_KEYBD_U;
        case PX_ASCII_UPPER_V: return PX_CONSOLE_KEYBD_V;
        case PX_ASCII_UPPER_W: return PX_CONSOLE_KEYBD_W;
        case PX_ASCII_UPPER_X: return PX_CONSOLE_KEYBD_X;
        case PX_ASCII_UPPER_Y: return PX_CONSOLE_KEYBD_Y;
        case PX_ASCII_UPPER_Z: return PX_CONSOLE_KEYBD_Z;

        case PX_ASCII_ZERO:  return PX_CONSOLE_KEYBD_ZERO;
        case PX_ASCII_ONE:   return PX_CONSOLE_KEYBD_ONE;
        case PX_ASCII_TWO:   return PX_CONSOLE_KEYBD_TWO;
        case PX_ASCII_THREE: return PX_CONSOLE_KEYBD_THREE;
        case PX_ASCII_FOUR:  return PX_CONSOLE_KEYBD_FOUR;
        case PX_ASCII_FIVE:  return PX_CONSOLE_KEYBD_FIVE;
        case PX_ASCII_SIX:   return PX_CONSOLE_KEYBD_SIX;
        case PX_ASCII_SEVEN: return PX_CONSOLE_KEYBD_SEVEN;
        case PX_ASCII_EIGHT: return PX_CONSOLE_KEYBD_EIGHT;
        case PX_ASCII_NINE:  return PX_CONSOLE_KEYBD_NINE;

        case VK_RETURN: return PX_CONSOLE_KEYBD_ENTER;
        case VK_ESCAPE: return PX_CONSOLE_KEYBD_ESCAPE;
        case VK_SPACE:  return PX_CONSOLE_KEYBD_SPACE;
        case VK_BACK:   return PX_CONSOLE_KEYBD_BACK_SPACE;
        case VK_TAB:    return PX_CONSOLE_KEYBD_HORIZONTAL_TAB;
        case VK_LEFT:   return PX_CONSOLE_KEYBD_ARROW_LEFT;
        case VK_RIGHT:  return PX_CONSOLE_KEYBD_ARROW_RIGHT;
        case VK_UP:     return PX_CONSOLE_KEYBD_ARROW_UP;
        case VK_DOWN:   return PX_CONSOLE_KEYBD_ARROW_DOWN;
        case VK_HOME:   return PX_CONSOLE_KEYBD_HOME;
        case VK_END:    return PX_CONSOLE_KEYBD_END;
        case VK_PRIOR:  return PX_CONSOLE_KEYBD_PAGE_UP;
        case VK_NEXT:   return PX_CONSOLE_KEYBD_PAGE_DOWN;

        case VK_F1:  return PX_CONSOLE_KEYBD_FUNC1;
        case VK_F2:  return PX_CONSOLE_KEYBD_FUNC2;
        case VK_F3:  return PX_CONSOLE_KEYBD_FUNC3;
        case VK_F4:  return PX_CONSOLE_KEYBD_FUNC4;
        case VK_F5:  return PX_CONSOLE_KEYBD_FUNC5;
        case VK_F6:  return PX_CONSOLE_KEYBD_FUNC6;
        case VK_F7:  return PX_CONSOLE_KEYBD_FUNC7;
        case VK_F8:  return PX_CONSOLE_KEYBD_FUNC8;
        case VK_F9:  return PX_CONSOLE_KEYBD_FUNC9;
        case VK_F10: return PX_CONSOLE_KEYBD_FUNC10;
        case VK_F11: return PX_CONSOLE_KEYBD_FUNC11;
        case VK_F12: return PX_CONSOLE_KEYBD_FUNC12;

        default: break;
    }

    return PX_CONSOLE_KEYBD_NONE;
}

PxConsoleMsg
pxWindowsConsoleReadMessage(PxReader* self)
{
    PxConsoleMsg result = {.type = PX_CONSOLE_MSG_NONE};

    INPUT_RECORD record = {0};

    HANDLE input = GetStdHandle(STD_INPUT_HANDLE);
    DWORD  size  = 0;

    if (ReadConsoleInput(input, &record, 1, &size) == 0)
        return result;

    switch (record.EventType) {
        case KEY_EVENT: {
            KEY_EVENT_RECORD event = record.Event.KeyEvent;

            switch (event.bKeyDown) {
                case 0: {
                    pxiword button  = pxWindowsMapConsoleKeybdButton(event.wVirtualKeyCode);
                    pxuword modifs  = pxWindowsMapConsoleKeybdModifs(event.dwControlKeyState);
                    pxi32   unicode = event.uChar.UnicodeChar;

                    result = pxConsoleMsgKeybdRelease(button, modifs, unicode);
                } break;

                default: {
                    pxiword button  = pxWindowsMapConsoleKeybdButton(event.wVirtualKeyCode);
                    pxuword modifs  = pxWindowsMapConsoleKeybdModifs(event.dwControlKeyState);
                    pxi32   unicode = event.uChar.UnicodeChar;

                    result = pxConsoleMsgKeybdPress(button, modifs, unicode);
                } break;
            }
        } break;

        default: break;
    }

    return result;
}

PxConsoleMsg
pxWindowsConsolePollMessage(PxReader* self)
{
    PxConsoleMsg result = {.type = PX_CONSOLE_MSG_NONE};

    HANDLE input = GetStdHandle(STD_INPUT_HANDLE);
    DWORD  size  = 0;

    GetNumberOfConsoleInputEvents(input, &size);

    if (size != 0)
        result = pxWindowsConsoleReadMessage(self);

    return result;
}

#endif // PX_WINDOWS_CONSOLE_MESSAGE_C
