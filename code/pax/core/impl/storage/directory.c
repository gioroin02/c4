#ifndef PAX_CORE_STORAGE_SYSTEM_C
#define PAX_CORE_STORAGE_SYSTEM_C

#include "./directory.h"

#if PAX_SYSTEM == PAX_SYSTEM_WINDOWS

    #include "../../win32/storage/directory.c"

    #define __pax_current_directory_memory8__ pax_win32_current_directory_memory8
    #define __pax_current_directory__         pax_win32_current_directory

#elif PAX_SYSTEM == PAX_SYSTEM_LINUX

    #include "../../linux/storage/directory.c"

    #define __pax_current_directory_memory8__ pax_linux_current_directory_memory8
    #define __pax_current_directory__         pax_linux_current_directory

#else

    #error "Unknown platform"

#endif

paxiword
pax_current_directory_memory8(Pax_Arena* arena, paxu8* memory, paxiword length)
{
    return __pax_current_directory_memory8__(arena, memory, length);
}

Pax_String8
pax_current_directory(Pax_Arena* arena, paxiword length)
{
    return __pax_current_directory__(arena, length);
}

#endif // PAX_CORE_STORAGE_SYSTEM_C
