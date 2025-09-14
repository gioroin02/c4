#include "../export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    PxArena arena = pxMemoryReserve(16);

    PxBuilder builder = pxBuilderReserve(&arena, PX_MEMORY_KIB);

    C4Color color = c4ColorRGB(0xf0, 0xe0, 0xd0);

    pxBuilderBuild(&builder, "${0}\n",
        pxFormatCmdDelegate(&color, &c4FormatProcColor));

    printf("%.*s", pxCast(int, builder.size),
        builder.memory);
}
