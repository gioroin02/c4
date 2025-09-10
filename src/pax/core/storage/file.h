#ifndef PX_CORE_STORAGE_FILE_H
#define PX_CORE_STORAGE_FILE_H

#include "attribute.h"

typedef void* PxFile;

PxFile
pxStandardInput(PxArena* arena);

PxFile
pxStandardOutput(PxArena* arena);

PxFile
pxStandardError(PxArena* arena);

PxFile
pxFileCreate(PxArena* arena, PxString8 base, PxString8 name, PxFileMode mode);

PxFile
pxFileReplace(PxArena* arena, PxString8 base, PxString8 name, PxFileMode mode);

PxFile
pxFileOpen(PxArena* arena, PxString8 base, PxString8 name, PxFileMode mode);

void
pxFileClose(PxFile self);

pxb8
pxFileDestroy(PxFile self, PxArena* arena);

pxb8
pxFileDelete(PxArena* arena, PxString8 base, PxString8 name);

pxiword
pxFileWrite(PxFile self, PxBuffer8* buffer);

pxiword
pxFileWriteMemory(PxFile self, void* memory, pxiword amount, pxiword stride);

pxiword
pxFileRead(PxFile self, PxBuffer8* buffer);

pxiword
pxFileReadMemory(PxFile self, void* memory, pxiword amount, pxiword stride);

PxWriter
pxFileWriter(PxFile self, PxArena* arena, pxiword length);

PxReader
pxFileReader(PxFile self, PxArena* arena, pxiword length);

#endif // PX_CORE_STORAGE_FILE_H
