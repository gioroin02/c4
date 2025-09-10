#ifndef PX_CORE_STORAGE_FILE_C
#define PX_CORE_STORAGE_FILE_C

#include "file.h"

#if PX_SYSTEM == PX_SYSTEM_WINDOWS

    #include "../../windows/storage/file.c"

    #define __pxStandardInput__  pxWindowsStandardInput
    #define __pxStandardOutput__ pxWindowsStandardOutput
    #define __pxStandardError__  pxWindowsStandardError

    #define __pxFileCreate__      pxWindowsFileCreate
    #define __pxFileReplace__     pxWindowsFileReplace
    #define __pxFileOpen__        pxWindowsFileOpen
    #define __pxFileClose__       pxWindowsFileClose
    #define __pxFileDestroy__     pxWindowsFileDestroy
    #define __pxFileDelete__      pxWindowsFileDelete
    #define __pxFileWriteMemory__ pxWindowsFileWriteMemory
    #define __pxFileReadMemory__  pxWindowsFileReadMemory

#elif PX_SYSTEM == PX_SYSTEM_LINUX

    #include "../../linux/storage/file.c"

    #define __pxStandardInput__  pxLinuxStandardInput
    #define __pxStandardOutput__ pxLinuxStandardOutput
    #define __pxStandardError__  pxLinuxStandardError

    #define __pxFileCreate__      pxLinuxFileCreate
    #define __pxFileReplace__     pxLinuxFileReplace
    #define __pxFileOpen__        pxLinuxFileOpen
    #define __pxFileClose__       pxLinuxFileClose
    #define __pxFileDestroy__     pxLinuxFileDestroy
    #define __pxFileDelete__      pxLinuxFileDelete
    #define __pxFileWriteMemory__ pxLinuxFileWriteMemory
    #define __pxFileReadMemory__  pxLinuxFileReadMemory

#else

    #error "Unknown platform"

#endif

PxFile
pxStandardInput(PxArena* arena)
{
    return __pxStandardInput__(arena);
}

PxFile
pxStandardOutput(PxArena* arena)
{
    return __pxStandardOutput__(arena);
}

PxFile
pxStandardError(PxArena* arena)
{
    return __pxStandardError__(arena);
}

PxFile
pxFileCreate(PxArena* arena, PxString8 base, PxString8 name, PxFileMode mode)
{
    return __pxFileCreate__(arena, base, name, mode);
}

PxFile
pxFileReplace(PxArena* arena, PxString8 base, PxString8 name, PxFileMode mode)
{
    return __pxFileReplace__(arena, base, name, mode);
}

PxFile
pxFileOpen(PxArena* arena, PxString8 base, PxString8 name, PxFileMode mode)
{
    return __pxFileOpen__(arena, base, name, mode);
}

void
pxFileClose(PxFile self)
{
    __pxFileClose__(self);
}

pxb8
pxFileDestroy(PxFile self, PxArena* arena)
{
    return __pxFileDestroy__(self, arena);
}

pxb8
pxFileDelete(PxArena* arena, PxString8 base, PxString8 name)
{
    return __pxFileDelete__(arena, base, name);
}

pxiword
pxFileWrite(PxFile self, PxBuffer8* buffer)
{
    pxBuffer8Normalize(buffer);

    pxu8*   memory = buffer->memory;
    pxiword size   = buffer->size;

    if (size <= 0) return 0;

    pxiword temp = pxFileWriteMemory(self, memory, size, 1);

    buffer->size -= temp;
    buffer->head  = (buffer->head + temp) % buffer->length;

    return temp;
}

pxiword
pxFileWriteMemory(PxFile self, void* memory, pxiword amount, pxiword stride)
{
    return __pxFileWriteMemory__(self, memory, amount, stride);
}

pxiword
pxFileRead(PxFile self, PxBuffer8* buffer)
{
    pxBuffer8Normalize(buffer);

    pxu8*   memory = buffer->memory + buffer->size;
    pxiword size   = buffer->length - buffer->size;

    if (size <= 0) return 0;

    pxiword temp = pxFileReadMemory(self, memory, size, 1);

    buffer->size += temp;
    buffer->tail  = (buffer->tail + temp) % buffer->length;

    return temp;
}

pxiword
pxFileReadMemory(PxFile self, void* memory, pxiword amount, pxiword stride)
{
    return __pxFileReadMemory__(self, memory, amount, stride);
}

PxWriter
pxFileWriter(PxFile self, PxArena* arena, pxiword length)
{
    PxWriter result = {0};

    if (self == 0 || length <= 0) return result;

    result.buffer = pxBuffer8Reserve(arena, length);

    if (result.buffer.length > 0) {
        result.ctxt = self;
        result.proc = &pxFileWrite;
    }

    return result;
}

PxReader
pxFileReader(PxFile self, PxArena* arena, pxiword length)
{
    PxReader result = {0};

    if (self == 0 || length <= 0) return result;

    result.buffer = pxBuffer8Reserve(arena, length);

    if (result.buffer.length) {
        result.ctxt = self;
        result.proc = &pxFileRead;
    }

    return result;
}

#endif // PX_CORE_STORAGE_FILE_C
