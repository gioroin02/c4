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
        "\"board_height\": 5, \"player_color\": {\"color_rgb\": {\"r\": 126, \"g\": 2, \"b\":0}}, \"player_text\": \"ciao\" } }")

int
main(int argc, char** argv)
{
    PxArena   arena  = pxMemoryReserve(16);
    PxBuffer8 source = pxBuffer8Reserve(&arena, PX_MEMORY_KIB);
    PxBuffer8 target = pxBuffer8Reserve(&arena, PX_MEMORY_KIB);

    PxReader buff_reader = pxBufferReader(&source, &arena, PX_MEMORY_KIB);
    PxWriter buff_writer = pxBufferWriter(&target, &arena, PX_MEMORY_KIB);

    PxConsole console = pxConsoleCreate(&arena);
    PxWriter  writer  = pxConsoleWriter(console, &arena, PX_MEMORY_KIB);

    PxLogger logger = pxLoggerReserve(&arena, PX_MEMORY_KIB, &writer);

    pxLoggerSetFlags(&logger, PX_REPORT_FLAG_COLOR | PX_REPORT_FLAG_LEVEL);
    pxLoggerSetLevel(&logger, PX_REPORT_LEVEL_TRACE);

    pxBuffer8WriteString8Tail(&source, MESSAGE);

    PxJsonReader json_reader = pxJsonReaderMake(&arena, 8, &buff_reader);
    PxJsonWriter json_writer = pxJsonWriterMake(&arena, 8, &buff_writer);

    C4Msg message = (C4Msg) {0};

    c4JsonReadMsg(&message, &json_reader, &arena);

    pxLoggerTrace(&logger, "${0}",
        pxFormatCmdDelegate(&message, &c4FormatProcMsg));

    c4JsonWriteMsg(&message, &json_writer, &arena);

    printf("\n");

    pxLoggerWrite(&logger, "${0}\n",
        pxFormatCmdString8(pxString8Make(target.memory, target.size)));
}
