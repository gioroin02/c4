#ifndef PAX_CORE_STRING_UNICODE_C
#define PAX_CORE_STRING_UNICODE_C

#include "./unicode.h"

paxb8
pax_unicode_is_valid(paxi32 value)
{
    if (value >= 0x0 && value <= 0xd7ff) return 1;

    if (value >= 0xe000 && value <= 0x10ffff)
        return 1;

    return 0;
}

paxb8
pax_unicode_is_surrogate(paxi32 value)
{
    if (value >= 0xd800 && value <= 0xdfff)
        return 1;

    return 0;
}

paxb8
pax_unicode_is_surrogate_low(paxi32 value)
{
    if (value >= 0xdc00 && value <= 0xdfff)
        return 1;

    return 0;
}

paxb8
pax_unicode_is_surrogate_high(paxi32 value)
{
    if (value >= 0xd800 && value <= 0xdbff)
        return 1;

    return 0;
}

paxb8
pax_unicode_is_ascii(paxi32 value)
{
    if (value >= 0x00 && value <= 0x7f)
        return 1;

    return 0;
}

paxb8
pax_unicode_is_ascii_cntrl(paxi32 value)
{
    if (value >= 0x01 && value <= 0x20)
        return 1;

    return 0;
}

paxb8
pax_utf8_encode(Pax_UTF8* self, paxi32 value)
{
    paxiword units = pax_utf8_units_to_write(value);

    for (paxiword i = 0; i < PAX_UTF8_UNITS; i += 1)
        self->items[i] = 0;

    self->size = 0;

    switch (units) {
        case 1: self->a = pax_as(paxu8, value); break;

        case 2:
            self->a = pax_as(paxu8, ((value >> 6) & 0xff) | 0xc0);
            self->b = pax_as(paxu8, ((value >> 0) & 0x3f) | 0x80);
        break;

        case 3:
            self->a = pax_as(paxu8, ((value >> 12) & 0xff) | 0xe0);
            self->b = pax_as(paxu8, ((value >>  6) & 0x3f) | 0x80);
            self->c = pax_as(paxu8, ((value >>  0) & 0x3f) | 0x80);
        break;

        case 4:
            self->a = pax_as(paxu8, ((value >> 18) & 0xff) | 0xf0);
            self->b = pax_as(paxu8, ((value >> 12) & 0x3f) | 0x80);
            self->c = pax_as(paxu8, ((value >>  6) & 0x3f) | 0x80);
            self->d = pax_as(paxu8, ((value >>  0) & 0x3f) | 0x80);
        break;

        default: return 0;
    }

    self->size = units;

    return 1;
}

paxiword
pax_utf8_write_forw(paxu8* memory, paxiword length, paxiword index, paxi32 value)
{
    Pax_UTF8 utf8 = {0};

    if (pax_utf8_encode(&utf8, value) == 0) return 0;

    if (index < 0 || index + utf8.size > length)
        return 0;

    for (paxiword i = 0; i < utf8.size; i += 1)
        memory[index + i] = utf8.items[i];

    return utf8.size;
}

paxiword
pax_utf8_write_back(paxu8* memory, paxiword length, paxiword index, paxi32 value)
{
    Pax_UTF8 utf8 = {0};

    if (pax_utf8_encode(&utf8, value) == 0) return 0;

    if (index - utf8.size < 0 || index >= length)
        return 0;

    for (paxiword i = 0; i < utf8.size; i += 1)
        memory[index - utf8.size + i] = utf8.items[i];

    return utf8.size;
}

paxb8
pax_utf8_decode(Pax_UTF8* self, paxi32* value)
{
    paxiword units = pax_utf8_units_to_read(self->items[0]);
    paxi32   temp  = 0;

    if (self->size != units) return 0;

    switch (units) {
        case 1: temp = self->a; break;

        case 2:
            if (pax_utf8_is_trailing(self->b) == 0) return 0;

            temp  = (self->a & 0x1f) << 6;
            temp += (self->b & 0x3f) << 0;
        break;

        case 3:
            if (pax_utf8_is_trailing(self->b) == 0) return 0;
            if (pax_utf8_is_trailing(self->c) == 0) return 0;

            temp  = (self->a & 0x0f) << 12;
            temp += (self->b & 0x3f) << 6;
            temp += (self->c & 0x3f) << 0;
        break;

        case 4:
            if (pax_utf8_is_trailing(self->b) == 0) return 0;
            if (pax_utf8_is_trailing(self->c) == 0) return 0;
            if (pax_utf8_is_trailing(self->d) == 0) return 0;

            temp  = (self->a & 0x07) << 18;
            temp += (self->b & 0x3f) << 12;
            temp += (self->c & 0x3f) << 6;
            temp += (self->d & 0x3f) << 0;
        break;

        default: return 0;
    }

    if (pax_utf8_is_overlong(temp, units) != 0)
        return 0;

    if (pax_unicode_is_valid(temp) == 0) return 0;

    if (value != 0) *value = temp;

    return 1;
}

