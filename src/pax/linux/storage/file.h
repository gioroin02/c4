#ifndef PX_LINUX_STORAGE_FILE_H
#define PX_LINUX_STORAGE_FILE_H

#include "import.h"

typedef struct PxLinuxFile PxLinuxFile;

PxLinuxFile*
pxLinuxStandardInput(PxArena* arena);

PxLinuxFile*
pxLinuxStandardOutput(PxArena* arena);

PxLinuxFile*
pxLinuxStandardError(PxArena* arena);

PxLinuxFile*
pxLinuxFileCreate(PxArena* arena, PxString8 base, PxString8 name, PxFileMode mode);

PxLinuxFile*
pxLinuxFileReplace(PxArena* arena, PxString8 base, PxString8 name, PxFileMode mode);

PxLinuxFile*
pxLinuxFileOpen(PxArena* arena, PxString8 base, PxString8 name, PxFileMode mode);

void
pxLinuxFileClose(PxLinuxFile* self);

pxb8
pxLinuxFileDestroy(PxLinuxFile* self, PxArena* arena);

pxb8
pxLinuxFileDelete(PxArena* arena, PxString8 base, PxString8 name);

pxiword
pxLinuxFileWriteMemory(PxLinuxFile* self, void* memory, pxiword amount, pxiword stride);

pxiword
pxLinuxFileReadMemory(PxLinuxFile* self, void* memory, pxiword amount, pxiword stride);

#endif // PX_LINUX_STORAGE_FILE_H
