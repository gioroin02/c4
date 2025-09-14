#include "../export.h"
#include "../../memory/export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    PxArena   arena   = pxMemoryReserve(32);
    PxBuilder builder = pxBuilderReserve(&arena, PX_MEMORY_KIB);

    PxString8 string = {0};

    pxBuilderChain(&builder, 0, 5, (PxFormatCmd[]) {
        pxFormatCmdString8(pxs8("coords = {x = ")),
        pxFormatCmdInteger(10, PX_FORMAT_OPTION_LEADING_PLUS, PX_IWORD_MAX),
        pxFormatCmdString8(pxs8(", y = ")),
        pxFormatCmdInteger(10, PX_FORMAT_OPTION_NONE, PX_IWORD_MIN),
        pxFormatCmdString8(pxs8(", z = ${?}}")),
    });

    string = pxString8FromBuilder(&arena, &builder);

    printf("'\x1b[34m%s\x1b[0m'\n", string.memory);

    pxBuilderClear(&builder);

    pxBuilderBuild(&builder, "coords = {x = ${0}, y = ${1}, z = ${2}}",
        pxFormatCmdInteger(10, PX_FORMAT_OPTION_LEADING_PLUS, PX_IWORD_MAX),
        pxFormatCmdInteger(10, PX_FORMAT_OPTION_NONE,         PX_IWORD_MIN));

    string = pxString8FromBuilder(&arena, &builder);

    printf("'\x1b[34m%s\x1b[0m'\n", string.memory);

    pxBuilderClear(&builder);

    pxBuilderBuild(&builder, "coords = {x = 0, y = 1, z = 2}", {0});

    string = pxString8FromBuilder(&arena, &builder);

    printf("'\x1b[34m%s\x1b[0m'\n", string.memory);

}
