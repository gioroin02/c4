#ifndef PX_CORE_STORAGE_SYSTEM_C
#define PX_CORE_STORAGE_SYSTEM_C

#include "directory.h"

#if PX_SYSTEM == PX_SYSTEM_WINDOWS

    #include "../../windows/storage/directory.c"

    #define __pxStorageCurrentDirectoryPath__ pxWindowsStorageCurrentDirectoryPath
    #define __pxStorageCurrentDirectory__     pxWindowsStorageCurrentDirectory

#elif PX_SYSTEM == PX_SYSTEM_LINUX

    #include "../../linux/storage/directory.c"

    #define __pxStorageCurrentDirectoryPath__ pxLinuxStorageCurrentDirectoryPath
    #define __pxStorageCurrentDirectory__     pxLinuxStorageCurrentDirectory

#else

    #error "Unknown platform"

#endif

PxPath
pxStorageCurrentDirectoryPath(PxArena* arena)
{
    return __pxStorageCurrentDirectoryPath__(arena);
}

PxString8
pxStorageCurrentDirectory(PxArena* arena)
{
    return __pxStorageCurrentDirectory__(arena);
}

#endif // PX_CORE_STORAGE_SYSTEM_C
