#ifndef PX_CORE_STORAGE_PATH_H
#define PX_CORE_STORAGE_PATH_H

#include "import.h"

typedef struct PxPathNode
{
    pxu8*   memory;
    pxiword length;

    struct PxPathNode* next;
    struct PxPathNode* prev;
}
PxPathNode;

typedef struct PxPath
{
    PxPathNode* head;
    PxPathNode* tail;

    pxiword size;
}
PxPath;

PxPath
pxPathFromString8(PxArena* arena, PxString8 string, PxString8 pivot);

PxPath
pxPathFromString16(PxArena* arena, PxString16 string, PxString16 pivot);

PxPath
pxPathFromString32(PxArena* arena, PxString32 string, PxString32 pivot);

pxb8
pxPathInsertNode(PxPath* self, PxPathNode* value);

PxPathNode*
pxPathRemoveNode(PxPath* self);

pxb8
pxPathInsertString8(PxPath* self, PxArena* arena, PxString8 value, PxString8 pivot);

pxb8
pxPathInsertString16(PxPath* self, PxArena* arena, PxString16 value, PxString16 pivot);

pxb8
pxPathInsertString32(PxPath* self, PxArena* arena, PxString32 value, PxString32 pivot);

PxString8
pxString8FromPath(PxArena* arena, PxPath* value, PxString8 pivot);

PxString16
pxString16FromPath(PxArena* arena, PxPath* value, PxString16 pivot);

PxString32
pxString32FromPath(PxArena* arena, PxPath* value, PxString32 pivot);

#endif // PX_CORE_STORAGE_PATH_H
