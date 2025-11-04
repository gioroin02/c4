#ifndef PAX_WIN32_DISPLAY_DISPLAY_H
#define PAX_WIN32_DISPLAY_DISPLAY_H

#include "./import.h"

typedef struct Pax_Win32_Display        Pax_Win32_Display;
typedef struct Pax_Win32_Display_Buffer Pax_Win32_Display_Buffer;

/* Display */

Pax_Win32_Display*
pax_win32_display_create(Pax_Arena* arena, Pax_String8 name);

void
pax_win32_display_destroy(Pax_Win32_Display* self);

void
pax_win32_display_clear(Pax_Win32_Display* self);

void
pax_win32_display_flush(Pax_Win32_Display* self, Pax_Win32_Display_Buffer* buffer);

paxb8
pax_win32_display_poll_message(Pax_Win32_Display* self, Pax_Display_Message* value);

void
pax_win32_display_set_message_filter(Pax_Win32_Display* self, Pax_Display_Message_Filter filter);

paxb8
pax_win32_display_set_visibility(Pax_Win32_Display* self, Pax_Display_Visibility visibility);

/* Display Buffer */

Pax_Win32_Display_Buffer*
pax_win32_display_buffer_create(Pax_Win32_Display* self, Pax_Arena* arena, paxiword width, paxiword height);

void
pax_win32_display_buffer_destroy(Pax_Win32_Display_Buffer* self);

paxiword
pax_win32_display_buffer_length(Pax_Win32_Display_Buffer* self);

paxiword
pax_win32_display_buffer_width(Pax_Win32_Display_Buffer* self);

paxiword
pax_win32_display_buffer_height(Pax_Win32_Display_Buffer* self);

paxiword
pax_win32_display_buffer_stride(Pax_Win32_Display_Buffer* self);

paxb8
pax_win32_display_buffer_write(Pax_Win32_Display_Buffer* self, paxiword x, paxiword y, paxu8 r, paxu8 g, paxu8 b);

paxb8
pax_win32_display_buffer_read(Pax_Win32_Display_Buffer* self, paxiword x, paxiword y, paxu8* r, paxu8* g, paxu8* b);

#endif // PAX_WIN32_DISPLAY_DISPLAY_H
