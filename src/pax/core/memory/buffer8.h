#ifndef PX_CORE_MEMORY_BUFFER_8_H
#define PX_CORE_MEMORY_BUFFER_8_H

#include "arena.h"

typedef struct PxBuffer8
{
    pxu8*   memory;
    pxiword length;
    pxiword size;
    pxiword head;
    pxiword tail;
}
PxBuffer8;

/* PxBuffer8 */

PxBuffer8
pxBuffer8Make(pxu8* memory, pxiword length);

PxBuffer8
pxBuffer8MakeFull(pxu8* memory, pxiword length);

PxBuffer8
pxBuffer8Reserve(PxArena* arena, pxiword length);

PxBuffer8
pxBuffer8ReserveFull(PxArena* arena, pxiword length);

PxBuffer8
pxBuffer8Copy(PxArena* arena, PxBuffer8 value);

PxBuffer8
pxBuffer8CopyAmount(PxArena* arena, PxBuffer8 value, pxiword amount);

PxBuffer8
pxBuffer8CopyMemory8(PxArena* arena, pxu8* memory, pxiword length);

void
pxBuffer8Clear(PxBuffer8* self);

void
pxBuffer8Fill(PxBuffer8* self);

void
pxBuffer8Normalize(PxBuffer8* self);

/* PxBuffer8 getting */

pxb8
pxBuffer8GetForw(PxBuffer8* self, pxiword index, pxu8* value);

pxu8
pxBuffer8GetForwOr(PxBuffer8* self, pxiword index, pxu8 value);

pxb8
pxBuffer8GetBack(PxBuffer8* self, pxiword index, pxu8* value);

pxu8
pxBuffer8GetBackOr(PxBuffer8* self, pxiword index, pxu8 value);

/* PxBuffer8 dropping */

pxiword
pxBuffer8DropHead(PxBuffer8* self, pxiword amount);

pxiword
pxBuffer8DropTail(PxBuffer8* self, pxiword amount);

/* PxBuffer8 writing */

pxiword
pxBuffer8WriteHead(PxBuffer8* self, PxBuffer8* buffer);

pxiword
pxBuffer8WriteMemory8Head(PxBuffer8* self, pxu8* memory, pxiword length);

pxiword
pxBuffer8WriteTail(PxBuffer8* self, PxBuffer8* buffer);

pxiword
pxBuffer8WriteMemory8Tail(PxBuffer8* self, pxu8* memory, pxiword length);

/* PxBuffer8 reading */

pxiword
pxBuffer8ReadHead(PxBuffer8* self, PxBuffer8* buffer);

pxiword
pxBuffer8ReadMemory8Head(PxBuffer8* self, pxu8* memory, pxiword length);

pxiword
pxBuffer8ReadTail(PxBuffer8* self, PxBuffer8* buffer);

pxiword
pxBuffer8ReadMemory8Tail(PxBuffer8* self, pxu8* memory, pxiword length);

/* PxBuffer8 peeking */

pxiword
pxBuffer8PeekHead(PxBuffer8* self, PxBuffer8* buffer);

pxiword
pxBuffer8PeekMemory8Head(PxBuffer8* self, pxu8* memory, pxiword length);

pxiword
pxBuffer8PeekTail(PxBuffer8* self, PxBuffer8* buffer);

pxiword
pxBuffer8PeekMemory8Tail(PxBuffer8* self, pxu8* memory, pxiword length);

#endif // PX_CORE_MEMORY_BUFFER_8_H
