#ifndef PX_WINDOWS_STORAGE_FILE_H
#define PX_WINDOWS_STORAGE_FILE_H

#include "import.h"

typedef struct PxWindowsFile PxWindowsFile;

PxWindowsFile*
pxWindowsStandardInput(PxArena* arena);

PxWindowsFile*
pxWindowsStandardOutput(PxArena* arena);

PxWindowsFile*
pxWindowsStandardError(PxArena* arena);

PxWindowsFile*
pxWindowsFileCreate(PxArena* arena, PxString8 base, PxString8 name, PxFileMode mode);

PxWindowsFile*
pxWindowsFileReplace(PxArena* arena, PxString8 base, PxString8 name, PxFileMode mode);

PxWindowsFile*
pxWindowsFileOpen(PxArena* arena, PxString8 base, PxString8 name, PxFileMode mode);

void
pxWindowsFileClose(PxWindowsFile* self);

pxb8
pxWindowsFileDestroy(PxWindowsFile* self, PxArena* arena);

pxb8
pxWindowsFileDelete(PxArena* arena, PxString8 base, PxString8 name);

pxiword
pxWindowsFileWriteMemory(PxWindowsFile* self, void* memory, pxiword amount, pxiword stride);

pxiword
pxWindowsFileReadMemory(PxWindowsFile* self, void* memory, pxiword amount, pxiword stride);

#endif // PX_WINDOWS_STORAGE_FILE_H
