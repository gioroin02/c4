#ifndef PAX_CORE_STORAGE_FILE_C
#define PAX_CORE_STORAGE_FILE_C

#include "./file.h"

#if PAX_SYSTEM == PAX_SYSTEM_WINDOWS

    #include "../../win32/storage/file.c"

    #define __pax_default_input__  pax_win32_default_input
    #define __pax_default_output__ pax_win32_default_output
    #define __pax_default_error__  pax_win32_default_error

    #define __pax_file_create__  pax_win32_file_create
    #define __pax_file_replace__ pax_win32_file_replace
    #define __pax_file_open__    pax_win32_file_open
    #define __pax_file_close__   pax_win32_file_close
    #define __pax_file_destroy__ pax_win32_file_destroy
    #define __pax_file_write__   pax_win32_file_write
    #define __pax_file_read__    pax_win32_file_read

#elif PAX_SYSTEM == PAX_SYSTEM_LINUX

    #include "../../linux/storage/file.c"

    #define __pax_default_input__  pax_linux_default_input
    #define __pax_default_output__ pax_linux_default_output
    #define __pax_default_error__  pax_linux_default_error

    #define __pax_file_create__  pax_linux_file_create
    #define __pax_file_replace__ pax_linux_file_replace
    #define __pax_file_open__    pax_linux_file_open
    #define __pax_file_close__   pax_linux_file_close
    #define __pax_file_destroy__ pax_linux_file_destroy
    #define __pax_file_write__   pax_linux_file_write
    #define __pax_file_read__    pax_linux_file_read

#else

    #error "Unknown platform"

#endif

Pax_File
pax_default_input(Pax_Arena* arena)
{
    return __pax_default_input__(arena);
}

Pax_File
pax_default_output(Pax_Arena* arena)
{
    return __pax_default_output__(arena);
}

Pax_File
pax_default_error(Pax_Arena* arena)
{
    return __pax_default_error__(arena);
}

Pax_File
pax_file_create(Pax_Arena* arena, Pax_String8 base, Pax_String8 name, Pax_File_Mode mode)
{
    return __pax_file_create__(arena, base, name, mode);
}

Pax_File
pax_file_replace(Pax_Arena* arena, Pax_String8 base, Pax_String8 name, Pax_File_Mode mode)
{
    return __pax_file_replace__(arena, base, name, mode);
}

Pax_File
pax_file_open(Pax_Arena* arena, Pax_String8 base, Pax_String8 name, Pax_File_Mode mode)
{
    return __pax_file_open__(arena, base, name, mode);
}

void
pax_file_close(Pax_File self)
{
    __pax_file_close__(self);
}

paxb8
pax_file_destroy(Pax_Arena* arena, Pax_String8 base, Pax_String8 name)
{
    return __pax_file_destroy__(arena, base, name);
}

paxiword
pax_file_write(Pax_File self, paxu8* memory, paxiword length)
{
    return __pax_file_write__(self, memory, length);
}

paxiword
pax_file_read(Pax_File self, paxu8* memory, paxiword length)
{
    return __pax_file_read__(self, memory, length);
}

Pax_Source*
pax_source_from_file(Pax_Arena* arena, Pax_File self)
{
    Pax_Source result = {0};

    if (self == 0) return 0;

    result.ctxt = self;
    result.proc = &pax_file_read;

    return pax_arena_clone(arena, Pax_Source, &result, 1);
}

Pax_Target*
pax_target_from_file(Pax_Arena* arena, Pax_File self)
{
    Pax_Target result = {0};

    if (self == 0) return 0;

    result.ctxt = self;
    result.proc = &pax_file_write;

    return pax_arena_clone(arena, Pax_Target, &result, 1);
}

#endif // PAX_CORE_STORAGE_FILE_C
