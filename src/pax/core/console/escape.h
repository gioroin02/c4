#ifndef PX_CORE_CONSOLE_ESCAPE_H
#define PX_CORE_CONSOLE_ESCAPE_H

#include "import.h"

#define PX_ESCAPE_GROUPS 8
#define PX_ESCAPE_VALUES 8

typedef enum PxEscapeType
{
    PX_ESCAPE_NONE,

    PX_ESCAPE_UNICODE,
    PX_ESCAPE_FUNCTION,

    PX_ESCAPE_GRAPHIC,

    PX_ESCAPE_UP,
    PX_ESCAPE_DOWN,
    PX_ESCAPE_LEFT,
    PX_ESCAPE_RIGHT,
    PX_ESCAPE_HOME,
    PX_ESCAPE_END,
}
PxEscapeType;

typedef struct PxEscapeGroup
{
    pxuword values[PX_ESCAPE_VALUES];
    pxiword size;
}
PxEscapeGroup;

typedef struct PxEscape
{
    PxEscapeType  type;
    PxEscapeGroup groups[PX_ESCAPE_GROUPS];
    pxiword       size;
}
PxEscape;

PxEscapeType
pxEscapeSetType(PxEscape* self, PxEscapeType value);

pxb8
pxEscapeInsertGroupTail(PxEscape* self);

pxb8
pxEscapeInsertValueTail(PxEscape* self, pxiword group, pxuword value);

pxb8
pxEscapeReadValue(PxEscape* self, pxiword group, pxiword index, pxuword* value);

pxuword
pxEscapeReadValueOr(PxEscape* self, pxiword group, pxiword index, pxuword value);

pxb8
pxEscapeFromString8(PxEscape* self, PxString8 string, pxiword* size);

pxb8
pxEscapeGroupFromString8(PxEscape* self, PxString8 string);

#endif // PX_CORE_CONSOLE_ESCAPE_H
