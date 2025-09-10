#include "../export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    PxArena arena = pxMemoryReserve(16);

    PxFile file = 0;

    if (argc >= 2) {
        PxString8 base = pxs8(".");
        PxString8 name = pxString8FromMemory(argv[1], 128);

        file = pxFileOpen(&arena,
            base, name, PX_FILE_MODE_READ);
    } else
        file = pxStandardInput(&arena);

    if (file != 0) printf("%p\n", file);

    PxBuffer8 buffer = pxBuffer8Reserve(&arena, 256);

    while (1) {
        if (pxFileRead(file, &buffer) == 0)
            break;

        printf("%.*s", pxCast(int, buffer.size),
            buffer.memory);

        pxBuffer8Clear(&buffer);
    }

    pxFileClose(file);
}
