#ifndef PX_WINDOWS_STORAGE_FILE_C
#define PX_WINDOWS_STORAGE_FILE_C

#include "file.h"

#define NOMINMAX
#define NOGDI
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

struct PxWindowsFile
{
    HANDLE handle;
};

PxWindowsFile*
pxWindowsStandardInput(PxArena* arena)
{
    pxiword offset = pxArenaOffset(arena);

    PxWindowsFile* result =
        pxArenaReserve(arena, PxWindowsFile, 1);

    if (result != 0) {
        result->handle = GetStdHandle(STD_INPUT_HANDLE);

        if (result->handle != INVALID_HANDLE_VALUE)
            return result;
    }

    pxArenaRewind(arena, offset);

    return 0;
}

PxWindowsFile*
pxWindowsStandardOutput(PxArena* arena)
{
    pxiword offset = pxArenaOffset(arena);

    PxWindowsFile* result =
        pxArenaReserve(arena, PxWindowsFile, 1);

    if (result != 0) {
        result->handle = GetStdHandle(STD_OUTPUT_HANDLE);

        if (result->handle != INVALID_HANDLE_VALUE)
            return result;
    }

    pxArenaRewind(arena, offset);

    return 0;
}

PxWindowsFile*
pxWindowsStandardError(PxArena* arena)
{
    pxiword offset = pxArenaOffset(arena);

    PxWindowsFile* result =
        pxArenaReserve(arena, PxWindowsFile, 1);

    if (result != 0) {
        result->handle = GetStdHandle(STD_OUTPUT_HANDLE);

        if (result->handle != INVALID_HANDLE_VALUE)
            return result;
    }

    pxArenaRewind(arena, offset);

    return 0;
}

PxWindowsFile*
pxWindowsFileCreate(PxArena* arena, PxString8 base, PxString8 name, PxFileMode mode)
{
    pxiword offset = pxArenaOffset(arena);
    pxiword access = 0;

    if ((mode & PX_FILE_MODE_READ)  != 0) access |= GENERIC_READ;
    if ((mode & PX_FILE_MODE_WRITE) != 0) access |= GENERIC_WRITE;
    if ((mode & PX_FILE_MODE_EXEC)  != 0) access |= GENERIC_EXECUTE;

    PxWindowsFile* result = pxArenaReserve(arena, PxWindowsFile, 1);

    if (result != 0) {
        pxiword temp = pxArenaOffset(arena);
        PxPath  path = pxPathFromString8(arena, base, pxs8("/"));

        pxPathInsertString8(&path, arena, name, pxs8("/"));

        PxString16 string =
            pxString16FromPath(arena, &path, pxs16(L"\\"));

        if (string.length > 0) {
            wchar_t* memory = pxCast(wchar_t*, string.memory);

            result->handle = CreateFileW(memory, access, FILE_SHARE_READ,
                0, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, 0);

            pxArenaRewind(arena, temp);

            if (result->handle != INVALID_HANDLE_VALUE)
                return result;
        }
    }

    pxArenaRewind(arena, offset);

    return 0;
}

PxWindowsFile*
pxWindowsFileReplace(PxArena* arena, PxString8 base, PxString8 name, PxFileMode mode)
{
    pxiword offset = pxArenaOffset(arena);
    pxiword access = 0;

    if ((mode & PX_FILE_MODE_READ)  != 0) access |= GENERIC_READ;
    if ((mode & PX_FILE_MODE_WRITE) != 0) access |= GENERIC_WRITE;
    if ((mode & PX_FILE_MODE_EXEC)  != 0) access |= GENERIC_EXECUTE;

    PxWindowsFile* result = pxArenaReserve(arena, PxWindowsFile, 1);

    if (result != 0) {
        pxiword temp = pxArenaOffset(arena);
        PxPath  path = pxPathFromString8(arena, base, pxs8("/"));

        pxPathInsertString8(&path, arena, name, pxs8("/"));

        PxString16 string =
            pxString16FromPath(arena, &path, pxs16(L"\\"));

        if (string.length > 0) {
            wchar_t* memory = pxCast(wchar_t*, string.memory);

            result->handle = CreateFileW(memory, access, FILE_SHARE_READ,
                0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);

            pxArenaRewind(arena, temp);

            if (result->handle != INVALID_HANDLE_VALUE)
                return result;
        }
    }

    pxArenaRewind(arena, offset);

    return 0;
}

