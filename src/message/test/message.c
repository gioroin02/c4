#include "../export.h"

#include <stdio.h>

#define RED(expr)    "\x1b[31m" expr "\x1b[0m"
#define GREEN(expr)  "\x1b[32m" expr "\x1b[0m"
#define YELLOW(expr) "\x1b[33m" expr "\x1b[0m"
#define BLUE(expr)   "\x1b[34m" expr "\x1b[0m"
#define PURPLE(expr) "\x1b[35m" expr "\x1b[0m"
#define AZURE(expr)  "\x1b[36m" expr "\x1b[0m"

#define MESSAGE \
    pxs8("{ \"player_accept\": { \"player_number\": 4, \"player_code\": 156, \"board_width\": 5, " \
        "\"board_height\": 5, \"piece_color\": 2, \"piece_shape\": \"ciao\" } }")

int
main(int argc, char** argv)
{
    PxArena   arena  = pxMemoryReserve(16);
    PxBuffer8 source = pxBuffer8Reserve(&arena, PX_MEMORY_KIB);
    PxBuffer8 target = pxBuffer8Reserve(&arena, PX_MEMORY_KIB);
    PxBuffer8 buffer = pxBuffer8Reserve(&arena, PX_MEMORY_KIB);

    pxBuffer8WriteString8Tail(&source, MESSAGE);

    PxJsonReader reader = pxJsonReaderMake(&arena, 8,
        pxBufferReader(&source, &buffer));

    PxJsonWriter writer = pxJsonWriterMake(&arena, 8,
        pxBufferWriter(&target, &buffer));

    C4Message message = (C4Message) {0};

    c4JsonReadMessage(&message, &reader, &arena);
    c4ShowMessage(&message);

    pxBuffer8Clear(&buffer);

    c4JsonWriteMessage(&message, &writer, &arena);

    printf("\n");

    printf("%.*s\n", pxCast(int, buffer.size),
        buffer.memory);
}
