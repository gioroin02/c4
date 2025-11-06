#ifndef PX_CORE_FORMAT_PRINTING_H
#define PX_CORE_FORMAT_PRINTING_H

#include "unsigned.h"
#include "integer.h"
#include "boolean.h"

#include "message.h"

pxiword
pxTargetPrintUnsigned(PxTarget target, pxuword value, PxFormatRadix radix, PxFormatFlag flags);

pxiword
pxTargetPrintInteger(PxTarget target, pxiword value, PxFormatRadix radix, PxFormatFlag flags);

pxiword
pxTargetPrintBoolean(PxTarget target, pxbword value, PxFormatFlag flags);

pxb8
pxTargetFormatMsg(PxTarget target, PxFormatMsg value, pxiword* size);

pxb8
pxTargetPrintList(PxTarget target, PxFormatMsg* values, pxiword length, pxiword* size);

pxb8
pxTargetPrintFormat(PxTarget target, PxString8 format, PxFormatMsg* values, pxiword length, pxiword* size);

#endif // PX_CORE_FORMAT_PRINTING_H
