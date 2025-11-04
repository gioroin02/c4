#ifndef PAX_WIN32_STORAGE_DIRECTORY_C
#define PAX_WIN32_STORAGE_DIRECTORY_C

#include "./directory.h"

#define NOMINMAX
#define NOGDI
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

paxiword
pax_win32_current_directory_memory8(Pax_Arena* arena, paxu8* memory, paxiword length)
{
    paxiword size = GetCurrentDirectoryW(0, 0);
    paxiword mark = pax_arena_tell(arena);

    if (memory == 0 || size <= 0 || length < size) return 0;

    paxu16* buffer = pax_arena_reserve(arena, paxu16, size);

    if (buffer == 0) return 0;

    GetCurrentDirectoryW(size, buffer);

    paxiword index  = 0;
    paxiword other  = 0;
    paxiword result = pax_utf8_units_from_memory16(buffer, size - 1);

    if (result <= 0 || result > length) return 0;

    while (index < size) {
        paxi32 unicode = 0;

        index += pax_utf16_read_forw(buffer, size,
            index, &unicode);

        if (unicode == PAX_ASCII_BACK_SLASH)
            unicode = PAX_ASCII_SLASH;

        other += pax_utf8_write_forw(memory, length,
            other, unicode);
    }

    pax_arena_rewind(arena, mark, 0);

    return result;
}

Pax_String8
pax_win32_current_directory(Pax_Arena* arena, paxiword length)
{
    if (length <= 0) return (Pax_String8) {0};

    paxiword mark   = pax_arena_tell(arena);
    paxu8*   memory = pax_arena_reserve(arena, paxu8, length + 1);

    if (memory == 0) return (Pax_String8) {0};

    paxiword size =
        pax_win32_current_directory_memory8(arena, memory, length);

    if (size > 0 && size <= length) {
        Pax_String8 string =
            pax_string8_make(memory, size);

        pax_arena_rewind(arena, mark, size + 1);

        return string;
    }

    pax_arena_rewind(arena, mark, 0);

    return (Pax_String8) {0};
}

#endif // PAX_WIN32_STORAGE_DIRECTORY_C
