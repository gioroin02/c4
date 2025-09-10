#include "../export.h"

#include <stdio.h>

int
main(int argc, char** argv)
{
    pxu8 memory[PX_MEMORY_KIB] = {0};

    PxArena arena = pxArenaMake(memory, pxSize(memory));

    PxStringList list = pxStringListFromString8(&arena,
        pxs8("lorem:ispum::dolor:sit:amet"), pxs8(":"));

    for (PxStringNode* n = list.head; n != 0; n = n->next)
        printf("%s -> ", n->memory);

    printf("\\\n");

    for (PxStringNode* n = list.tail; n != 0; n = n->prev)
        printf("%s -> ", n->memory);

    printf("\\\n");

    pxiword offset = pxArenaOffset(&arena);

    PxString16 string16 = pxString16FromStringList(&arena,
        &list, pxs16(L"|"), pxs16(L""), pxs16(L""));

    wprintf(L"%s\n", string16.memory);

    pxArenaRewind(&arena, offset);

    pxStringListRemoveHead(&list, 0);
    pxStringListRemoveTail(&list, 0);

    for (PxStringNode* n = list.head; n != 0; n = n->next)
        printf("%s -> ", n->memory);

    printf("\\\n");

    for (PxStringNode* n = list.tail; n != 0; n = n->prev)
        printf("%s -> ", n->memory);

    printf("\\\n");

    string16 = pxString16FromStringList(&arena,
        &list, pxs16(L"|"), pxs16(L""), pxs16(L""));

    wprintf(L"%s\n", string16.memory);
}
