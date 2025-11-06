#ifndef PX_ENCODING_JSON_SCANNER_C
#define PX_ENCODING_JSON_SCANNER_C

#include "scanner.h"

static pxb8
pxJsonIsString(pxu8 value)
{
    if (value != PX_ASCII_NULL && value != PX_ASCII_QUOTE)
        return 1;

    return 0;
}

static pxb8
pxJsonIsNumber(pxu8 value)
{
    if (value >= PX_ASCII_ZERO && value <= PX_ASCII_NINE)
        return 1;

    if (value == PX_ASCII_PLUS)  return 1;
    if (value == PX_ASCII_MINUS) return 1;
    if (value == PX_ASCII_POINT) return 1;

    if (value == PX_ASCII_LOWER_E) return 1;
    if (value == PX_ASCII_UPPER_E) return 1;

    return 0;
}

static pxb8
pxJsonIsWord(pxu8 value)
{
    if (value >= PX_ASCII_LOWER_A && value <= PX_ASCII_LOWER_Z)
        return 1;

    if (value >= PX_ASCII_UPPER_A && value <= PX_ASCII_UPPER_Z)
        return 1;

    return 0;
}

pxu8
pxSourceDropJsonSpaces(PxSource source)
{
    pxu8 byte = pxSourcePeekByte(source);

    while (pxUnicodeIsAsciiCntrl(byte) != 0 && byte != 0) {
        pxSourceDrop(source, 1);

        byte = pxSourcePeekByte(source);
    }

    return byte;
}

PxString8
pxSourceMatchJsonSymbol(PxSource source, PxArena* arena, pxiword length, PxJsonTokenType* type)
{
    if (length <= 0) return pxString8Make(0, 0);

    pxu8*   memory = pxArenaReserve(arena, pxu8, length + 1);
    pxiword size   = 1;

    PxJsonTokenType result = PX_JSON_TOKEN_ERROR;

    if (memory == 0) return pxString8Make(0, 0);

    memory[size - 1] = pxSourceReadByte(source);

    switch (memory[size - 1]) {
        case PX_ASCII_BRACE_LEFT:
            result = PX_JSON_TOKEN_OBJECT_OPEN;
        break;

        case PX_ASCII_BRACE_RIGHT:
            result = PX_JSON_TOKEN_OBJECT_CLOSE;
        break;

        case PX_ASCII_SQUARE_LEFT:
            result = PX_JSON_TOKEN_ARRAY_OPEN;
        break;

        case PX_ASCII_SQUARE_RIGHT:
            result = PX_JSON_TOKEN_ARRAY_CLOSE;
        break;

        case PX_ASCII_COLON:
            result = PX_JSON_TOKEN_COLON;
        break;

        case PX_ASCII_COMMA:
            result = PX_JSON_TOKEN_COMMA;
        break;

        default: break;
    }

    if (type != 0) *type = result;

    return pxString8Make(memory, size);
}

PxString8
pxSourceMatchJsonString(PxSource source, PxArena* arena, pxiword length, PxJsonTokenType* type)
{
    if (length <= 2) return pxString8Make(0, 0);

    pxu8*   memory = pxArenaReserve(arena, pxu8, length + 1);
    pxiword size   = 0;

    if (memory == 0) return pxString8Make(0, 0);

    pxu8 byte = pxSourceReadByte(source);

    if (byte != PX_ASCII_QUOTE) {
        if (type != 0)
            *type = PX_JSON_TOKEN_ERROR;

        return pxString8Make(memory, size);
    }

    byte = pxSourcePeekByte(source);

    for (; pxJsonIsString(byte) != 0; size += 1) {
        if (size >= length) {
            if (type != 0)
                *type = PX_JSON_TOKEN_ERROR;

            return pxString8Make(memory, size);
        }

        memory[size] = pxSourceReadByte(source);

        byte = pxSourcePeekByte(source);
    }

    byte = pxSourceReadByte(source);

    if (byte != PX_ASCII_QUOTE) {
        if (type != 0)
            *type = PX_JSON_TOKEN_ERROR;

        return pxString8Make(memory, size);
    }

    if (type != 0) *type = PX_JSON_TOKEN_STRING;

    return pxString8Make(memory, size);
}

