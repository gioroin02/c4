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

void
showConsoleEscSeqncFromString8(PxString8 string)
{
    PxConsoleEscSeqnc escape = {0};

    pxb8 state = pxConsoleEscSeqncFromString8(string, &escape);

    printf("\x1b[94m'");

    for (pxiword i = 0; i < string.length; i += 1) {
        pxu8 byte = string.memory[i];

        if (byte > 32 && byte < 128)
            printf("%c", string.memory[i]);
        else
            printf("\\x%02x", string.memory[i]);

        if (i + 1 < string.length)
            printf(" ");
    }

    printf("'\x1b[0m -> %s\n", state != 0 ? "\x1b[92mT\x1b[0m" : "\x1b[91mF\x1b[0m");

    if (state != 0) showConsoleEscSeqnc(escape);
}

int
main(int argc, char** argv)
{
    printf("VALID:\n\n");

    showConsoleEscSeqncFromString8(pxs8("\x1b[1;5D"));
    showConsoleEscSeqncFromString8(pxs8("\x1b[A"));
    showConsoleEscSeqncFromString8(pxs8("\x1b[38;2;1;2;3m"));
    showConsoleEscSeqncFromString8(pxs8("\x1b[9m"));
    showConsoleEscSeqncFromString8(pxs8("\x1b[97:5u"));
    showConsoleEscSeqncFromString8(pxs8("\x1b[12~"));
    showConsoleEscSeqncFromString8(pxs8("\x1b[15;10H"));
    showConsoleEscSeqncFromString8(pxs8("\x1b[97;;229u"));

    printf("\nINVALID:\n\n");

    showConsoleEscSeqncFromString8(pxs8("\x1b[\x1b\x31;6A"));
    showConsoleEscSeqncFromString8(pxs8("\x1bz"));
}
