#include "../export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    PxArena arena = pxMemoryReserve(16);

    PxFile file = pxStandardInput(&arena);

    if (argc >= 2) {
        PxString8 base = pxs8(".");
        PxString8 name = pxString8FromMemory(argv[1], 128);

        file = pxFileOpen(&arena, base, name, PX_FILE_MODE_RD);
    }

    if (file != 0) printf("%p\n", file);

    PxBuffer8 buffer = pxBuffer8Reserve(&arena, 256);
    PxSource  source = pxSourceFromFile(file);

    while (1) {
        if (pxSourceReadBuffer8(source, &buffer) == 0)
            break;

        printf("%.*s", px_as(int, buffer.size),
            buffer.memory);

        pxBuffer8Clear(&buffer);
    }

    pxFileClose(file);
}
