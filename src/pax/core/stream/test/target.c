#include "../export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    PxArena arena = pxMemoryReserve(16);

    PxBuffer8 buffer = pxBuffer8Reserve(&arena, 256);
    PxTarget  target = pxTargetFromBuffer8(&buffer);

    PxBuffer8 items = pxBuffer8Reserve(&arena, 256);

    pxTargetWriteByte(target, PX_ASCII_LOWER_A);

    printf("direct write = %s\n", buffer.memory);

    target = pxBufferedTarget(target, &items);

    pxTargetWriteByte(target, PX_ASCII_LOWER_A);

    printf("buffer write = %s\n", buffer.memory);

    getchar();

    pxTargetFlush(target);

    printf("buffer flush = %s\n", buffer.memory);
}
