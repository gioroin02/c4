#ifndef PX_CORE_LOGGING_LOGGER_H
#define PX_CORE_LOGGING_LOGGER_H

#include "import.h"

#define pxLoggerWrite(self, format, ...) pxLoggerFormat(self, PX_REPORT_LEVEL_WRITE, pxs8(format), \
    0, pxSizeVargs(PxFormatCmd, __VA_ARGS__), pxVargs(PxFormatCmd, __VA_ARGS__))

#define pxLoggerFatal(self, format, ...) pxLoggerFormat(self, PX_REPORT_LEVEL_FATAL, pxs8(format), \
    0, pxSizeVargs(PxFormatCmd, __VA_ARGS__), pxVargs(PxFormatCmd, __VA_ARGS__))

#define pxLoggerError(self, format, ...) pxLoggerFormat(self, PX_REPORT_LEVEL_ERROR, pxs8(format), \
    0, pxSizeVargs(PxFormatCmd, __VA_ARGS__), pxVargs(PxFormatCmd, __VA_ARGS__))

#define pxLoggerWarn(self, format, ...) pxLoggerFormat(self, PX_REPORT_LEVEL_WARN, pxs8(format), \
    0, pxSizeVargs(PxFormatCmd, __VA_ARGS__), pxVargs(PxFormatCmd, __VA_ARGS__))

#define pxLoggerMessage(self, format, ...) pxLoggerFormat(self, PX_REPORT_LEVEL_MESSAGE, pxs8(format), \
    0, pxSizeVargs(PxFormatCmd, __VA_ARGS__), pxVargs(PxFormatCmd, __VA_ARGS__))

#define pxLoggerInfo(self, format, ...) pxLoggerFormat(self, PX_REPORT_LEVEL_INFO, pxs8(format), \
    0, pxSizeVargs(PxFormatCmd, __VA_ARGS__), pxVargs(PxFormatCmd, __VA_ARGS__))

#define pxLoggerDebug(self, format, ...) pxLoggerFormat(self, PX_REPORT_LEVEL_DEBUG, pxs8(format), \
    0, pxSizeVargs(PxFormatCmd, __VA_ARGS__), pxVargs(PxFormatCmd, __VA_ARGS__))

#define pxLoggerTrace(self, format, ...) pxLoggerFormat(self, PX_REPORT_LEVEL_TRACE, pxs8(format), \
    0, pxSizeVargs(PxFormatCmd, __VA_ARGS__), pxVargs(PxFormatCmd, __VA_ARGS__))

typedef enum PxReportLevel
{
    PX_REPORT_LEVEL_NONE,
    PX_REPORT_LEVEL_WRITE,
    PX_REPORT_LEVEL_FATAL,
    PX_REPORT_LEVEL_ERROR,
    PX_REPORT_LEVEL_WARN,
    PX_REPORT_LEVEL_MESSAGE,
    PX_REPORT_LEVEL_INFO,
    PX_REPORT_LEVEL_DEBUG,
    PX_REPORT_LEVEL_TRACE,
}
PxReportLevel;

typedef enum PxReportFlag
{
    PX_REPORT_FLAG_NONE  = 0x0,
    PX_REPORT_FLAG_LEVEL = 0x1,
    PX_REPORT_FLAG_COLOR = 0x2,
}
PxReportFlag;

typedef struct PxLogger
{
    PxBuilder     builder;
    PxReportLevel level;
    PxReportFlag  flags;

    PxWriter* writer;
}
PxLogger;

PxLogger
pxLoggerReserve(PxArena* arena, pxiword length, PxWriter* writer);

PxReportLevel
pxLoggerSetLevel(PxLogger* self, PxReportLevel level);

PxReportFlag
pxLoggerSetFlags(PxLogger* self, PxReportFlag flags);

pxb8
pxLoggerStart(PxLogger* self, PxReportLevel level);

pxb8
pxLoggerStop(PxLogger* self, PxReportLevel level);

pxb8
pxLoggerFormat(PxLogger* self, PxReportLevel level, PxString8 format, pxiword start, pxiword stop, PxFormatCmd* list);

#endif // PX_CORE_LOGGING_LOGGER_H