paxiword
pax_utf8_read_forw(paxu8* memory, paxiword length, paxiword index, paxi32* value)
{
    Pax_UTF8 utf8 = {0};

    if (index >= 0 && index < length)
        utf8.size = pax_utf8_units_to_read(memory[index]);

    if (utf8.size <= 0 || index + utf8.size > length)
        return 0;

    for (paxiword i = 0; i < utf8.size; i += 1)
        utf8.items[i] = memory[index + i];

    if (pax_utf8_decode(&utf8, value) == 0) return 0;

    return utf8.size;
}

paxiword
pax_utf8_read_back(paxu8* memory, paxiword length, paxiword index, paxi32* value)
{
    Pax_UTF8 utf8  = {0};
    paxiword start = index;

    if (index < 0 || index >= length) return 0;

    while (pax_utf8_is_trailing(memory[index]) != 0) {
        index -= 1;

        if (index < 0 || index >= length)
            return 0;
    }

    utf8.size = start - index + 1;

    if (utf8.size != pax_utf8_units_to_read(memory[index]))
        return 0;

    for (paxiword i = 0; i < utf8.size; i += 1)
        utf8.items[i] = memory[index + i];

    if (pax_utf8_decode(&utf8, value) == 0) return 0;

    return utf8.size;
}

paxiword
pax_utf8_units_to_write(paxi32 value)
{
    if (value >=     0x0 && value <=     0x7f) return 1;
    if (value >=    0x80 && value <=    0x7ff) return 2;
    if (value >=   0x800 && value <=   0xd7ff) return 3;
    if (value >=  0xe000 && value <=   0xffff) return 3;
    if (value >= 0x10000 && value <= 0x10ffff) return 4;

    return 0;
}

paxiword
pax_utf8_units_to_read(paxu8 value)
{
    if (value >=  0x0 && value <= 0x7f) return 1;
    if (value >= 0xc0 && value <= 0xdf) return 2;
    if (value >= 0xe0 && value <= 0xef) return 3;
    if (value >= 0xf0 && value <= 0xf7) return 4;

    return 0;
}

paxb8
pax_utf8_is_trailing(paxu8 value)
{
    return (value & 0xc0) == 0x80 ? 1 : 0;
}

paxb8
pax_utf8_is_overlong(paxi32 value, paxiword units)
{
    if (value >=     0xc080 && value <=     0xc1ff && units == 2) return 1;
    if (value >=   0xe08080 && value <=   0xe09fff && units == 3) return 1;
    if (value >= 0xf0808080 && value <= 0xf0bfffff && units == 4) return 1;

    return 0;
}

paxiword
pax_utf8_units_from_memory16(paxu16* memory, paxiword length)
{
    paxiword result  = 0;
    paxi32   unicode = 0;

    for (paxiword index = 0; index < length;) {
        paxiword read =
            pax_utf16_read_forw(memory, length, index, &unicode);

        paxiword write = pax_utf8_units_to_write(unicode);

        if (read <= 0 || write <= 0) return 0;

        index  += read;
        result += write;
    }

    return result;
}

paxiword
pax_utf8_units_from_memory32(paxu32* memory, paxiword length)
{
    paxiword result  = 0;
    paxi32   unicode = 0;

    for (paxiword index = 0; index < length;) {
        paxiword read =
            pax_utf32_read_forw(memory, length, index, &unicode);

        paxiword write = pax_utf8_units_to_write(unicode);

        if (read <= 0 || write <= 0) return 0;

        index  += read;
        result += write;
    }

    return result;
}

paxb8
pax_utf16_encode(Pax_UTF16* self, paxi32 value)
{
    paxiword units = pax_utf16_units_to_write(value);

    for (paxiword i = 0; i < PAX_UTF16_UNITS; i += 1)
        self->items[i] = 0;

    self->size = 0;

    switch (units) {
        case 1: self->a = pax_as(paxu16, value); break;

        case 2:
            self->a = pax_as(paxu16, (((value - 0x10000) >> 10) & 0xffff) | 0xd800);
            self->b = pax_as(paxu16, (((value - 0x10000) >>  0) & 0x03ff) | 0xdc00);
        break;

        default: return 0;
    }

    self->size = units;

    return 1;
}

