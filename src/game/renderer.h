#ifndef C4_GAME_RENDERER_H
#define C4_GAME_RENDERER_H

#include "import.h"

typedef enum C4ColorType
{
    PX_CONSOLE_COLOR_NONE,
    PX_CONSOLE_COLOR_INDEX,
    PX_CONSOLE_COLOR_RGBA,
}
C4ColorType;

typedef pxu8 C4ColorIndex;

typedef union C4ColorRGBA
{
    struct {
        pxu8 r;
        pxu8 g;
        pxu8 b;
        pxu8 a;
    };

    pxu8 items[4];
}
C4ColorRGBA;

typedef struct C4Color
{
    C4ColorType type;

    union
    {
        C4ColorIndex color_index;
        C4ColorRGBA  color_rgba;
    };
}
C4Color;

typedef struct C4FrameElement
{
    pxi32   unicode;
    C4Color foreground;
    C4Color background;
}
C4FrameElement;

typedef struct C4FrameBuffer
{
    PxArray items;

    pxiword width;
    pxiword height;
}
C4FrameBuffer;

typedef PxWriter C4Renderer;

C4FrameBuffer
c4FrameBufferMake(PxArena* arena, pxiword width, pxiword height);

pxb8
c4FrameBufferRead(C4FrameBuffer* self, pxiword x, pxiword y, C4FrameElement* value);

C4FrameElement
c4FrameBufferReadOr(C4FrameBuffer* self, pxiword x, pxiword y, C4FrameElement value);

pxb8
c4FrameBufferUpdate(C4FrameBuffer* self, pxiword x, pxiword y, C4FrameElement value);

pxb8
c4FrameBufferReset(C4FrameBuffer* self, pxi32 unicode, C4Color foreground, C4Color background);

pxb8
c4FrameBufferPaint(C4FrameBuffer* self, pxiword x, pxiword y, pxi32 unicode, C4Color foreground, C4Color background);

C4Renderer
c4RendererMake(PxConsole console, PxArena* arena, pxiword length);

void
c4RendererFlush(C4Renderer* writer);

pxiword
c4RendererMoveUp(C4Renderer* self, PxArena* arena, pxu8 amount);

pxiword
c4RendererMoveDown(C4Renderer* self, PxArena* arena, pxu8 amount);

pxiword
c4RendererMoveLeft(C4Renderer* self, PxArena* arena, pxu8 amount);

pxiword
c4RendererMoveRight(C4Renderer* self, PxArena* arena, pxu8 amount);

pxiword
c4RendererMoveTo(C4Renderer* self, PxArena* arena, pxiword x, pxiword y);

pxiword
c4RendererShowCursor(C4Renderer* self, pxb8 state);

pxiword
c4RendererReset(C4Renderer* self, pxb8 scroll);

pxiword
c4RendererForeground(C4Renderer* self, PxArena* arena, C4Color color);

pxiword
c4RendererForegroundIndex(C4Renderer* self, PxArena* arena, C4ColorIndex color);

pxiword
c4RendererForegroundRGBA(C4Renderer* self, PxArena* arena, C4ColorRGBA color);

pxiword
c4RendererBackground(C4Renderer* self, PxArena* arena, C4Color color);

pxiword
c4RendererBackgroundIndex(C4Renderer* self, PxArena* arena, C4ColorIndex color);

pxiword
c4RendererBackgroundRGBA(C4Renderer* self, PxArena* arena, C4ColorRGBA color);

pxiword
c4RendererUnicode(C4Renderer* self, PxArena* arena, pxi32 value);

void
c4RendererFrame(C4Renderer* self, PxArena* arena, C4FrameBuffer* frame);

#endif // C4_GAME_RENDERER_H
