#ifndef PX_CORE_FORMAT_MEMORY16_H
#define PX_CORE_FORMAT_MEMORY16_H

#include "option.h"

pxiword
pxMemory16WriteUnsigned8(pxu16* memory, pxiword length, pxuword radix, PxFormatOption options, pxu8 value);

pxiword
pxMemory16WriteUnsigned16(pxu16* memory, pxiword length, pxuword radix, PxFormatOption options, pxu16 value);

pxiword
pxMemory16WriteUnsigned32(pxu16* memory, pxiword length, pxuword radix, PxFormatOption options, pxu32 value);

pxiword
pxMemory16WriteUnsigned64(pxu16* memory, pxiword length, pxuword radix, PxFormatOption options, pxu64 value);

pxiword
pxMemory16WriteUnsigned(pxu16* memory, pxiword length, pxuword radix, PxFormatOption options, pxuword value);

pxiword
pxMemory16WriteInteger8(pxu16* memory, pxiword length, pxuword radix, PxFormatOption options, pxi8 value);

pxiword
pxMemory16WriteInteger16(pxu16* memory, pxiword length, pxuword radix, PxFormatOption options, pxi16 value);

pxiword
pxMemory16WriteInteger32(pxu16* memory, pxiword length, pxuword radix, PxFormatOption options, pxi32 value);

pxiword
pxMemory16WriteInteger64(pxu16* memory, pxiword length, pxuword radix, PxFormatOption options, pxi64 value);

pxiword
pxMemory16WriteInteger(pxu16* memory, pxiword length, pxuword radix, PxFormatOption options, pxiword value);

#endif // PX_CORE_FORMAT_MEMORY16_H
