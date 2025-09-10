#ifndef PX_CORE_FORMAT_STRING32_H
#define PX_CORE_FORMAT_STRING32_H

#include "memory32.h"

/* String from number */

PxString32
pxString32FromUnsigned8(PxArena* arena, pxuword radix, PxFormatOption options, pxu8 value);

PxString32
pxString32FromUnsigned16(PxArena* arena, pxuword radix, PxFormatOption options, pxu16 value);

PxString32
pxString32FromUnsigned32(PxArena* arena, pxuword radix, PxFormatOption options, pxu32 value);

PxString32
pxString32FromUnsigned64(PxArena* arena, pxuword radix, PxFormatOption options, pxu64 value);

PxString32
pxString32FromUnsigned(PxArena* arena, pxuword radix, PxFormatOption options, pxuword value);

PxString32
pxString32FromInteger8(PxArena* arena, pxuword radix, PxFormatOption options, pxi8 value);

PxString32
pxString32FromInteger16(PxArena* arena, pxuword radix, PxFormatOption options, pxi16 value);

PxString32
pxString32FromInteger32(PxArena* arena, pxuword radix, PxFormatOption options, pxi32 value);

PxString32
pxString32FromInteger64(PxArena* arena, pxuword radix, PxFormatOption options, pxi64 value);

PxString32
pxString32FromInteger(PxArena* arena, pxuword radix, PxFormatOption options, pxiword value);

/* Number from string */

pxb8
pxUnsigned8FromString32(pxu8* self, pxuword radix, PxFormatOption options, PxString32 string);

pxb8
pxUnsigned16FromString32(pxu16* self, pxuword radix, PxFormatOption options, PxString32 string);

pxb8
pxUnsigned32FromString32(pxu32* self, pxuword radix, PxFormatOption options, PxString32 string);

pxb8
pxUnsigned64FromString32(pxu64* self, pxuword radix, PxFormatOption options, PxString32 string);

pxb8
pxUnsignedFromString32(pxuword* self, pxuword radix, PxFormatOption options, PxString32 string);

pxb8
pxInteger8FromString32(pxi8* self, pxuword radix, PxFormatOption options, PxString32 string);

pxb8
pxInteger16FromString32(pxi16* self, pxuword radix, PxFormatOption options, PxString32 string);

pxb8
pxInteger32FromString32(pxi32* self, pxuword radix, PxFormatOption options, PxString32 string);

pxb8
pxInteger64FromString32(pxi64* self, pxuword radix, PxFormatOption options, PxString32 string);

pxb8
pxIntegerFromString32(pxiword* self, pxuword radix, PxFormatOption options, PxString32 string);

#endif // PX_CORE_FORMAT_STRING32_H