paxiword
pax_utf16_write_forw(paxu16* memory, paxiword length, paxiword index, paxi32 value)
{
    Pax_UTF16 utf16 = {0};

    if (pax_utf16_encode(&utf16, value) == 0) return 0;

    if (index < 0 || index + utf16.size > length)
        return 0;

    for (paxiword i = 0; i < utf16.size; i += 1)
        memory[index + i] = utf16.items[i];

    return utf16.size;
}

paxiword
pax_utf16_write_back(paxu16* memory, paxiword length, paxiword index, paxi32 value)
{
    Pax_UTF16 utf16 = {0};

    if (pax_utf16_encode(&utf16, value) == 0) return 0;

    if (index - utf16.size < 0 || index >= length)
        return 0;

    for (paxiword i = 0; i < utf16.size; i += 1)
        memory[index - utf16.size + i] = utf16.items[i];

    return utf16.size;
}

paxb8
pax_utf16_decode(Pax_UTF16* self, paxi32* value)
{
    paxiword units = pax_utf16_units_to_read(self->items[0]);
    paxi32   temp  = 0;

    if (self->size != units) return 0;

    switch (units) {
        case 1: temp = self->a; break;

        case 2:
            if (pax_unicode_is_surrogate_low(self->b) == 0)
                return 0;

            temp += (self->a - 0xd800) << 10;
            temp += (self->b - 0xdc00) <<  0;
            temp += 0x10000;
        break;

        default: return 0;
    }

    if (pax_unicode_is_valid(temp) == 0) return 0;

    if (value != 0) *value = temp;

    return 1;
}

paxiword
pax_utf16_read_forw(paxu16* memory, paxiword length, paxiword index, paxi32* value)
{
    Pax_UTF16 utf16 = {0};

    if (index >= 0 && index < length)
        utf16.size = pax_utf16_units_to_read(memory[index]);

    if (utf16.size <= 0 || index + utf16.size > length)
        return 0;

    for (paxiword i = 0; i < utf16.size; i += 1)
        utf16.items[i] = memory[index + i];

    if (pax_utf16_decode(&utf16, value) == 0) return 0;

    return utf16.size;
}

paxiword
pax_utf16_read_back(paxu16* memory, paxiword length, paxiword index, paxi32* value)
{
    Pax_UTF16 utf16 = {0};
    paxiword  start = index;

    if (index < 0 || index >= length) return 0;

    while (pax_unicode_is_surrogate_low(memory[index]) != 0) {
        index -= 1;

        if (index < 0 || index >= length)
            return 0;
    }

    utf16.size = start - index + 1;

    if (utf16.size != pax_utf16_units_to_read(memory[index]))
        return 0;

    for (paxiword i = 0; i < utf16.size; i += 1)
        utf16.items[i] = memory[index + i];

    if (pax_utf16_decode(&utf16, value) == 0) return 0;

    return utf16.size;
}

paxiword
pax_utf16_units_to_write(paxi32 value)
{
    if (value >=     0x0 && value <=   0xd7ff) return 1;
    if (value >=  0xe000 && value <=   0xffff) return 1;
    if (value >= 0x10000 && value <= 0x10ffff) return 2;

    return 0;
}

paxiword
pax_utf16_units_to_read(paxu16 value)
{
    if (value >=    0x0 && value <= 0xd7ff) return 1;
    if (value >= 0xd800 && value <= 0xdbff) return 2;
    if (value >= 0xe000 && value <= 0xffff) return 1;

    return 0;
}

paxiword
pax_utf16_units_from_memory8(paxu8* memory, paxiword length)
{
    paxiword result  = 0;
    paxi32   unicode = 0;

    for (paxiword index = 0; index < length;) {
        paxiword read =
            pax_utf8_read_forw(memory, length, index, &unicode);

        paxiword write = pax_utf16_units_to_write(unicode);

        if (read <= 0 || write <= 0) return 0;

        index  += read;
        result += write;
    }

    return result;
}

paxiword
pax_utf16_units_from_memory32(paxu32* memory, paxiword length)
{
    paxiword result  = 0;
    paxi32   unicode = 0;

    for (paxiword index = 0; index < length;) {
        paxiword read =
            pax_utf32_read_forw(memory, length, index, &unicode);

        paxiword write = pax_utf16_units_to_write(unicode);

        if (read <= 0 || write <= 0) return 0;

        index  += read;
        result += write;
    }

    return result;
}

