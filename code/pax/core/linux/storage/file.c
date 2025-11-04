#ifndef PAX_LINUX_STORAGE_FILE_C
#define PAX_LINUX_STORAGE_FILE_C

#include "./file.h"

#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

struct Pax_Linux_File
{
    int handle;
};

Pax_Linux_File*
pax_linux_default_input(Pax_Arena* arena)
{
    paxiword mark = pax_arena_tell(arena);

    Pax_Linux_File* result =
        pax_arena_reserve(arena, Pax_Linux_File, 1);

    if (result != 0) {
        result->handle = STDIN_FILENO;

        if (result->handle != -1)
            return result;
    }

    pax_arena_rewind(arena, mark, 0);

    return 0;
}

Pax_Linux_File*
pax_linux_default_output(Pax_Arena* arena)
{
    paxiword mark = pax_arena_tell(arena);

    Pax_Linux_File* result =
        pax_arena_reserve(arena, Pax_Linux_File, 1);

    if (result != 0) {
        result->handle = STDOUT_FILENO;

        if (result->handle != -1)
            return result;
    }

    pax_arena_rewind(arena, mark, 0);

    return 0;
}

Pax_Linux_File*
pax_linux_default_error(Pax_Arena* arena)
{
    paxiword mark = pax_arena_tell(arena);

    Pax_Linux_File* result =
        pax_arena_reserve(arena, Pax_Linux_File, 1);

    if (result != 0) {
        result->handle = STDERR_FILENO;

        if (result->handle != -1)
            return result;
    }

    pax_arena_rewind(arena, mark, 0);

    return 0;
}

Pax_Linux_File*
pax_linux_file_create(Pax_Arena* arena, Pax_String8 base, Pax_String8 name, Pax_File_Mode mode)
{
    paxiword mark   = pax_arena_tell(arena);
    paxiword access = O_CREAT | O_EXCL;

    if ((mode & PAX_FILE_MODE_RD_WR) == PAX_FILE_MODE_RD_WR)
        access |= O_RDWR;

    if ((mode & PAX_FILE_MODE_RD) != 0) access |= O_RDONLY;
    if ((mode & PAX_FILE_MODE_WR) != 0) access |= O_WRONLY;

    Pax_Linux_File* result = pax_arena_reserve(arena, Pax_Linux_File, 1);

    if (result != 0) {
        paxiword offset = pax_arena_tell(arena) - mark;
        Pax_Path path   = pax_path_create(arena, PAX_MEMORY_KIB);

        pax_path_insert_string8(&path, base, pax_str8("/"));
        pax_path_insert_string8(&path, name, pax_str8("/"));

        Pax_String8 string =
            pax_string8_from_path(arena, &path, PAX_ASCII_SLASH);

        if (string.length > 0) {
            result->handle = open(string.memory, access, 0644);

            pax_arena_rewind(arena, mark, offset);

            if (result->handle != -1)
                return result;
        }
    }

    pax_arena_rewind(arena, mark, 0);

    return 0;
}

Pax_Linux_File*
pax_linux_file_replace(Pax_Arena* arena, Pax_String8 base, Pax_String8 name, Pax_File_Mode mode)
{
    paxiword mark   = pax_arena_tell(arena);
    paxiword access = O_CREAT | O_TRUNC;

    if ((mode & PAX_FILE_MODE_RD_WR) == PAX_FILE_MODE_RD_WR)
        access |= O_RDWR;

    if ((mode & PAX_FILE_MODE_RD) != 0) access |= O_RDONLY;
    if ((mode & PAX_FILE_MODE_WR) != 0) access |= O_WRONLY;

    Pax_Linux_File* result = pax_arena_reserve(arena, Pax_Linux_File, 1);

    if (result != 0) {
        paxiword offset = pax_arena_tell(arena) - mark;
        Pax_Path path   = pax_path_create(arena, PAX_MEMORY_KIB);

        pax_path_insert_string8(&path, base, pax_str8("/"));
        pax_path_insert_string8(&path, name, pax_str8("/"));

        Pax_String8 string =
            pax_string8_from_path(arena, &path, PAX_ASCII_SLASH);

        if (string.length > 0) {
            result->handle = open(string.memory, access, 0644);

            pax_arena_rewind(arena, mark, offset);

            if (result->handle != -1)
                return result;
        }
    }

    pax_arena_rewind(arena, mark, 0);

    return 0;
}

