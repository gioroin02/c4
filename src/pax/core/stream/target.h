#ifndef PX_CORE_STREAM_TARGET_H
#define PX_CORE_STREAM_TARGET_H

#include "import.h"

typedef struct PxTarget
{
    void* ctxt;
    void* proc;

    PxBuffer8* buffer;
}
PxTarget;

typedef pxiword (PxTargetProc) (void*, pxu8*, pxiword);

PxTarget
pxBufferedTarget(PxTarget target, PxBuffer8* buffer);

PxTarget
pxTargetFromBuffer8(PxBuffer8* self);

pxiword
pxTargetFlush(PxTarget self);

pxiword
pxTargetWriteMemory8(PxTarget self, pxu8* memory, pxiword length);

pxiword
pxTargetWriteMemory16(PxTarget self, pxu16* memory, pxiword length);

pxiword
pxTargetWriteMemory32(PxTarget self, pxu32* memory, pxiword length);

pxiword
pxTargetWriteBuffer8(PxTarget self, PxBuffer8* value);

pxiword
pxTargetWriteBuffer16(PxTarget self, PxBuffer16* value);

pxiword
pxTargetWriteBuffer32(PxTarget self, PxBuffer32* value);

pxiword
pxTargetWriteByte(PxTarget self, pxu8 value);

pxiword
pxTargetWriteString8(PxTarget self, PxString8 value);

pxiword
pxTargetWriteString16(PxTarget self, PxString16 value);

pxiword
pxTargetWriteString32(PxTarget self, PxString32 value);

pxiword
pxTargetWriteUnicode(PxTarget self, pxi32 value);

#endif // PX_CORE_STREAM_TARGET_H
