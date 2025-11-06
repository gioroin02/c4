#include "../export.h"

#include <stdio.h>

void
readBytePerByte(PxSource source)
{
    pxu8 byte = pxSourceReadByte(source);

    printf("read = [\n");

    while (byte != 0) {
        printf("%3u", byte);

        if (byte > 0x20 && byte < 0x80)
            printf(" (%c)", byte);

        printf("\n");

        byte = pxSourceReadByte(source);
    }

    printf("]\n");
}

void
peekBytePerByte(PxSource source)
{
    pxu8 byte = pxSourcePeekByte(source);

    printf("peek = [\n");

    while (byte != 0) {
        printf("%3u", byte);

        if (byte > 0x20 && byte < 0x80)
            printf(" (%c)", byte);

        printf("\n");

        pxSourceDrop(source, 1);

        byte = pxSourcePeekByte(source);
    }

    printf("]\n");
}

void
readString8(PxSource source, PxArena* arena, pxiword length)
{
    PxString8 string = pxSourceReadString8(source, arena, length);

    printf("string8 = [\n");

    for (pxiword i = 0; i < string.length; i += 1) {
        printf("%3u", string.memory[i]);

        if (string.memory[i] > 0x20 && string.memory[i] < 0x80)
            printf(" (%c)", string.memory[i]);

        printf("\n");
    }

    printf("]\n");
}

int
main(int argc, char** argv)
{
    pxu8 memory[PX_MEMORY_KIB] = {0};

    PxArena arena = pxArenaMake(memory, px_size(memory));

    PxBuffer8 items = pxBuffer8Reserve(&arena, 16);

    PxBuffer8 buffer = pxBuffer8Reserve(&arena, 256);
    PxSource  source = pxBufferedSource(pxSourceFromBuffer8(&items), &buffer);

    pxBuffer8WriteString8Tail(&items, pxs8("ciao\narrivederci"));

    readBytePerByte(source);

    pxBuffer8WriteString8Tail(&items, pxs8("ciao\narrivederci"));

    peekBytePerByte(source);

    pxBuffer8WriteString8Tail(&items, pxs8("ciao\narrivederci"));

    readString8(source, &arena, 8);
}
