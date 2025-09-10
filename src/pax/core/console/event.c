#ifndef PX_CORE_CONSOLE_EVENT_C
#define PX_CORE_CONSOLE_EVENT_C

#include "event.h"

PxConsoleEvent
pxConsoleEventKeybdPress(pxiword button, pxuword modifs, pxi32 unicode)
{
    PxConsoleEventKeybdPress press = {
        .button  = button,
        .modifs  = modifs,
        .unicode = unicode,
    };
    return (PxConsoleEvent) {
        .type        = PX_CONSOLE_EVENT_KEYBD_PRESS,
        .keybd_press = press,
    };
}

PxConsoleEvent
pxConsoleEventKeybdRelease(pxiword button, pxuword modifs, pxi32 unicode)
{
    PxConsoleEventKeybdRelease release = {
        .button  = button,
        .modifs  = modifs,
        .unicode = unicode,
    };

    return (PxConsoleEvent) {
        .type          = PX_CONSOLE_EVENT_KEYBD_RELEASE,
        .keybd_release = release,
    };
}

#endif // PX_CORE_CONSOLE_EVENT_C
