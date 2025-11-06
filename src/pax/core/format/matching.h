#ifndef PX_CORE_FORMAT_MATCHING_H
#define PX_CORE_FORMAT_MATCHING_H

#include "unsigned.h"
#include "integer.h"
#include "boolean.h"

PxString8
pxSourceMatchUnsigned(PxSource source, PxArena* arena, pxiword length, PxFormatRadix radix, PxFormatFlag flags);

PxString8
pxSourceMatchInteger(PxSource source, PxArena* arena, pxiword length, PxFormatRadix radix, PxFormatFlag flags);

PxString8
pxSourceMatchBoolean(PxSource source, PxArena* arena, pxiword length, PxFormatFlag flags);

#endif // PX_CORE_FORMAT_MATCHING_H
