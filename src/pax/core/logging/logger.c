#ifndef PX_CORE_LOGGING_LOGGER_C
#define PX_CORE_LOGGING_LOGGER_C

#include "logger.h"

PxLogger
pxLoggerMake(PxTarget target, PxReportLevel level, PxReportFlag flags)
{
    return (PxLogger) {
        .level  = level,
        .flags  = flags,
        .target = target,
    };
}

PxReportLevel
pxLoggerSetLevel(PxLogger* self, PxReportLevel level)
{
    PxReportLevel result =
        self->level;

    self->level = level;

    return result;
}

PxReportFlag
pxLoggerSetFlags(PxLogger* self, PxReportFlag flags)
{
    PxReportFlag result =
        self->flags;

    self->flags = flags;

    return result;
}

pxb8
pxLoggerWriteStart(PxLogger* self, PxReportLevel level)
{
    PxString8 reset = pxs8("\x1b[0m");

    PxString8 colors[] = {
        [PX_REPORT_LEVEL_FATAL] = pxs8("\x1b[95m"),
        [PX_REPORT_LEVEL_ERROR] = pxs8("\x1b[91m"),
        [PX_REPORT_LEVEL_WARN]  = pxs8("\x1b[93m"),
        [PX_REPORT_LEVEL_INFO]  = pxs8("\x1b[92m"),
        [PX_REPORT_LEVEL_DEBUG] = pxs8("\x1b[96m"),
        [PX_REPORT_LEVEL_TRACE] = pxs8("\x1b[94m"),
    };

    PxString8 headings[] = {
        [PX_REPORT_LEVEL_FATAL] = pxs8("[ FATAL ] "),
        [PX_REPORT_LEVEL_ERROR] = pxs8("[ ERROR ] "),
        [PX_REPORT_LEVEL_WARN]  = pxs8("[  WARN ] "),
        [PX_REPORT_LEVEL_INFO]  = pxs8("[  INFO ] "),
        [PX_REPORT_LEVEL_DEBUG] = pxs8("[ DEBUG ] "),
        [PX_REPORT_LEVEL_TRACE] = pxs8("[ TRACE ] "),
    };

    pxiword result = 0;

    if ((self->flags & PX_REPORT_FLAG_LEVEL) != 0) {
        if ((self->flags & PX_REPORT_FLAG_COLOR) != 0)
            result += pxTargetWriteString8(self->target, colors[level]);

        result += pxTargetWriteString8(self->target, headings[level]);

        if ((self->flags & PX_REPORT_FLAG_COLOR) != 0)
            result += pxTargetWriteString8(self->target, reset);
    }

    return result;
}

pxb8
pxLoggerWriteStop(PxLogger* self, PxReportLevel level)
{
    return pxTargetFlush(self->target);
}

pxb8
pxLoggerWriteFormat(PxLogger* self, PxReportLevel level, PxString8 format, PxFormatMsg* values, pxiword length)
{
    if (level == PX_REPORT_LEVEL_NONE)
        return 0;

    if (self->level >= level) {
        pxLoggerWriteStart(self, level);
        pxTargetPrintFormat(self->target, format, values, length, 0);
        pxLoggerWriteStop(self, level);

        return 1;
    }

    return 0;
}

pxb8
pxLoggerPrintFormat(PxLogger* self, PxString8 format, PxFormatMsg* values, pxiword length)
{
    return pxLoggerWriteFormat(self, PX_REPORT_LEVEL_PRINT, format, values, length);
}

pxb8
pxLoggerFatalFormat(PxLogger* self, PxString8 format, PxFormatMsg* values, pxiword length)
{
    return pxLoggerWriteFormat(self, PX_REPORT_LEVEL_FATAL, format, values, length);
}

pxb8
pxLoggerErrorFormat(PxLogger* self, PxString8 format, PxFormatMsg* values, pxiword length)
{
    return pxLoggerWriteFormat(self, PX_REPORT_LEVEL_ERROR, format, values, length);
}

pxb8
pxLoggerWarnFormat(PxLogger* self, PxString8 format, PxFormatMsg* values, pxiword length)
{
    return pxLoggerWriteFormat(self, PX_REPORT_LEVEL_WARN, format, values, length);
}

pxb8
pxLoggerInfoFormat(PxLogger* self, PxString8 format, PxFormatMsg* values, pxiword length)
{
    return pxLoggerWriteFormat(self, PX_REPORT_LEVEL_INFO, format, values, length);
}

pxb8
pxLoggerDebugFormat(PxLogger* self, PxString8 format, PxFormatMsg* values, pxiword length)
{
    return pxLoggerWriteFormat(self, PX_REPORT_LEVEL_DEBUG, format, values, length);
}

pxb8
pxLoggerTraceFormat(PxLogger* self, PxString8 format, PxFormatMsg* values, pxiword length)
{
    return pxLoggerWriteFormat(self, PX_REPORT_LEVEL_TRACE, format, values, length);
}

#endif // PX_CORE_LOGGING_LOGGER_C
