#ifndef PX_ENCODING_JSON_WRITER_H
#define PX_ENCODING_JSON_WRITER_H

#include "message.h"

typedef struct PxJsonWriter
{
    PxQueue stack;
    pxb8    comma;

    PxWriter* writer;
}
PxJsonWriter;

PxJsonWriter
pxJsonWriterMake(PxArena* arena, pxiword length, PxWriter* writer);

pxiword
pxJsonWriteChain(PxJsonWriter* self, PxArena* arena, pxiword start, pxiword stop, PxJsonMsg* list);

pxb8
pxJsonWriteMessage(PxJsonWriter* self, PxArena* arena, PxJsonMsg message);

#endif // PX_ENCODING_JSON_WRITER_H
