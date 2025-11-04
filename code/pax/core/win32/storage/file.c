#ifndef PAX_WIN32_STORAGE_FILE_C
#define PAX_WIN32_STORAGE_FILE_C

#include "./file.h"

#define NOMINMAX
#define NOGDI
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

struct Pax_Win32_File
{
    HANDLE handle;
};

Pax_Win32_File*
pax_win32_default_input(Pax_Arena* arena)
{
    paxiword mark = pax_arena_tell(arena);

    Pax_Win32_File* result =
        pax_arena_reserve(arena, Pax_Win32_File, 1);

    if (result != 0) {
        result->handle = GetStdHandle(STD_INPUT_HANDLE);

        if (result->handle != INVALID_HANDLE_VALUE)
            return result;
    }

    pax_arena_rewind(arena, mark, 0);

    return 0;
}

Pax_Win32_File*
pax_win32_default_output(Pax_Arena* arena)
{
    paxiword mark = pax_arena_tell(arena);

    Pax_Win32_File* result =
        pax_arena_reserve(arena, Pax_Win32_File, 1);

    if (result != 0) {
        result->handle = GetStdHandle(STD_OUTPUT_HANDLE);

        if (result->handle != INVALID_HANDLE_VALUE)
            return result;
    }

    pax_arena_rewind(arena, mark, 0);

    return 0;
}

Pax_Win32_File*
pax_win32_default_error(Pax_Arena* arena)
{
    paxiword mark = pax_arena_tell(arena);

    Pax_Win32_File* result =
        pax_arena_reserve(arena, Pax_Win32_File, 1);

    if (result != 0) {
        result->handle = GetStdHandle(STD_OUTPUT_HANDLE);

        if (result->handle != INVALID_HANDLE_VALUE)
            return result;
    }

    pax_arena_rewind(arena, mark, 0);

    return 0;
}

Pax_Win32_File*
pax_win32_file_create(Pax_Arena* arena, Pax_String8 base, Pax_String8 name, Pax_File_Mode mode)
{
    paxiword mark   = pax_arena_tell(arena);
    paxiword access = 0;

    if ((mode & PAX_FILE_MODE_RD) != 0) access |= GENERIC_READ;
    if ((mode & PAX_FILE_MODE_WR) != 0) access |= GENERIC_WRITE;

    Pax_Win32_File* result = pax_arena_reserve(arena, Pax_Win32_File, 1);

    if (result != 0) {
        paxiword offset = pax_arena_tell(arena) - mark;
        Pax_Path path   = pax_path_create(arena, base.length + name.length);

        pax_path_insert_string8(&path, base, pax_str8("/"));
        pax_path_insert_string8(&path, name, pax_str8("/"));

        Pax_String16 string =
            pax_string16_from_path(arena, &path, PAX_ASCII_BACK_SLASH);

        if (string.length > 0) {
            wchar_t* memory = pax_as(wchar_t*, string.memory);

            result->handle = CreateFileW(memory, access, FILE_SHARE_READ,
                0, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, 0);

            pax_arena_rewind(arena, mark, offset);

            if (result->handle != INVALID_HANDLE_VALUE)
                return result;
        }
    }

    pax_arena_rewind(arena, mark, 0);

    return 0;
}

Pax_Win32_File*
pax_win32_file_replace(Pax_Arena* arena, Pax_String8 base, Pax_String8 name, Pax_File_Mode mode)
{
    paxiword mark   = pax_arena_tell(arena);
    paxiword access = 0;

    if ((mode & PAX_FILE_MODE_RD) != 0) access |= GENERIC_READ;
    if ((mode & PAX_FILE_MODE_WR) != 0) access |= GENERIC_WRITE;

    Pax_Win32_File* result = pax_arena_reserve(arena, Pax_Win32_File, 1);

    if (result != 0) {
        paxiword offset = pax_arena_tell(arena) - mark;
        Pax_Path path   = pax_path_create(arena, base.length + name.length);

        pax_path_insert_string8(&path, base, pax_str8("/"));
        pax_path_insert_string8(&path, name, pax_str8("/"));

        Pax_String16 string =
            pax_string16_from_path(arena, &path, PAX_ASCII_BACK_SLASH);

        if (string.length > 0) {
            wchar_t* memory = pax_as(wchar_t*, string.memory);

            result->handle = CreateFileW(memory, access, FILE_SHARE_READ,
                0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);

            pax_arena_rewind(arena, mark, offset);

            if (result->handle != INVALID_HANDLE_VALUE)
                return result;
        }
    }

    pax_arena_rewind(arena, mark, 0);

    return 0;
}

