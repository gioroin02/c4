#include "../export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    PxArena   arena  = pxMemoryReserve(16);
    PxBuffer8 buffer = pxBuffer8Reserve(&arena, PX_MEMORY_KIB);

    pxiword wrote = pxBuffer8WriteBooleanTail(&buffer, 256,
        PX_FORMAT_FLAG_UPPER | PX_FORMAT_FLAG_PLUS);

    pxbword value = 0;

    pxiword read = pxMemory8ReadBoolean(buffer.memory, buffer.size, &value,
        PX_FORMAT_FLAG_UPPER | PX_FORMAT_FLAG_PLUS);

    printf("'%.*s' [%lli], %llu, %lli, %s\n", px_as(int, wrote), buffer.memory, wrote,
        value, read, read == wrote ? "ok" : "ko");
}