paxb8
pax_utf32_encode(Pax_UTF32* self, paxi32 value)
{
    paxiword units = pax_utf32_units_to_write(value);

    for (paxiword i = 0; i < PAX_UTF32_UNITS; i += 1)
        self->items[i] = 0;

    self->size = 0;

    switch (units) {
        case 1:
            self->a = pax_as(paxu32, value);
        break;

        default: return 0;
    }

    self->size = units;

    return 1;
}

paxiword
pax_utf32_write_forw(paxu32* memory, paxiword length, paxiword index, paxi32 value)
{
    Pax_UTF32 utf32 = {0};

    if (pax_utf32_encode(&utf32, value) == 0) return 0;

    if (index < 0 || index + utf32.size > length)
        return 0;

    for (paxiword i = 0; i < utf32.size; i += 1)
        memory[index + i] = utf32.items[i];

    return utf32.size;
}

paxiword
pax_utf32_write_back(paxu32* memory, paxiword length, paxiword index, paxi32 value)
{
    Pax_UTF32 utf32 = {0};

    if (pax_utf32_encode(&utf32, value) == 0) return 0;

    if (index - utf32.size < 0 || index >= length)
        return 0;

    for (paxiword i = 0; i < utf32.size; i += 1)
        memory[index - utf32.size + i] = utf32.items[i];

    return utf32.size;
}

paxb8
pax_utf32_decode(Pax_UTF32* self, paxi32* value)
{
    paxiword units = pax_utf32_units_to_read(self->items[0]);
    paxi32   temp  = 0;

    if (self->size != units) return 0;

    switch (units) {
        case 1: temp = self->a; break;

        default: return 0;
    }

    if (pax_unicode_is_valid(temp) == 0) return 0;

    if (value != 0) *value = temp;

    return 1;
}

paxiword
pax_utf32_read_forw(paxu32* memory, paxiword length, paxiword index, paxi32* value)
{
    Pax_UTF32 utf32 = {0};

    if (index >= 0 && index < length)
        utf32.size = pax_utf32_units_to_read(memory[index]);

    if (utf32.size <= 0 || index + utf32.size > length)
        return 0;

    for (paxiword i = 0; i < utf32.size; i += 1)
        utf32.items[i] = memory[index + i];

    if (pax_utf32_decode(&utf32, value) == 0) return 0;

    return utf32.size;
}

paxiword
pax_utf32_read_back(paxu32* memory, paxiword length, paxiword index, paxi32* value)
{
    Pax_UTF32 utf32 = {.size = 1};

    if (index < 0 || index >= length) return 0;

    if (utf32.size != pax_utf32_units_to_read(memory[index]))
        return 0;

    for (paxiword i = 0; i < utf32.size; i += 1)
        utf32.items[i] = memory[index + i];

    if (pax_utf32_decode(&utf32, value) == 0) return 0;

    return utf32.size;
}

paxiword
pax_utf32_units_to_write(paxi32 value)
{
    if (value >=    0x0 && value <=   0xd7ff) return 1;
    if (value >= 0xe000 && value <= 0x10ffff) return 1;

    return 0;
}

paxiword
pax_utf32_units_to_read(paxu32 value)
{
    if (value >=    0x0 && value <=   0xd7ff) return 1;
    if (value >= 0xe000 && value <= 0x10ffff) return 1;

    return 0;
}

paxiword
pax_utf32_units_from_memory8(paxu8* memory, paxiword length)
{
    paxiword result  = 0;
    paxi32   unicode = 0;

    for (paxiword index = 0; index < length;) {
        paxiword read =
            pax_utf8_read_forw(memory, length, index, &unicode);

        paxiword write = pax_utf32_units_to_write(unicode);

        if (read <= 0 || write <= 0) return 0;

        index  += read;
        result += write;
    }

    return result;
}

paxiword
pax_utf32_units_from_memory16(paxu16* memory, paxiword length)
{
    paxiword result  = 0;
    paxi32   unicode = 0;

    for (paxiword index = 0; index < length;) {
        paxiword read =
            pax_utf16_read_forw(memory, length, index, &unicode);

        paxiword write = pax_utf32_units_to_write(unicode);

        if (read <= 0 || write <= 0) return 0;

        index  += read;
        result += write;
    }

    return result;
}

#endif // PAX_CORE_STRING_UNICODE_C
