#ifndef PX_CORE_FORMAT_STRING8_H
#define PX_CORE_FORMAT_STRING8_H

#include "memory8.h"

/* String from number */

PxString8
pxString8FromUnsigned8(PxArena* arena, pxuword radix, PxFormatOption options, pxu8 value);

PxString8
pxString8FromUnsigned16(PxArena* arena, pxuword radix, PxFormatOption options, pxu16 value);

PxString8
pxString8FromUnsigned32(PxArena* arena, pxuword radix, PxFormatOption options, pxu32 value);

PxString8
pxString8FromUnsigned64(PxArena* arena, pxuword radix, PxFormatOption options, pxu64 value);

PxString8
pxString8FromUnsigned(PxArena* arena, pxuword radix, PxFormatOption options, pxuword value);

PxString8
pxString8FromInteger8(PxArena* arena, pxuword radix, PxFormatOption options, pxi8 value);

PxString8
pxString8FromInteger16(PxArena* arena, pxuword radix, PxFormatOption options, pxi16 value);

PxString8
pxString8FromInteger32(PxArena* arena, pxuword radix, PxFormatOption options, pxi32 value);

PxString8
pxString8FromInteger64(PxArena* arena, pxuword radix, PxFormatOption options, pxi64 value);

PxString8
pxString8FromInteger(PxArena* arena, pxuword radix, PxFormatOption options, pxiword value);

/* Number from string */

pxb8
pxUnsigned8FromString8(pxu8* self, pxuword radix, PxFormatOption options, PxString8 string);

pxb8
pxUnsigned16FromString8(pxu16* self, pxuword radix, PxFormatOption options, PxString8 string);

pxb8
pxUnsigned32FromString8(pxu32* self, pxuword radix, PxFormatOption options, PxString8 string);

pxb8
pxUnsigned64FromString8(pxu64* self, pxuword radix, PxFormatOption options, PxString8 string);

pxb8
pxUnsignedFromString8(pxuword* self, pxuword radix, PxFormatOption options, PxString8 string);

pxb8
pxInteger8FromString8(pxi8* self, pxuword radix, PxFormatOption options, PxString8 string);

pxb8
pxInteger16FromString8(pxi16* self, pxuword radix, PxFormatOption options, PxString8 string);

pxb8
pxInteger32FromString8(pxi32* self, pxuword radix, PxFormatOption options, PxString8 string);

pxb8
pxInteger64FromString8(pxi64* self, pxuword radix, PxFormatOption options, PxString8 string);

pxb8
pxIntegerFromString8(pxiword* self, pxuword radix, PxFormatOption options, PxString8 string);

#endif // PX_CORE_FORMAT_STRING8_H
