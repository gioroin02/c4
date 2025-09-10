#ifndef PX_CORE_STRING_CONVERT_H
#define PX_CORE_STRING_CONVERT_H

#include "string8.h"
#include "string16.h"
#include "string32.h"

pxiword
pxUtf8UnitsFromMemory16(pxu16* memory, pxiword length);

pxiword
pxUtf8UnitsFromMemory32(pxu32* memory, pxiword length);

PxString8
pxString8CopyString16(PxArena* arena, PxString16 value);

PxString8
pxString8CopyString32(PxArena* arena, PxString32 value);

pxiword
pxUtf16UnitsFromMemory8(pxu8* memory, pxiword length);

pxiword
pxUtf16UnitsFromMemory32(pxu32* memory, pxiword length);

PxString16
pxString16CopyString8(PxArena* arena, PxString8 value);

PxString16
pxString16CopyString32(PxArena* arena, PxString32 value);

pxiword
pxUtf32UnitsFromMemory8(pxu8* memory, pxiword length);

pxiword
pxUtf32UnitsFromMemory16(pxu16* memory, pxiword length);

PxString32
pxString32CopyString8(PxArena* arena, PxString8 value);

PxString32
pxString32CopyString16(PxArena* arena, PxString16 value);

#endif // PX_CORE_STRING_CONVERT_H
