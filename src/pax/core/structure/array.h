#ifndef PX_CORE_STRUCTURE_ARRAY_H
#define PX_CORE_STRUCTURE_ARRAY_H

#include "import.h"

#define pxArrayReserve(arena, t, length) \
    pxArrayReserveMemory(arena, length, px_size(t))

#define pxArrayInsert(self, index, t, x) \
    pxArrayInsertMemory(self, index, x, px_size(t))

#define pxArrayInsertHead(self, t, x) \
    pxArrayInsertHeadMemory(self, x, px_size(t))

#define pxArrayInsertTail(self, t, x) \
    pxArrayInsertTailMemory(self, x, px_size(t))

#define pxArrayRemove(self, index, t, x) \
    pxArrayRemoveMemory(self, index, x, px_size(t))

#define pxArrayRemoveHead(self, t, x) \
    pxArrayRemoveHeadMemory(self, x, px_size(t))

#define pxArrayRemoveTail(self, t, x) \
    pxArrayRemoveTailMemory(self, x, px_size(t))

#define pxArrayUpdate(self, index, t, x) \
    pxArrayUpdateMemory(self, index, x, px_size(t))

#define pxArrayUpdateHead(self, t, x) \
    pxArrayUpdateHeadMemory(self, x, px_size(t))

#define pxArrayUpdateTail(self, t, x) \
    pxArrayUpdateTailMemory(self, x, px_size(t))

#define pxArrayGet(self, index, t, x) \
    pxArrayGetMemory(self, index, x, px_size(t))

#define pxArrayGetHead(self, t, x) \
    pxArrayGetHeadMemory(self, x, px_size(t))

#define pxArrayGetTail(self, t, x) \
    pxArrayGetTailMemory(self, x, px_size(t))

typedef struct
{
    pxu8*   memory;
    pxiword length;
    pxiword stride;
    pxiword size;
}
PxArray;

PxArray
pxArrayReserveMemory(PxArena* arena, pxiword length, pxiword stride);

PxArray
pxArrayCopy(PxArena* arena, PxArray* value);

PxArray
pxArrayCopyAmount(PxArena* arena, PxArray* value, pxiword amount);

void
pxArrayClear(PxArray* self);

void
pxArrayFill(PxArray* self);

pxb8
pxArrayInsertMemory(PxArray* self, pxiword index, void* memory, pxiword stride);

pxb8
pxArrayInsertHeadMemory(PxArray* self, void* memory, pxiword stride);

pxb8
pxArrayInsertTailMemory(PxArray* self, void* memory, pxiword stride);

pxb8
pxArrayCreate(PxArray* self, pxiword index);

pxb8
pxArrayCreateHead(PxArray* self);

pxb8
pxArrayCreateTail(PxArray* self);

pxb8
pxArrayRemoveMemory(PxArray* self, pxiword index, void* memory, pxiword stride);

pxb8
pxArrayRemoveHeadMemory(PxArray* self, void* memory, pxiword stride);

pxb8
pxArrayRemoveTailMemory(PxArray* self, void* memory, pxiword stride);

pxb8
pxArrayDrop(PxArray* self, pxiword index);

pxb8
pxArrayDropHead(PxArray* self);

pxb8
pxArrayDropTail(PxArray* self);

pxb8
pxArrayUpdateMemory(PxArray* self, pxiword index, void* memory, pxiword stride);

pxb8
pxArrayUpdateHeadMemory(PxArray* self, void* memory, pxiword stride);

pxb8
pxArrayUpdateTailMemory(PxArray* self, void* memory, pxiword stride);

pxb8
pxArrayGetMemory(PxArray* self, pxiword index, void* memory, pxiword stride);

pxb8
pxArrayGetHeadMemory(PxArray* self, void* memory, pxiword stride);

pxb8
pxArrayGetTailMemory(PxArray* self, void* memory, pxiword stride);

#endif // PX_CORE_STRUCTURE_ARRAY_H
