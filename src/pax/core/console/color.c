#ifndef PX_CORE_CONSOLE_COLOR_C
#define PX_CORE_CONSOLE_COLOR_C

#include "color.h"

PxConsoleColor
pxConsoleColor16(pxu8 index)
{
    return (PxConsoleColor) {
        .type = PX_CONSOLE_COLOR_16,

        .color_16 = {
            .index = index,
        },
    };
}

PxConsoleColor
pxConsoleColor256(pxu8 index)
{
    return (PxConsoleColor) {
        .type = PX_CONSOLE_COLOR_256,

        .color_256 = {
            .index = index,
        },
    };
}

PxConsoleColor
pxConsoleColorRGB(pxu8 r, pxu8 g, pxu8 b)
{
    return (PxConsoleColor) {
        .type = PX_CONSOLE_COLOR_RGB,

        .color_rgb = {
            .r = r,
            .g = g,
            .b = b,
        },
    };
}

pxb8
pxConsoleColorIsEqual(PxConsoleColor self, PxConsoleColor value)
{
    if (self.type != value.type) return 0;

    switch (self.type) {
        case PX_CONSOLE_COLOR_16:
            return pxConsoleColor16IsEqual(self.color_16, value.color_16);

        case PX_CONSOLE_COLOR_256:
            return pxConsoleColor256IsEqual(self.color_256, value.color_256);

        case PX_CONSOLE_COLOR_RGB:
            return pxConsoleColorRGBIsEqual(self.color_rgb, value.color_rgb);

        default: break;
    }

    return 0;
}

pxb8
pxConsoleColor16IsEqual(PxConsoleColor16 self, PxConsoleColor16 value)
{
    return self.index == value.index ? 1 : 0;
}

pxb8
pxConsoleColor256IsEqual(PxConsoleColor256 self, PxConsoleColor256 value)
{
    return self.index = value.index ? 1 : 0;
}

pxb8
pxConsoleColorRGBIsEqual(PxConsoleColorRGB self, PxConsoleColorRGB value)
{
    if (self.r != value.r) return 0;
    if (self.g != value.g) return 0;
    if (self.b != value.b) return 0;

    return 1;
}

#endif // PX_CORE_CONSOLE_COLOR_C
