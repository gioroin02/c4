#ifndef PX_CORE_CONSOLE_MESSAGE_C
#define PX_CORE_CONSOLE_MESSAGE_C

#include "message.h"

#if PX_SYSTEM == PX_SYSTEM_WINDOWS

    #include "../../windows/console/message.c"

    #define __pxConsoleReadMessage__ pxWindowsConsoleReadMessage
    #define __pxConsolePollMessage__ pxWindowsConsolePollMessage

#elif PX_SYSTEM == PX_SYSTEM_LINUX

    #include "../../linux/console/message.c"

    #define __pxConsoleReadMessage__ pxLinuxConsoleReadMessage
    #define __pxConsolePollMessage__ pxLinuxConsolePollMessage

#else

    #error "Unknown platform"

#endif

PxConsoleMsg
pxConsoleMsgKeybdPress(pxiword button, pxuword modifs, pxi32 unicode)
{
    return (PxConsoleMsg) {
        .type = PX_CONSOLE_MSG_KEYBD_PRESS,

        .keybd_press = {
            .button  = button,
            .modifs  = modifs,
            .unicode = unicode,
        },
    };
}

PxConsoleMsg
pxConsoleMsgKeybdRelease(pxiword button, pxuword modifs, pxi32 unicode)
{
    return (PxConsoleMsg) {
        .type = PX_CONSOLE_MSG_KEYBD_RELEASE,

        .keybd_release = {
            .button  = button,
            .modifs  = modifs,
            .unicode = unicode,
        },
    };
}

PxConsoleMsg
pxConsoleReadMessage(PxReader* self)
{
    return __pxConsoleReadMessage__(self);
}

PxConsoleMsg
pxConsolePollMessage(PxReader* self)
{
    return __pxConsolePollMessage__(self);
}

#endif // PX_CORE_CONSOLE_MESSAGE_C
