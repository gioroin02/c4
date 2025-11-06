#ifndef PX_CORE_FORMAT_PRINTING_C
#define PX_CORE_FORMAT_PRINTING_C

#include "printing.h"

static PxString8
pxString8MatchFormatSpec(PxString8 string)
{
    pxu8*   memory = string.memory;
    pxiword length = string.length;
    pxiword index  = 0;

    if (memory == 0 || length <= 2) return (PxString8) {0};

    if (memory[index] != PX_ASCII_BRACE_LEFT)
        return (PxString8) {0};

    for (index += 1; memory[index] != PX_ASCII_BRACE_RIGHT;) {
        if (index + 1 >= length)
            return (PxString8) {0};

        index += 1;
    }

    return pxString8Make(memory + 1, index - 1);
}

pxiword
pxTargetPrintUnsigned(PxTarget target, pxuword value, PxFormatRadix radix, PxFormatFlag flags)
{
    pxu8 memory[64] = {0};

    pxiword size = pxMemory8WriteUnsigned(
        memory, px_size_array(pxu8, memory), value, radix, flags);

    return pxTargetWriteMemory8(target, memory, size);
}

pxiword
pxTargetPrintInteger(PxTarget target, pxiword value, PxFormatRadix radix, PxFormatFlag flags)
{
    pxu8 memory[64] = {0};

    pxiword size = pxMemory8WriteInteger(
        memory, px_size_array(pxu8, memory), value, radix, flags);

    return pxTargetWriteMemory8(target, memory, size);
}

pxiword
pxTargetPrintBoolean(PxTarget target, pxbword value, PxFormatFlag flags)
{
    pxu8 memory[64] = {0};

    pxiword size = pxMemory8WriteBoolean(
        memory, px_size_array(pxu8, memory), value, flags);

    return pxTargetWriteMemory8(target, memory, size);
}

pxb8
pxTargetFormatMsg(PxTarget target, PxFormatMsg value, pxiword* size)
{
    pxiword result = 0;
    pxb8    state  = 0;

    switch (value.type) {
        case PX_FORMAT_MSG_STRING_8: {
            result = pxTargetWriteString8(target, value.string_8);

            if (result == value.string_8.length)
                state = 1;
        } break;

        case PX_FORMAT_MSG_STRING_16: {
            result = pxTargetWriteString16(target, value.string_16);

            if (result == value.string_16.length)
                state = 1;
        } break;

        case PX_FORMAT_MSG_STRING_32: {
            result = pxTargetWriteString32(target, value.string_32);

            if (result == value.string_32.length)
                state = 1;
        } break;

        case PX_FORMAT_MSG_UNICODE: {
            result = pxTargetWriteUnicode(target, value.unicode);

            if (result != 0) state = 1;
        } break;

        case PX_FORMAT_MSG_UNSIGNED: {
            result = pxTargetPrintUnsigned(target,
                value.unsigned_word, value.radix, value.flags);

            if (result != 0) state = 1;
        } break;

        case PX_FORMAT_MSG_INTEGER: {
            result = pxTargetPrintInteger(target,
                value.integer_word, value.radix, value.flags);

            if (result != 0) state = 1;
        } break;

        case PX_FORMAT_MSG_FLOATING: {
            /* result = pxTargetPrintFloating(target,
                value.floating_word, value.radix, value.flags);

            if (result != 0) */ state = 1;
        } break;

        case PX_FORMAT_MSG_BOOLEAN: {
            result = pxTargetPrintBoolean(target,
                value.boolean_word, value.flags);

            if (result != 0) state = 1;
        } break;

        default: break;
    }

    if (size != 0) *size = result;

    return state;
}

pxb8
pxTargetPrintList(PxTarget target, PxFormatMsg* values, pxiword length, pxiword* size)
{
    pxiword result = 0;

    for (pxiword i = 0; i < length; i += 1) {
        pxiword temp = 0;

        if (pxTargetFormatMsg(target, values[i], &temp) == 0)
            return 0;

        result += temp;
    }

    if (size != 0) *size = result;

    return 1;
}

pxb8
pxTargetPrintFormat(PxTarget target, PxString8 format, PxFormatMsg* values, pxiword length, pxiword* size)
{
    PxString8 left  = {0};
    PxString8 right = format;

    pxiword result = 0;
    pxiword index  = 0;

    while (right.length > 0) {
        pxiword temp = 0;

        pxString8Split(right, pxs8("$"), &left, &right);

        if (pxTargetFormatMsg(target, pxFormatMsgString8(left), &temp) == 0)
            return 0;

        result += temp;

        left  = pxString8MatchFormatSpec(right);
        right = pxString8SliceHead(right, left.length + 2);

        if (pxIntegerFromString8(left, &index, 10, 0) == 0)
            continue;

        if (left.length > 0 && index >= 0 && index < length) {
            if (pxTargetFormatMsg(target, values[index], &temp) == 0)
                return 0;

            result += temp;
        }
    }

    if (size != 0) *size = result;

    return 1;
}

#endif // PX_CORE_FORMAT_PRINTING_C
