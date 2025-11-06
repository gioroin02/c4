#ifndef PX_CORE_FORMAT_INTEGER_H
#define PX_CORE_FORMAT_INTEGER_H

#include "config.h"

pxiword
pxIntegerDigits(pxiword value, PxFormatRadix radix, PxFormatFlag flags);

/* Memory */

pxiword
pxMemory8WriteInteger(pxu8* memory, pxiword length, pxiword value, PxFormatRadix radix, PxFormatFlag flags);

pxiword
pxMemory8ReadInteger(pxu8* memory, pxiword length, pxiword* value, PxFormatRadix radix, PxFormatFlag flags);

pxiword
pxMemory16WriteInteger(pxu16* memory, pxiword length, pxiword value, PxFormatRadix radix, PxFormatFlag flags);

pxiword
pxMemory16ReadInteger(pxu16* memory, pxiword length, pxiword* value, PxFormatRadix radix, PxFormatFlag flags);

pxiword
pxMemory32WriteInteger(pxu32* memory, pxiword length, pxiword value, PxFormatRadix radix, PxFormatFlag flags);

pxiword
pxMemory32ReadInteger(pxu32* memory, pxiword length, pxiword* value, PxFormatRadix radix, PxFormatFlag flags);

/* String */

PxString8
pxString8FromInteger(PxArena* arena, pxiword value, PxFormatRadix radix, PxFormatFlag flags);

pxb8
pxIntegerFromString8(PxString8 string, pxiword* value, PxFormatRadix radix, PxFormatFlag flags);

PxString16
pxString16FromInteger(PxArena* arena, pxiword value, PxFormatRadix radix, PxFormatFlag flags);

pxb8
pxIntegerFromString16(PxString16 string, pxiword* value, PxFormatRadix radix, PxFormatFlag flags);

PxString32
pxString32FromInteger(PxArena* arena, pxiword value, PxFormatRadix radix, PxFormatFlag flags);

pxb8
pxIntegerFromString32(PxString32 string, pxiword* value, PxFormatRadix radix, PxFormatFlag flags);

#endif // PX_CORE_FORMAT_INTEGER_H
