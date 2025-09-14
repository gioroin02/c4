#include "../export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    PxArena arena = pxMemoryReserve(16);

    PxConsole console = pxConsoleCreate(&arena);
    PxReader  reader  = pxConsoleReader(console, &arena, PX_MEMORY_KIB);

    pxConsoleSetMode(console, PX_CONSOLE_MODE_MESSAGE);

    pxb8 active = 1;

    while (active != 0) {
        PxConsoleMsg message = pxConsoleReadMessage(&reader);

        switch (message.type) {
            case PX_CONSOLE_MSG_NONE: printf("none\r\n"); break;

            case PX_CONSOLE_MSG_KEYBD_PRESS: {
                printf("keybd_press   { btn = %lli, mod = %llu, uni = %li }\r\n",
                    message.keybd_press.button,
                    message.keybd_press.modifs,
                    message.keybd_press.unicode
                );

                if (message.keybd_press.button == PX_CONSOLE_KEYBD_ESCAPE)
                    active = 0;
            } break;

            case PX_CONSOLE_MSG_KEYBD_RELEASE: {
                printf("keybd_release { btn = %lli, mod = %llu, uni = %li }\r\n",
                    message.keybd_release.button,
                    message.keybd_release.modifs,
                    message.keybd_release.unicode
                );
            } break;

            default: break;
        }
    }

    pxConsoleSetMode(console, PX_CONSOLE_MODE_DEFAULT);
}
