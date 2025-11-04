#ifndef PAX_CORE_DISPLAY_BITMAP_C
#define PAX_CORE_DISPLAY_BITMAP_C

#include "./bitmap.h"

Pax_Bitmap
pax_bitmap_create(Pax_Arena* arena, paxiword width, paxiword height)
{
    if (width <= 0 || height <= 0)
        return (Pax_Bitmap) {0};

    paxiword length = width * height;
    paxiword stride = pax_size(paxu32);

    paxu8* memory = pax_arena_reserve_memory(arena, length, stride);

    if (memory == 0) return (Pax_Bitmap) {0};

    return (Pax_Bitmap) {
        .memory = memory,
        .width  = width,
        .height = height,
        .stride = stride,
    };
}

/*
void
pax_bitmap_clear(Pax_Bitmap* self, paxu32 value)
{
    if (!bmp || !bmp->pixels) return;

    uint32_t* p = (uint32_t*)bmp->pixels;
    paxiword count = bmp->width * bmp->height;

    for (paxiword i = 0; i < count; i++) {
        p[i] = color;
    }
}

void
pax_bitmap_write_to_buffer(Pax_Bitmap* bmp, void* dst_buffer, paxiword dst_pitch)
{
    if (!bmp || !bmp->pixels || !dst_buffer) return;
    if (dst_pitch < bmp->width * 4) return;  // protezione

    paxu8* src = bmp->pixels;
    paxu8* dst = (paxu8*)dst_buffer;

    paxiword min_h = bmp->height;
    paxiword copy_w = bmp->width * 4;

    for (paxiword y = 0; y < min_h; y++) {
        memcpy(dst, src, copy_w);
        src += bmp->pitch;
        dst += dst_pitch;
    }
}
*/

#endif // PAX_CORE_DISPLAY_BITMAP_C
