#include "../export.h"

#include "../../console/export.h"

int
main(int argc, char** argv)
{
    PxArena arena = pxMemoryReserve(16);

    PxConsole console = pxConsoleCreate(&arena);
    PxWriter  writer  = pxConsoleWriter(console, &arena, 1024);

    PxLogger logger = pxLoggerReserve(&arena, 1024, &writer);

    pxLoggerSetFlags(&logger, PX_REPORT_FLAG_LEVEL | PX_REPORT_FLAG_COLOR);
    pxLoggerSetLevel(&logger, PX_REPORT_LEVEL_WARN);

    pxLoggerWrite(&logger, "Level is \"warn\"\n\n", (PxFormatCmd) {0});

    pxLoggerError(&logger, "IMPORTANT\n", (PxFormatCmd) {0});

    pxLoggerInfo(&logger, "With args [${0}, ${1}, ${2}, ${3}, ${4}, ${5}]\n",
        pxFormatCmdInteger(10, PX_FORMAT_OPTION_NONE, 1),
        pxFormatCmdInteger(10, PX_FORMAT_OPTION_NONE, 2),
        pxFormatCmdInteger(10, PX_FORMAT_OPTION_NONE, 3),
        pxFormatCmdInteger(10, PX_FORMAT_OPTION_NONE, 4),
        pxFormatCmdInteger(10, PX_FORMAT_OPTION_NONE, 5),
        pxFormatCmdInteger(10, PX_FORMAT_OPTION_NONE, 6),
    );

    pxLoggerWarn(&logger, "No args\n", (PxFormatCmd) {0});
    pxLoggerTrace(&logger, "No args\n", (PxFormatCmd) {0});

    pxLoggerSetLevel(&logger, PX_REPORT_LEVEL_TRACE);

    pxLoggerWrite(&logger, "\nlevel is \"trace\"\n\n", (PxFormatCmd) {0});

    pxLoggerError(&logger, "IMPORTANT\n", (PxFormatCmd) {0});

    pxLoggerInfo(&logger, "With args [${0}, ${1}, ${2}, ${3}, ${4}, ${5}]\n",
        pxFormatCmdInteger(10, PX_FORMAT_OPTION_NONE, 1),
        pxFormatCmdInteger(10, PX_FORMAT_OPTION_NONE, 2),
        pxFormatCmdInteger(10, PX_FORMAT_OPTION_NONE, 3),
        pxFormatCmdInteger(10, PX_FORMAT_OPTION_NONE, 4),
        pxFormatCmdInteger(10, PX_FORMAT_OPTION_NONE, 5),
        pxFormatCmdInteger(10, PX_FORMAT_OPTION_NONE, 6),
    );

    pxLoggerWarn(&logger, "No args\n", (PxFormatCmd) {0});
    pxLoggerTrace(&logger, "No args\n", (PxFormatCmd) {0});
}
