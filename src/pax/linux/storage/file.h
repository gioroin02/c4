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
pxLinuxFileDestroy(PxArena* arena, PxString8 base, PxString8 name);

pxiword
pxLinuxFileWrite(PxLinuxFile* self, pxu8* memory, pxiword length);

pxiword
pxLinuxFileRead(PxLinuxFile* self, pxu8* memory, pxiword length);

#endif // PX_LINUX_STORAGE_FILE_H
