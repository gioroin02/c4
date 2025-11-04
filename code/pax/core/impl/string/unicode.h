#ifndef PAX_CORE_STRING_UNICODE_H
#define PAX_CORE_STRING_UNICODE_H

#include "./import.h"

#define PX_ASCII_ITEMS pax_as(paxiword, 128)

typedef enum Pax_ASCII
{
    PAX_ASCII_NULL,
    PAX_ASCII_1,
    PAX_ASCII_2,
    PAX_ASCII_3,
    PAX_ASCII_4,
    PAX_ASCII_5,
    PAX_ASCII_6,
    PAX_ASCII_BELL,
    PAX_ASCII_BACK_SPACE,
    PAX_ASCII_HORIZONTAL_TAB,
    PAX_ASCII_LINE_FEED,
    PAX_ASCII_VERTICAL_TAB,
    PAX_ASCII_PAGE_FEED,
    PAX_ASCII_CARRIAGE_RETURN,
    PAX_ASCII_14,
    PAX_ASCII_15,
    PAX_ASCII_16,
    PAX_ASCII_17,
    PAX_ASCII_18,
    PAX_ASCII_19,
    PAX_ASCII_20,
    PAX_ASCII_21,
    PAX_ASCII_22,
    PAX_ASCII_23,
    PAX_ASCII_CANCEL,
    PAX_ASCII_25,
    PAX_ASCII_26,
    PAX_ASCII_ESCAPE,
    PAX_ASCII_28,
    PAX_ASCII_29,
    PAX_ASCII_30,
    PAX_ASCII_31,
    PAX_ASCII_SPACE,
    PAX_ASCII_EXCLAMATION,
    PAX_ASCII_QUOTE,
    PAX_ASCII_SHARP,
    PAX_ASCII_DOLLAR,
    PAX_ASCII_PERCENT,
    PAX_ASCII_AMPERSAND,
    PAX_ASCII_APOSTROPHE,
    PAX_ASCII_PAREN_LEFT,
    PAX_ASCII_PAREN_RIGHT,
    PAX_ASCII_ASTERISK,
    PAX_ASCII_PLUS,
    PAX_ASCII_COMMA,
    PAX_ASCII_MINUS,
    PAX_ASCII_POINT,
    PAX_ASCII_SLASH,
    PAX_ASCII_ZERO,
    PAX_ASCII_ONE,
    PAX_ASCII_TWO,
    PAX_ASCII_THREE,
    PAX_ASCII_FOUR,
    PAX_ASCII_FIVE,
    PAX_ASCII_SIX,
    PAX_ASCII_SEVEN,
    PAX_ASCII_EIGHT,
    PAX_ASCII_NINE,
    PAX_ASCII_COLON,
    PAX_ASCII_SEMI_COLON,
    PAX_ASCII_LESS,
    PAX_ASCII_EQUAL,
    PAX_ASCII_MORE,
    PAX_ASCII_QUESTION,
    PAX_ASCII_COMMERCIAL,
    PAX_ASCII_UPPER_A,
    PAX_ASCII_UPPER_B,
    PAX_ASCII_UPPER_C,
    PAX_ASCII_UPPER_D,
    PAX_ASCII_UPPER_E,
    PAX_ASCII_UPPER_F,
    PAX_ASCII_UPPER_G,
    PAX_ASCII_UPPER_H,
    PAX_ASCII_UPPER_I,
    PAX_ASCII_UPPER_J,
    PAX_ASCII_UPPER_K,
    PAX_ASCII_UPPER_L,
    PAX_ASCII_UPPER_M,
    PAX_ASCII_UPPER_N,
    PAX_ASCII_UPPER_O,
    PAX_ASCII_UPPER_P,
    PAX_ASCII_UPPER_Q,
    PAX_ASCII_UPPER_R,
    PAX_ASCII_UPPER_S,
    PAX_ASCII_UPPER_T,
    PAX_ASCII_UPPER_U,
    PAX_ASCII_UPPER_V,
    PAX_ASCII_UPPER_W,
    PAX_ASCII_UPPER_X,
    PAX_ASCII_UPPER_Y,
    PAX_ASCII_UPPER_Z,
    PAX_ASCII_SQUARE_LEFT,
    PAX_ASCII_BACK_SLASH,
    PAX_ASCII_SQUARE_RIGHT,
    PAX_ASCII_CIRCUMFLEX,
    PAX_ASCII_UNDER_SCORE,
    PAX_ASCII_BACK_TICK,
    PAX_ASCII_LOWER_A,
    PAX_ASCII_LOWER_B,
    PAX_ASCII_LOWER_C,
    PAX_ASCII_LOWER_D,
    PAX_ASCII_LOWER_E,
    PAX_ASCII_LOWER_F,
    PAX_ASCII_LOWER_G,
    PAX_ASCII_LOWER_H,
    PAX_ASCII_LOWER_I,
    PAX_ASCII_LOWER_J,
    PAX_ASCII_LOWER_K,
    PAX_ASCII_LOWER_L,
    PAX_ASCII_LOWER_M,
    PAX_ASCII_LOWER_N,
    PAX_ASCII_LOWER_O,
    PAX_ASCII_LOWER_P,
    PAX_ASCII_LOWER_Q,
    PAX_ASCII_LOWER_R,
    PAX_ASCII_LOWER_S,
    PAX_ASCII_LOWER_T,
    PAX_ASCII_LOWER_U,
    PAX_ASCII_LOWER_V,
    PAX_ASCII_LOWER_W,
    PAX_ASCII_LOWER_X,
    PAX_ASCII_LOWER_Y,
    PAX_ASCII_LOWER_Z,
    PAX_ASCII_BRACE_LEFT,
    PAX_ASCII_PIPE,
    PAX_ASCII_BRACE_RIGHT,
    PAX_ASCII_TILDE,
    PAX_ASCII_DELETE,
}
Pax_ASCII;

