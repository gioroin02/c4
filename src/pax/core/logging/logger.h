#ifndef PX_CORE_LOGGING_LOGGER_H
#define PX_CORE_LOGGING_LOGGER_H

#include "import.h"

#define pxLoggerPrint(self, format) pxLoggerPrintFormat(self, format, 0, 0)

#define pxLoggerPrintVargs(self, format, ...) pxLoggerPrintFormat(self, format, \
    px_array_from_vargs(PxFormatMsg, __VA_ARGS__), px_size_vargs(PxFormatMsg, __VA_ARGS__))

#define pxLoggerFatal(self, format) pxLoggerFatalFormat(self, format, 0, 0)

#define pxLoggerFatalVargs(self, format, ...) pxLoggerFatalFormat(self, format, \
    px_array_from_vargs(PxFormatMsg, __VA_ARGS__), px_size_vargs(PxFormatMsg, __VA_ARGS__))

#define pxLoggerError(self, format) pxLoggerErrorFormat(self, format, 0, 0)

#define pxLoggerErrorVargs(self, format, ...) pxLoggerErrorFormat(self, format, \
    px_array_from_vargs(PxFormatMsg, __VA_ARGS__), px_size_vargs(PxFormatMsg, __VA_ARGS__))

#define pxLoggerWarn(self, format) pxLoggerWarnFormat(self, format, 0, 0)

#define pxLoggerWarnVargs(self, format, ...) pxLoggerWarnFormat(self, format, \
    px_array_from_vargs(PxFormatMsg, __VA_ARGS__), px_size_vargs(PxFormatMsg, __VA_ARGS__))

#define pxLoggerInfo(self, format) pxLoggerInfoFormat(self, format, 0, 0)

#define pxLoggerInfoVargs(self, format, ...) pxLoggerInfoFormat(self, format, \
    px_array_from_vargs(PxFormatMsg, __VA_ARGS__), px_size_vargs(PxFormatMsg, __VA_ARGS__))

#define pxLoggerDebug(self, format) pxLoggerDebugFormat(self, format, 0, 0)

#define pxLoggerDebugVargs(self, format, ...) pxLoggerDebugFormat(self, format, \
    px_array_from_vargs(PxFormatMsg, __VA_ARGS__), px_size_vargs(PxFormatMsg, __VA_ARGS__))

#define pxLoggerTrace(self, format) pxLoggerTraceFormat(self, format, 0, 0)

#define pxLoggerTraceVargs(self, format, ...) pxLoggerTraceFormat(self, format, \
    px_array_from_vargs(PxFormatMsg, __VA_ARGS__), px_size_vargs(PxFormatMsg, __VA_ARGS__))

typedef enum PxReportLevel
{
    PX_REPORT_LEVEL_NONE,

    PX_REPORT_LEVEL_PRINT,

    PX_REPORT_LEVEL_FATAL,
    PX_REPORT_LEVEL_ERROR,
    PX_REPORT_LEVEL_WARN,
    PX_REPORT_LEVEL_INFO,
    PX_REPORT_LEVEL_DEBUG,
    PX_REPORT_LEVEL_TRACE,
}
PxReportLevel;

typedef enum PxReportFlag
{
    PX_REPORT_FLAG_NONE  = 0,
    PX_REPORT_FLAG_LEVEL = 1 << 0,
    PX_REPORT_FLAG_COLOR = 1 << 1,
}
PxReportFlag;

typedef struct PxLogger
{
    PxReportLevel level;
    PxReportFlag  flags;

    PxTarget target;
}
PxLogger;

PxLogger
pxLoggerMake(PxTarget target, PxReportLevel level, PxReportFlag flags);

PxReportLevel
pxLoggerSetLevel(PxLogger* self, PxReportLevel level);

PxReportFlag
pxLoggerSetFlags(PxLogger* self, PxReportFlag flags);

pxb8
pxLoggerWriteStart(PxLogger* self, PxReportLevel level);

pxb8
pxLoggerWriteStop(PxLogger* self, PxReportLevel level);

pxb8
pxLoggerWriteFormat(PxLogger* self, PxReportLevel level, PxString8 format, PxFormatMsg* values, pxiword length);

/* Logging levels */

pxb8
pxLoggerPrintFormat(PxLogger* self, PxString8 format, PxFormatMsg* values, pxiword length);

pxb8
pxLoggerFatalFormat(PxLogger* self, PxString8 format, PxFormatMsg* values, pxiword length);

pxb8
pxLoggerErrorFormat(PxLogger* self, PxString8 format, PxFormatMsg* values, pxiword length);

pxb8
pxLoggerWarnFormat(PxLogger* self, PxString8 format, PxFormatMsg* values, pxiword length);

pxb8
pxLoggerInfoFormat(PxLogger* self, PxString8 format, PxFormatMsg* values, pxiword length);

pxb8
pxLoggerDebugFormat(PxLogger* self, PxString8 format, PxFormatMsg* values, pxiword length);

pxb8
pxLoggerTraceFormat(PxLogger* self, PxString8 format, PxFormatMsg* values, pxiword length);

#endif // PX_CORE_LOGGING_LOGGER_H
