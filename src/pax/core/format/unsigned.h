#ifndef PX_CORE_FORMAT_UNSIGNED_H
#define PX_CORE_FORMAT_UNSIGNED_H

#include "config.h"

pxiword
pxUnsignedDigits(pxuword value, PxFormatRadix radix, PxFormatFlag flags);

/* Memory */

pxiword
pxMemory8WriteUnsigned(pxu8* memory, pxiword length, pxuword value, PxFormatRadix radix, PxFormatFlag flags);

pxiword
pxMemory8ReadUnsigned(pxu8* memory, pxiword length, pxuword* value, PxFormatRadix radix, PxFormatFlag flags);

pxiword
pxMemory16WriteUnsigned(pxu16* memory, pxiword length, pxuword value, PxFormatRadix radix, PxFormatFlag flags);

pxiword
pxMemory16ReadUnsigned(pxu16* memory, pxiword length, pxuword* value, PxFormatRadix radix, PxFormatFlag flags);

pxiword
pxMemory32WriteUnsigned(pxu32* memory, pxiword length, pxuword value, PxFormatRadix radix, PxFormatFlag flags);

pxiword
pxMemory32ReadUnsigned(pxu32* memory, pxiword length, pxuword* value, PxFormatRadix radix, PxFormatFlag flags);

/* String */

PxString8
pxString8FromUnsigned(PxArena* arena, pxuword value, PxFormatRadix radix, PxFormatFlag flags);

pxb8
pxUnsignedFromString8(PxString8 string, pxuword* value, PxFormatRadix radix, PxFormatFlag flags);

PxString16
pxString16FromUnsigned(PxArena* arena, pxuword value, PxFormatRadix radix, PxFormatFlag flags);

pxb8
pxUnsignedFromString16(PxString16 string, pxuword* value, PxFormatRadix radix, PxFormatFlag flags);

PxString32
pxString32FromUnsigned(PxArena* arena, pxuword value, PxFormatRadix radix, PxFormatFlag flags);

pxb8
pxUnsignedFromString32(PxString32 string, pxuword* value, PxFormatRadix radix, PxFormatFlag flags);

#endif // PX_CORE_FORMAT_UNSIGNED_H
