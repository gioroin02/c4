#ifndef PX_CORE_CONSOLE_COLOR_H
#define PX_CORE_CONSOLE_COLOR_H

#include "import.h"

#define PX_CONSOLE_COLOR_RGB_UNITS px_as(pxiword, 3)

typedef enum PxConsoleColorType
{
    PX_CONSOLE_COLOR_NONE,
    PX_CONSOLE_COLOR_16,
    PX_CONSOLE_COLOR_256,
    PX_CONSOLE_COLOR_RGB,
}
PxConsoleColorType;

typedef struct PxConsoleColor16
{
    pxu8 index;
}
PxConsoleColor16;

typedef struct PxConsoleColor256
{
    pxu8 index;
}
PxConsoleColor256;

typedef union PxConsoleColorRGB
{
    struct
    {
        pxu8 r, g, b;
    };

    pxu8 items[PX_CONSOLE_COLOR_RGB_UNITS];
}
PxConsoleColorRGB;

typedef struct PxConsoleColor
{
    PxConsoleColorType type;

    union
    {
        PxConsoleColor16  color_16;
        PxConsoleColor256 color_256;
        PxConsoleColorRGB color_rgb;
    };
}
PxConsoleColor;

PxConsoleColor
pxConsoleColor16(pxu8 index);

PxConsoleColor
pxConsoleColor256(pxu8 index);

PxConsoleColor
pxConsoleColorRGB(pxu8 r, pxu8 g, pxu8 b);

pxb8
pxConsoleColorIsEqual(PxConsoleColor self, PxConsoleColor value);

pxb8
pxConsoleColor16IsEqual(PxConsoleColor16 self, PxConsoleColor16 value);

pxb8
pxConsoleColor256IsEqual(PxConsoleColor256 self, PxConsoleColor256 value);

pxb8
pxConsoleColorRGBIsEqual(PxConsoleColorRGB self, PxConsoleColorRGB value);

#endif // PX_CORE_CONSOLE_COLOR_H
