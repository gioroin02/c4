#include "../export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    PxArena arena = pxMemoryReserve(16);

    PxString8 base = pxs8(".");
    PxString8 name = pxs8("456undfglkjn34.txt");

    PxFile file = pxFileCreate(&arena, base, name, PX_FILE_MODE_RD);

    if (file != 0) printf("%p\n", file);

    getchar();

    pxFileClose(file);
    pxFileDestroy(&arena, base, name);
}
