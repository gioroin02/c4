#ifndef PX_CORE_FORMAT_BUILDER_H
#define PX_CORE_FORMAT_BUILDER_H

#include "string8.h"
#include "string16.h"
#include "string32.h"

#define pxBuilderBuild(self, format, ...) pxBuilderFormat(self, pxs8(format), \
    0, pxSizeVargs(PxFormatCmd, __VA_ARGS__), pxVargs(PxFormatCmd, __VA_ARGS__))

typedef enum PxFormatCmdType
{
    PX_FORMAT_CMD_NONE,

    PX_FORMAT_CMD_UNSIGNED_8,
    PX_FORMAT_CMD_UNSIGNED_16,
    PX_FORMAT_CMD_UNSIGNED_32,
    PX_FORMAT_CMD_UNSIGNED_64,
    PX_FORMAT_CMD_UNSIGNED,

    PX_FORMAT_CMD_INTEGER_8,
    PX_FORMAT_CMD_INTEGER_16,
    PX_FORMAT_CMD_INTEGER_32,
    PX_FORMAT_CMD_INTEGER_64,
    PX_FORMAT_CMD_INTEGER,

    PX_FORMAT_CMD_BOOLEAN_8,
    PX_FORMAT_CMD_BOOLEAN_16,
    PX_FORMAT_CMD_BOOLEAN_32,
    PX_FORMAT_CMD_BOOLEAN_64,
    PX_FORMAT_CMD_BOOLEAN,

    PX_FORMAT_CMD_UNICODE,

    PX_FORMAT_CMD_STRING_8,
    PX_FORMAT_CMD_STRING_16,
    PX_FORMAT_CMD_STRING_32,

    PX_FORMAT_CMD_DELEGATE,
}
PxFormatCmdType;

typedef struct PxFormatCmdUnsigned8
{
    pxuword        radix;
    PxFormatOption options;
    pxu8           value;
}
PxFormatCmdUnsigned8;

typedef struct PxFormatCmdUnsigned16
{
    pxuword        radix;
    PxFormatOption options;
    pxu16          value;
}
PxFormatCmdUnsigned16;

typedef struct PxFormatCmdUnsigned32
{
    pxuword        radix;
    PxFormatOption options;
    pxu32          value;
}
PxFormatCmdUnsigned32;

typedef struct PxFormatCmdUnsigned64
{
    pxuword        radix;
    PxFormatOption options;
    pxu64          value;
}
PxFormatCmdUnsigned64;

typedef struct PxFormatCmdUnsigned
{
    pxuword        radix;
    PxFormatOption options;
    pxuword        value;
}
PxFormatCmdUnsigned;

typedef struct PxFormatCmdInteger8
{
    pxuword        radix;
    PxFormatOption options;
    pxi8           value;
}
PxFormatCmdInteger8;

typedef struct PxFormatCmdInteger16
{
    pxuword        radix;
    PxFormatOption options;
    pxi16          value;
}
PxFormatCmdInteger16;

typedef struct PxFormatCmdInteger32
{
    pxuword        radix;
    PxFormatOption options;
    pxi32          value;
}
PxFormatCmdInteger32;

typedef struct PxFormatCmdInteger64
{
    pxuword        radix;
    PxFormatOption options;
    pxi64          value;
}
PxFormatCmdInteger64;

typedef struct PxFormatCmdInteger
{
    pxuword        radix;
    PxFormatOption options;
    pxiword        value;
}
PxFormatCmdInteger;

typedef struct PxFormatCmdDelegate
{
    void* ctxt;
    void* proc;
}
PxFormatCmdDelegate;

typedef struct PxFormatCmd
{
    PxFormatCmdType type;

    union
    {
        PxFormatCmdUnsigned8  unsigned_8;
        PxFormatCmdUnsigned16 unsigned_16;
        PxFormatCmdUnsigned32 unsigned_32;
        PxFormatCmdUnsigned64 unsigned_64;
        PxFormatCmdUnsigned   unsigned_word;

        PxFormatCmdInteger8  integer_8;
        PxFormatCmdInteger16 integer_16;
        PxFormatCmdInteger32 integer_32;
        PxFormatCmdInteger64 integer_64;
        PxFormatCmdInteger   integer_word;

        pxb8    boolean_8;
        pxb16   boolean_16;
        pxb32   boolean_32;
        pxb64   boolean_64;
        pxbword boolean_word;

        pxi32 unicode;

        PxString8  string_8;
        PxString16 string_16;
        PxString32 string_32;

        PxFormatCmdDelegate delegate;
    };
}
PxFormatCmd;

typedef struct PxBuilder
{
    pxu8*   memory;
    pxiword length;
    pxiword size;
}
PxBuilder;

typedef pxiword (PxFormatProc) (void*, PxBuilder*);

/* Commands */

PxFormatCmd
pxFormatCmdUnsigned8(pxuword radix, PxFormatOption options, pxu8 value);

PxFormatCmd
pxFormatCmdUnsigned16(pxuword radix, PxFormatOption options, pxu16 value);

PxFormatCmd
pxFormatCmdUnsigned32(pxuword radix, PxFormatOption options, pxu32 value);

PxFormatCmd
pxFormatCmdUnsigned64(pxuword radix, PxFormatOption options, pxu64 value);

PxFormatCmd
pxFormatCmdUnsigned(pxuword radix, PxFormatOption options, pxuword value);

PxFormatCmd
pxFormatCmdInteger8(pxuword radix, PxFormatOption options, pxi8 value);

PxFormatCmd
pxFormatCmdInteger16(pxuword radix, PxFormatOption options, pxi16 value);

PxFormatCmd
pxFormatCmdInteger32(pxuword radix, PxFormatOption options, pxi32 value);

PxFormatCmd
pxFormatCmdInteger64(pxuword radix, PxFormatOption options, pxi64 value);

PxFormatCmd
pxFormatCmdInteger(pxuword radix, PxFormatOption options, pxiword value);

PxFormatCmd
pxFormatCmdBoolean8(pxb8 value);

PxFormatCmd
pxFormatCmdBoolean16(pxb16 value);

PxFormatCmd
pxFormatCmdBoolean32(pxb32 value);

PxFormatCmd
pxFormatCmdBoolean64(pxb64 value);

PxFormatCmd
pxFormatCmdBoolean(pxbword value);

PxFormatCmd
pxFormatCmdUnicode(pxi32 value);

PxFormatCmd
pxFormatCmdString8(PxString8 value);

PxFormatCmd
pxFormatCmdString16(PxString16 value);

PxFormatCmd
pxFormatCmdString32(PxString32 value);

PxFormatCmd
pxFormatCmdDelegate(void* ctxt, void* proc);

/* Builder */

PxBuilder
pxBuilderMake(pxu8* memory, pxiword length);

PxBuilder
pxBuilderReserve(PxArena* arena, pxiword length);

void
pxBuilderClear(PxBuilder* self);

void
pxBuilderReset(PxBuilder* self);

pxiword
pxBuilderFormat(PxBuilder* self, PxString8 format, pxiword start, pxiword stop, PxFormatCmd* list);

pxiword
pxBuilderChain(PxBuilder* self, pxiword start, pxiword stop, PxFormatCmd* list);

pxiword
pxBuilderCommand(PxBuilder* self, PxFormatCmd command);

PxString8
pxString8FromBuilder(PxArena* arena, PxBuilder* builder);

PxString16
pxString16FromBuilder(PxArena* arena, PxBuilder* builder);

PxString32
pxString32FromBuilder(PxArena* arena, PxBuilder* builder);

#endif // PX_CORE_FORMAT_BUILDER_H
