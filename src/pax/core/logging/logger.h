#ifndef PX_CORE_LOGGING_LOGGER_H
#define PX_CORE_LOGGING_LOGGER_H

#include "import.h"

#define pxLoggerReport(self, format) \
    pxLoggerFormat(self, PX_REPORT_LEVEL_NONE, format)

#define pxLoggerFatal(self, format) \
    pxLoggerFormat(self, PX_REPORT_LEVEL_FATAL, format)

#define pxLoggerError(self, format) \
    pxLoggerFormat(self, PX_REPORT_LEVEL_ERROR, format)

#define pxLoggerWarn(self, format) \
    pxLoggerFormat(self, PX_REPORT_LEVEL_WARN, format)

#define pxLoggerMsg(self, format) \
    pxLoggerFormat(self, PX_REPORT_LEVEL_MESSAGE, format)

#define pxLoggerInfo(self, format) \
    pxLoggerFormat(self, PX_REPORT_LEVEL_INFO, format)

#define pxLoggerDebug(self, format) \
    pxLoggerFormat(self, PX_REPORT_LEVEL_DEBUG, format)

#define pxLoggerTrace(self, format) \
    pxLoggerFormat(self, PX_REPORT_LEVEL_TRACE, format)

typedef enum PxReportLevel
{
    PX_REPORT_LEVEL_NONE,
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
    PX_REPORT_FLAG_NONE   = 0x0,
    PX_REPORT_FLAG_COLORS = 0x1,
}
PxReportFlag;

typedef struct PxLogger
{
    PxArena*      arena;
    PxWriter      writer;
    PxReportLevel level;
    PxReportFlag  flags;
    PxStringList  list;
}
PxLogger;

PxLogger
pxLoggerMake(PxArena* arena, PxWriter writer, PxReportLevel level, PxReportFlag flags);

PxReportLevel
pxLoggerSetLevel(PxLogger* self, PxReportLevel level);

PxReportFlag
pxLoggerSetFlags(PxLogger* self, PxReportFlag flags);

void
pxLoggerClear(PxLogger* self);

pxb8
pxLoggerFormat(PxLogger* self, PxReportLevel level, PxString8 format);

pxb8
pxLoggerUnsigned8(PxLogger* self, pxiword index, pxu8 value);

pxb8
pxLoggerUnsigned16(PxLogger* self, pxiword index, pxu16 value);

pxb8
pxLoggerUnsigned32(PxLogger* self, pxiword index, pxu32 value);

pxb8
pxLoggerUnsigned64(PxLogger* self, pxiword index, pxu64 value);

pxb8
pxLoggerUnsigned(PxLogger* self, pxiword index, pxuword value);

pxb8
pxLoggerInteger8(PxLogger* self, pxiword index, pxi8 value);

pxb8
pxLoggerInteger16(PxLogger* self, pxiword index, pxi16 value);

pxb8
pxLoggerInteger32(PxLogger* self, pxiword index, pxi32 value);

pxb8
pxLoggerInteger64(PxLogger* self, pxiword index, pxi64 value);

pxb8
pxLoggerInteger(PxLogger* self, pxiword index, pxiword value);

pxb8
pxLoggerMemory8(PxLogger* self, pxiword index, pxu8* value);

pxb8
pxLoggerMemory16(PxLogger* self, pxiword index, pxu16* value);

pxb8
pxLoggerMemory32(PxLogger* self, pxiword index, pxu32* value);

pxb8
pxLoggerString8(PxLogger* self, pxiword index, PxString8 value);

pxb8
pxLoggerString16(PxLogger* self, pxiword index, PxString16 value);

pxb8
pxLoggerString32(PxLogger* self, pxiword index, PxString32 value);

#endif // PX_CORE_LOGGING_LOGGER_H
