#ifndef PX_CORE_FORMAT_BOOLEAN_H
#define PX_CORE_FORMAT_BOOLEAN_H

#include "config.h"

pxiword
pxBooleanDigits(pxbword value, PxFormatFlag flags);

/* Memory */

pxiword
pxMemory8WriteBoolean(pxu8* memory, pxiword length, pxbword value, PxFormatFlag flags);

pxiword
pxMemory8ReadBoolean(pxu8* memory, pxiword length, pxbword* value, PxFormatFlag flags);

pxiword
pxMemory16WriteBoolean(pxu16* memory, pxiword length, pxbword value, PxFormatFlag flags);

pxiword
pxMemory16ReadBoolean(pxu16* memory, pxiword length, pxbword* value, PxFormatFlag flags);

pxiword
pxMemory32WriteBoolean(pxu32* memory, pxiword length, pxbword value, PxFormatFlag flags);

pxiword
pxMemory32ReadBoolean(pxu32* memory, pxiword length, pxbword* value, PxFormatFlag flags);

/* String */

PxString8
pxString8FromBoolean(PxArena* arena, pxbword value, PxFormatFlag flags);

pxb8
pxBooleanFromString8(PxString8 string, pxbword* value, PxFormatFlag flags);

PxString16
pxString16FromBoolean(PxArena* arena, pxbword value, PxFormatFlag flags);

pxb8
pxBooleanFromString16(PxString16 string, pxbword* value, PxFormatFlag flags);

PxString32
pxString32FromBoolean(PxArena* arena, pxbword value, PxFormatFlag flags);

pxb8
pxBooleanFromString32(PxString32 string, pxbword* value, PxFormatFlag flags);

#endif // PX_CORE_FORMAT_BOOLEAN_H
