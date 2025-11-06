#include "../export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    PxArena arena = pxMemoryReserve(16);

    PxConsole console = pxConsoleCreate(&arena);
    PxReader  reader  = pxReaderFromSource(pxSourceFromConsole(console), &arena, 1024);

    pxConsoleSetMode(console, PX_CONSOLE_MODE_MESSAGE);

    pxb8 active = 1;

    while (active != 0) {
        PxConsoleMsg message = pxConsoleWaitMsg(&reader, &arena);

        switch (message.type) {
            case PX_CONSOLE_MSG_NONE: printf("none\r\n"); break;

            case PX_CONSOLE_MSG_KEYBD_PRESS: {
                printf("keybd_press   { btn = %lli, mod = %llu, uni = %li }\r\n",
                    message.keybd_button.button,
                    message.keybd_button.modifs,
                    message.keybd_button.unicode
                );

                if (message.keybd_button.button == PX_CONSOLE_KEYBD_ESCAPE)
                    active = 0;
            } break;

            case PX_CONSOLE_MSG_KEYBD_RELEASE: {
                printf("keybd_release { btn = %lli, mod = %llu, uni = %li }\r\n",
                    message.keybd_button.button,
                    message.keybd_button.modifs,
                    message.keybd_button.unicode
                );
            } break;

            default: break;
        }
    }

    pxConsoleSetMode(console, PX_CONSOLE_MODE_DEFAULT);
}
