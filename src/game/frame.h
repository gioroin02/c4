#ifndef C4_GAME_FRAME_H
#define C4_GAME_FRAME_H

#include "color.h"

typedef struct C4FrameElement
{
    PxString8 text;
    C4Color   front;
    C4Color   back;
}
C4FrameElement;

typedef struct C4FrameBuffer
{
    PxArray items;

    pxiword width;
    pxiword height;
}
C4FrameBuffer;

C4FrameBuffer
c4FrameBufferMake(PxArena* arena, pxiword width, pxiword height);

pxb8
c4FrameBufferRead(C4FrameBuffer* self, pxiword x, pxiword y, C4FrameElement* value);

C4FrameElement
c4FrameBufferReadOr(C4FrameBuffer* self, pxiword x, pxiword y, C4FrameElement value);

pxb8
c4FrameBufferUpdate(C4FrameBuffer* self, pxiword x, pxiword y, C4FrameElement value);

pxb8
c4FrameBufferReset(C4FrameBuffer* self, PxString8 text, C4Color front, C4Color back);

pxb8
c4FrameBufferPaintCell(C4FrameBuffer* self, pxiword x, pxiword y, PxString8 text, C4Color front, C4Color back);

pxb8
c4FrameBufferPaintRect(C4FrameBuffer* self, pxiword x, pxiword y, pxiword w, pxiword h, PxString8 text, C4Color front, C4Color back);

void
c4WriterFrame(PxWriter* self, C4FrameBuffer* frame);

#endif // C4_GAME_FRAME_H
