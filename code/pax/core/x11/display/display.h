#ifndef PAX_X11_DISPLAY_DISPLAY_H
#define PAX_X11_DISPLAY_DISPLAY_H

#include "./import.h"

typedef struct Pax_X11_Display        Pax_X11_Display;
typedef struct Pax_X11_Display_Buffer Pax_X11_Display_Buffer;

/* Display */

Pax_X11_Display*
pax_x11_display_create(Pax_Arena* arena, Pax_String8 name);

void
pax_x11_display_destroy(Pax_X11_Display* self);

void
pax_x11_display_clear(Pax_X11_Display* self);

void
pax_x11_display_flush(Pax_X11_Display* self, Pax_X11_Display_Buffer* buffer);

paxb8
pax_x11_display_poll_message(Pax_X11_Display* self, Pax_Display_Message* value);

void
pax_x11_display_set_message_filter(Pax_X11_Display* self, Pax_Display_Message_Filter filter);

paxb8
pax_x11_display_set_visibility(Pax_X11_Display* self, Pax_Display_Visibility visibility);

/* Display Buffer */

Pax_X11_Display_Buffer*
pax_x11_display_buffer_create(Pax_X11_Display* self, Pax_Arena* arena, paxiword x, paxiword y);

void
pax_x11_display_buffer_destroy(Pax_X11_Display_Buffer* self);

paxiword
pax_x11_display_buffer_length(Pax_X11_Display_Buffer* self);

paxiword
pax_x11_display_buffer_width(Pax_X11_Display_Buffer* self);

paxiword
pax_x11_display_buffer_height(Pax_X11_Display_Buffer* self);

paxiword
pax_x11_display_buffer_stride(Pax_X11_Display_Buffer* self);

paxb8
pax_x11_display_buffer_write(Pax_X11_Display_Buffer* self, paxiword x, paxiword y, paxu8 r, paxu8 g, paxu8 b);

paxb8
pax_x11_display_buffer_read(Pax_X11_Display_Buffer* self, paxiword x, paxiword y, paxu8* r, paxu8* g, paxu8* b);

#endif // PAX_X11_DISPLAY_DISPLAY_H
