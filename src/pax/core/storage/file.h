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
pxFileDestroy(PxArena* arena, PxString8 base, PxString8 name);

pxiword
pxFileWrite(PxFile self, pxu8* memory, pxiword length);

pxiword
pxFileRead(PxFile self, pxu8* memory, pxiword length);

PxSource
pxSourceFromFile(PxFile self);

PxTarget
pxTargetFromFile(PxFile self);

#endif // PX_CORE_STORAGE_FILE_H
