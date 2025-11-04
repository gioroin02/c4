#ifndef PAX_CORE_DISPLAY_BITMAP_H
#define PAX_CORE_DISPLAY_BITMAP_H

#include "./import.h"

typedef struct Pax_Bitmap
{
    paxu8*   memory;
    paxiword width;
    paxiword height;
    paxiword stride;
}
Pax_Bitmap;

Pax_Bitmap
pax_bitmap_create(Pax_Arena* arena, paxiword x, paxiword y);

/*
void
pax_bitmap_clear(Pax_Bitmap* bmp, paxu32 value);

void
pax_bitmap_write_pixel(Pax_Bitmap* bmp, paxiword x, paxiword y, paxu32 value);
*/

#endif // PAX_CORE_DISPLAY_BITMAP_H