PxString8
pxSourceMatchJsonNumber(PxSource source, PxArena* arena, pxiword length, PxJsonTokenType* type)
{
    if (length <= 0) return pxString8Make(0, 0);

    pxu8*   memory = pxArenaReserve(arena, pxu8, length + 1);
    pxiword size   = 0;

    PxJsonTokenType result = PX_JSON_TOKEN_NONE;

    if (memory == 0) return pxString8Make(0, 0);

    pxu8 byte = pxSourcePeekByte(source);

    for (; pxJsonIsNumber(byte) != 0; size += 1) {
        if (size >= length) {
            if (type != 0)
                *type = PX_JSON_TOKEN_ERROR;

            return pxString8Make(memory, size);
        }

        memory[size] = pxSourceReadByte(source);

        switch (byte) {
            case PX_ASCII_PLUS:
            case PX_ASCII_ZERO:
            case PX_ASCII_ONE:
            case PX_ASCII_TWO:
            case PX_ASCII_THREE:
            case PX_ASCII_FOUR:
            case PX_ASCII_FIVE:
            case PX_ASCII_SIX:
            case PX_ASCII_SEVEN:
            case PX_ASCII_EIGHT:
            case PX_ASCII_NINE: {
                if (result == PX_JSON_TOKEN_NONE)
                    result = PX_JSON_TOKEN_UNSIGNED;
            } break;

            case PX_ASCII_MINUS: {
                if (result == PX_JSON_TOKEN_NONE)
                    result = PX_JSON_TOKEN_INTEGER;
            } break;

            case PX_ASCII_POINT:
            case PX_ASCII_LOWER_E:
            case PX_ASCII_UPPER_E:
                result = PX_JSON_TOKEN_FLOATING;
            break;
        }

        byte = pxSourcePeekByte(source);
    }

    if (type != 0) *type = result;

    return pxString8Make(memory, size);
}

PxString8
pxSourceMatchJsonWord(PxSource source, PxArena* arena, pxiword length, PxJsonTokenType* type)
{
    if (length <= 0) return pxString8Make(0, 0);

    pxu8*   memory = pxArenaReserve(arena, pxu8, length + 1);
    pxiword size   = 0;

    PxJsonTokenType result = PX_JSON_TOKEN_NONE;

    if (memory == 0) return pxString8Make(0, 0);

    pxu8 byte = pxSourcePeekByte(source);

    for (; pxJsonIsWord(byte) != 0; size += 1) {
        if (size >= length) {
            if (type != 0)
                *type = PX_JSON_TOKEN_ERROR;

            return pxString8Make(memory, size);
        }

        memory[size] = pxSourceReadByte(source);

        byte = pxSourcePeekByte(source);
    }

    if (pxString8IsEqualMemory8(pxs8("true"), memory, size) != 0)
        result = PX_JSON_TOKEN_BOOLEAN;

    if (pxString8IsEqualMemory8(pxs8("false"), memory, size) != 0)
        result = PX_JSON_TOKEN_BOOLEAN;

    if (pxString8IsEqualMemory8(pxs8("null"), memory, size) != 0)
        result = PX_JSON_TOKEN_NULL;

    if (result == PX_JSON_TOKEN_NONE) result = PX_JSON_TOKEN_ERROR;

    if (type != 0) *type = result;

    return pxString8Make(memory, size);
}

