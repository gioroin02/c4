#ifndef PX_CORE_STREAM_SOURCE_H
#define PX_CORE_STREAM_SOURCE_H

#include "import.h"

typedef struct PxSource
{
    void* ctxt;
    void* proc;

    PxBuffer8* buffer;
}
PxSource;

typedef pxiword (PxSourceProc) (void*, pxu8*, pxiword);

PxSource
pxBufferedSource(PxSource source, PxBuffer8* buffer);

PxSource
pxSourceFromBuffer8(PxBuffer8* self);

pxiword
pxSourceFill(PxSource self);

pxiword
pxSourceDrop(PxSource self, pxiword amount);

pxiword
pxSourceReadMemory8(PxSource self, pxu8* memory, pxiword length);

pxiword
pxSourceReadBuffer8(PxSource self, PxBuffer8* buffer);

pxu8
pxSourceReadByte(PxSource self);

PxString8
pxSourceReadString8(PxSource self, PxArena* arena, pxiword length);

pxiword
pxSourceReadUnicode(PxSource self, pxi32* value);

pxiword
pxSourcePeekMemory8(PxSource self, pxu8* memory, pxiword length);

pxiword
pxSourcePeekBuffer8(PxSource self, PxBuffer8* buffer);

pxu8
pxSourcePeekByte(PxSource self);

PxString8
pxSourcePeekString8(PxSource self, PxArena* arena, pxiword length);

pxiword
pxSourcePeekUnicode(PxSource self, pxi32* value);

#endif // PX_CORE_STREAM_SOURCE_H
