#include "../export.h"

#include <stdio.h>

void
showConsoleEscSeqnc(PxConsoleEscSeqnc value)
{
    printf("func  = %3c\n", value.func);
    printf("flags = %3u\n", value.flags);

    for (pxiword i = 0; i < value.size; i += 1) {
        PxConsoleEscGroup* group = &value.items[i];

        printf(" -> group(%lli) = ", i);

        for (pxiword j = 0; j < group->size; j += 1) {
            printf("%3llu", group->items[j]);

            if (j + 1 < group->size)
                printf(" ");
        }

        printf("\n");
    }
}

int
main(int argc, char** argv)
{
    PxConsoleMsg      message = pxConsoleMsgCursorHide();
    PxConsoleEscSeqnc escape  = pxConsoleEscSeqncFromConsoleMsg(message);

    showConsoleEscSeqnc(escape);
}