PxJsonToken
pxSourceReadJsonToken(PxSource source, PxArena* arena)
{
    pxiword offset = pxArenaOffset(arena);

    pxu8 byte = pxSourceDropJsonSpaces(source);

    PxJsonTokenType type   = PX_JSON_TOKEN_NULL;
    PxString8       string = {0};

    switch (byte) {
        case PX_ASCII_NULL: return pxJsonTokenCount();

        case PX_ASCII_BRACE_LEFT:
        case PX_ASCII_BRACE_RIGHT:
        case PX_ASCII_SQUARE_LEFT:
        case PX_ASCII_SQUARE_RIGHT:
        case PX_ASCII_COLON:
        case PX_ASCII_COMMA:
            string = pxSourceMatchJsonSymbol(source, arena, 4, &type);
        break;

        case PX_ASCII_QUOTE:
            string = pxSourceMatchJsonString(source, arena, PX_MEMORY_KIB, &type);
        break;

        case PX_ASCII_PLUS:
        case PX_ASCII_MINUS:
        case PX_ASCII_ZERO:
        case PX_ASCII_ONE:
        case PX_ASCII_TWO:
        case PX_ASCII_THREE:
        case PX_ASCII_FOUR:
        case PX_ASCII_FIVE:
        case PX_ASCII_SIX:
        case PX_ASCII_SEVEN:
        case PX_ASCII_EIGHT:
        case PX_ASCII_NINE:
            string = pxSourceMatchJsonNumber(source, arena, 64, &type);
        break;

        case PX_ASCII_LOWER_T:
        case PX_ASCII_LOWER_F:
        case PX_ASCII_LOWER_N:
            string = pxSourceMatchJsonWord(source, arena, 8, &type);
        break;

        default: break;
    }

    PxFormatRadix radix = PX_FORMAT_RADIX_10;
    PxFormatFlag  flags = PX_FORMAT_FLAG_PLUS;

    PxJsonToken result = {0};

    switch (type) {
        case PX_JSON_TOKEN_STRING: {
            if (string.length < PX_MEMORY_KIB)
                pxArenaRewind(arena, offset + string.length + 1);

            return pxJsonTokenString(string);
        } break;

        case PX_JSON_TOKEN_UNSIGNED: {
            pxuword value = 0;
            pxb8    state = pxUnsignedFromString8(string, &value, radix, flags);

            pxArenaRewind(arena, offset);

            if (state == 0)
                return pxJsonTokenError();

            return pxJsonTokenUnsigned(value);
        } break;

        case PX_JSON_TOKEN_INTEGER: {
            pxiword value = 0;
            pxb8    state = pxIntegerFromString8(string, &value, radix, flags);

            pxArenaRewind(arena, offset);

            if ( state == 0)
                return pxJsonTokenError();

            return pxJsonTokenInteger(value);
        } break;

        case PX_JSON_TOKEN_FLOATING: {
            pxfword value = 0;
            pxb8    state = 0; /* pxFloatingFromString8(string, &value, radix, flags); */

            pxArenaRewind(arena, offset);

            if (state == 0)
                return pxJsonTokenError();

            return pxJsonTokenFloating(value);
        } break;

        case PX_JSON_TOKEN_BOOLEAN: {
            pxbword value = 0;
            pxb8    state = pxBooleanFromString8(string, &value, flags);

            pxArenaRewind(arena, offset);

            if (state == 0)
                return pxJsonTokenError();

            return pxJsonTokenBoolean(value);
        } break;

        default: break;
    }

    pxArenaRewind(arena, offset);

    switch (type) {
        case PX_JSON_TOKEN_OBJECT_OPEN:  return pxJsonTokenObjectOpen();
        case PX_JSON_TOKEN_OBJECT_CLOSE: return pxJsonTokenObjectClose();
        case PX_JSON_TOKEN_ARRAY_OPEN:   return pxJsonTokenArrayOpen();
        case PX_JSON_TOKEN_ARRAY_CLOSE:  return pxJsonTokenArrayClose();
        case PX_JSON_TOKEN_COLON:        return pxJsonTokenColon();
        case PX_JSON_TOKEN_COMMA:        return pxJsonTokenComma();
        case PX_JSON_TOKEN_NULL:         return pxJsonTokenNull();

        default: break;
    }

    return pxJsonTokenMake(type);
}

#endif // PX_ENCODING_JSON_SCANNER_C
