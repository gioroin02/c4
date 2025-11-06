#ifndef PX_ENCODING_JSON_SCANNER_H
#define PX_ENCODING_JSON_SCANNER_H

#include "token.h"

pxu8
pxSourceDropJsonSpaces(PxSource source);

PxString8
pxSourceMatchJsonSymbol(PxSource source, PxArena* arena, pxiword length, PxJsonTokenType* type);

PxString8
pxSourceMatchJsonString(PxSource source, PxArena* arena, pxiword length, PxJsonTokenType* type);

PxString8
pxSourceMatchJsonNumber(PxSource source, PxArena* arena, pxiword length, PxJsonTokenType* type);

PxString8
pxSourceMatchJsonWord(PxSource source, PxArena* arena, pxiword length, PxJsonTokenType* type);

PxJsonToken
pxSourceReadJsonToken(PxSource source, PxArena* arena);

#endif // PX_ENCODING_JSON_SCANNER_H