PxWindowsFile*
pxWindowsFileOpen(PxArena* arena, PxString8 base, PxString8 name, PxFileMode mode)
{
    pxiword offset = pxArenaOffset(arena);
    pxiword access = 0;

    if ((mode & PX_FILE_MODE_READ)  != 0) access |= GENERIC_READ;
    if ((mode & PX_FILE_MODE_WRITE) != 0) access |= GENERIC_WRITE;
    if ((mode & PX_FILE_MODE_EXEC)  != 0) access |= GENERIC_EXECUTE;

    PxWindowsFile* result = pxArenaReserve(arena, PxWindowsFile, 1);

    if (result != 0) {
        pxiword temp = pxArenaOffset(arena);
        PxPath  path = pxPathFromString8(arena, base, pxs8("/"));

        pxPathInsertString8(&path, arena, name, pxs8("/"));

        PxString16 string =
            pxString16FromPath(arena, &path, pxs16(L"\\"));

        if (string.length > 0) {
            wchar_t* memory = pxCast(wchar_t*, string.memory);

            result->handle = CreateFileW(memory, access, FILE_SHARE_READ,
                0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

            pxArenaRewind(arena, temp);

            if (result->handle != INVALID_HANDLE_VALUE)
                return result;
        }
    }

    pxArenaRewind(arena, offset);

    return 0;
}

void
pxWindowsFileClose(PxWindowsFile* self)
{
    if (self == 0 || self->handle == INVALID_HANDLE_VALUE)
        return;

    CloseHandle(self->handle);

    self->handle = INVALID_HANDLE_VALUE;
}

pxb8
pxWindowsFileDestroy(PxWindowsFile* self, PxArena* arena)
{
    if (self == 0 || self->handle == INVALID_HANDLE_VALUE)
        return 0;

    pxiword length = GetFinalPathNameByHandleW(
        self->handle, 0, 0, FILE_NAME_NORMALIZED);

    if (length <= 0) return 0;

    pxiword offset = pxArenaOffset(arena);
    pxu16*  memory = pxArenaReserve(arena, pxu16, length + 1);

    if (memory != 0) {
        pxiword size = GetFinalPathNameByHandleW(self->handle,
            memory, length, FILE_NAME_NORMALIZED);

        if (size + 1 == length) {
            CloseHandle(self->handle);

            pxb8 state = DeleteFileW(pxCast(wchar_t*, memory));

            pxArenaRewind(arena, offset);

            if (state != 0) return 1;
        }
    }

    pxArenaRewind(arena, offset);

    return 0;
}

pxb8
pxWindowsFileDelete(PxArena* arena, PxString8 base, PxString8 name)
{
    pxiword offset = pxArenaOffset(arena);
    PxPath  path   = pxPathFromString8(arena, base, pxs8("/"));

    pxPathInsertString8(&path, arena, name, pxs8("/"));

    PxString16 string =
        pxString16FromPath(arena, &path, pxs16(L"\\"));

    if (string.length > 0) {
        pxb8 result =
            DeleteFileW(pxCast(wchar_t*, string.memory));

        pxArenaRewind(arena, offset);

        if (result != 0) return 1;
    }

    pxArenaRewind(arena, offset);

    return 0;
}

pxiword
pxWindowsFileWriteMemory(PxWindowsFile* self, void* memory, pxiword amount, pxiword stride)
{
    pxiword length = amount * stride;
    DWORD   temp   = 0;

    for (pxiword i = 0; i < length;) {
        char* mem = pxCast(char*, memory + i);
        int   len = pxCast(int,   length - i);

        pxb32 state = WriteFile(self->handle, mem, len, &temp, 0);

        if (state != 0 && temp > 0 && temp <= length - i)
            i += temp;
        else
            return i;
    }

    return length;
}

pxiword
pxWindowsFileReadMemory(PxWindowsFile* self, void* memory, pxiword amount, pxiword stride)
{
    pxiword length = amount * stride;
    DWORD   temp   = 0;

    char* mem = pxCast(char*, memory);
    int   len = pxCast(int,   length);

    pxb32 state = ReadFile(self->handle, mem, len, &temp, 0);

    if (state != 0 && temp > 0 && temp <= length)
        return temp;

    return 0;
}

#endif // PX_WINDOWS_STORAGE_FILE_C
