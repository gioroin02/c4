#ifndef PX_CORE_STRING_BUFFERS_H
#define PX_CORE_STRING_BUFFERS_H

#include "convert.h"

/* Buffer8 */

pxiword
pxBuffer8WriteUnicodeHead(PxBuffer8* self, pxi32 value);

pxiword
pxBuffer8WriteMemory16Head(PxBuffer8* self, pxu16* memory, pxiword length);

pxiword
pxBuffer8WriteMemory32Head(PxBuffer8* self, pxu32* memory, pxiword length);

pxiword
pxBuffer8WriteString8Head(PxBuffer8* self, PxString8 string);

pxiword
pxBuffer8WriteString16Head(PxBuffer8* self, PxString16 string);

pxiword
pxBuffer8WriteString32Head(PxBuffer8* self, PxString32 string);

pxiword
pxBuffer8WriteUnicodeTail(PxBuffer8* self, pxi32 value);

pxiword
pxBuffer8WriteMemory16Tail(PxBuffer8* self, pxu16* memory, pxiword length);

pxiword
pxBuffer8WriteMemory32Tail(PxBuffer8* self, pxu32* memory, pxiword length);

pxiword
pxBuffer8WriteString8Tail(PxBuffer8* self, PxString8 string);

pxiword
pxBuffer8WriteString16Tail(PxBuffer8* self, PxString16 string);

pxiword
pxBuffer8WriteString32Tail(PxBuffer8* self, PxString32 string);

PxString8
pxBuffer8ReadString8Head(PxBuffer8* self, PxArena* arena, pxiword length);

PxString8
pxBuffer8ReadString8Tail(PxBuffer8* self, PxArena* arena, pxiword length);

PxString8
pxBuffer8PeekString8Head(PxBuffer8* self, PxArena* arena, pxiword length);

PxString8
pxBuffer8PeekString8Tail(PxBuffer8* self, PxArena* arena, pxiword length);

/* Buffer16 */

pxiword
pxBuffer16WriteUnicodeHead(PxBuffer16* self, pxi32 value);

/*

pxiword
pxBuffer16WriteMemory8Head(PxBuffer16* self, pxu8* memory, pxiword length);

pxiword
pxBuffer16WriteMemory32Head(PxBuffer16* self, pxu32* memory, pxiword length);

pxiword
pxBuffer16WriteString8Head(PxBuffer16* self, PxString8 string);

*/

pxiword
pxBuffer16WriteString16Head(PxBuffer16* self, PxString16 string);

/*

pxiword
pxBuffer16WriteString32Head(PxBuffer16* self, PxString32 string);

*/

pxiword
pxBuffer16WriteUnicodeTail(PxBuffer16* self, pxi32 value);

/*

pxiword
pxBuffer16WriteMemory8Tail(PxBuffer16* self, pxu8* memory, pxiword length);

pxiword
pxBuffer16WriteMemory32Tail(PxBuffer16* self, pxu32* memory, pxiword length);

pxiword
pxBuffer16WriteString8Tail(PxBuffer16* self, PxString8 string);

*/

pxiword
pxBuffer16WriteString16Tail(PxBuffer16* self, PxString16 string);

/*

pxiword
pxBuffer16WriteString32Tail(PxBuffer16* self, PxString32 string);

PxString16
pxBuffer16ReadString16Head(PxBuffer16* self, PxArena* arena, pxiword length);

PxString16
pxBuffer16ReadString16Tail(PxBuffer16* self, PxArena* arena, pxiword length);

PxString16
pxBuffer16PeekString16Head(PxBuffer16* self, PxArena* arena, pxiword length);

PxString16
pxBuffer16PeekString16Tail(PxBuffer16* self, PxArena* arena, pxiword length);

*/ /* Buffer32 */

pxiword
pxBuffer32WriteUnicodeHead(PxBuffer32* self, pxi32 value);

/*

pxiword
pxBuffer32WriteMemory8Head(PxBuffer32* self, pxu8* memory, pxiword length);

pxiword
pxBuffer32WriteMemory16Head(PxBuffer32* self, pxu16* memory, pxiword length);

pxiword
pxBuffer32WriteString8Head(PxBuffer32* self, PxString8 string);

pxiword
pxBuffer32WriteString16Head(PxBuffer32* self, PxString16 string);

*/

pxiword
pxBuffer32WriteString32Head(PxBuffer32* self, PxString32 string);

pxiword
pxBuffer32WriteUnicodeTail(PxBuffer32* self, pxi32 value);

/*

pxiword
pxBuffer32WriteMemory8Tail(PxBuffer32* self, pxu8* memory, pxiword length);

pxiword
pxBuffer32WriteMemory16Tail(PxBuffer32* self, pxu16* memory, pxiword length);

pxiword
pxBuffer32WriteString8Tail(PxBuffer32* self, PxString8 string);

pxiword
pxBuffer32WriteString16Tail(PxBuffer32* self, PxString16 string);

*/

pxiword
pxBuffer32WriteString32Tail(PxBuffer32* self, PxString32 string);

/*

PxString32
pxBuffer32ReadString32Head(PxBuffer32* self, PxArena* arena, pxiword length);

PxString32
pxBuffer32ReadString32Tail(PxBuffer32* self, PxArena* arena, pxiword length);

PxString32
pxBuffer32PeekString32Head(PxBuffer32* self, PxArena* arena, pxiword length);

PxString32
pxBuffer32PeekString32Tail(PxBuffer32* self, PxArena* arena, pxiword length);

*/

#endif // PX_CORE_STRING_BUFFERS_H
