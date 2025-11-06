#ifndef PX_LINUX_STORAGE_FILE_C
#define PX_LINUX_STORAGE_FILE_C

#include "file.h"

#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

struct PxLinuxFile
{
    int handle;
};

PxLinuxFile*
pxLinuxStandardInput(PxArena* arena)
{
    pxiword offset = pxArenaOffset(arena);

    PxLinuxFile* result =
        pxArenaReserve(arena, PxLinuxFile, 1);

    if (result != 0) {
        result->handle = STDIN_FILENO;

        if (result->handle != -1)
            return result;
    }

    pxArenaRewind(arena, offset);

    return 0;
}

PxLinuxFile*
pxLinuxStandardOutput(PxArena* arena)
{
    pxiword offset = pxArenaOffset(arena);

    PxLinuxFile* result =
        pxArenaReserve(arena, PxLinuxFile, 1);

    if (result != 0) {
        result->handle = STDOUT_FILENO;

        if (result->handle != -1)
            return result;
    }

    pxArenaRewind(arena, offset);

    return 0;
}

PxLinuxFile*
pxLinuxStandardError(PxArena* arena)
{
    pxiword offset = pxArenaOffset(arena);

    PxLinuxFile* result =
        pxArenaReserve(arena, PxLinuxFile, 1);

    if (result != 0) {
        result->handle = STDERR_FILENO;

        if (result->handle != -1)
            return result;
    }

    pxArenaRewind(arena, offset);

    return 0;
}

PxLinuxFile*
pxLinuxFileCreate(PxArena* arena, PxString8 base, PxString8 name, PxFileMode mode)
{
    pxiword offset = pxArenaOffset(arena);
    pxiword access = O_CREAT | O_EXCL;

    if ((mode & PX_FILE_MODE_RD_WR) == PX_FILE_MODE_RD_WR)
        access |= O_RDWR;

    if ((mode & PX_FILE_MODE_RD) != 0) access |= O_RDONLY;
    if ((mode & PX_FILE_MODE_WR) != 0) access |= O_WRONLY;

    PxLinuxFile* result = pxArenaReserve(arena, PxLinuxFile, 1);

    if (result != 0) {
        pxiword temp = pxArenaOffset(arena);
        PxPath  path = pxPathFromString8(arena, base, pxs8("/"));

        pxPathInsertString8(&path, arena, name, pxs8("/"));

        PxString8 string =
            pxString8FromPath(arena, &path, pxs8("/"));

        if (string.length > 0) {
            result->handle = open(string.memory, access, 0644);

            pxArenaRewind(arena, temp);

            if (result->handle != -1)
                return result;
        }
    }

    pxArenaRewind(arena, offset);

    return 0;
}

PxLinuxFile*
pxLinuxFileReplace(PxArena* arena, PxString8 base, PxString8 name, PxFileMode mode)
{
    pxiword offset = pxArenaOffset(arena);
    pxiword access = O_CREAT | O_TRUNC;

    if ((mode & PX_FILE_MODE_RD_WR) == PX_FILE_MODE_RD_WR)
        access |= O_RDWR;

    if ((mode & PX_FILE_MODE_RD) != 0) access |= O_RDONLY;
    if ((mode & PX_FILE_MODE_WR) != 0) access |= O_WRONLY;

    PxLinuxFile* result = pxArenaReserve(arena, PxLinuxFile, 1);

    if (result != 0) {
        pxiword temp = pxArenaOffset(arena);
        PxPath  path = pxPathFromString8(arena, base, pxs8("/"));

        pxPathInsertString8(&path, arena, name, pxs8("/"));

        PxString8 string =
            pxString8FromPath(arena, &path, pxs8("/"));

        if (string.length > 0) {
            result->handle = open(string.memory, access, 0644);

            pxArenaRewind(arena, temp);

            if (result->handle != -1)
                return result;
        }
    }

    pxArenaRewind(arena, offset);

    return 0;
}

PxLinuxFile*
pxLinuxFileOpen(PxArena* arena, PxString8 base, PxString8 name, PxFileMode mode)
{
    pxiword offset = pxArenaOffset(arena);
    pxiword access = O_APPEND;

    if ((mode & PX_FILE_MODE_RD_WR) == PX_FILE_MODE_RD_WR)
        access |= O_RDWR;

    if ((mode & PX_FILE_MODE_RD) != 0) access |= O_RDONLY;
    if ((mode & PX_FILE_MODE_WR) != 0) access |= O_WRONLY;

    PxLinuxFile* result = pxArenaReserve(arena, PxLinuxFile, 1);

    if (result != 0) {
        pxiword temp = pxArenaOffset(arena);
        PxPath  path = pxPathFromString8(arena, base, pxs8("/"));

        pxPathInsertString8(&path, arena, name, pxs8("/"));

        PxString8 string =
            pxString8FromPath(arena, &path, pxs8("/"));

        if (string.length > 0) {
            result->handle = open(string.memory, access, 0644);

            pxArenaRewind(arena, temp);

            if (result->handle != -1)
                return result;
        }
    }

    pxArenaRewind(arena, offset);

    return 0;
}

void
pxLinuxFileClose(PxLinuxFile* self)
{
    if (self == 0 || self->handle == -1)
        return;

    pxiword result = 0;

    do {
        result = close(self->handle);
    } while (result == -1 && errno == EINTR);

    self->handle = -1;
}

pxb8
pxLinuxFileDestroy(PxArena* arena, PxString8 base, PxString8 name)
{
    pxiword offset = pxArenaOffset(arena);
    PxPath  path   = pxPathFromString8(arena, base, pxs8("/"));

    pxPathInsertString8(&path, arena, name, pxs8("/"));

    PxString8 string =
        pxString8FromPath(arena, &path, pxs8("/"));

    if (string.length > 0) {
        pxiword result = unlink(string.memory);

        pxArenaRewind(arena, offset);

        if (result != -1) return 1;
    }

    pxArenaRewind(arena, offset);

    return 0;
}

pxiword
pxLinuxFileWrite(PxLinuxFile* self, pxu8* memory, pxiword length)
{
    pxiword temp = 0;

    for (pxiword i = 0; i < length;) {
        char* mem = px_as(char*, memory + i);
        int   len = px_as(int,   length - i);

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

pxiword
pxLinuxFileRead(PxLinuxFile* self, pxu8* memory, pxiword length)
{
    pxiword temp = 0;

    char* mem = px_as(char*, memory);
    int   len = px_as(int,   length);

    do {
        temp = read(self->handle, mem, len);
    } while (temp == -1 && errno == EINTR);

    if (temp > 0 && temp <= length)
        return temp;

    return 0;
}

#endif // PX_LINUX_STORAGE_FILE_C