Pax_Linux_File*
pax_linux_file_open(Pax_Arena* arena, Pax_String8 base, Pax_String8 name, Pax_File_Mode mode)
{
    paxiword mark   = pax_arena_tell(arena);
    paxiword access = O_APPEND;

    if ((mode & PAX_FILE_MODE_RD_WR) == PAX_FILE_MODE_RD_WR)
        access |= O_RDWR;

    if ((mode & PAX_FILE_MODE_RD) != 0) access |= O_RDONLY;
    if ((mode & PAX_FILE_MODE_WR) != 0) access |= O_WRONLY;

    Pax_Linux_File* result = pax_arena_reserve(arena, Pax_Linux_File, 1);

    if (result != 0) {
        paxiword offset = pax_arena_tell(arena) - mark;
        Pax_Path path   = pax_path_create(arena, PAX_MEMORY_KIB);

        pax_path_insert_string8(&path, base, pax_str8("/"));
        pax_path_insert_string8(&path, name, pax_str8("/"));

        Pax_String8 string =
            pax_string8_from_path(arena, &path, PAX_ASCII_SLASH);

        if (string.length > 0) {
            result->handle = open(string.memory, access, 0644);

            pax_arena_rewind(arena, mark, offset);

            if (result->handle != -1)
                return result;
        }
    }

    pax_arena_rewind(arena, mark, 0);

    return 0;
}

void
pax_linux_file_close(Pax_Linux_File* self)
{
    if (self == 0 || self->handle == -1)
        return;

    paxiword result = 0;

    do {
        result = close(self->handle);
    } while (result == -1 && errno == EINTR);

    self->handle = -1;
}

paxb8
pax_linux_file_destroy(Pax_Arena* arena, Pax_String8 base, Pax_String8 name)
{
    paxiword mark = pax_arena_tell(arena);
    Pax_Path path = pax_path_create(arena, base.length + name.length);

    pax_path_insert_string8(&path, base, pax_str8("/"));
    pax_path_insert_string8(&path, name, pax_str8("/"));

    Pax_String8 string =
        pax_string8_from_path(arena, &path, PAX_ASCII_SLASH);

    if (string.length > 0) {
        paxiword result = unlink(string.memory);

        pax_arena_rewind(arena, mark, 0);

        if (result != -1) return 1;
    }

    pax_arena_rewind(arena, mark, 0);

    return 0;
}

paxiword
pax_linux_file_write(Pax_Linux_File* self, paxu8* memory, paxiword length)
{
    paxiword temp = 0;

    for (paxiword i = 0; i < length;) {
        char* mem = pax_as(char*, memory + i);
        int   len = pax_as(int,   length - i);

        do {
            temp = write(self->handle, mem, len);
        } while (temp == -1 && errno == EINTR);

        if (temp > 0 && temp <= length - i)
            i += temp;
        else
            return i;
    }

    return length;
}

paxiword
pax_linux_file_read(Pax_Linux_File* self, paxu8* memory, paxiword length)
{
    paxiword temp = 0;

    char* mem = pax_as(char*, memory);
    int   len = pax_as(int,   length);

    do {
        temp = read(self->handle, mem, len);
    } while (temp == -1 && errno == EINTR);

    if (temp > 0 && temp <= length)
        return temp;

    return 0;
}

#endif // PAX_LINUX_STORAGE_FILE_C
