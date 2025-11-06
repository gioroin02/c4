#ifndef PX_CORE_STRING_UNICODE_C
#define PX_CORE_STRING_UNICODE_C

#include "unicode.h"

pxb8
pxUnicodeIsValid(pxi32 value)
{
    if (value >= 0x0 && value <= 0xd7ff)
        return 1;

    if (value >= 0xe000 && value <= 0x10ffff)
        return 1;

    return 0;
}

pxb8
pxUnicodeIsSurrogate(pxi32 value)
{
    if (value >= 0xd800 && value <= 0xdfff)
        return 1;

    return 0;
}

pxb8
pxUnicodeIsSurrogateLow(pxi32 value)
{
    if (value >= 0xdc00 && value <= 0xdfff)
        return 1;

    return 0;
}

pxb8
pxUnicodeIsSurrogateHigh(pxi32 value)
{
    if (value >= 0xd800 && value <= 0xdbff)
        return 1;

    return 0;
}

pxb8
pxUnicodeIsAscii(pxi32 value)
{
    if (value >= 0x0 && value <= 0x7f)
        return 1;

    return 0;
}

pxb8
pxUnicodeIsAsciiCntrl(pxi32 value)
{
    if (value >= 0x0 && value <= 0x20)
        return 1;

    return 0;
}

pxb8
pxUtf8Encode(PxUtf8* self, pxi32 value)
{
    pxiword units = pxUtf8UnitsToWrite(value);

    pxMemoryZero(self->items, PX_UTF8_UNITS, 1);

    self->size = 0;

    switch (units) {
        case 1: self->a = px_as(pxu8, value); break;

        case 2:
            self->a = px_as(pxu8, ((value >> 6) & 0xff) | 0xc0);
            self->b = px_as(pxu8, ((value >> 0) & 0x3f) | 0x80);
        break;

        case 3:
            self->a = px_as(pxu8, ((value >> 12) & 0xff) | 0xe0);
            self->b = px_as(pxu8, ((value >>  6) & 0x3f) | 0x80);
            self->c = px_as(pxu8, ((value >>  0) & 0x3f) | 0x80);
        break;

        case 4:
            self->a = px_as(pxu8, ((value >> 18) & 0xff) | 0xf0);
            self->b = px_as(pxu8, ((value >> 12) & 0x3f) | 0x80);
            self->c = px_as(pxu8, ((value >>  6) & 0x3f) | 0x80);
            self->d = px_as(pxu8, ((value >>  0) & 0x3f) | 0x80);
        break;

        default: return 0;
    }

    self->size = units;

    return 1;
}

pxiword
pxUtf8WriteForw(pxu8* memory, pxiword length, pxiword index, pxi32 value)
{
    PxUtf8 utf8 = {0};

    if (pxUtf8Encode(&utf8, value) == 0) return 0;

    if (index < 0 || index + utf8.size > length)
        return 0;

    for (pxiword i = 0; i < utf8.size; i += 1)
        memory[index + i] = utf8.items[i];

    return utf8.size;
}

pxiword
pxUtf8WriteBack(pxu8* memory, pxiword length, pxiword index, pxi32 value)
{
    PxUtf8 utf8 = {0};

    if (pxUtf8Encode(&utf8, value) == 0) return 0;

    if (index - utf8.size < 0 || index >= length)
        return 0;

    for (pxiword i = 0; i < utf8.size; i += 1)
        memory[index - utf8.size + i] = utf8.items[i];

    return utf8.size;
}

pxb8
pxUtf8Decode(PxUtf8* self, pxi32* value)
{
    pxiword units = pxUtf8UnitsToRead(self->items[0]);
    pxi32   temp  = 0;

    if (self->size != units) return 0;

    switch (units) {
        case 1: temp = self->a; break;

        case 2:
            if (pxUtf8IsTrailing(self->b) == 0) return 0;

            temp  = (self->a & 0x1f) << 6;
            temp += (self->b & 0x3f) << 0;
        break;

        case 3:
            if (pxUtf8IsTrailing(self->b) == 0) return 0;
            if (pxUtf8IsTrailing(self->c) == 0) return 0;

            temp  = (self->a & 0x0f) << 12;
            temp += (self->b & 0x3f) << 6;
            temp += (self->c & 0x3f) << 0;
        break;

        case 4:
            if (pxUtf8IsTrailing(self->b) == 0) return 0;
            if (pxUtf8IsTrailing(self->c) == 0) return 0;
            if (pxUtf8IsTrailing(self->d) == 0) return 0;

            temp  = (self->a & 0x07) << 18;
            temp += (self->b & 0x3f) << 12;
            temp += (self->c & 0x3f) << 6;
            temp += (self->d & 0x3f) << 0;
        break;

        default: return 0;
    }

    if (pxUtf8IsOverlong(temp, units) != 0)
        return 0;

    if (pxUnicodeIsValid(temp) == 0) return 0;

    if (value != 0) *value = temp;

    return 1;
}

