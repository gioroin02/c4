#ifndef PX_CORE_LOGGING_LOGGER_C
#define PX_CORE_LOGGING_LOGGER_C

#include "logger.h"

PxString8
pxFormatSpecifierFromMemory8(pxu8* memory, pxiword length, pxiword start)
{
    pxiword index = start;

    if (index < 0 || index >= length || length < 3)
        return (PxString8) {0};

    if (memory[index] != PX_ASCII_DOLLAR)
        return (PxString8) {0};

    index += 1;

    if (memory[index] != PX_ASCII_BRACE_LEFT)
        return (PxString8) {0};

    index += 1;

    while (memory[index] != PX_ASCII_BRACE_RIGHT) {
        if (index < 0 || index >= length)
            break;

        index += 1;
    }

    index += 1;

    return (PxString8) {
        .memory = memory + start,
        .length = index  - start,
    };
}

PxLogger
pxLoggerMake(PxArena* arena, PxWriter writer, PxReportLevel level, PxReportFlag flags)
{
    return (PxLogger) {
        .arena  = arena,
        .writer = writer,
        .level  = level,
        .flags  = flags,
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

void
pxLoggerClear(PxLogger* self)
{
    self->list.head = 0;
    self->list.tail = 0;
    self->list.size = 0;
}

pxb8
pxLoggerFormat(PxLogger* self, PxReportLevel level, PxString8 format)
{
    if (level > self->level && level != PX_REPORT_LEVEL_NONE)
        return 0;

    switch (level) {
        case PX_REPORT_LEVEL_FATAL:
            if ((self->flags & PX_REPORT_FLAG_COLORS) != 0)
                pxWriterString8(&self->writer, pxs8("\x1b[35m"));

            pxWriterString8(&self->writer, pxs8("[FATAL] "));

            if ((self->flags & PX_REPORT_FLAG_COLORS) != 0)
                pxWriterString8(&self->writer, pxs8("\x1b[0m"));
        break;

        case PX_REPORT_LEVEL_ERROR:
            if ((self->flags & PX_REPORT_FLAG_COLORS) != 0)
                pxWriterString8(&self->writer, pxs8("\x1b[31m"));

            pxWriterString8(&self->writer, pxs8("[ERROR] "));

            if ((self->flags & PX_REPORT_FLAG_COLORS) != 0)
                pxWriterString8(&self->writer, pxs8("\x1b[0m"));
        break;

        case PX_REPORT_LEVEL_WARN:
            if ((self->flags & PX_REPORT_FLAG_COLORS) != 0)
                pxWriterString8(&self->writer, pxs8("\x1b[33m"));

            pxWriterString8(&self->writer, pxs8("[WARN] "));

            if ((self->flags & PX_REPORT_FLAG_COLORS) != 0)
                pxWriterString8(&self->writer, pxs8("\x1b[0m"));
        break;

        case PX_REPORT_LEVEL_MESSAGE:
            pxWriterString8(&self->writer, pxs8("[MESSAGE] "));
        break;

        case PX_REPORT_LEVEL_INFO:
            if ((self->flags & PX_REPORT_FLAG_COLORS) != 0)
                pxWriterString8(&self->writer, pxs8("\x1b[32m"));

            pxWriterString8(&self->writer, pxs8("[INFO] "));

            if ((self->flags & PX_REPORT_FLAG_COLORS) != 0)
                pxWriterString8(&self->writer, pxs8("\x1b[0m"));
        break;

        case PX_REPORT_LEVEL_DEBUG:
            if ((self->flags & PX_REPORT_FLAG_COLORS) != 0)
                pxWriterString8(&self->writer, pxs8("\x1b[36m"));

            pxWriterString8(&self->writer, pxs8("[DEBUG] "));

            if ((self->flags & PX_REPORT_FLAG_COLORS) != 0)
                pxWriterString8(&self->writer, pxs8("\x1b[0m"));
        break;

        case PX_REPORT_LEVEL_TRACE:
            if ((self->flags & PX_REPORT_FLAG_COLORS) != 0)
                pxWriterString8(&self->writer, pxs8("\x1b[34m"));

            pxWriterString8(&self->writer, pxs8("[TRACE] "));

            if ((self->flags & PX_REPORT_FLAG_COLORS) != 0)
                pxWriterString8(&self->writer, pxs8("\x1b[0m"));
        break;

        default: break;
    }

    for (pxiword i = 0; i < format.length; i += 1) {
        pxu8 byte = format.memory[i];

        if (byte == PX_ASCII_DOLLAR) {
            PxString8 spec = pxFormatSpecifierFromMemory8(
                format.memory, format.length, i);

            PxStringNode* node  = 0;
            pxiword       index = 0;
            pxb8          state = 0;

            state = pxIntegerFromString8(&index, 10, PX_FORMAT_OPTION_NONE,
                pxString8Slice(spec, 2, spec.length - 1));

            if (state != 0)
                state = pxStringListRead(&self->list, index, &node);

            if (state != 0 && node != 0) {
                PxString8 string =
                    pxString8FromMemory(node->memory, node->length);

                pxWriterString8(&self->writer, string);
            } else
                pxWriterString8(&self->writer, spec);

            i += spec.length - 1;
        } else
            pxWriterByte(&self->writer, byte);
    }

    pxWriterFlush(&self->writer);

    return 1;
}

pxb8
pxLoggerUnsigned8(PxLogger* self, pxiword index, pxu8 value)
{
    pxiword offset = pxArenaOffset(self->arena);

    PxStringNode* node =
        pxArenaReserve(self->arena, PxStringNode, 1);

    PxString8 string = pxString8FromUnsigned8(
        self->arena, 10, PX_FORMAT_OPTION_NONE, value);

    if (node != 0 && string.length > 0) {
        node->memory = string.memory;
        node->length = string.length;

        if (pxStringListInsert(&self->list, index, node) != 0)
            return 1;
    }

    pxArenaRewind(self->arena, offset);

    return 0;
}

pxb8
pxLoggerUnsigned16(PxLogger* self, pxiword index, pxu16 value)
{
    pxiword offset = pxArenaOffset(self->arena);

    PxStringNode* node =
        pxArenaReserve(self->arena, PxStringNode, 1);

    PxString8 string = pxString8FromUnsigned16(
        self->arena, 10, PX_FORMAT_OPTION_NONE, value);

    if (node != 0 && string.length > 0) {
        node->memory = string.memory;
        node->length = string.length;

        if (pxStringListInsert(&self->list, index, node) != 0)
            return 1;
    }

    pxArenaRewind(self->arena, offset);

    return 0;
}

pxb8
pxLoggerUnsigned32(PxLogger* self, pxiword index, pxu32 value)
{
    pxiword offset = pxArenaOffset(self->arena);

    PxStringNode* node =
        pxArenaReserve(self->arena, PxStringNode, 1);

    PxString8 string = pxString8FromUnsigned32(
        self->arena, 10, PX_FORMAT_OPTION_NONE, value);

    if (node != 0 && string.length > 0) {
        node->memory = string.memory;
        node->length = string.length;

        if (pxStringListInsert(&self->list, index, node) != 0)
            return 1;
    }

    pxArenaRewind(self->arena, offset);

    return 0;
}

pxb8
pxLoggerUnsigned64(PxLogger* self, pxiword index, pxu64 value)
{
    pxiword offset = pxArenaOffset(self->arena);

    PxStringNode* node =
        pxArenaReserve(self->arena, PxStringNode, 1);

    PxString8 string = pxString8FromUnsigned64(
        self->arena, 10, PX_FORMAT_OPTION_NONE, value);

    if (node != 0 && string.length > 0) {
        node->memory = string.memory;
        node->length = string.length;

        if (pxStringListInsert(&self->list, index, node) != 0)
            return 1;
    }

    pxArenaRewind(self->arena, offset);

    return 0;
}

pxb8
pxLoggerUnsigned(PxLogger* self, pxiword index, pxuword value)
{
    pxiword offset = pxArenaOffset(self->arena);

    PxStringNode* node =
        pxArenaReserve(self->arena, PxStringNode, 1);

    PxString8 string = pxString8FromUnsigned(
        self->arena, 10, PX_FORMAT_OPTION_NONE, value);

    if (node != 0 && string.length > 0) {
        node->memory = string.memory;
        node->length = string.length;

        if (pxStringListInsert(&self->list, index, node) != 0)
            return 1;
    }

    pxArenaRewind(self->arena, offset);

    return 0;
}

pxb8
pxLoggerInteger8(PxLogger* self, pxiword index, pxi8 value)
{
    pxiword offset = pxArenaOffset(self->arena);

    PxStringNode* node =
        pxArenaReserve(self->arena, PxStringNode, 1);

    PxString8 string = pxString8FromInteger8(
        self->arena, 10, PX_FORMAT_OPTION_NONE, value);

    if (node != 0 && string.length > 0) {
        node->memory = string.memory;
        node->length = string.length;

        if (pxStringListInsert(&self->list, index, node) != 0)
            return 1;
    }

    pxArenaRewind(self->arena, offset);

    return 0;
}

pxb8
pxLoggerInteger16(PxLogger* self, pxiword index, pxi16 value)
{
    pxiword offset = pxArenaOffset(self->arena);

    PxStringNode* node =
        pxArenaReserve(self->arena, PxStringNode, 1);

    PxString8 string = pxString8FromInteger16(
        self->arena, 10, PX_FORMAT_OPTION_NONE, value);

    if (node != 0 && string.length > 0) {
        node->memory = string.memory;
        node->length = string.length;

        if (pxStringListInsert(&self->list, index, node) != 0)
            return 1;
    }

    pxArenaRewind(self->arena, offset);

    return 0;
}

pxb8
pxLoggerInteger32(PxLogger* self, pxiword index, pxi32 value)
{
    pxiword offset = pxArenaOffset(self->arena);

    PxStringNode* node =
        pxArenaReserve(self->arena, PxStringNode, 1);

    PxString8 string = pxString8FromInteger32(
        self->arena, 10, PX_FORMAT_OPTION_NONE, value);

    if (node != 0 && string.length > 0) {
        node->memory = string.memory;
        node->length = string.length;

        if (pxStringListInsert(&self->list, index, node) != 0)
            return 1;
    }

    pxArenaRewind(self->arena, offset);

    return 0;
}

pxb8
pxLoggerInteger64(PxLogger* self, pxiword index, pxi64 value)
{
    pxiword offset = pxArenaOffset(self->arena);

    PxStringNode* node =
        pxArenaReserve(self->arena, PxStringNode, 1);

    PxString8 string = pxString8FromInteger64(
        self->arena, 10, PX_FORMAT_OPTION_NONE, value);

    if (node != 0 && string.length > 0) {
        node->memory = string.memory;
        node->length = string.length;

        if (pxStringListInsert(&self->list, index, node) != 0)
            return 1;
    }

    pxArenaRewind(self->arena, offset);

    return 0;
}

pxb8
pxLoggerInteger(PxLogger* self, pxiword index, pxiword value)
{
    pxiword offset = pxArenaOffset(self->arena);

    PxStringNode* node =
        pxArenaReserve(self->arena, PxStringNode, 1);

    PxString8 string = pxString8FromInteger64(
        self->arena, 10, PX_FORMAT_OPTION_NONE, value);

    if (node != 0 && string.length > 0) {
        node->memory = string.memory;
        node->length = string.length;

        if (pxStringListInsert(&self->list, index, node) != 0)
            return 1;
    }

    pxArenaRewind(self->arena, offset);

    return 0;
}

pxb8
pxLoggerMemory8(PxLogger* self, pxiword index, pxu8* value)
{
    pxiword offset = pxArenaOffset(self->arena);

    PxStringNode* node =
        pxArenaReserve(self->arena, PxStringNode, 1);

    PxString8 string =
        pxString8CopyMemory8(self->arena, value, PX_MEMORY_KIB);

    if (node != 0 && string.length > 0) {
        node->memory = string.memory;
        node->length = string.length;

        if (pxStringListInsert(&self->list, index, node) != 0)
            return 1;
    }

    pxArenaRewind(self->arena, offset);

    return 0;
}

pxb8
pxLoggerMemory16(PxLogger* self, pxiword index, pxu16* value)
{
    pxiword offset = pxArenaOffset(self->arena);

    PxStringNode* node =
        pxArenaReserve(self->arena, PxStringNode, 1);

    PxString8 string = pxString8CopyString16(self->arena,
        pxString16FromMemory(value, PX_MEMORY_KIB));

    if (node != 0 && string.length > 0) {
        node->memory = string.memory;
        node->length = string.length;

        if (pxStringListInsert(&self->list, index, node) != 0)
            return 1;
    }

    pxArenaRewind(self->arena, offset);

    return 0;
}

pxb8
pxLoggerMemory32(PxLogger* self, pxiword index, pxu32* value)
{
    pxiword offset = pxArenaOffset(self->arena);

    PxStringNode* node =
        pxArenaReserve(self->arena, PxStringNode, 1);

    PxString8 string = pxString8CopyString32(self->arena,
        pxString32FromMemory(value, PX_MEMORY_KIB));

    if (node != 0 && string.length > 0) {
        node->memory = string.memory;
        node->length = string.length;

        if (pxStringListInsert(&self->list, index, node) != 0)
            return 1;
    }

    pxArenaRewind(self->arena, offset);

    return 0;
}

pxb8
pxLoggerString8(PxLogger* self, pxiword index, PxString8 value)
{
    pxiword offset = pxArenaOffset(self->arena);

    PxStringNode* node =
        pxArenaReserve(self->arena, PxStringNode, 1);

    PxString8 string = pxString8Copy(self->arena, value);

    if (node != 0 && string.length > 0) {
        node->memory = string.memory;
        node->length = string.length;

        if (pxStringListInsert(&self->list, index, node) != 0)
            return 1;
    }

    pxArenaRewind(self->arena, offset);

    return 0;
}

pxb8
pxLoggerString16(PxLogger* self, pxiword index, PxString16 value)
{
    pxiword offset = pxArenaOffset(self->arena);

    PxStringNode* node =
        pxArenaReserve(self->arena, PxStringNode, 1);

    PxString8 string = pxString8CopyString16(self->arena, value);

    if (node != 0 && string.length > 0) {
        node->memory = string.memory;
        node->length = string.length;

        if (pxStringListInsert(&self->list, index, node) != 0)
            return 1;
    }

    pxArenaRewind(self->arena, offset);

    return 0;
}

pxb8
pxLoggerString32(PxLogger* self, pxiword index, PxString32 value)
{
    pxiword offset = pxArenaOffset(self->arena);

    PxStringNode* node =
        pxArenaReserve(self->arena, PxStringNode, 1);

    PxString8 string = pxString8CopyString32(self->arena, value);

    if (node != 0 && string.length > 0) {
        node->memory = string.memory;
        node->length = string.length;

        if (pxStringListInsert(&self->list, index, node) != 0)
            return 1;
    }

    pxArenaRewind(self->arena, offset);

    return 0;
}

#endif // PX_CORE_LOGGING_LOGGER_C
