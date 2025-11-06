#ifndef PX_CORE_STORAGE_PATH_C
#define PX_CORE_STORAGE_PATH_C

#include "path.h"

PxPath
pxPathFromString8(PxArena* arena, PxString8 string, PxString8 pivot)
{
    PxPath result = {0};

    pxPathInsertString8(&result, arena, string, pivot);

    return result;
}

PxPath
pxPathFromString16(PxArena* arena, PxString16 string, PxString16 pivot)
{
    PxPath result = {0};

    pxPathInsertString16(&result, arena, string, pivot);

    return result;
}

PxPath
pxPathFromString32(PxArena* arena, PxString32 string, PxString32 pivot)
{
    PxPath result = {0};

    pxPathInsertString32(&result, arena, string, pivot);

    return result;
}

pxb8
pxPathInsertNode(PxPath* self, PxPathNode* value)
{
    if (value == 0) return 0;

    PxPathNode* tail = self->tail;

    if (self->head == 0) self->head = value;

    if (self->tail != 0) {
        value->prev = tail;
        tail->next  = value;
    }

    self->tail  = value;
    self->size += 1;

    return 1;
}

PxPathNode*
pxPathRemoveNode(PxPath* self)
{
    if (self->size <= 0) return 0;

    PxPathNode* result = self->tail;

    if (self->head == self->tail)
        self->head = 0;

    PxPathNode* tail = self->tail->prev;

    self->tail  = tail;
    self->size -= 1;

    if (tail != 0) tail->next = 0;

    result->next = 0;
    result->prev = 0;

    return result;
}

pxb8
pxPathInsertString8(PxPath* self, PxArena* arena, PxString8 value, PxString8 pivot)
{
    pxiword offset = pxArenaOffset(arena);

    PxString8 left  = {0};
    PxString8 right = value;

    while (right.length > 0) {
        pxString8Split(right, pivot, &left, &right);

        pxiword   temp   = pxArenaOffset(arena);
        PxString8 string = pxString8Copy(arena, left);

        pxb8 curr = pxString8IsEqual(string, pxs8("."));
        pxb8 prev = pxString8IsEqual(string, pxs8(".."));

        if (curr != 0 || prev != 0) {
            pxArenaRewind(arena, temp);

            if (prev != 0) {
                if (self->size <= 0)
                    return 0;

                pxPathRemoveNode(self);
            }

            continue;
        }

        PxPathNode* node =
            pxArenaReserve(arena, PxPathNode, 1);

        if (string.length != left.length || node == 0)
            break;

        node->memory = string.memory;
        node->length = string.length;

        pxPathInsertNode(self, node);
    }

    if (right.length <= 0) return 1;

    pxArenaRewind(arena, offset);

    return 0;
}

pxb8
pxPathInsertString16(PxPath* self, PxArena* arena, PxString16 value, PxString16 pivot)
{
    pxiword offset = pxArenaOffset(arena);

    PxString16 left  = {0};
    PxString16 right = value;

    while (right.length > 0) {
        pxString16Split(right, pivot, &left, &right);

        pxiword   temp   = pxArenaOffset(arena);
        PxString8 string = pxString8CopyString16(arena, left);

        pxb8 curr = pxString8IsEqual(string, pxs8("."));
        pxb8 prev = pxString8IsEqual(string, pxs8(".."));

        if (curr != 0 || prev != 0) {
            pxArenaRewind(arena, temp);

            if (prev != 0) {
                if (self->size <= 0)
                    return 0;

                pxPathRemoveNode(self);
            }

            continue;
        }

        PxPathNode* node =
            pxArenaReserve(arena, PxPathNode, 1);

        if (string.length != left.length || node == 0)
            break;

        node->memory = string.memory;
        node->length = string.length;

        pxPathInsertNode(self, node);
    }

    if (right.length <= 0) return 1;

    pxArenaRewind(arena, offset);

    return 0;
}

