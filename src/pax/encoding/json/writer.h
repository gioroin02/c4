#ifndef PX_ENCODING_JSON_WRITER_H
#define PX_ENCODING_JSON_WRITER_H

#include "message.h"

typedef enum PxJsonWriterFlag
{
    PX_JSON_WRITER_NONE  = 0,
    PX_JSON_WRITER_COMMA = 1 << 0,
}
PxJsonWriterFlag;

typedef struct PxJsonWriter
{
    PxTarget target;
    PxQueue  stack;

    PxJsonWriterFlag flags;
}
PxJsonWriter;

typedef pxb8 (PxJsonWriterProc) (void*, PxJsonWriter*, PxArena*);

PxJsonWriter
pxJsonWriterReserve(PxTarget target, PxArena* arena, pxiword length);

pxb8
pxJsonWriterMsg(PxJsonWriter* self, PxArena* arena, PxJsonMsg message);

pxiword
pxJsonWriterList(PxJsonWriter* self, PxArena* arena, PxJsonMsg* values, pxiword length);

pxb8
pxJsonWriterObjectOpen(PxJsonWriter* self, PxArena* arena);

pxb8
pxJsonWriterObjectClose(PxJsonWriter* self, PxArena* arena);

pxb8
pxJsonWriterArrayOpen(PxJsonWriter* self, PxArena* arena);

pxb8
pxJsonWriterArrayClose(PxJsonWriter* self, PxArena* arena);

#endif // PX_ENCODING_JSON_WRITER_H
