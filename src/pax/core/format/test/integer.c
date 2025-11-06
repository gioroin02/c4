#include "../export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    PxArena   arena  = pxMemoryReserve(16);
    PxBuffer8 buffer = pxBuffer8Reserve(&arena, PX_MEMORY_KIB);

    pxiword wrote = pxBuffer8WriteIntegerTail(&buffer, -256,
        PX_FORMAT_RADIX_16, PX_FORMAT_FLAG_UPPER | PX_FORMAT_FLAG_PLUS);

    pxiword value = 0;

    pxiword read = pxMemory8ReadInteger(buffer.memory, buffer.size, &value,
        PX_FORMAT_RADIX_16, PX_FORMAT_FLAG_UPPER | PX_FORMAT_FLAG_PLUS);

    printf("'%.*s' [%lli], %lli, %lli, %s\n", px_as(int, wrote), buffer.memory, wrote,
        value, read, read == wrote ? "ok" : "ko");
}
