#ifndef PX_CORE_STRING_UNICODE_H
#define PX_CORE_STRING_UNICODE_H

#include "import.h"

#define PX_ASCII_POINTS px_as(pxiword, 128)

typedef enum PxAscii
{
    PX_ASCII_NULL,
    PX_ASCII_1,
    PX_ASCII_2,
    PX_ASCII_3,
    PX_ASCII_4,
    PX_ASCII_5,
    PX_ASCII_6,
    PX_ASCII_BELL,
    PX_ASCII_BACK_SPACE,
    PX_ASCII_HORIZONTAL_TAB,
    PX_ASCII_LINE_FEED,
    PX_ASCII_VERTICAL_TAB,
    PX_ASCII_PAGE_FEED,
    PX_ASCII_CARRIAGE_RETURN,
    PX_ASCII_14,
    PX_ASCII_15,
    PX_ASCII_16,
    PX_ASCII_17,
    PX_ASCII_18,
    PX_ASCII_19,
    PX_ASCII_20,
    PX_ASCII_21,
    PX_ASCII_22,
    PX_ASCII_23,
    PX_ASCII_CANCEL,
    PX_ASCII_25,
    PX_ASCII_26,
    PX_ASCII_ESCAPE,
    PX_ASCII_28,
    PX_ASCII_29,
    PX_ASCII_30,
    PX_ASCII_31,
    PX_ASCII_SPACE,
    PX_ASCII_EXCLAMATION,
    PX_ASCII_QUOTE,
    PX_ASCII_SHARP,
    PX_ASCII_DOLLAR,
    PX_ASCII_PERCENT,
    PX_ASCII_AMPERSAND,
    PX_ASCII_APOSTROPHE,
    PX_ASCII_PAREN_LEFT,
    PX_ASCII_PAREN_RIGHT,
    PX_ASCII_ASTERISK,
    PX_ASCII_PLUS,
    PX_ASCII_COMMA,
    PX_ASCII_MINUS,
    PX_ASCII_POINT,
    PX_ASCII_SLASH,
    PX_ASCII_ZERO,
    PX_ASCII_ONE,
    PX_ASCII_TWO,
    PX_ASCII_THREE,
    PX_ASCII_FOUR,
    PX_ASCII_FIVE,
    PX_ASCII_SIX,
    PX_ASCII_SEVEN,
    PX_ASCII_EIGHT,
    PX_ASCII_NINE,
    PX_ASCII_COLON,
    PX_ASCII_SEMI_COLON,
    PX_ASCII_LESS,
    PX_ASCII_EQUAL,
    PX_ASCII_MORE,
    PX_ASCII_QUESTION,
    PX_ASCII_COMMERCIAL,
    PX_ASCII_UPPER_A,
    PX_ASCII_UPPER_B,
    PX_ASCII_UPPER_C,
    PX_ASCII_UPPER_D,
    PX_ASCII_UPPER_E,
    PX_ASCII_UPPER_F,
    PX_ASCII_UPPER_G,
    PX_ASCII_UPPER_H,
    PX_ASCII_UPPER_I,
    PX_ASCII_UPPER_J,
    PX_ASCII_UPPER_K,
    PX_ASCII_UPPER_L,
    PX_ASCII_UPPER_M,
    PX_ASCII_UPPER_N,
    PX_ASCII_UPPER_O,
    PX_ASCII_UPPER_P,
    PX_ASCII_UPPER_Q,
    PX_ASCII_UPPER_R,
    PX_ASCII_UPPER_S,
    PX_ASCII_UPPER_T,
    PX_ASCII_UPPER_U,
    PX_ASCII_UPPER_V,
    PX_ASCII_UPPER_W,
    PX_ASCII_UPPER_X,
    PX_ASCII_UPPER_Y,
    PX_ASCII_UPPER_Z,
    PX_ASCII_SQUARE_LEFT,
    PX_ASCII_BACK_SLASH,
    PX_ASCII_SQUARE_RIGHT,
    PX_ASCII_CIRCUMFLEX,
    PX_ASCII_UNDER_SCORE,
    PX_ASCII_BACK_TICK,
    PX_ASCII_LOWER_A,
    PX_ASCII_LOWER_B,
    PX_ASCII_LOWER_C,
    PX_ASCII_LOWER_D,
    PX_ASCII_LOWER_E,
    PX_ASCII_LOWER_F,
    PX_ASCII_LOWER_G,
    PX_ASCII_LOWER_H,
    PX_ASCII_LOWER_I,
    PX_ASCII_LOWER_J,
    PX_ASCII_LOWER_K,
    PX_ASCII_LOWER_L,
    PX_ASCII_LOWER_M,
    PX_ASCII_LOWER_N,
    PX_ASCII_LOWER_O,
    PX_ASCII_LOWER_P,
    PX_ASCII_LOWER_Q,
    PX_ASCII_LOWER_R,
    PX_ASCII_LOWER_S,
    PX_ASCII_LOWER_T,
    PX_ASCII_LOWER_U,
    PX_ASCII_LOWER_V,
    PX_ASCII_LOWER_W,
    PX_ASCII_LOWER_X,
    PX_ASCII_LOWER_Y,
    PX_ASCII_LOWER_Z,
    PX_ASCII_BRACE_LEFT,
    PX_ASCII_PIPE,
    PX_ASCII_BRACE_RIGHT,
    PX_ASCII_TILDE,
    PX_ASCII_DELETE,
}
PxAscii;

