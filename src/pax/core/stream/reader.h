#ifndef PX_STREAM_READER_H
#define PX_STREAM_READER_H

#include "buffer8.h"

typedef pxiword (PxReaderProc) (void*, PxBuffer8*);

typedef struct PxReader
{
    PxBuffer8 buffer;

    void* ctxt;
    void* proc;
}
PxReader;

PxReader
pxBufferReader(PxBuffer8* self, PxArena* arena, pxiword length);

pxiword
pxReaderFill(PxReader* self);

pxu8
pxReaderPeekByte(PxReader* self, pxiword offset);

PxString8
pxReaderPeekString8(PxReader* self, PxArena* arena, pxiword length);

PxString8
pxReaderPeekLine(PxReader* self, PxArena* arena, pxiword length);

pxu8
pxReaderByte(PxReader* self, pxiword offset);

PxString8
pxReaderString8(PxReader* self, PxArena* arena, pxiword length);

PxString8
pxReaderLine(PxReader* self, PxArena* arena, pxiword length);

#endif // PX_STREAM_READER_H
