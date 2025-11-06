#include "../export.h"

#include <stdio.h>
#include <stdlib.h>

#include <time.h>

#define RED(x) "\x1b[91m" x "\x1b[0m"
#define GRN(x) "\x1b[92m" x "\x1b[0m"
#define YLW(x) "\x1b[93m" x "\x1b[0m"
#define BLU(x) "\x1b[94m" x "\x1b[0m"
#define MAG(x) "\x1b[95m" x "\x1b[0m"
#define CYA(x) "\x1b[96m" x "\x1b[0m"

#define TRUE  GRN("T")
#define FALSE RED("F")

typedef struct Context
{
    PxChannel channel;
}
Context;

pxuword
pollingProc(Context* context)
{
    if (pxChannelIsOpen(&context->channel) == 0)
        return 0;

    for (pxiword i = 0; i < 26; i += 1) {
        pxu8 byte = 'A' + i;

        pxChannelWrite(&context->channel, &byte, 1);

        pxCurrentThreadSleep(rand() % 500);
    }

    pxChannelClose(&context->channel);

    return 1;
}

int
main(int argc, char** argv)
{
    PxArena arena = pxMemoryReserve(16);

    srand(time(0));

    printf("Threads start...\n");

    Context context = {0};

    context.channel = pxChannelOpen(&arena, 1024);

    PxThread polling = pxThreadCreate(&arena, &context, &pollingProc);

    while (pxChannelIsOpen(&context.channel) != 0) {
        pxu8    byte = 0;
        pxiword size = pxChannelRead(&context.channel, &byte, 1);

        if (size != 0) printf("%c\n", byte);
    }

    pxThreadJoin(polling);

    printf("Threads stop...\n");
}
