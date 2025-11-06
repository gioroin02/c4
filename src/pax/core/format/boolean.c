#ifndef PX_CORE_FORMAT_BOOLEAN_C
#define PX_CORE_FORMAT_BOOLEAN_C

#include "boolean.h"

#define PX_STRING_8_LOWER_FALSE  pxString8Vargs('f', 'a', 'l', 's', 'e')
#define PX_STRING_16_LOWER_FALSE pxString16Vargs('f', 'a', 'l', 's', 'e')
#define PX_STRING_32_LOWER_FALSE pxString32Vargs('f', 'a', 'l', 's', 'e')

#define PX_STRING_8_UPPER_FALSE  pxString8Vargs('F', 'A', 'L', 'S', 'E')
#define PX_STRING_16_UPPER_FALSE pxString16Vargs('F', 'A', 'L', 'S', 'E')
#define PX_STRING_32_UPPER_FALSE pxString32Vargs('F', 'A', 'L', 'S', 'E')

#define PX_STRING_8_LOWER_TRUE  pxString8Vargs('t', 'r', 'u', 'e')
#define PX_STRING_16_LOWER_TRUE pxString16Vargs('t', 'r', 'u', 'e')
#define PX_STRING_32_LOWER_TRUE pxString32Vargs('t', 'r', 'u', 'e')

#define PX_STRING_8_UPPER_TRUE  pxString8Vargs('T', 'R', 'U', 'E')
#define PX_STRING_16_UPPER_TRUE pxString16Vargs('T', 'R', 'U', 'E')
#define PX_STRING_32_UPPER_TRUE pxString32Vargs('T', 'R', 'U', 'E')

static const PxString8 PX_STRING_8_BOOLEANS[] =
{
    PX_STRING_8_LOWER_FALSE,
    PX_STRING_8_UPPER_FALSE,
    PX_STRING_8_LOWER_TRUE,
    PX_STRING_8_UPPER_TRUE,
};

static const PxString16 PX_STRING_16_BOOLEANS[] =
{
    PX_STRING_16_LOWER_FALSE,
    PX_STRING_16_UPPER_FALSE,
    PX_STRING_16_LOWER_TRUE,
    PX_STRING_16_UPPER_TRUE,
};

static const PxString32 PX_STRING_32_BOOLEANS[] =
{
    PX_STRING_32_LOWER_FALSE,
    PX_STRING_32_UPPER_FALSE,
    PX_STRING_32_LOWER_TRUE,
    PX_STRING_32_UPPER_TRUE,
};

pxiword
pxBooleanDigits(pxbword value, PxFormatFlag flags)
{
    return value != 0 ? 4 : 5;
}

pxiword
pxMemory8WriteBoolean(pxu8* memory, pxiword length, pxbword value, PxFormatFlag flags)
{
    pxiword size  = pxBooleanDigits(value, flags);
    pxiword index = 0;
    pxuword upper = flags & PX_FORMAT_FLAG_UPPER;

    if (size <= 0 || size > length) return 0;

    index += value != 0 ? 2 : 0;
    index += upper != 0 ? 1 : 0;

    pxMemory8WriteString8(memory, length,
        PX_STRING_8_BOOLEANS[index]);

    return size;
}

pxiword
pxMemory8ReadBoolean(pxu8* memory, pxiword length, pxbword* value, PxFormatFlag flags)
{
    pxiword index = 0;

    if (length <= 0) return 0;

    switch (memory[0]) {
        case PX_ASCII_LOWER_F: index = 0; break;
        case PX_ASCII_UPPER_F: index = 1; break;
        case PX_ASCII_LOWER_T: index = 2; break;
        case PX_ASCII_UPPER_T: index = 3; break;

        default: return 0;
    }

    PxString8 string = PX_STRING_8_BOOLEANS[index];

    if (pxString8IsEqualMemory8(string, memory, length) == 0)
        return 0;

    if (value != 0) *value = index >= 2 ? 1 : 0;

    return length;
}

pxiword
pxMemory16WriteBoolean(pxu16* memory, pxiword length, pxbword value, PxFormatFlag flags)
{
    pxiword size  = pxBooleanDigits(value, flags);
    pxiword index = 0;
    pxuword upper = flags & PX_FORMAT_FLAG_UPPER;

    if (size <= 0 || size > length) return 0;

    index += value != 0 ? 2 : 0;
    index += upper != 0 ? 1 : 0;

    pxMemory16WriteString16(memory, length,
        PX_STRING_16_BOOLEANS[index]);

    return size;
}

