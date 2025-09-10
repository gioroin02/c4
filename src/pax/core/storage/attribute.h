#ifndef PX_CORE_STORAGE_ATTRIBUTE_H
#define PX_CORE_STORAGE_ATTRIBUTE_H

#include "import.h"

typedef enum PxFileMode
{
    PX_FILE_MODE_NONE  = 0x0,
    PX_FILE_MODE_READ  = 0x1,
    PX_FILE_MODE_WRITE = 0x2,
    PX_FILE_MODE_EXEC  = 0x4,
    PX_FILE_MODE_FULL  = 0x7,
}
PxFileMode;

typedef enum PxFileType
{
    PX_FILE_NONE,
    PX_FILE_SIMPLE,
    PX_FILE_DIRECTORY,
}
PxFileType;

#endif // PX_CORE_STORAGE_ATTRIBUTE_H
