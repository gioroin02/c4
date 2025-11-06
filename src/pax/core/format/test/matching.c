#include "../export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    PxArena arena = pxMemoryReserve(16);

    PxBuffer8 buffer = pxBuffer8Reserve(&arena, 256);
    PxSource  source = pxSourceFromBuffer8(&buffer);

    PxBuffer8 back = pxBuffer8Reserve(&arena, 256);

    source = pxBufferedSource(source, &back);

    pxBuffer8WriteString8Tail(&buffer, pxs8("35, 60"));

    PxFormatRadix radix = PX_FORMAT_RADIX_10;
    PxFormatFlag  flags = PX_FORMAT_FLAG_UPPER | PX_FORMAT_FLAG_PLUS;

    PxString8 string =
        pxSourceMatchUnsigned(source, &arena, 16, radix, flags);

    printf("%s\n", string.memory);
}
