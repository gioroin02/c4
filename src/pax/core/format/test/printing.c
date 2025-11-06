#include "../export.h"
#include "../../memory/export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    PxArena   arena  = pxMemoryReserve(32);
    PxBuffer8 buffer = pxBuffer8Reserve(&arena, 256);
    PxTarget  target = pxTargetFromBuffer8(&buffer);

    PxString8 string = {0};
    pxiword   size   = 0;

    pxTargetPrintList(target, (PxFormatMsg[]) {
        pxFormatMsgString8(pxs8("coords = {x = ")),
        pxFormatMsgInteger(PX_IWORD_MAX),
        pxFormatMsgString8(pxs8(", y = ")),
        pxFormatMsgInteger(PX_IWORD_MIN),
        pxFormatMsgString8(pxs8(", z = ${?}}")),
    }, 5, &size);

    string = pxBuffer8ReadString8Head(&buffer, &arena, buffer.size);

    printf("'\x1b[94m%s\x1b[0m' (%lli)\n", string.memory, size);

    pxTargetPrintFormat(target, pxs8("coords = {x = ${0}, y = ${1}, z = ${-1}}"),
        (PxFormatMsg[]) {
            pxFormatMsgInteger(PX_IWORD_MAX), pxFormatMsgInteger(PX_IWORD_MIN)
        },
    2, &size);

    string = pxBuffer8ReadString8Head(&buffer, &arena, buffer.size);

    printf("'\x1b[94m%s\x1b[0m' (%lli)\n", string.memory, size);

    pxTargetPrintFormat(target, pxs8("coords = {x = 0, y = 1, z = 2}"), 0, 0, &size);

    string = pxBuffer8ReadString8Head(&buffer, &arena, buffer.size);

    printf("'\x1b[94m%s\x1b[0m' (%lli)\n", string.memory, size);
}
