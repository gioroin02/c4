#ifndef PX_CORE_MEMORY_BUFFER_16_C
#define PX_CORE_MEMORY_BUFFER_16_C

#include "buffer16.h"

PxBuffer16
pxBuffer16Make(pxu16* memory, pxiword length)
{
    PxBuffer16 result = {0};

    if (memory != 0 && length > 0) {
        result.memory = memory;
        result.length = length;
    }

    return result;
}

PxBuffer16
pxBuffer16MakeFull(pxu16* memory, pxiword length)
{
    PxBuffer16 result = {0};

    if (memory != 0 || length > 0) {
        result.memory = memory;
        result.length = length;
        result.size   = length;
        result.tail   = length;
    }

    return result;
}

PxBuffer16
pxBuffer16Reserve(PxArena* arena, pxiword length)
{
    pxu16* memory =
        pxArenaReserve(arena, pxu16, length);

    return pxBuffer16Make(memory, length);
}

PxBuffer16
pxBuffer16ReserveFull(PxArena* arena, pxiword length)
{
    pxu16* memory =
        pxArenaReserve(arena, pxu16, length);

    return pxBuffer16MakeFull(memory, length);
}

PxBuffer16
pxBuffer16Copy(PxArena* arena, PxBuffer16 value)
{
    return pxBuffer16CopyAmount(arena, value, value.length);
}

PxBuffer16
pxBuffer16CopyAmount(PxArena* arena, PxBuffer16 value, pxiword length)
{
    PxBuffer16 result = pxBuffer16Reserve(arena, length);

    if (result.length <= 0) return result;

    result.size = px_min(result.length, value.size);
    result.tail = result.size;

    for (pxiword i = 0; i < result.size; i += 1)
        result.memory[i] = value.memory[(value.head + i) % value.length];

    return result;
}

PxBuffer16
pxBuffer16CopyMemory16(PxArena* arena, pxu16* memory, pxiword length)
{
    PxBuffer16 result = pxBuffer16Reserve(arena, length);

    if (result.length <= 0) return result;

    result.size = result.length;
    result.tail = result.length;

    pxMemoryCopy(result.memory, memory, result.size, 2);

    return result;
}

void
pxBuffer16Clear(PxBuffer16* self)
{
    self->size = 0;
    self->head = 0;
    self->tail = 0;
}

void
pxBuffer16Fill(PxBuffer16* self)
{
    pxiword diff = self->length - self->size;

    self->size = self->length;
    self->tail = self->head;

    for (pxiword i = 0; i < diff; i += 1)
        self->memory[(self->head + i) % self->length] = 0;
}

void
pxBuffer16Normalize(PxBuffer16* self)
{
    pxu16*  memory = self->memory;
    pxiword length = self->tail;
    pxiword offset = self->head;

    if (self->head > self->tail) {
        memory = self->memory + self->length - self->head;
        offset = self->head - self->tail;

        pxMemoryFlip(self->memory + self->head,
            self->length - self->head, 2);

        pxMemoryFlip(self->memory, self->tail, 2);
        pxMemoryFlip(self->memory, self->length, 2);
    }

    if (offset > 0 && self->head > 0)
        pxMemoryCopyBack(memory + offset, length, offset, 2);

    self->head = 0;
    self->tail = self->size;
}

pxb8
pxBuffer16GetForw(PxBuffer16* self, pxiword index, pxu16* value)
{
    if (index < 0 || index >= self->size)
        return 0;

    index = (self->head + index) % self->length;

    if (value != 0)
        *value = self->memory[index];

    return 1;
}

pxu16
pxBuffer16GetForwOr(PxBuffer16* self, pxiword index, pxu16 value)
{
    if (index < 0 || index >= self->size)
        return value;

    index = (self->head + index) % self->length;

    return self->memory[index];
}

pxb8
pxBuffer16GetBack(PxBuffer16* self, pxiword index, pxu16* value)
{
    if (index < 0 || index >= self->size)
        return 0;

    index = (self->tail + self->length - index) % self->length;

    if (value != 0)
        *value = self->memory[index];

    return 1;
}

pxu16
pxBuffer16GetBackOr(PxBuffer16* self, pxiword index, pxu16 value)
{
    if (index < 0 || index >= self->size)
        return value;

    index = (self->tail + self->length - index) % self->length;

    return self->memory[index];
}

pxiword
pxBuffer16DropHead(PxBuffer16* self, pxiword amount)
{
    amount = px_min(amount, self->size);

    if (amount > 0) {
        pxiword next = self->head + amount;

        self->size -= amount;
        self->head  = next % self->length;
    }

    return amount;
}

pxiword
pxBuffer16DropTail(PxBuffer16* self, pxiword amount)
{
    amount = px_min(amount, self->size);

    if (amount > 0) {
        pxiword prev = self->tail + self->length - amount;

        self->size -= amount;
        self->tail  = prev % self->length;
    }

    return amount;
}

pxiword
pxBuffer16WriteHead(PxBuffer16* self, PxBuffer16* buffer)
{
    pxiword size = px_min(buffer->size, self->length - self->size);

    if (size <= 0 || size > self->length) return 0;

    pxiword prev = self->head + self->length - size;

    self->size += size;
    self->head  = prev % self->length;

    for (pxiword i = 0; i < size; i += 1) {
        self->memory[(self->head + i) % self->length] =
            buffer->memory[(buffer->head + i) % buffer->length];
    }

    buffer->size -= size;
    buffer->head = (buffer->head + size) % buffer->length;

    return size;
}