#define PX_UTF8_UNITS  px_as(pxiword, 4)
#define PX_UTF16_UNITS px_as(pxiword, 2)
#define PX_UTF32_UNITS px_as(pxiword, 1)

typedef struct PxUtf8
{
    union
    {
        struct
        {
            pxu8 a, b, c, d;
        };

        pxu8 items[PX_UTF8_UNITS];
    };

    pxiword size;
}
PxUtf8;

typedef struct PxUtf16
{
    union
    {
        struct
        {
            pxu16 a, b;
        };

        pxu16 items[PX_UTF16_UNITS];
    };

    pxiword size;
}
PxUtf16;

typedef struct PxUtf32
{
    union
    {
        struct
        {
            pxu32 a;
        };

        pxu32 items[PX_UTF32_UNITS];
    };

    pxiword size;
}
PxUtf32;

/* Unicode */

pxb8
pxUnicodeIsValid(pxi32 value);

pxb8
pxUnicodeIsSurrogate(pxi32 value);

pxb8
pxUnicodeIsSurrogateLow(pxi32 value);

pxb8
pxUnicodeIsSurrogateHigh(pxi32 value);

pxb8
pxUnicodeIsAscii(pxi32 value);

pxb8
pxUnicodeIsAsciiCntrl(pxi32 value);

/* Utf8 */

pxb8
pxUtf8Encode(PxUtf8* self, pxi32 value);

pxiword
pxUtf8WriteForw(pxu8* memory, pxiword length, pxiword index, pxi32 value);

pxiword
pxUtf8WriteBack(pxu8* memory, pxiword length, pxiword index, pxi32 value);

pxb8
pxUtf8Decode(PxUtf8* self, pxi32* value);

pxiword
pxUtf8ReadForw(pxu8* memory, pxiword length, pxiword index, pxi32* value);

pxiword
pxUtf8ReadBack(pxu8* memory, pxiword length, pxiword index, pxi32* value);

pxiword
pxUtf8UnitsToWrite(pxi32 value);

pxiword
pxUtf8UnitsToRead(pxu8 value);

pxb8
pxUtf8IsTrailing(pxu8 value);

pxb8
pxUtf8IsOverlong(pxi32 value, pxiword units);

pxiword
pxUtf8UnitsFromMemory16(pxu16* memory, pxiword length);

pxiword
pxUtf8UnitsFromMemory32(pxu32* memory, pxiword length);

/* Utf16 */

pxb8
pxUtf16Encode(PxUtf16* self, pxi32 value);

pxiword
pxUtf16WriteForw(pxu16* memory, pxiword length, pxiword index, pxi32 value);

pxiword
pxUtf16WriteBack(pxu16* memory, pxiword length, pxiword index, pxi32 value);

pxb8
pxUtf16Decode(PxUtf16* self, pxi32* value);

pxiword
pxUtf16ReadForw(pxu16* memory, pxiword length, pxiword index, pxi32* value);

pxiword
pxUtf16ReadBack(pxu16* memory, pxiword length, pxiword index, pxi32* value);

pxiword
pxUtf16UnitsToWrite(pxi32 value);

pxiword
pxUtf16UnitsToRead(pxu16 value);

pxiword
pxUtf16UnitsFromMemory8(pxu8* memory, pxiword length);

pxiword
pxUtf16UnitsFromMemory32(pxu32* memory, pxiword length);

/* Utf32 */

pxb8
pxUtf32Encode(PxUtf32* self, pxi32 value);

pxiword
pxUtf32WriteForw(pxu32* memory, pxiword length, pxiword index, pxi32 value);

pxiword
pxUtf32WriteBack(pxu32* memory, pxiword length, pxiword index, pxi32 value);

pxb8
pxUtf32Decode(PxUtf32* self, pxi32* value);

pxiword
pxUtf32ReadForw(pxu32* memory, pxiword length, pxiword index, pxi32* value);

pxiword
pxUtf32ReadBack(pxu32* memory, pxiword length, pxiword index, pxi32* value);

pxiword
pxUtf32UnitsToWrite(pxi32 value);

pxiword
pxUtf32UnitsToRead(pxu32 value);

pxiword
pxUtf32UnitsFromMemory8(pxu8* memory, pxiword length);

pxiword
pxUtf32UnitsFromMemory16(pxu16* memory, pxiword length);

#endif // PX_CORE_STRING_UNICODE_H
