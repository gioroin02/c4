#ifndef PX_STREAM_WRITER_H
#define PX_STREAM_WRITER_H

#include "buffer8.h"

typedef pxiword (PxWriterProc) (void*, PxBuffer8*);

typedef struct PxWriter
{
    PxBuffer8 buffer;

    void* ctxt;
    void* proc;
}
PxWriter;

PxWriter
pxBufferWriter(PxBuffer8* self, PxArena* arena, pxiword length);

pxiword
pxWriterFlush(PxWriter* self);

pxiword
pxWriterByte(PxWriter* self, pxu8 value);

pxiword
pxWriterString8(PxWriter* self, PxString8 value);

pxiword
pxWriterString16(PxWriter* self, PxString16 value);

pxiword
pxWriterString32(PxWriter* self, PxString32 value);

pxiword
pxWriterBuffer8(PxWriter* self, PxBuffer8* value);

pxiword
pxWriterUnicode(PxWriter* self, PxArena* arena, pxi32 value);

pxiword
pxWriterUnsigned8(PxWriter* self, PxArena* arena, pxuword radix, PxFormatOption option, pxu8 value);

pxiword
pxWriterUnsigned16(PxWriter* self, PxArena* arena, pxuword radix, PxFormatOption option, pxu16 value);

pxiword
pxWriterUnsigned32(PxWriter* self, PxArena* arena, pxuword radix, PxFormatOption option, pxu32 value);

pxiword
pxWriterUnsigned64(PxWriter* self, PxArena* arena, pxuword radix, PxFormatOption option, pxu64 value);

pxiword
pxWriterUnsigned(PxWriter* self, PxArena* arena, pxuword radix, PxFormatOption option, pxuword value);

pxiword
pxWriterInteger8(PxWriter* self, PxArena* arena, pxuword radix, PxFormatOption option, pxi8 value);

pxiword
pxWriterInteger16(PxWriter* self, PxArena* arena, pxuword radix, PxFormatOption option, pxi16 value);

pxiword
pxWriterInteger32(PxWriter* self, PxArena* arena, pxuword radix, PxFormatOption option, pxi32 value);

pxiword
pxWriterInteger64(PxWriter* self, PxArena* arena, pxuword radix, PxFormatOption option, pxi64 value);

pxiword
pxWriterInteger(PxWriter* self, PxArena* arena, pxuword radix, PxFormatOption option, pxiword value);

pxiword
pxWriterMemory(PxWriter* self, void* memory, pxiword amount, pxiword stride);

#endif // PX_STREAM_WRITER_H