pxiword
pxUtf8ReadForw(pxu8* memory, pxiword length, pxiword index, pxi32* value)
{
    PxUtf8 utf8 = {0};

    if (index >= 0 && index < length)
        utf8.size = pxUtf8UnitsToRead(memory[index]);

    if (utf8.size <= 0 || index + utf8.size > length)
        return 0;

    for (pxiword i = 0; i < utf8.size; i += 1)
        utf8.items[i] = memory[index + i];

    if (pxUtf8Decode(&utf8, value) == 0) return 0;

    return utf8.size;
}

pxiword
pxUtf8ReadBack(pxu8* memory, pxiword length, pxiword index, pxi32* value)
{
    PxUtf8  utf8  = {0};
    pxiword start = index;

    if (index < 0 || index >= length) return 0;

    while (pxUtf8IsTrailing(memory[index]) != 0) {
        index -= 1;

        if (index < 0 || index >= length)
            return 0;
    }

    utf8.size = start - index + 1;

    if (utf8.size != pxUtf8UnitsToRead(memory[index]))
        return 0;

    for (pxiword i = 0; i < utf8.size; i += 1)
        utf8.items[i] = memory[index + i];

    if (pxUtf8Decode(&utf8, value) == 0) return 0;

    return utf8.size;
}

pxiword
pxUtf8UnitsToWrite(pxi32 value)
{
    if (value >=     0x0 && value <=     0x7f) return 1;
    if (value >=    0x80 && value <=    0x7ff) return 2;
    if (value >=   0x800 && value <=   0xd7ff) return 3;
    if (value >=  0xe000 && value <=   0xffff) return 3;
    if (value >= 0x10000 && value <= 0x10ffff) return 4;

    return 0;
}

pxiword
pxUtf8UnitsToRead(pxu8 value)
{
    if (value >=  0x0 && value <= 0x7f) return 1;
    if (value >= 0xc0 && value <= 0xdf) return 2;
    if (value >= 0xe0 && value <= 0xef) return 3;
    if (value >= 0xf0 && value <= 0xf7) return 4;

    return 0;
}

pxb8
pxUtf8IsTrailing(pxu8 value)
{
    return (value & 0xc0) == 0x80 ? 1 : 0;
}

pxb8
pxUtf8IsOverlong(pxi32 value, pxiword units)
{
    if (value >=     0xc080 && value <=     0xc1ff && units == 2) return 1;
    if (value >=   0xe08080 && value <=   0xe09fff && units == 3) return 1;
    if (value >= 0xf0808080 && value <= 0xf0bfffff && units == 4) return 1;

    return 0;
}

pxiword
pxUtf8UnitsFromMemory16(pxu16* memory, pxiword length)
{
    pxiword result = 0;

    for (pxiword index = 0; index < length;) {
        pxi32 unicode = 0;

        pxiword read = pxUtf16ReadForw(
            memory, length, index, &unicode);

        pxiword write = pxUtf8UnitsToWrite(unicode);

        if (read <= 0 || write <= 0) return 0;

        index  += read;
        result += write;
    }

    return result;
}

pxiword
pxUtf8UnitsFromMemory32(pxu32* memory, pxiword length)
{
    pxiword result = 0;

    for (pxiword index = 0; index < length;) {
        pxi32 unicode = 0;

        pxiword read = pxUtf32ReadForw(
            memory, length, index, &unicode);

        pxiword write = pxUtf8UnitsToWrite(unicode);

        if (read <= 0 || write <= 0) return 0;

        index  += read;
        result += write;
    }

    return result;
}

pxb8
pxUtf16Encode(PxUtf16* self, pxi32 value)
{
    pxiword units = pxUtf16UnitsToWrite(value);

    pxMemoryZero(self->items, PX_UTF16_UNITS, 2);

    self->size = 0;

    switch (units) {
        case 1: self->a = px_as(pxu16, value); break;

        case 2:
            self->a = px_as(pxu16, (((value - 0x10000) >> 10) & 0xffff) | 0xd800);
            self->b = px_as(pxu16, (((value - 0x10000) >>  0) & 0x03ff) | 0xdc00);
        break;

        default: return 0;
    }

    self->size = units;

    return 1;
}

