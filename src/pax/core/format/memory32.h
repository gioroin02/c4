#ifndef PX_CORE_FORMAT_MEMORY32_H
#define PX_CORE_FORMAT_MEMORY32_H

#include "option.h"

pxiword
pxMemory32WriteUnsigned8(pxu32* memory, pxiword length, pxuword radix, PxFormatOption options, pxu8 value);

pxiword
pxMemory32WriteUnsigned16(pxu32* memory, pxiword length, pxuword radix, PxFormatOption options, pxu16 value);

pxiword
pxMemory32WriteUnsigned32(pxu32* memory, pxiword length, pxuword radix, PxFormatOption options, pxu32 value);

pxiword
pxMemory32WriteUnsigned64(pxu32* memory, pxiword length, pxuword radix, PxFormatOption options, pxu64 value);

pxiword
pxMemory32WriteUnsigned(pxu32* memory, pxiword length, pxuword radix, PxFormatOption options, pxuword value);

pxiword
pxMemory32WriteInteger8(pxu32* memory, pxiword length, pxuword radix, PxFormatOption options, pxi8 value);

pxiword
pxMemory32WriteInteger16(pxu32* memory, pxiword length, pxuword radix, PxFormatOption options, pxi16 value);

pxiword
pxMemory32WriteInteger32(pxu32* memory, pxiword length, pxuword radix, PxFormatOption options, pxi32 value);

pxiword
pxMemory32WriteInteger64(pxu32* memory, pxiword length, pxuword radix, PxFormatOption options, pxi64 value);

pxiword
pxMemory32WriteInteger(pxu32* memory, pxiword length, pxuword radix, PxFormatOption options, pxiword value);

#endif // PX_CORE_FORMAT_MEMORY32_H
