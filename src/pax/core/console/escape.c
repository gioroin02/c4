#ifndef PX_CORE_CONSOLE_ESCAPE_C
#define PX_CORE_CONSOLE_ESCAPE_C

#include "escape.h"

PxEscapeType
pxEscapeSetType(PxEscape* self, PxEscapeType value)
{
    pxu8 result = self->type;

    self->type = value;

    return result;
}

pxb8
pxEscapeInsertGroupTail(PxEscape* self)
{
    pxiword index = self->size;

    if (index < 0 || index >= PX_ESCAPE_GROUPS)
        return 0;

    self->size += 1;

    return 1;
}

pxb8
pxEscapeInsertValueTail(PxEscape* self, pxiword group, pxuword value)
{
    if (group < 0 || group >= self->size)
        return 0;

    PxEscapeGroup* child = &self->groups[group];
    pxiword        index = child->size;

    if (index < 0 || index >= PX_ESCAPE_VALUES)
        return 0;

    child->size += 1;

    child->values[index] = value;

    return 1;
}

pxb8
pxEscapeReadValue(PxEscape* self, pxiword group, pxiword index, pxuword* value)
{
    if (group < 0 || group >= self->size)
        return 0;

    PxEscapeGroup* child = &self->groups[group];

    if (index < 0 || index >= child->size)
        return 0;

    if (value != 0) *value = child->values[index];

    return 1;
}

pxuword
pxEscapeReadValueOr(PxEscape* self, pxiword group, pxiword index, pxuword value)
{
    if (group < 0 || group >= self->size)
        return value;

    PxEscapeGroup* child = &self->groups[group];

    if (index < 0 || index >= child->size)
        return value;

    return child->values[index];
}

pxb8
pxEscapeFromString8(PxEscape* self, PxString8 string, pxiword* size)
{
    if (string.length <= 2) {
        if (size != 0)
            *size = string.length;

        return 0;
    }

    if (string.memory[0] != 0x1b) {
        if (size != 0) *size = 1;

        return 0;
    }

    if (string.memory[1] != 0x5b) {
        if (size != 0) *size = 2;;

        return 0;
    }

    PxString8 left  = {0};
    PxString8 right = {0};
    pxiword   index = 2;

    right = pxString8Slice(string, index, string.length - 1);

    while (right.length > 0) {
        index += pxString8Split(right, pxs8(";"), &left, &right);

        if (pxEscapeGroupFromString8(self, left) == 0)
            break;
    }

    switch (string.memory[index]) {
        case PX_ASCII_LOWER_U:
            pxEscapeSetType(self, PX_ESCAPE_UNICODE);
        break;

        case PX_ASCII_LOWER_M:
            pxEscapeSetType(self, PX_ESCAPE_GRAPHIC);
        break;

        case PX_ASCII_UPPER_A:
            pxEscapeSetType(self, PX_ESCAPE_UP);
        break;

        case PX_ASCII_UPPER_B:
            pxEscapeSetType(self, PX_ESCAPE_DOWN);
        break;

        case PX_ASCII_UPPER_C:
            pxEscapeSetType(self, PX_ESCAPE_RIGHT);
        break;

        case PX_ASCII_UPPER_D:
            pxEscapeSetType(self, PX_ESCAPE_LEFT);
        break;

        case PX_ASCII_UPPER_H:
            pxEscapeSetType(self, PX_ESCAPE_HOME);
        break;

        case PX_ASCII_UPPER_F:
            pxEscapeSetType(self, PX_ESCAPE_END);
        break;

        case PX_ASCII_TILDE:
            pxEscapeSetType(self, PX_ESCAPE_FUNCTION);
        break;

        default: break;
    }

    if (size != 0) *size = index + 1;

    if (self->type == PX_ESCAPE_NONE) return 0;

    return 1;
}

pxb8
pxEscapeGroupFromString8(PxEscape* self, PxString8 string)
{
    pxuword value = 0;
    pxb8    state = 0;

    PxFormatOption options = PX_FORMAT_OPTION_NONE;

    switch (pxString8Contains(string, pxs8(":"))) {
        case 0: {
            pxiword group = self->size;

            pxEscapeInsertGroupTail(self);

            state = pxUnsignedFromString8(&value, 10, options, string);

            if (state != 0)
                pxEscapeInsertValueTail(self, group, value);

            if (state != 0 || string.length == 0)
                return 1;
        } break;

        default: break;
    }

    return 0;
}

#endif // PX_CORE_CONSOLE_ESCAPE_C
