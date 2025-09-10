#ifndef PX_CORE_FORMAT_STRING16_H
#define PX_CORE_FORMAT_STRING16_H

#include "memory16.h"

/* String from number */

PxString16
pxString16FromUnsigned8(PxArena* arena, pxuword radix, PxFormatOption options, pxu8 value);

PxString16
pxString16FromUnsigned16(PxArena* arena, pxuword radix, PxFormatOption options, pxu16 value);

PxString16
pxString16FromUnsigned32(PxArena* arena, pxuword radix, PxFormatOption options, pxu32 value);

PxString16
pxString16FromUnsigned64(PxArena* arena, pxuword radix, PxFormatOption options, pxu64 value);

PxString16
pxString16FromUnsigned(PxArena* arena, pxuword radix, PxFormatOption options, pxuword value);

PxString16
pxString16FromInteger8(PxArena* arena, pxuword radix, PxFormatOption options, pxi8 value);

PxString16
pxString16FromInteger16(PxArena* arena, pxuword radix, PxFormatOption options, pxi16 value);

PxString16
pxString16FromInteger32(PxArena* arena, pxuword radix, PxFormatOption options, pxi32 value);

PxString16
pxString16FromInteger64(PxArena* arena, pxuword radix, PxFormatOption options, pxi64 value);

PxString16
pxString16FromInteger(PxArena* arena, pxuword radix, PxFormatOption options, pxiword value);

/* Number from string */

pxb8
pxUnsigned8FromString16(pxu8* self, pxuword radix, PxFormatOption options, PxString16 string);

pxb8
pxUnsigned16FromString16(pxu16* self, pxuword radix, PxFormatOption options, PxString16 string);

pxb8
pxUnsigned32FromString16(pxu32* self, pxuword radix, PxFormatOption options, PxString16 string);

pxb8
pxUnsigned64FromString16(pxu64* self, pxuword radix, PxFormatOption options, PxString16 string);

pxb8
pxUnsignedFromString16(pxuword* self, pxuword radix, PxFormatOption options, PxString16 string);

pxb8
pxInteger8FromString16(pxi8* self, pxuword radix, PxFormatOption options, PxString16 string);

pxb8
pxInteger16FromString16(pxi16* self, pxuword radix, PxFormatOption options, PxString16 string);

pxb8
pxInteger32FromString16(pxi32* self, pxuword radix, PxFormatOption options, PxString16 string);

pxb8
pxInteger64FromString16(pxi64* self, pxuword radix, PxFormatOption options, PxString16 string);

pxb8
pxIntegerFromString16(pxiword* self, pxuword radix, PxFormatOption options, PxString16 string);

#endif // PX_CORE_FORMAT_STRING16_H
