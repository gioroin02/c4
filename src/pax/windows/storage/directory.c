#ifndef PX_WINDOWS_STORAGE_DIRECTORY_C
#define PX_WINDOWS_STORAGE_DIRECTORY_C

#include "directory.h"

#define NOMINMAX
#define NOGDI
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

PxPath
pxWindowsStorageCurrentDirectoryPath(PxArena* arena)
{
    pxiword length = GetCurrentDirectoryW(0, 0);

    if (length <= 0) return (PxPath) {0};

    pxiword offset = pxArenaOffset(arena);
    pxu16*  result = pxArenaReserve(arena, pxu16, length);

    PxString16 string = {.memory = result, .length = length};

    if (result != 0) {
        pxiword size = GetCurrentDirectoryW(length, result);

        if (size + 1 == length)
            return pxPathFromString16(arena, string, pxs16(L"\\"));
    }

    pxArenaRewind(arena, offset);

    return (PxPath) {0};
}

PxString8
pxWindowsStorageCurrentDirectory(PxArena* arena)
{
    PxPath path =
        pxWindowsStorageCurrentDirectoryPath(arena);

    return pxString8FromPath(arena, &path, pxs8("/"));
}

#endif // PX_WINDOWS_STORAGE_DIRECTORY_C
