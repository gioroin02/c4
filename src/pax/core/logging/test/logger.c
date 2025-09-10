#include "../export.h"

#include "../../console/export.h"

int
main(int argc, char** argv)
{
    PxArena arena = pxMemoryReserve(16);

    PxConsole console = pxConsoleCreate(&arena, 1024);
    PxWriter  writer  = pxConsoleWriter(console, &arena, 1024);

    PxLogger logger = pxLoggerMake(&arena, writer,
        PX_REPORT_LEVEL_WARN, PX_REPORT_FLAG_COLORS);

    pxLoggerInteger64(&logger, 0, 356);
    pxLoggerString16(&logger, 1, pxs16(L"ciao"));

    pxLoggerReport(&logger, pxs8("WARN\n\n"));

    pxLoggerWarn(&logger,
        pxs8("code = ${0}, text = ${1}, number = ${0}\n"));

    pxLoggerMsg(&logger, pxs8("prova\n"));

    pxLoggerInfo(&logger,
        pxs8("code = ${0}, text = ${1}, number = ${2}\n"));

    pxLoggerSetLevel(&logger, PX_REPORT_LEVEL_TRACE);

    pxLoggerReport(&logger, pxs8("\nTRACE\n\n"));

    pxLoggerWarn(&logger,
        pxs8("code = ${0}, text = ${1}, number = ${0}\n"));

    pxLoggerMsg(&logger, pxs8("prova\n"));

    pxLoggerInfo(&logger,
        pxs8("code = ${0}, text = ${1}, number = ${2}\n"));
}
