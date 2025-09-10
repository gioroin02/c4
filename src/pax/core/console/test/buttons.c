#include "../export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    PxArena arena = pxMemoryReserve(16);

    PxConsole console = pxConsoleCreate(&arena, PX_MEMORY_KIB);

    pxConsoleSetMode(console, PX_CONSOLE_MODE_EVENT);

    pxb8 active = 1;

    while (active != 0) {
        PxConsoleEvent event = pxConsoleReadEvent(console);

        switch (event.type) {
            case PX_CONSOLE_EVENT_NONE: printf("none\r\n"); break;

            case PX_CONSOLE_EVENT_KEYBD_PRESS: {
                printf("keybd_press   { btn = %lli, mod = %llu, uni = %li }\r\n",
                    event.keybd_press.button,
                    event.keybd_press.modifs,
                    event.keybd_press.unicode
                );

                if (event.keybd_press.button == PX_CONSOLE_KEYBD_ESCAPE)
                    active = 0;
            } break;

            case PX_CONSOLE_EVENT_KEYBD_RELEASE: {
                printf("keybd_release { btn = %lli, mod = %llu, uni = %li }\r\n",
                    event.keybd_release.button,
                    event.keybd_release.modifs,
                    event.keybd_release.unicode
                );
            } break;

            default: break;
        }
    }

    pxConsoleSetMode(console, PX_CONSOLE_MODE_DEFAULT);
}
