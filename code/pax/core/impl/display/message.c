#ifndef PAX_CORE_DISPLAY_MESSAGE_C
#define PAX_CORE_DISPLAY_MESSAGE_C

#include "./message.h"

Pax_Display_Message
pax_display_message_display_destroy()
{
    return (Pax_Display_Message) {
        .kind = PAX_DISPLAY_MESSAGE_KIND_DISPLAY_DESTROY,
    };
}

Pax_Display_Message
pax_display_message_display_rect(paxiword left, paxiword top, paxiword width, paxiword height)
{
    return (Pax_Display_Message) {
        .kind = PAX_DISPLAY_MESSAGE_KIND_DISPLAY_RECT,

        .display_rect = {
            .left   = left,
            .top    = top,
            .width  = width,
            .height = height,
        },
    };
}

Pax_Display_Message
pax_display_message_keyboard_button(Pax_Keyboard_Button button, paxb8 active, paxiword code)
{
    return (Pax_Display_Message) {
        .kind = PAX_DISPLAY_MESSAGE_KIND_KEYBOARD_BUTTON,

        .keyboard_button = {
            .button = button,
            .code   = code,
            .active = active,
        },
    };
}

Pax_Display_Message
pax_display_message_mouse_button(Pax_Mouse_Button button, paxb8 active)
{
    return (Pax_Display_Message) {
        .kind = PAX_DISPLAY_MESSAGE_KIND_MOUSE_BUTTON,

        .mouse_button = {
            .button = button,
            .active = active,
        },
    };
}

Pax_Display_Message
pax_display_message_mouse_coords(paxiword x, paxiword y)
{
    return (Pax_Display_Message) {
        .kind = PAX_DISPLAY_MESSAGE_KIND_MOUSE_COORDS,

        .mouse_coords = {
            .x = x,
            .y = y,
        },
    };
}

Pax_Display_Message
pax_display_message_mouse_wheel(paxiword x, paxiword y)
{
    return (Pax_Display_Message) {
        .kind = PAX_DISPLAY_MESSAGE_KIND_MOUSE_WHEEL,

        .mouse_wheel = {
            .x = x,
            .y = y,
        },
    };
}

Pax_Display_Message_Queue
pax_display_message_queue_create(Pax_Arena* arena, paxiword length)
{
    return (Pax_Display_Message_Queue) {
        .array = pax_array_ring_create(arena, Pax_Display_Message, length),
    };
}

paxb8
pax_display_message_queue_is_empty(Pax_Display_Message_Queue* self)
{
    return pax_array_ring_is_empty(&self->array);
}

paxb8
pax_display_message_queue_is_full(Pax_Display_Message_Queue* self)
{
    return pax_array_ring_is_full(&self->array);
}

paxb8
pax_display_message_queue_insert(Pax_Display_Message_Queue* self, Pax_Display_Message value)
{
    return pax_array_ring_insert_tail(&self->array, Pax_Display_Message, &value, 1);
}

paxb8
pax_display_message_queue_remove(Pax_Display_Message_Queue* self, Pax_Display_Message* value)
{
    return pax_array_ring_remove_head(&self->array, Pax_Display_Message, value, 1);
}

#endif // PAX_CORE_DISPLAY_MESSAGE_C
