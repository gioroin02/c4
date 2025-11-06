#include "../export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    PxArena   arena  = pxMemoryReserve(16);
    PxBuffer8 buffer = pxBuffer8Reserve(&arena, PX_MEMORY_KIB);

    pxiword wrote = pxBuffer8WriteUnsignedTail(&buffer, 256,
        PX_FORMAT_RADIX_16, PX_FORMAT_FLAG_UPPER | PX_FORMAT_FLAG_PLUS);

    pxuword value = 0;

    pxiword read = pxMemory8ReadUnsigned(buffer.memory, buffer.size, &value,
        PX_FORMAT_RADIX_16, PX_FORMAT_FLAG_UPPER | PX_FORMAT_FLAG_PLUS);

    printf("'%.*s' [%lli], %llu, %lli, %s\n", px_as(int, wrote), buffer.memory, wrote,
        value, read, read == wrote ? "ok" : "ko");
}
