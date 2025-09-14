#ifndef PX_LINUX_CONSOLE_MESSAGE_H
#define PX_LINUX_CONSOLE_MESSAGE_H

#include "import.h"

PxConsoleMsg
pxLinuxConsoleReadMessage(PxReader* self);

PxConsoleMsg
pxLinuxConsolePollMessage(PxReader* self);

#endif // PX_LINUX_CONSOLE_MESSAGE_H