#define PAX_UTF8_UNITS  pax_as(paxiword, 4)
#define PAX_UTF16_UNITS pax_as(paxiword, 2)
#define PAX_UTF32_UNITS pax_as(paxiword, 1)

typedef struct Pax_UTF8
{
    union
    {
        struct
        {
            paxu8 a, b, c, d;
        };

        paxu8 items[PAX_UTF8_UNITS];
    };

    paxiword size;
}
Pax_UTF8;

typedef struct Pax_UTF16
{
    union
    {
        struct
        {
            paxu16 a, b;
        };

        paxu16 items[PAX_UTF16_UNITS];
    };

    paxiword size;
}
Pax_UTF16;

typedef struct Pax_UTF32
{
    union
    {
        struct
        {
            paxu32 a;
        };

        paxu32 items[PAX_UTF32_UNITS];
    };

    paxiword size;
}
Pax_UTF32;

/* Unicode */

paxb8
pax_unicode_is_valid(paxi32 value);

paxb8
pax_unicode_is_surrogate(paxi32 value);

paxb8
pax_unicode_is_surrogate_low(paxi32 value);

paxb8
pax_unicode_is_surrogate_high(paxi32 value);

paxb8
pax_unicode_is_ascii(paxi32 value);

paxb8
pax_unicode_is_ascii_cntrl(paxi32 value);

/* Utf8 */

paxb8
pax_utf8_encode(Pax_UTF8* self, paxi32 value);

paxiword
pax_utf8_write_forw(paxu8* memory, paxiword length, paxiword index, paxi32 value);

paxiword
pax_utf8_write_back(paxu8* memory, paxiword length, paxiword index, paxi32 value);

paxb8
pax_utf8_decode(Pax_UTF8* self, paxi32* value);

paxiword
pax_utf8_read_forw(paxu8* memory, paxiword length, paxiword index, paxi32* value);

paxiword
pax_utf8_read_back(paxu8* memory, paxiword length, paxiword index, paxi32* value);

paxiword
pax_utf8_units_to_write(paxi32 value);

paxiword
pax_utf8_units_to_read(paxu8 value);

paxb8
pax_utf8_is_trailing(paxu8 value);

paxb8
pax_utf8_is_overlong(paxi32 value, paxiword units);

paxiword
pax_utf8_units_from_memory16(paxu16* memory, paxiword length);

paxiword
pax_utf8_units_from_memory32(paxu32* memory, paxiword length);

/* Utf16 */

paxb8
pax_utf16_encode(Pax_UTF16* self, paxi32 value);

paxiword
pax_utf16_write_forw(paxu16* memory, paxiword length, paxiword index, paxi32 value);

paxiword
pax_utf16_write_back(paxu16* memory, paxiword length, paxiword index, paxi32 value);

paxb8
pax_utf16_decode(Pax_UTF16* self, paxi32* value);

paxiword
pax_utf16_read_forw(paxu16* memory, paxiword length, paxiword index, paxi32* value);

paxiword
pax_utf16_read_back(paxu16* memory, paxiword length, paxiword index, paxi32* value);

paxiword
pax_utf16_units_to_write(paxi32 value);

paxiword
pax_utf16_units_to_read(paxu16 value);

paxiword
pax_utf16_units_from_memory8(paxu8* memory, paxiword length);

paxiword
pax_utf16_units_from_memory32(paxu32* memory, paxiword length);

/* Utf32 */

paxb8
pax_utf32_encode(Pax_UTF32* self, paxi32 value);

paxiword
pax_utf32_write_forw(paxu32* memory, paxiword length, paxiword index, paxi32 value);

paxiword
pax_utf32_write_back(paxu32* memory, paxiword length, paxiword index, paxi32 value);

paxb8
pax_utf32_decode(Pax_UTF32* self, paxi32* value);

paxiword
pax_utf32_read_forw(paxu32* memory, paxiword length, paxiword index, paxi32* value);

paxiword
pax_utf32_read_back(paxu32* memory, paxiword length, paxiword index, paxi32* value);

paxiword
pax_utf32_units_to_write(paxi32 value);

paxiword
pax_utf32_units_to_read(paxu32 value);

paxiword
pax_utf32_units_from_memory8(paxu8* memory, paxiword length);

paxiword
pax_utf32_units_from_memory16(paxu16* memory, paxiword length);

#endif // PAX_CORE_STRING_UNICODE_H