pxb8
pxPathInsertString32(PxPath* self, PxArena* arena, PxString32 value, PxString32 pivot)
{
    pxiword offset = pxArenaOffset(arena);

    PxString32 left  = {0};
    PxString32 right = value;

    while (right.length > 0) {
        pxString32Split(right, pivot, &left, &right);

        pxiword   temp   = pxArenaOffset(arena);
        PxString8 string = pxString8CopyString32(arena, left);

        pxb8 curr = pxString8IsEqual(string, pxs8("."));
        pxb8 prev = pxString8IsEqual(string, pxs8(".."));

        if (curr != 0 || prev != 0) {
            pxArenaRewind(arena, temp);

            if (prev != 0) {
                if (self->size <= 0)
                    return 0;

                pxPathRemoveNode(self);
            }

            continue;
        }

        PxPathNode* node =
            pxArenaReserve(arena, PxPathNode, 1);

        if (string.length != left.length || node == 0)
            break;

        node->memory = string.memory;
        node->length = string.length;

        pxPathInsertNode(self, node);
    }

    if (right.length <= 0) return 1;

    pxArenaRewind(arena, offset);

    return 0;
}

PxString8
pxString8FromPath(PxArena* arena, PxPath* value, PxString8 pivot)
{
    pxiword length = 0;

    for (PxPathNode* node = value->head; node != 0; node = node->next) {
        length += node->length;

        if (node->next != 0)
            length += pivot.length;
    }

    pxu8* result = pxArenaReserve(arena, pxu8, length + 1);

    if (result == 0) return (PxString8) {0};

    pxiword offset = pxArenaOffset(arena);
    pxiword index  = 0;

    for (PxPathNode* node = value->head; node != 0; node = node->next) {
        PxString8 string = {.memory = node->memory, .length = node->length};

        for (pxiword i = 0; i < string.length; i += 1)
            result[index + i] = string.memory[i];

        index += string.length;

        if (node->next != 0) {
            for (pxiword i = 0; i < pivot.length; i += 1)
                result[index + i] = pivot.memory[i];

            index += pivot.length;
        }
    }

    return pxString8Make(result, length);
}

PxString16
pxString16FromPath(PxArena* arena, PxPath* value, PxString16 pivot)
{
    pxiword length = 0;

    for (PxPathNode* node = value->head; node != 0; node = node->next) {
        length += pxUtf16UnitsFromMemory8(
            node->memory, node->length);

        if (node->next != 0)
            length += pivot.length;
    }

    pxu16* result = pxArenaReserve(arena, pxu16, length + 1);

    if (result == 0) return (PxString16) {0};

    pxiword offset = pxArenaOffset(arena);
    pxiword index  = 0;

    for (PxPathNode* node = value->head; node != 0; node = node->next) {
        pxiword other = 0;

        while (other < node->length) {
            pxi32 unicode = 0;

            other += pxUtf8ReadForw(node->memory, node->length,
                other, &unicode);

            index += pxUtf16WriteForw(result, length, index, unicode);
        }

        if (node->next != 0) {
            for (pxiword i = 0; i < pivot.length; i += 1)
                result[index + i] = pivot.memory[i];

            index += pivot.length;
        }
    }

    return pxString16Make(result, length);
}

PxString32
pxString32FromPath(PxArena* arena, PxPath* value, PxString32 pivot)
{
    pxiword length = 0;

    for (PxPathNode* node = value->head; node != 0; node = node->next) {
        length += pxUtf32UnitsFromMemory8(
            node->memory, node->length);

        if (node->next != 0)
            length += pivot.length;
    }

    pxu32* result = pxArenaReserve(arena, pxu32, length + 1);

    if (result == 0) return (PxString32) {0};

    pxiword offset = pxArenaOffset(arena);
    pxiword index  = 0;

    for (PxPathNode* node = value->head; node != 0; node = node->next) {
        pxiword other = 0;

        while (other < node->length) {
            pxi32 unicode = 0;

            other += pxUtf8ReadForw(node->memory, node->length,
                other, &unicode);

            index += pxUtf32WriteForw(result, length, index, unicode);
        }

        if (node->next != 0) {
            for (pxiword i = 0; i < pivot.length; i += 1)
                result[index + i] = pivot.memory[i];

            index += pivot.length;
        }
    }

    return pxString32Make(result, length);
}

#endif // PX_CORE_STORAGE_PATH_C
