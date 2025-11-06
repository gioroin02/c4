#ifndef PX_CORE_BASE_MEMORY_H
#define PX_CORE_BASE_MEMORY_H

#include "number.h"

#define PX_MEMORY_KB px_as(pxiword, 1000)
#define PX_MEMORY_MB px_as(pxiword, 1000 * 1000)
#define PX_MEMORY_GB px_as(pxiword, 1000 * 1000 * 1000)

#define PX_MEMORY_KIB px_as(pxiword, 1024)
#define PX_MEMORY_MIB px_as(pxiword, 1024 * 1024)
#define PX_MEMORY_GIB px_as(pxiword, 1024 * 1024 * 1024)

void*
pxMemoryZero(void* memory, pxiword amount, pxiword stride);

void*
pxMemoryFlip(void* memory, pxiword amount, pxiword stride);

void*
pxMemoryCopy(void* memory, void* value, pxiword amount, pxiword stride);

void*
pxMemoryCopyFlipped(void* memory, void* value, pxiword amount, pxiword stride);

void*
pxMemoryCopyBack(void* memory, pxiword amount, pxiword offset, pxiword stride);

void*
pxMemoryCopyForw(void* memory, pxiword amount, pxiword offset, pxiword stride);

pxb8
pxMemoryIsEqual(void* memory, void* value, pxiword amount, pxiword stride);

#endif // PX_CORE_BASE_MEMORY_H
