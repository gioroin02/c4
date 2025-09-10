#ifndef PX_LINUX_STORAGE_DIRECTORY_C
#define PX_LINUX_STORAGE_DIRECTORY_C

#include "directory.h"

#include <unistd.h>
#include <linux/limits.h>

PxPath
pxLinuxStorageCurrentDirectoryPath(PxArena* arena)
{
    pxiword length = PATH_MAX;

    if (length <= 0) return (PxPath) {0};

    pxiword offset = pxArenaOffset(arena);
    pxu8*   result = pxArenaReserve(arena, pxu8, length + 1);

    PxString8 string = {0};

    if (result != 0) {
        void* memory = getcwd(result, length);

        if (memory != 0) {
            string = pxString8FromMemory(memory, PATH_MAX);
            length = string.length;

            pxArenaRewind(arena, offset + length + 1);

            return pxPathFromString8(arena, string, pxs8("/"));
        }
    }

    pxArenaRewind(arena, offset);

    return (PxPath) {0};
}

PxString8
pxLinuxStorageCurrentDirectory(PxArena* arena)
{
    PxPath path =
        pxLinuxStorageCurrentDirectoryPath(arena);

    return pxString8FromPath(arena, &path, pxs8("/"));
}

#endif // PX_LINUX_STORAGE_DIRECTORY_C
