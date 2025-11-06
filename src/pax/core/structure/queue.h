#ifndef PX_CORE_STRUCTURE_QUEUE_H
#define PX_CORE_STRUCTURE_QUEUE_H

#include "import.h"

#define pxQueueReserve(arena, t, length) \
    pxQueueReserveMemory(arena, length, px_size(t))

#define pxQueueInsertHead(self, t, x) \
    pxQueueInsertHeadMemory(self, x, px_size(t))

#define pxQueueInsertTail(self, t, x) \
    pxQueueInsertTailMemory(self, x, px_size(t))

#define pxQueueRemoveHead(self, t, x) \
    pxQueueRemoveHeadMemory(self, x, px_size(t))

#define pxQueueRemoveTail(self, t, x) \
    pxQueueRemoveTailMemory(self, x, px_size(t))

#define pxQueueUpdate(self, index, t, x) \
    pxQueueUpdateMemory(self, index, x, px_size(t))

#define pxQueueUpdateHead(self, t, x) \
    pxQueueUpdateHeadMemory(self, x, px_size(t))

#define pxQueueUpdateTail(self, t, x) \
    pxQueueUpdateTailMemory(self, x, px_size(t))

#define pxQueueGet(self, index, t, x) \
    pxQueueGetMemory(self, index, x, px_size(t))

#define pxQueueGetHead(self, t, x) \
    pxQueueGetHeadMemory(self, x, px_size(t))

#define pxQueueGetTail(self, t, x) \
    pxQueueGetTailMemory(self, x, px_size(t))

typedef struct
{
    pxu8*   memory;
    pxiword length;
    pxiword stride;
    pxiword size;
    pxiword head;
    pxiword tail;
}
PxQueue;

PxQueue
pxQueueReserveMemory(PxArena* arena, pxiword length, pxiword stride);

PxQueue
pxQueueCopy(PxArena* arena, PxQueue* value);

PxQueue
pxQueueCopyAmount(PxArena* arena, PxQueue* value, pxiword amount);

void
pxQueueClear(PxQueue* self);

void
pxQueueFill(PxQueue* self);

pxb8
pxQueueInsertHeadMemory(PxQueue* self, void* memory, pxiword stride);

pxb8
pxQueueInsertTailMemory(PxQueue* self, void* memory, pxiword stride);

pxb8
pxQueueCreateHead(PxQueue* self);

pxb8
pxQueueCreateTail(PxQueue* self);

pxb8
pxQueueRemoveHeadMemory(PxQueue* self, void* memory, pxiword stride);

pxb8
pxQueueRemoveTailMemory(PxQueue* self, void* memory, pxiword stride);

pxb8
pxQueueDropHead(PxQueue* self);

pxb8
pxQueueDropTail(PxQueue* self);

pxb8
pxQueueUpdateMemory(PxQueue* self, pxiword index, void* memory, pxiword stride);

pxb8
pxQueueUpdateHeadMemory(PxQueue* self, void* memory, pxiword stride);

pxb8
pxQueueUpdateTailMemory(PxQueue* self, void* memory, pxiword stride);

pxb8
pxQueueGetMemory(PxQueue* self, pxiword index, void* memory, pxiword stride);

pxb8
pxQueueGetHeadMemory(PxQueue* self, void* memory, pxiword stride);

pxb8
pxQueueGetTailMemory(PxQueue* self, void* memory, pxiword stride);

#endif // PX_CORE_STRUCTURE_QUEUE_H
