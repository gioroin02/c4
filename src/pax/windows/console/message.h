#ifndef PX_WINDOWS_CONSOLE_MESSAGE_H
#define PX_WINDOWS_CONSOLE_MESSAGE_H

#include "import.h"

PxConsoleMsg
pxWindowsConsoleReadMessage(PxReader* self);

PxConsoleMsg
pxWindowsConsolePollMessage(PxReader* self);

#endif // PX_WINDOWS_CONSOLE_MESSAGE_H
