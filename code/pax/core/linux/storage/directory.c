#ifndef PAX_LINUX_STORAGE_DIRECTORY_C
#define PAX_LINUX_STORAGE_DIRECTORY_C

#include "./directory.h"

#include <unistd.h>
#include <linux/limits.h>

paxiword
pax_linux_current_directory_memory8(Pax_Arena* arena, paxu8* memory, paxiword length)
{
    if (memory == 0 || length <= 0) return 0;

    paxiword stride = pax_size(paxu8);
    void*    temp   = getcwd(memory, length);

    if (temp == 0) return 0;

    Pax_String8 string =
        pax_string8_from_memory(memory, length, stride);

    return string.length;
}

Pax_String8
pax_linux_current_directory(Pax_Arena* arena, paxiword length)
{
    if (length <= 0) return (Pax_String8) {0};

    paxiword mark   = pax_arena_tell(arena);
    paxu8*   memory = pax_arena_reserve(arena, paxu8, length + 1);

    if (memory == 0) return (Pax_String8) {0};

    paxiword size =
        pax_linux_current_directory_memory8(arena, memory, length);

    if (size > 0 && size <= length) {
        Pax_String8 string =
            pax_string8_make(memory, size);

        pax_arena_rewind(arena, mark, size + 1);

        return string;
    }

    pax_arena_rewind(arena, mark, 0);

    return (Pax_String8) {0};
}

#endif // PAX_LINUX_STORAGE_DIRECTORY_C