pxiword
pxMemory16ReadBoolean(pxu16* memory, pxiword length, pxbword* value, PxFormatFlag flags)
{
    pxiword index = 0;

    if (length <= 0) return 0;

    switch (memory[0]) {
        case PX_ASCII_LOWER_F: index = 0; break;
        case PX_ASCII_UPPER_F: index = 1; break;
        case PX_ASCII_LOWER_T: index = 2; break;
        case PX_ASCII_UPPER_T: index = 3; break;

        default: return 0;
    }

    PxString16 string = PX_STRING_16_BOOLEANS[index];

    if (pxString16IsEqualMemory16(string, memory, length) == 0)
        return 0;

    if (value != 0) *value = index >= 2 ? 1 : 0;

    return length;
}

pxiword
pxMemory32WriteBoolean(pxu32* memory, pxiword length, pxbword value, PxFormatFlag flags)
{
    pxiword size  = pxBooleanDigits(value, flags);
    pxiword index = 0;
    pxuword upper = flags & PX_FORMAT_FLAG_UPPER;

    if (size <= 0 || size > length) return 0;

    index += value != 0 ? 2 : 0;
    index += upper != 0 ? 1 : 0;

    pxMemory32WriteString32(memory, length,
        PX_STRING_32_BOOLEANS[index]);

    return size;
}

pxiword
pxMemory32ReadBoolean(pxu32* memory, pxiword length, pxbword* value, PxFormatFlag flags)
{
    pxiword index = 0;

    if (length <= 0) return 0;

    switch (memory[0]) {
        case PX_ASCII_LOWER_F: index = 0; break;
        case PX_ASCII_UPPER_F: index = 1; break;
        case PX_ASCII_LOWER_T: index = 2; break;
        case PX_ASCII_UPPER_T: index = 3; break;

        default: return 0;
    }

    PxString32 string = PX_STRING_32_BOOLEANS[index];

    if (pxString32IsEqualMemory32(string, memory, length) == 0)
        return 0;

    if (value != 0) *value = index >= 2 ? 1 : 0;

    return length;
}

PxString8
pxString8FromBoolean(PxArena* arena, pxbword value, PxFormatFlag flags)
{
    pxiword offset = pxArenaOffset(arena);
    pxiword length = pxBooleanDigits(value, flags);

    pxu8* memory =
        pxArenaReserve(arena, pxu8, length + 1);

    pxiword size = pxMemory8WriteBoolean(
        memory, length, value, flags);

    if (size == length)
        return pxString8Make(memory, length);

    pxArenaRewind(arena, offset);

    return (PxString8) {0};
}

pxb8
pxBooleanFromString8(PxString8 string, pxbword* value, PxFormatFlag flags)
{
    pxu8*   memory = string.memory;
    pxiword length = string.length;

    pxiword size = pxMemory8ReadBoolean(
        memory, length, value, flags);

    if (size == length) return 1;

    return 0;
}

PxString16
pxString16FromBoolean(PxArena* arena, pxbword value, PxFormatFlag flags)
{
    pxiword offset = pxArenaOffset(arena);
    pxiword length = pxBooleanDigits(value, flags);

    pxu16* memory =
        pxArenaReserve(arena, pxu16, length + 1);

    pxiword size = pxMemory16WriteBoolean(
        memory, length, value, flags);

    if (size == length)
        return pxString16Make(memory, length);

    pxArenaRewind(arena, offset);

    return (PxString16) {0};
}

pxb8
pxBooleanFromString16(PxString16 string, pxbword* value, PxFormatFlag flags)
{
    pxu16*  memory = string.memory;
    pxiword length = string.length;

    pxiword size = pxMemory16ReadBoolean(
        memory, length, value, flags);

    if (size == length) return 1;

    return 0;
}

PxString32
pxString32FromBoolean(PxArena* arena, pxbword value, PxFormatFlag flags)
{
    pxiword offset = pxArenaOffset(arena);
    pxiword length = pxBooleanDigits(value, flags);

    pxu32* memory =
        pxArenaReserve(arena, pxu32, length + 1);

    pxiword size = pxMemory32WriteBoolean(
        memory, length, value, flags);

    if (size == length)
        return pxString32Make(memory, length);

    pxArenaRewind(arena, offset);

    return (PxString32) {0};
}

pxb8
pxBooleanFromString32(PxString32 string, pxbword* value, PxFormatFlag flags)
{
    pxu32*  memory = string.memory;
    pxiword length = string.length;

    pxiword size = pxMemory32ReadBoolean(
        memory, length, value, flags);

    if (size == length) return 1;

    return 0;
}

#endif // PX_CORE_FORMAT_BOOLEAN_C
