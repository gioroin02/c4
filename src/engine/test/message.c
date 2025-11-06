#include "../export.h"

#include <stdio.h>

#define RED(x) "\x1b[91m" x "\x1b[0m"
#define GRN(x) "\x1b[92m" x "\x1b[0m"
#define YLW(x) "\x1b[93m" x "\x1b[0m"
#define BLU(x) "\x1b[94m" x "\x1b[0m"
#define MAG(x) "\x1b[95m" x "\x1b[0m"
#define CYA(x) "\x1b[96m" x "\x1b[0m"

#define MESSAGE \
    pxs8("{ \"player_accept\": { \"player_number\": 4, \"player_code\": 156, \"board_width\": 5, " \
        "\"board_height\": 5, \"player_color\": {\"color_rgb\": {\"r\": 126, \"g\": 2, \"b\":0}}, \"player_text\": \"ciao\" } }")

int
main(int argc, char** argv)
{
    PxArena   arena  = pxMemoryReserve(16);
    PxBuffer8 buffer = pxBuffer8Reserve(&arena, PX_MEMORY_KIB);

    PxBuffer8 temp = pxBuffer8Reserve(&arena, 256);

    PxSource source = pxBufferedSource(pxSourceFromBuffer8(&buffer), &temp);

    PxConsole console = pxConsoleCreate(&arena);
    PxTarget  target  = pxTargetFromConsole(console);

    pxBuffer8WriteString8Tail(&buffer, MESSAGE);

    PxJsonReader reader = pxJsonReaderReserve(source, &arena, 8);
    PxJsonWriter writer = pxJsonWriterReserve(target, &arena, 8);

    C4GameMsg message = (C4GameMsg) {0};

    c4JsonReadGameMsg(&message, &reader, &arena);
    c4JsonWriteGameMsg(&message, &writer, &arena);
}