pxiword
pxUtf16WriteForw(pxu16* memory, pxiword length, pxiword index, pxi32 value)
{
    PxUtf16 utf16 = {0};

    if (pxUtf16Encode(&utf16, value) == 0) return 0;

    if (index < 0 || index + utf16.size > length)
        return 0;

    for (pxiword i = 0; i < utf16.size; i += 1)
        memory[index + i] = utf16.items[i];

    return utf16.size;
}

pxiword
pxUtf16WriteBack(pxu16* memory, pxiword length, pxiword index, pxi32 value)
{
    PxUtf16 utf16 = {0};

    if (pxUtf16Encode(&utf16, value) == 0) return 0;

    if (index - utf16.size < 0 || index >= length)
        return 0;

    for (pxiword i = 0; i < utf16.size; i += 1)
        memory[index - utf16.size + i] = utf16.items[i];

    return utf16.size;
}

pxb8
pxUtf16Decode(PxUtf16* self, pxi32* value)
{
    pxiword units = pxUtf16UnitsToRead(self->items[0]);
    pxi32   temp  = 0;

    if (self->size != units) return 0;

    switch (units) {
        case 1: temp = self->a; break;

        case 2:
            if (pxUnicodeIsSurrogateHigh(self->b) == 0)
                return 0;

            temp += (self->a - 0xd800) << 10;
            temp += (self->b - 0xdc00) <<  0;
            temp += 0x10000;
        break;

        default: return 0;
    }

    if (pxUnicodeIsValid(temp) == 0) return 0;

    if (value != 0) *value = temp;

    return 1;
}

pxiword
pxUtf16ReadForw(pxu16* memory, pxiword length, pxiword index, pxi32* value)
{
    PxUtf16 utf16 = {0};

    if (index >= 0 && index < length)
        utf16.size = pxUtf16UnitsToRead(memory[index]);

    if (utf16.size <= 0 || index + utf16.size > length)
        return 0;

    for (pxiword i = 0; i < utf16.size; i += 1)
        utf16.items[i] = memory[index + i];

    if (pxUtf16Decode(&utf16, value) == 0) return 0;

    return utf16.size;
}

pxiword
pxUtf16ReadBack(pxu16* memory, pxiword length, pxiword index, pxi32* value)
{
    PxUtf16 utf16 = {0};
    pxiword start = index;

    if (index < 0 || index >= length) return 0;

    while (pxUnicodeIsSurrogateLow(memory[index]) != 0) {
        index -= 1;

        if (index < 0 || index >= length)
            return 0;
    }

    utf16.size = start - index + 1;

    if (utf16.size != pxUtf16UnitsToRead(memory[index]))
        return 0;

    for (pxiword i = 0; i < utf16.size; i += 1)
        utf16.items[i] = memory[index + i];

    if (pxUtf16Decode(&utf16, value) == 0) return 0;

    return utf16.size;
}

pxiword
pxUtf16UnitsToWrite(pxi32 value)
{
    if (value >=     0x0 && value <=   0xd7ff) return 1;
    if (value >=  0xe000 && value <=   0xffff) return 1;
    if (value >= 0x10000 && value <= 0x10ffff) return 2;

    return 0;
}

pxiword
pxUtf16UnitsToRead(pxu16 value)
{
    if (value >=    0x0 && value <= 0xd7ff) return 1;
    if (value >= 0xd800 && value <= 0xdbff) return 2;
    if (value >= 0xe000 && value <= 0xffff) return 1;

    return 0;
}

pxiword
pxUtf16UnitsFromMemory8(pxu8* memory, pxiword length)
{
    pxiword result = 0;

    for (pxiword index = 0; index < length;) {
        pxi32 unicode = 0;

        pxiword read = pxUtf8ReadForw(
            memory, length, index, &unicode);

        pxiword write = pxUtf16UnitsToWrite(unicode);

        if (read <= 0 || write <= 0) return 0;

        index  += read;
        result += write;
    }

    return result;
}

pxiword
pxUtf16UnitsFromMemory32(pxu32* memory, pxiword length)
{
    pxiword result = 0;

    for (pxiword index = 0; index < length;) {
        pxi32 unicode = 0;

        pxiword read = pxUtf32ReadForw(
            memory, length, index, &unicode);

        pxiword write = pxUtf16UnitsToWrite(unicode);

        if (read <= 0 || write <= 0) return 0;

        index  += read;
        result += write;
    }

    return result;
}

