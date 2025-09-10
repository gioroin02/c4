#ifndef PX_CORE_FORMAT_MEMORY8_H
#define PX_CORE_FORMAT_MEMORY8_H

#include "option.h"

pxiword
pxMemory8WriteUnsigned8(pxu8* memory, pxiword length, pxuword radix, PxFormatOption options, pxu8 value);

pxiword
pxMemory8WriteUnsigned16(pxu8* memory, pxiword length, pxuword radix, PxFormatOption options, pxu16 value);

pxiword
pxMemory8WriteUnsigned32(pxu8* memory, pxiword length, pxuword radix, PxFormatOption options, pxu32 value);

pxiword
pxMemory8WriteUnsigned64(pxu8* memory, pxiword length, pxuword radix, PxFormatOption options, pxu64 value);

pxiword
pxMemory8WriteUnsigned(pxu8* memory, pxiword length, pxuword radix, PxFormatOption options, pxuword value);

pxiword
pxMemory8WriteInteger8(pxu8* memory, pxiword length, pxuword radix, PxFormatOption options, pxi8 value);

pxiword
pxMemory8WriteInteger16(pxu8* memory, pxiword length, pxuword radix, PxFormatOption options, pxi16 value);

pxiword
pxMemory8WriteInteger32(pxu8* memory, pxiword length, pxuword radix, PxFormatOption options, pxi32 value);

pxiword
pxMemory8WriteInteger64(pxu8* memory, pxiword length, pxuword radix, PxFormatOption options, pxi64 value);

pxiword
pxMemory8WriteInteger(pxu8* memory, pxiword length, pxuword radix, PxFormatOption options, pxiword value);

#endif // PX_CORE_FORMAT_MEMORY8_H
