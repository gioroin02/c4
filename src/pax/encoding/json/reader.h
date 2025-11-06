#ifndef PX_ENCODING_JSON_READER_H
#define PX_ENCODING_JSON_READER_H

#include "scanner.h"
#include "message.h"

typedef enum PxJsonReaderFlag
{
    PX_JSON_READER_NONE = 0,
    PX_JSON_READER_COMMA = 1 << 0,
    PX_JSON_READER_COLON = 1 << 1,
}
PxJsonReaderFlag;

typedef struct PxJsonReader
{
    PxSource source;
    PxQueue  stack;

    PxJsonReaderFlag flags;

    PxString8   name;
    PxJsonToken token;
}
PxJsonReader;

PxJsonReader
pxJsonReaderReserve(PxSource source, PxArena* arena, pxiword length);

PxJsonMsg
pxJsonReaderMsg(PxJsonReader* self, PxArena* arena);

pxb8
pxJsonReaderObjectOpen(PxJsonReader* self, PxArena* arena, PxJsonMsg* message);

pxb8
pxJsonReaderObjectClose(PxJsonReader* self, PxArena* arena, PxJsonMsg* message);

pxb8
pxJsonReaderArrayOpen(PxJsonReader* self, PxArena* arena, PxJsonMsg* message);

pxb8
pxJsonReaderArrayClose(PxJsonReader* self, PxArena* arena, PxJsonMsg* message);

#endif // PX_ENCODING_JSON_READER_H
