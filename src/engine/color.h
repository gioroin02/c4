#ifndef C4_ENGINE_COLOR_H
#define C4_ENGINE_COLOR_H

#include "import.h"

#define C4_COLOR_16_BLACK       pxConsoleColor16(0x0)
#define C4_COLOR_16_GREY_BRIGHT pxConsoleColor16(0x7)
#define C4_COLOR_16_GREY_DARK   pxConsoleColor16(0x8)
#define C4_COLOR_16_WHITE       pxConsoleColor16(0xf)

#define C4_COLOR_16_RED_DARK     pxConsoleColor16(0x1)
#define C4_COLOR_16_GREEN_DARK   pxConsoleColor16(0x2)
#define C4_COLOR_16_YELLOW_DARK  pxConsoleColor16(0x3)
#define C4_COLOR_16_BLUE_DARK    pxConsoleColor16(0x4)
#define C4_COLOR_16_MAGENTA_DARK pxConsoleColor16(0x5)
#define C4_COLOR_16_CYAN_DARK    pxConsoleColor16(0x6)

#define C4_COLOR_16_RED_BRIGHT     pxConsoleColor16(0x9)
#define C4_COLOR_16_GREEN_BRIGHT   pxConsoleColor16(0xa)
#define C4_COLOR_16_YELLOW_BRIGHT  pxConsoleColor16(0xb)
#define C4_COLOR_16_BLUE_BRIGHT    pxConsoleColor16(0xc)
#define C4_COLOR_16_MAGENTA_BRIGHT pxConsoleColor16(0xd)
#define C4_COLOR_16_CYAN_BRIGHT    pxConsoleColor16(0xe)

#define C4_COLOR_256_BLACK pxConsoleColor256(0x00)
#define C4_COLOR_256_WHITE pxConsoleColor256(0xff)

#define C4_COLOR_RGB_BLACK pxConsoleColorRGB(0x00, 0x00, 0x00)
#define C4_COLOR_RGB_WHITE pxConsoleColorRGB(0xff, 0xff, 0xff)

/* JSON writing */

pxb8
c4JsonWriteConsoleColor(PxConsoleColor* self, PxJsonWriter* writer, PxArena* arena);

pxb8
c4JsonWriteConsoleColor16(PxConsoleColor16* self, PxJsonWriter* writer, PxArena* arena);

pxb8
c4JsonWriteConsoleColor256(PxConsoleColor256* self, PxJsonWriter* writer, PxArena* arena);

pxb8
c4JsonWriteConsoleColorRGB(PxConsoleColorRGB* self, PxJsonWriter* writer, PxArena* arena);

/* JSON reading */

pxb8
c4JsonReadConsoleColor(PxConsoleColor* self, PxJsonReader* reader, PxArena* arena);

pxb8
c4JsonReadConsoleColor16(PxConsoleColor16* self, PxJsonReader* reader, PxArena* arena);

pxb8
c4JsonReadConsoleColor256(PxConsoleColor256* self, PxJsonReader* reader, PxArena* arena);

pxb8
c4JsonReadConsoleColorRGB(PxConsoleColorRGB* self, PxJsonReader* reader, PxArena* arena);

#endif // C4_ENGINE_COLOR_H