pxiword
pxBuffer16WriteMemory16Head(PxBuffer16* self, pxu16* memory, pxiword length)
{
    pxiword size = px_min(length, self->length - self->size);

    if (size <= 0 || size > self->length) return 0;

    pxiword prev = self->head + self->length - size;

    self->size += size;
    self->head  = prev % self->length;

    for (pxiword i = 0; i < size; i += 1)
        self->memory[(self->head + i) % self->length] = memory[i];

    return size;
}

pxiword
pxBuffer16WriteTail(PxBuffer16* self, PxBuffer16* buffer)
{
    pxiword size = px_min(buffer->size, self->length - self->size);

    if (size <= 0 || size > self->length) return 0;

    pxiword next = self->tail + size;

    for (pxiword i = 0; i < size; i += 1) {
        self->memory[(self->tail + i) % self->length] =
            buffer->memory[(buffer->head + i) % buffer->length];
    }

    self->size += size;
    self->tail  = next % self->length;

    buffer->size -= size;
    buffer->head  = (buffer->head + size) % buffer->length;

    return size;
}

pxiword
pxBuffer16WriteMemory16Tail(PxBuffer16* self, pxu16* memory, pxiword length)
{
    pxiword size = px_min(length, self->length - self->size);

    if (size <= 0 || size > self->length) return 0;

    pxiword next = self->tail + size;

    for (pxiword i = 0; i < size; i += 1)
        self->memory[(self->tail + i) % self->length] = memory[i];

    self->size += size;
    self->tail  = next % self->length;

    return size;
}

pxiword
pxBuffer16ReadHead(PxBuffer16* self, PxBuffer16* buffer)
{
    pxiword size = px_min(self->size, buffer->length - buffer->size);

    if (size <= 0 || size > self->size) return 0;

    pxiword next = self->head + size;

    for (pxiword i = 0; i < size; i += 1) {
        buffer->memory[(buffer->tail + i) % buffer->length] =
            self->memory[(self->head + i) % self->length];
    }

    self->size -= size;
    self->head  = next % self->length;

    buffer->size += size;
    buffer->tail  = (buffer->tail + size) % buffer->length;

    return size;
}

pxiword
pxBuffer16ReadMemory16Head(PxBuffer16* self, pxu16* memory, pxiword length)
{
    pxiword size = px_min(self->size, length);

    if (size <= 0 || size > self->size) return 0;

    pxiword next = self->head + size;

    for (pxiword i = 0; i < size; i += 1)
        memory[i] = self->memory[(self->head + i) % self->length];

    self->size -= size;
    self->head  = next % self->length;

    return size;
}

pxiword
pxBuffer16ReadTail(PxBuffer16* self, PxBuffer16* buffer)
{
    pxiword size = px_min(self->size, buffer->length - buffer->size);

    if (size <= 0 || size > self->size) return 0;

    pxiword prev = self->tail + self->length - size;

    self->size -= size;
    self->tail  = prev % self->length;

    for (pxiword i = 0; i < size; i += 1) {
        buffer->memory[(buffer->tail + i) % buffer->length] =
            self->memory[(self->tail + i) % self->length];
    }

    buffer->size += size;
    buffer->tail  = (buffer->tail + size) % buffer->length;

    return size;
}

pxiword
pxBuffer16ReadMemory16Tail(PxBuffer16* self, pxu16* memory, pxiword length)
{
    pxiword size = px_min(self->size, length);

    if (size <= 0 || size > self->size) return 0;

    pxiword prev = self->tail + self->length - size;

    self->size -= size;
    self->tail  = prev % self->length;

    for (pxiword i = 0; i < size; i += 1)
        memory[i] = self->memory[(self->tail + i) % self->length];

    return size;
}

pxiword
pxBuffer16PeekHead(PxBuffer16* self, PxBuffer16* buffer)
{
    pxiword size = px_min(self->size, buffer->length - buffer->size);

    if (size <= 0 || size > self->size) return 0;

    for (pxiword i = 0; i < size; i += 1) {
        buffer->memory[(buffer->tail + i) % buffer->length] =
            self->memory[(self->head + i) % self->length];
    }

    buffer->size += size;
    buffer->tail  = (buffer->tail + size) % buffer->length;

    return size;
}

pxiword
pxBuffer16PeekMemory16Head(PxBuffer16* self, pxu16* memory, pxiword length)
{
    pxiword size = px_min(self->size, length);

    if (size <= 0 || size > self->size) return 0;

    for (pxiword i = 0; i < size; i += 1)
        memory[i] = self->memory[(self->head + i) % self->length];

    return size;
}

pxiword
pxBuffer16PeekTail(PxBuffer16* self, PxBuffer16* buffer)
{
    pxiword size = px_min(self->size, buffer->length - buffer->size);

    if (size <= 0 || size > self->size) return 0;

    pxiword prev = self->tail + self->length - size;
    pxiword tail = prev % self->length;

    for (pxiword i = 0; i < size; i += 1) {
        buffer->memory[(buffer->tail + i) % buffer->length] =
            self->memory[(tail + i) % self->length];
    }

    buffer->size += size;
    buffer->tail  = (buffer->tail + size) % buffer->length;

    return size;
}

pxiword
pxBuffer16PeekMemory16Tail(PxBuffer16* self, pxu16* memory, pxiword length)
{
    pxiword size = px_min(self->size, length);

    if (size <= 0 || size > self->size) return 0;

    pxiword prev = self->tail + self->length - size;
    pxiword tail = prev % self->length;

    for (pxiword i = 0; i < size; i += 1)
        memory[i] = self->memory[(tail + i) % self->length];

    return size;
}

#endif // PX_CORE_MEMORY_BUFFER_16_C
