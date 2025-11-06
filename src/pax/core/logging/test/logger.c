#include "../export.h"

#include "../../console/export.h"

int
main(int argc, char** argv)
{
    PxArena arena = pxMemoryReserve(16);

    PxConsole console = pxConsoleCreate(&arena);
    PxTarget  target  = pxTargetFromConsole(console);

    PxLogger logger = pxLoggerMake(target, PX_REPORT_LEVEL_WARN,
        PX_REPORT_FLAG_LEVEL | PX_REPORT_FLAG_COLOR);

    pxLoggerPrint(&logger, pxs8("Level is \"WARN\"\n\n"));

    pxLoggerFatal(&logger, pxs8("Testing...\n"));
    pxLoggerError(&logger, pxs8("Testing...\n"));
    pxLoggerWarn(&logger,  pxs8("Testing...\n"));

    pxLoggerInfoVargs(&logger, pxs8("With args [${0}, ${1}, ${2}, ${3}, ${4}, ${5}]\n"),
        pxFormatMsgInteger(1), pxFormatMsgInteger(2), pxFormatMsgInteger(3),
        pxFormatMsgInteger(4), pxFormatMsgInteger(5), pxFormatMsgInteger(6));

    pxLoggerDebug(&logger, pxs8("Testing...\n"));

    pxLoggerTraceFormat(&logger, pxs8("strings = str8(${0}), str16(${1}), str32(${2})\n"),
        (PxFormatMsg[]) {
            pxFormatMsgString8(pxString8Vargs('h', 'e', 'l', 'l', 'o')),
            pxFormatMsgString16(pxString16Vargs('h', 'e', 'l', 'l', 'o')),
            pxFormatMsgString32(pxString32Vargs('h', 'e', 'l', 'l', 'o')),
        }, 3);

    pxLoggerSetLevel(&logger, PX_REPORT_LEVEL_TRACE);

    pxLoggerPrint(&logger, pxs8("\nLevel is \"TRACE\"\n\n"));

    pxLoggerFatal(&logger, pxs8("Testing...\n"));
    pxLoggerError(&logger, pxs8("Testing...\n"));
    pxLoggerWarn(&logger,  pxs8("Testing...\n"));

    pxLoggerInfoVargs(&logger, pxs8("With args [${0}, ${1}, ${2}, ${3}, ${4}, ${5}]\n"),
        pxFormatMsgInteger(1), pxFormatMsgInteger(2), pxFormatMsgInteger(3),
        pxFormatMsgInteger(4), pxFormatMsgInteger(5), pxFormatMsgInteger(6));

    pxLoggerDebug(&logger, pxs8("Testing...\n"));

    pxLoggerTraceFormat(&logger, pxs8("strings = str8(${0}), str16(${1}), str32(${2})\n"),
        (PxFormatMsg[]) {
            pxFormatMsgString8(pxString8Vargs('h', 'e', 'l', 'l', 'o')),
            pxFormatMsgString16(pxString16Vargs('h', 'e', 'l', 'l', 'o')),
            pxFormatMsgString32(pxString32Vargs('h', 'e', 'l', 'l', 'o')),
        }, 3);
}