pxb8
pxUtf32Encode(PxUtf32* self, pxi32 value)
{
    pxiword units = pxUtf32UnitsToWrite(value);

    pxMemoryZero(self->items, PX_UTF32_UNITS, 4);

    self->size = 0;

    switch (units) {
        case 1:
            self->a = px_as(pxu32, value);
        break;

        default: return 0;
    }

    self->size = units;

    return 1;
}

pxiword
pxUtf32WriteForw(pxu32* memory, pxiword length, pxiword index, pxi32 value)
{
    PxUtf32 utf32 = {0};

    if (pxUtf32Encode(&utf32, value) == 0) return 0;

    if (index < 0 || index + utf32.size > length)
        return 0;

    for (pxiword i = 0; i < utf32.size; i += 1)
        memory[index + i] = utf32.items[i];

    return utf32.size;
}

pxiword
pxUtf32WriteBack(pxu32* memory, pxiword length, pxiword index, pxi32 value)
{
    PxUtf32 utf32 = {0};

    if (pxUtf32Encode(&utf32, value) == 0) return 0;

    if (index - utf32.size < 0 || index >= length)
        return 0;

    for (pxiword i = 0; i < utf32.size; i += 1)
        memory[index - utf32.size + i] = utf32.items[i];

    return utf32.size;
}

pxb8
pxUtf32Decode(PxUtf32* self, pxi32* value)
{
    pxiword units = pxUtf32UnitsToRead(self->items[0]);
    pxi32   temp  = 0;

    if (self->size != units) return 0;

    switch (units) {
        case 1: temp = self->a; break;

        default: return 0;
    }

    if (pxUnicodeIsValid(temp) == 0) return 0;

    if (value != 0) *value = temp;

    return 1;
}

pxiword
pxUtf32ReadForw(pxu32* memory, pxiword length, pxiword index, pxi32* value)
{
    PxUtf32 utf32 = {0};

    if (index >= 0 && index < length)
        utf32.size = pxUtf32UnitsToRead(memory[index]);

    if (utf32.size <= 0 || index + utf32.size > length)
        return 0;

    for (pxiword i = 0; i < utf32.size; i += 1)
        utf32.items[i] = memory[index + i];

    if (pxUtf32Decode(&utf32, value) == 0) return 0;

    return utf32.size;
}

pxiword
pxUtf32ReadBack(pxu32* memory, pxiword length, pxiword index, pxi32* value)
{
    PxUtf32 utf32 = {.size = 1};

    if (index < 0 || index >= length) return 0;

    if (utf32.size != pxUtf32UnitsToRead(memory[index]))
        return 0;

    for (pxiword i = 0; i < utf32.size; i += 1)
        utf32.items[i] = memory[index + i];

    if (pxUtf32Decode(&utf32, value) == 0) return 0;

    return utf32.size;
}

pxiword
pxUtf32UnitsToWrite(pxi32 value)
{
    if (value >=    0x0 && value <=   0xd7ff) return 1;
    if (value >= 0xe000 && value <= 0x10ffff) return 1;

    return 0;
}

pxiword
pxUtf32UnitsToRead(pxu32 value)
{
    if (value >=    0x0 && value <=   0xd7ff) return 1;
    if (value >= 0xe000 && value <= 0x10ffff) return 1;

    return 0;
}

pxiword
pxUtf32UnitsFromMemory8(pxu8* memory, pxiword length)
{
    pxiword result = 0;

    for (pxiword index = 0; index < length;) {
        pxi32 unicode = 0;

        pxiword read = pxUtf8ReadForw(
            memory, length, index, &unicode);

        pxiword write = pxUtf32UnitsToWrite(unicode);

        if (read <= 0 || write <= 0) return 0;

        index  += read;
        result += write;
    }

    return result;
}

pxiword
pxUtf32UnitsFromMemory16(pxu16* memory, pxiword length)
{
    pxiword result = 0;

    for (pxiword index = 0; index < length;) {
        pxi32 unicode = 0;

        pxiword read = pxUtf16ReadForw(
            memory, length, index, &unicode);

        pxiword write = pxUtf32UnitsToWrite(unicode);

        if (read <= 0 || write <= 0) return 0;

        index  += read;
        result += write;
    }

    return result;
}

#endif // PX_CORE_STRING_UNICODE_C
