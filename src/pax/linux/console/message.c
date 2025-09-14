#ifndef PX_LINUX_CONSOLE_MESSAGE_C
#define PX_LINUX_CONSOLE_MESSAGE_C

#include "message.h"

PxConsoleMsg
pxLinuxConsoleReadMessage(PxReader* self)
{
    return (PxConsoleMsg) {.type = PX_CONSOLE_MSG_NONE};
}

PxConsoleMsg
pxLinuxConsolePollMessage(PxReader* self)
{
    return (PxConsoleMsg) {.type = PX_CONSOLE_MSG_NONE};
}

#endif // PX_LINUX_CONSOLE_MESSAGE_C
