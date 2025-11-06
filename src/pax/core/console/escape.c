#ifndef PX_CORE_CONSOLE_ESCAPE_C
#define PX_CORE_CONSOLE_ESCAPE_C

#include "escape.h"

PxConsoleEscGroup
pxConsoleEscGroupMake(pxuword* values, pxiword length)
{
    PxConsoleEscGroup result = {0};

    for (pxiword i = 0; i < length; i += 1)
        pxConsoleEscGroupInsert(&result, values[i]);

    return result;
}

pxb8
pxConsoleEscGroupInsert(PxConsoleEscGroup* self, pxuword value)
{
    pxiword index = self->size;

    if (index < 0 || index >= PX_CONSOLE_ESC_VALUES)
        return 0;

    self->items[index] = value;

    self->size += 1;

    return 1;
}

pxb8
pxConsoleEscGroupFromString8(PxString8 string, PxConsoleEscGroup* value)
{
    PxConsoleEscGroup temp = {0};

    PxFormatRadix radix = PX_FORMAT_RADIX_10;
    PxFormatFlag  flags = PX_FORMAT_FLAG_NONE;

    PxString8 left  = {0};
    PxString8 right = string;

    while (right.length > 0) {
        pxString8Split(right, pxs8(":"), &left, &right);

        pxuword item  = 0;
        pxb8    state = 0;

        state = pxUnsignedFromString8(left, &item, radix, flags);

        if (left.length >= 0 && state != 0)
            pxConsoleEscGroupInsert(&temp, item);
        else
            return 0;
    }

    if (value != 0) *value = temp;

    return 1;
}

PxConsoleEscSeqnc
pxConsoleEscSeqncMake(PxConsoleEscGroup* values, pxiword length)
{
    PxConsoleEscSeqnc result = {0};

    for (pxiword i = 0; i < length; i += 1)
        pxConsoleEscSeqncInsert(&result, values[i]);

    return result;
}

pxb8
pxConsoleEscSeqncInsert(PxConsoleEscSeqnc* self, PxConsoleEscGroup value)
{
    pxiword index = self->size;

    if (index < 0 || index >= PX_CONSOLE_ESC_GROUPS)
        return 0;

    self->items[index] = value;

    self->size += 1;

    return 1;
}

pxb8
pxConsoleEscSeqncGet(PxConsoleEscSeqnc* self, pxiword group, pxiword index, pxuword* value)
{
    if (group < 0 || group >= self->size)
        return 0;

    PxConsoleEscGroup* item = &self->items[group];

    if (index < 0 || index >= item->size)
        return 0;

    if (value != 0) *value = item->items[index];

    return 1;
}

pxuword
pxConsoleEscSeqncGetOr(PxConsoleEscSeqnc* self, pxiword group, pxiword index, pxuword value)
{
    if (group < 0 || group >= self->size)
        return value;

    PxConsoleEscGroup* item = &self->items[group];

    if (index < 0 || index >= item->size)
        return value;

    return item->items[index];
}

pxb8
pxConsoleEscSeqncFromString8(PxString8 string, PxConsoleEscSeqnc* value)
{
    PxConsoleEscSeqnc temp = {0};

    pxiword index = 2;

    if (string.length <= index) return 0;

    if (string.memory[0] != 0x1b) return 0;
    if (string.memory[1] != 0x5b) return 0;

    PxString8 left  = {0};
    PxString8 right = pxString8Slice(string, index, string.length - 1);

    while (right.length > 0) {
        pxString8Split(right, pxs8(";"), &left, &right);

        PxConsoleEscGroup group = {0};

        if (pxConsoleEscGroupFromString8(left, &group) == 0)
            return 0;

        if (pxConsoleEscSeqncInsert(&temp, group) == 0) break;
    }

    temp.func = string.memory[string.length - 1];

    if (value != 0) *value = temp;

    return 1;
}

#endif // PX_CORE_CONSOLE_ESCAPE_C