Pax_Win32_File*
pax_win32_file_open(Pax_Arena* arena, Pax_String8 base, Pax_String8 name, Pax_File_Mode mode)
{
    paxiword mark   = pax_arena_tell(arena);
    paxiword access = 0;

    if ((mode & PAX_FILE_MODE_RD) != 0) access |= GENERIC_READ;
    if ((mode & PAX_FILE_MODE_WR) != 0) access |= GENERIC_WRITE;

    Pax_Win32_File* result = pax_arena_reserve(arena, Pax_Win32_File, 1);

    if (result != 0) {
        paxiword offset = pax_arena_tell(arena) - mark;
        Pax_Path path   = pax_path_create(arena, base.length + name.length);

        pax_path_insert_string8(&path, base, pax_str8("/"));
        pax_path_insert_string8(&path, name, pax_str8("/"));

        Pax_String16 string =
            pax_string16_from_path(arena, &path, PAX_ASCII_BACK_SLASH);

        if (string.length > 0) {
            wchar_t* memory = pax_as(wchar_t*, string.memory);

            result->handle = CreateFileW(memory, access, FILE_SHARE_READ,
                0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

            pax_arena_rewind(arena, mark, offset);

            if (result->handle != INVALID_HANDLE_VALUE)
                return result;
        }
    }

    pax_arena_rewind(arena, mark, 0);

    return 0;
}

void
pax_win32_file_close(Pax_Win32_File* self)
{
    if (self == 0 || self->handle == INVALID_HANDLE_VALUE)
        return;

    CloseHandle(self->handle);

    self->handle = INVALID_HANDLE_VALUE;
}

paxb8
pax_win32_file_destroy(Pax_Arena* arena, Pax_String8 base, Pax_String8 name)
{
    paxiword mark = pax_arena_tell(arena);
    Pax_Path path = pax_path_create(arena, PAX_MEMORY_KIB);

    pax_path_insert_string8(&path, base, pax_str8("/"));
    pax_path_insert_string8(&path, name, pax_str8("/"));

    Pax_String16 string =
        pax_string16_from_path(arena, &path, PAX_ASCII_BACK_SLASH);

    if (string.length > 0) {
        paxb8 result =
            DeleteFileW(pax_as(wchar_t*, string.memory));

        pax_arena_rewind(arena, mark, 0);

        if (result != 0) return 1;
    }

    pax_arena_rewind(arena, mark, 0);

    return 0;
}

paxiword
pax_win32_file_write(Pax_Win32_File* self, paxu8* memory, paxiword length)
{
    DWORD temp = 0;

    for (paxiword i = 0; i < length;) {
        char* mem = pax_as(char*, memory + i);
        int   len = pax_as(int,   length - i);

        paxb32 state = WriteFile(self->handle, mem, len, &temp, 0);

        if (state != 0 && temp > 0 && temp <= length - i)
            i += temp;
        else
            return i;
    }

    return length;
}

paxiword
pax_win32_file_read(Pax_Win32_File* self, paxu8* memory, paxiword length)
{
    DWORD temp = 0;

    char* mem = pax_as(char*, memory);
    int   len = pax_as(int,   length);

    paxb32 state = ReadFile(self->handle, mem, len, &temp, 0);

    if (state != 0 && temp > 0 && temp <= length)
        return temp;

    return 0;
}

#endif // PAX_WIN32_STORAGE_FILE_C
