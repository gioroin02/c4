#ifndef PAX_CORE_DISPLAY_DISPLAY_C
#define PAX_CORE_DISPLAY_DISPLAY_C

#include "./display.h"
#include "message.h"

#if PAX_SYSTEM == PAX_SYSTEM_WINDOWS

    #include "../../win32/display/display.c"

    #define __pax_display_create__  pax_win32_display_create
    #define __pax_display_destroy__ pax_win32_display_destroy
    #define __pax_display_clear__   pax_win32_display_clear
    #define __pax_display_flush__   pax_win32_display_flush

    #define __pax_display_poll_message__ pax_win32_display_poll_message

    #define __pax_display_set_message_filter__ pax_win32_display_set_message_filter
    #define __pax_display_set_visibility__     pax_win32_display_set_visibility

    #define __pax_display_buffer_create__  pax_win32_display_buffer_create
    #define __pax_display_buffer_destroy__ pax_win32_display_buffer_destroy
    #define __pax_display_buffer_length__  pax_win32_display_buffer_length
    #define __pax_display_buffer_width__   pax_win32_display_buffer_width
    #define __pax_display_buffer_height__  pax_win32_display_buffer_height
    #define __pax_display_buffer_stride__  pax_win32_display_buffer_stride
    #define __pax_display_buffer_write__   pax_win32_display_buffer_write
    #define __pax_display_buffer_read__    pax_win32_display_buffer_read


#elif PAX_SYSTEM == PAX_SYSTEM_LINUX

    #if PAX_DISPLAY_XORG != 0

    #include "../../x11/display/display.c"

        #define __pax_display_create__  pax_x11_display_create
        #define __pax_display_destroy__ pax_x11_display_destroy
        #define __pax_display_clear__   pax_x11_display_clear
        #define __pax_display_flush__   pax_x11_display_flush

        #define __pax_display_poll_message__ pax_x11_display_poll_message

        #define __pax_display_set_message_filter__ pax_x11_display_set_message_filter
        #define __pax_display_set_visibility__     pax_x11_display_set_visibility

        #define __pax_display_buffer_create__  pax_x11_display_buffer_create
        #define __pax_display_buffer_destroy__ pax_x11_display_buffer_destroy
        #define __pax_display_buffer_length__  pax_x11_display_buffer_length
        #define __pax_display_buffer_width__   pax_x11_display_buffer_width
        #define __pax_display_buffer_height__  pax_x11_display_buffer_height
        #define __pax_display_buffer_stride__  pax_x11_display_buffer_stride
        #define __pax_display_buffer_write__   pax_x11_display_buffer_write
        #define __pax_display_buffer_read__    pax_x11_display_buffer_read

    #else

        #error "Unknown platform"

    #endif

#else

    #error "Unknown platform"

#endif

Pax_Display
pax_display_create(Pax_Arena* arena, Pax_String8 name)
{
    return __pax_display_create__(arena, name);
}

void
pax_display_destroy(Pax_Display self)
{
    __pax_display_destroy__(self);
}

void
pax_display_clear(Pax_Display self)
{
    __pax_display_clear__(self);
}

void
pax_display_flush(Pax_Display self, Pax_Display_Buffer buffer)
{
    __pax_display_flush__(self, buffer);
}

paxb8
pax_display_poll_message(Pax_Display self, Pax_Display_Message* value)
{
    return __pax_display_poll_message__(self, value);
}

void
pax_display_set_message_filter(Pax_Display self, Pax_Display_Message_Filter filter)
{
    __pax_display_set_message_filter__(self, filter);
}

paxb8
pax_display_set_visibility(Pax_Display self, Pax_Display_Visibility visibility)
{
    return __pax_display_set_visibility__(self, visibility);
}

Pax_Display_Buffer
pax_display_buffer_create(Pax_Display self, Pax_Arena* arena, paxiword width, paxiword height)
{
    return __pax_display_buffer_create__(self, arena, width, height);
}

void
pax_display_buffer_destroy(Pax_Display_Buffer self)
{
    __pax_display_buffer_destroy__(self);
}

paxiword
pax_display_buffer_length(Pax_Display_Buffer self)
{
    return __pax_display_buffer_length__(self);
}

paxiword
pax_display_buffer_width(Pax_Display_Buffer self)
{
    return __pax_display_buffer_width__(self);
}

paxiword
pax_display_buffer_height(Pax_Display_Buffer self)
{
    return __pax_display_buffer_height__(self);
}

paxiword
pax_display_buffer_stride(Pax_Display_Buffer self)
{
    return __pax_display_buffer_stride__(self);
}

paxb8
pax_display_buffer_write(Pax_Display_Buffer self, paxiword x, paxiword y, paxu8 r, paxu8 g, paxu8 b)
{
    return __pax_display_buffer_write__(self, x, y, r, g, b);
}

paxb8
pax_display_buffer_read(Pax_Display_Buffer self, paxiword x, paxiword y, paxu8* r, paxu8* g, paxu8* b)
{
    return __pax_display_buffer_read__(self, x, y, r, g, b);
}

#endif // PAX_CORE_DISPLAY_DISPLAY_C
