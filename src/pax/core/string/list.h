#ifndef PX_CORE_STRING_LIST_H
#define PX_CORE_STRING_LIST_H

#include "convert.h"

typedef struct PxStringNode PxStringNode;

struct PxStringNode
{
    pxu8*   memory;
    pxiword length;

    PxStringNode* next;
    PxStringNode* prev;
};

typedef struct PxStringList
{
    PxStringNode* head;
    PxStringNode* tail;

    pxiword size;
}
PxStringList;

PxStringList
pxStringListFromString8(PxArena* arena, PxString8 string, PxString8 pivot);

PxStringList
pxStringListFromString16(PxArena* arena, PxString16 string, PxString16 pivot);

PxStringList
pxStringListFromString32(PxArena* arena, PxString32 string, PxString32 pivot);

pxb8
pxStringListInsert(PxStringList* self, pxiword index, PxStringNode* value);

pxb8
pxStringListInsertHead(PxStringList* self, PxStringNode* value);

pxb8
pxStringListInsertTail(PxStringList* self, PxStringNode* value);

pxb8
pxStringListInsertString8(PxStringList* self, PxArena* arena, pxiword index, PxString8 value, PxString8 pivot);

pxb8
pxStringListInsertString16(PxStringList* self, PxArena* arena, pxiword index, PxString16 value, PxString16 pivot);

pxb8
pxStringListInsertString32(PxStringList* self, PxArena* arena, pxiword index, PxString32 value, PxString32 pivot);

pxb8
pxStringListRemove(PxStringList* self, pxiword index, PxStringNode** value);

pxb8
pxStringListRemoveHead(PxStringList* self, PxStringNode** value);

pxb8
pxStringListRemoveTail(PxStringList* self, PxStringNode** value);

pxb8
pxStringListRead(PxStringList* self, pxiword index, PxStringNode** value);

pxb8
pxStringListReadHead(PxStringList* self, PxStringNode** value);

pxb8
pxStringListReadTail(PxStringList* self, PxStringNode** value);

PxString8
pxString8FromStringList(PxArena* arena, PxStringList* value, PxString8 pivot, PxString8 prefix, PxString8 suffix);

PxString16
pxString16FromStringList(PxArena* arena, PxStringList* value, PxString16 pivot, PxString16 prefix, PxString16 suffix);

PxString32
pxString32FromStringList(PxArena* arena, PxStringList* value, PxString32 pivot, PxString32 prefix, PxString32 suffix);

#endif // PX_CORE_STRING_LIST_H
