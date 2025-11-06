#ifndef PX_CORE_STRING_CONVERT_H
#define PX_CORE_STRING_CONVERT_H

#include "string8.h"
#include "string16.h"
#include "string32.h"

/* Utf8 */

PxString8
pxString8CopyMemory16(PxArena* arena, pxu16* memory, pxiword length);

PxString8
pxString8CopyString16(PxArena* arena, PxString16 value);

PxString8
pxString8CopyMemory32(PxArena* arena, pxu32* memory, pxiword length);

PxString8
pxString8CopyString32(PxArena* arena, PxString32 value);

pxiword
pxMemory8WriteUnicode(pxu8* memory, pxiword length, pxi32 value);

pxiword
pxMemory8WriteString8(pxu8* memory, pxiword length, PxString8 value);

pxiword
pxMemory8WriteString16(pxu8* memory, pxiword length, PxString16 value);

pxiword
pxMemory8WriteString32(pxu8* memory, pxiword length, PxString32 value);

/* Utf16 */

PxString16
pxString16CopyMemory8(PxArena* arena, pxu8* memory, pxiword length);

PxString16
pxString16CopyString8(PxArena* arena, PxString8 value);

PxString16
pxString16CopyMemory32(PxArena* arena, pxu32* memory, pxiword length);

PxString16
pxString16CopyString32(PxArena* arena, PxString32 value);

pxiword
pxMemory16WriteUnicode(pxu16* memory, pxiword length, pxi32 value);

pxiword
pxMemory16WriteString8(pxu16* memory, pxiword length, PxString8 value);

pxiword
pxMemory16WriteString16(pxu16* memory, pxiword length, PxString16 value);

pxiword
pxMemory16WriteString32(pxu16* memory, pxiword length, PxString32 value);

/* Utf32 */

PxString32
pxString32CopyMemory8(PxArena* arena, pxu8* memory, pxiword length);

PxString32
pxString32CopyString8(PxArena* arena, PxString8 value);

PxString32
pxString32CopyMemory16(PxArena* arena, pxu16* memory, pxiword length);

PxString32
pxString32CopyString16(PxArena* arena, PxString16 value);

pxiword
pxMemory32WriteUnicode(pxu32* memory, pxiword length, pxi32 value);

pxiword
pxMemory32WriteString8(pxu32* memory, pxiword length, PxString8 value);

pxiword
pxMemory32WriteString16(pxu32* memory, pxiword length, PxString16 value);

pxiword
pxMemory32WriteString32(pxu32* memory, pxiword length, PxString32 value);

#endif // PX_CORE_STRING_CONVERT_H
