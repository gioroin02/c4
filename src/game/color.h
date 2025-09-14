#ifndef C4_GAME_COLOR_H
#define C4_GAME_COLOR_H

#include "import.h"

#define C4_COLOR_RGB_UNITS pxCast(pxiword, 3)

#define C4_COLOR_8_BLACK   (C4Color) {.type = C4_COLOR_8, .color_8 = 0x0}
#define C4_COLOR_8_WHITE   (C4Color) {.type = C4_COLOR_8, .color_8 = 0x7}

#define C4_COLOR_256_BLACK (C4Color) {.type = C4_COLOR_256, .color_256 = 0x00}
#define C4_COLOR_256_WHITE (C4Color) {.type = C4_COLOR_256, .color_256 = 0xff}

#define C4_COLOR_RGB_BLACK (C4Color) {.type = C4_COLOR_RGB, .color_rgb = {0x00, 0x00, 0x00}}
#define C4_COLOR_RGB_WHITE (C4Color) {.type = C4_COLOR_RGB, .color_rgb = {0xff, 0xff, 0xff}}

typedef enum C4ColorType
{
    C4_COLOR_NONE,
    C4_COLOR_8,
    C4_COLOR_256,
    C4_COLOR_RGB,
}
C4ColorType;

typedef pxu8 C4Color8;
typedef pxu8 C4Color256;

typedef union C4ColorRGB
{
    struct
    {
        pxu8 r, g, b;
    };

    pxu8 items[C4_COLOR_RGB_UNITS];
}
C4ColorRGB;

typedef struct C4Color
{
    C4ColorType type;

    union
    {
        C4Color8   color_8;
        C4Color256 color_256;
        C4ColorRGB color_rgb;
    };
}
C4Color;

C4Color
c4Color8(pxu8 value);

C4Color
c4Color256(pxu8 value);

C4Color
c4ColorRGB(pxu8 r, pxu8 g, pxu8 b);

pxb8
c4ColorIsEqual(C4Color self, C4Color value);

pxb8
c4Color8IsEqual(C4Color8 self, C4Color8 value);

pxb8
c4Color256IsEqual(C4Color256 self, C4Color256 value);

pxb8
c4ColorRGBIsEqual(C4ColorRGB self, C4ColorRGB value);

pxb8
c4JsonWriteColor(C4Color* self, PxJsonWriter* writer, PxArena* arena);

pxb8
c4JsonWriteColorRGB(C4ColorRGB* self, PxJsonWriter* writer, PxArena* arena);

pxb8
c4JsonReadColor(C4Color* self, PxJsonReader* reader, PxArena* arena);

pxb8
c4JsonReadColorRGB(C4ColorRGB* self, PxJsonReader* reader, PxArena* arena);

pxiword
c4FormatProcColor(C4Color* self, PxBuilder* builder);

pxiword
c4FormatProcColor8(C4Color8* self, PxBuilder* builder);

pxiword
c4FormatProcColor256(C4Color256* self, PxBuilder* builder);

pxiword
c4FormatProcColorRGB(C4ColorRGB* self, PxBuilder* builder);

#endif // C4_GAME_COLOR_H
