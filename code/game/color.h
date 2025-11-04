#ifndef C4_GAME_COLOR_H
#define C4_GAME_COLOR_H

#include "./import.h"

#define c4_color_index(value) \
    (C4_Color) {.kind = C4_COLOR_KIND_INDEX, .color_index = value}

#define c4_color_rgba(r, g, b, a) \
    (C4_Color) {.kind = C4_COLOR_KIND_RGBA, .color_rgba = {r, g, b, a}}

typedef enum C4_Color_Kind
{
    C4_COLOR_KIND_NONE,
    C4_COLOR_KIND_INDEX,
    C4_COLOR_KIND_RGBA,
}
C4_Color_Kind;

typedef paxu8 C4_Color_Index;

typedef union C4_Color_RGBA
{
    struct {
        paxu8 r;
        paxu8 g;
        paxu8 b;
        paxu8 a;
    };

    paxu8 items[4];
}
C4_Color_RGBA;

typedef struct C4_Color
{
    C4_Color_Kind kind;

    union
    {
        C4_Color_Index color_index;
        C4_Color_RGBA  color_rgba;
    };
}
C4_Color;

#endif // C4_GAME_COLOR_H
