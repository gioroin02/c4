#include "../export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    PxArena arena = pxMemoryReserve(16);

    PxConsoleQueue queue =
        pxConsoleQueueReserve(&arena, PX_MEMORY_KIB);

    pxConsoleQueueWriteList(&queue, (PxConsoleMsg[]) {
        pxConsoleMsgReset(),
        pxConsoleMsgCursorHide(),
        pxConsoleMsgString8(pxs8("test")),
        pxConsoleMsgStyleText256(55),
    }, 4);

    for (pxiword i = 0; i < queue.buffer.size; i += 1) {
        pxu8 byte = pxBuffer8GetForwOr(&queue.buffer, i, 0);

        if (byte > 0x20 && byte < 0x80)
            printf("%c", byte);
        else
            printf("\\x%02x", byte);
    }

    printf("\n");

    PxConsoleMsg value = {0};

    pxConsoleQueueReadMsg(&queue, &arena, &value);

    for (pxiword i = 0; i < queue.buffer.size; i += 1) {
        pxu8 byte = pxBuffer8GetForwOr(&queue.buffer, i, 0);

        if (byte > 0x20 && byte < 0x80)
            printf("%c", byte);
        else
            printf("\\x%02x", byte);
    }

    printf("\n");
}
