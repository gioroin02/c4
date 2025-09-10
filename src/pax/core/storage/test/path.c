#include "../export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    PxArena arena = pxMemoryReserve(16);

    PxPath path = pxStorageCurrentDirectoryPath(&arena);

    for (PxPathNode* n = path.head; n != 0; n = n->next) {
        for (pxiword i = 0; i < n->length; i += 1)
            printf("%c", pxCast(pxi8, n->memory[i]));

        if (n->next != 0)
            printf(" - ");
    }
    printf("\n");

    PxString8 string = pxStorageCurrentDirectory(&arena);

    printf("%s\n", string.memory);

    pxPathInsertString8(&path, &arena, pxs8(".."), pxs8("/"));

    string = pxString8FromPath(&arena, &path, pxs8("/"));

    printf("%s\n", string.memory);
}
