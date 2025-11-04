#ifndef PAX_CORE_DISPLAY_MESSAGE_H
#define PAX_CORE_DISPLAY_MESSAGE_H

#include "./import.h"

typedef enum Pax_Display_Message_Filter
{
    PAX_DISPLAY_MESSAGE_FILTER_NONE = 0,

    PAX_DISPLAY_MESSAGE_FILTER_DISPLAY  = 1 << 0,
    PAX_DISPLAY_MESSAGE_FILTER_KEYBOARD = 1 << 1,
    PAX_DISPLAY_MESSAGE_FILTER_MOUSE    = 1 << 2,
}
Pax_Display_Message_Filter;

typedef enum Pax_Display_Message_Kind
{
    PAX_DISPLAY_MESSAGE_KIND_NONE,

    PAX_DISPLAY_MESSAGE_KIND_DISPLAY_DESTROY,
    PAX_DISPLAY_MESSAGE_KIND_DISPLAY_RECT,

    PAX_DISPLAY_MESSAGE_KIND_KEYBOARD_BUTTON,

    PAX_DISPLAY_MESSAGE_KIND_MOUSE_BUTTON,
    PAX_DISPLAY_MESSAGE_KIND_MOUSE_COORDS,
    PAX_DISPLAY_MESSAGE_KIND_MOUSE_WHEEL,
}
Pax_Display_Message_Kind;

typedef enum Pax_Keyboard_Button
{
    PAX_KEYBOARD_BUTTON_NONE,

    PAX_KEYBOARD_BUTTON_A, PAX_KEYBOARD_BUTTON_B, PAX_KEYBOARD_BUTTON_C, PAX_KEYBOARD_BUTTON_D, PAX_KEYBOARD_BUTTON_E, PAX_KEYBOARD_BUTTON_F,
    PAX_KEYBOARD_BUTTON_G, PAX_KEYBOARD_BUTTON_H, PAX_KEYBOARD_BUTTON_I, PAX_KEYBOARD_BUTTON_J, PAX_KEYBOARD_BUTTON_K, PAX_KEYBOARD_BUTTON_L,
    PAX_KEYBOARD_BUTTON_M, PAX_KEYBOARD_BUTTON_N, PAX_KEYBOARD_BUTTON_O, PAX_KEYBOARD_BUTTON_P, PAX_KEYBOARD_BUTTON_Q, PAX_KEYBOARD_BUTTON_R,
    PAX_KEYBOARD_BUTTON_S, PAX_KEYBOARD_BUTTON_T, PAX_KEYBOARD_BUTTON_U, PAX_KEYBOARD_BUTTON_V, PAX_KEYBOARD_BUTTON_W, PAX_KEYBOARD_BUTTON_X,
    PAX_KEYBOARD_BUTTON_Y, PAX_KEYBOARD_BUTTON_Z,

    PAX_KEYBOARD_BUTTON_ZERO, PAX_KEYBOARD_BUTTON_ONE, PAX_KEYBOARD_BUTTON_TWO,   PAX_KEYBOARD_BUTTON_THREE, PAX_KEYBOARD_BUTTON_FOUR,
    PAX_KEYBOARD_BUTTON_FIVE, PAX_KEYBOARD_BUTTON_SIX, PAX_KEYBOARD_BUTTON_SEVEN, PAX_KEYBOARD_BUTTON_EIGHT, PAX_KEYBOARD_BUTTON_NINE,

    PAX_KEYBOARD_BUTTON_F1,  PAX_KEYBOARD_BUTTON_F2,  PAX_KEYBOARD_BUTTON_F3,  PAX_KEYBOARD_BUTTON_F4,  PAX_KEYBOARD_BUTTON_F5,
    PAX_KEYBOARD_BUTTON_F6,  PAX_KEYBOARD_BUTTON_F7,  PAX_KEYBOARD_BUTTON_F8,  PAX_KEYBOARD_BUTTON_F9,  PAX_KEYBOARD_BUTTON_F10,
    PAX_KEYBOARD_BUTTON_F11, PAX_KEYBOARD_BUTTON_F12,

    PAX_KEYBOARD_BUTTON_NUM0, PAX_KEYBOARD_BUTTON_NUM1, PAX_KEYBOARD_BUTTON_NUM2, PAX_KEYBOARD_BUTTON_NUM3, PAX_KEYBOARD_BUTTON_NUM4,
    PAX_KEYBOARD_BUTTON_NUM5, PAX_KEYBOARD_BUTTON_NUM6, PAX_KEYBOARD_BUTTON_NUM7, PAX_KEYBOARD_BUTTON_NUM8, PAX_KEYBOARD_BUTTON_NUM9,

    PAX_KEYBOARD_BUTTON_SPACE,
    PAX_KEYBOARD_BUTTON_ENTER,
    PAX_KEYBOARD_BUTTON_TAB,
    PAX_KEYBOARD_BUTTON_ESCAPE,
    PAX_KEYBOARD_BUTTON_BACKSPACE,
    PAX_KEYBOARD_BUTTON_DELETE,
    PAX_KEYBOARD_BUTTON_INSERT,
    PAX_KEYBOARD_BUTTON_HOME,
    PAX_KEYBOARD_BUTTON_END,
    PAX_KEYBOARD_BUTTON_PAGE_UP,
    PAX_KEYBOARD_BUTTON_PAGE_DOWN,

    PAX_KEYBOARD_BUTTON_LEFT,
    PAX_KEYBOARD_BUTTON_RIGHT,
    PAX_KEYBOARD_BUTTON_UP,
    PAX_KEYBOARD_BUTTON_DOWN,

    PAX_KEYBOARD_BUTTON_SHIFT_LEFT,
    PAX_KEYBOARD_BUTTON_SHIFT_RIGHT,
    PAX_KEYBOARD_BUTTON_CTRL_LEFT,
    PAX_KEYBOARD_BUTTON_CTRL_RIGHT,
    PAX_KEYBOARD_BUTTON_ALT_LEFT,
    PAX_KEYBOARD_BUTTON_ALT_RIGHT,
}
Pax_Keyboard_Button;

typedef enum Pax_Mouse_Button
{
    PAX_MOUSE_BUTTON_NONE,
    PAX_MOUSE_BUTTON_LEFT,
    PAX_MOUSE_BUTTON_MIDDLE,
    PAX_MOUSE_BUTTON_RIGHT,
}
Pax_Mouse_Button;

typedef struct Pax_Display_Message_Display_Rect
{
    paxiword left;
    paxiword top;
    paxiword width;
    paxiword height;
}
Pax_Display_Message_Display_Rect;

typedef struct Pax_Display_Message_Keyboard_Button
{
    Pax_Keyboard_Button button;
    paxiword            code;
    paxb8               active;
}
Pax_Display_Message_Keyboard_Button;

typedef struct Pax_Display_Message_Mouse_Button
{
    Pax_Mouse_Button button;
    paxb8            active;
}
Pax_Display_Message_Mouse_Button;

typedef struct Pax_Display_Message_Mouse_Coords
{
    paxiword x;
    paxiword y;
}
Pax_Display_Message_Mouse_Coords;

typedef struct Pax_Display_Message_Mouse_Wheel
{
    paxiword x;
    paxiword y;
}
Pax_Display_Message_Mouse_Wheel;

typedef struct Pax_Display_Message
{
    Pax_Display_Message_Kind kind;

    union
    {
        Pax_Display_Message_Display_Rect display_rect;

        Pax_Display_Message_Keyboard_Button keyboard_button;

        Pax_Display_Message_Mouse_Button mouse_button;
        Pax_Display_Message_Mouse_Coords mouse_coords;
        Pax_Display_Message_Mouse_Wheel  mouse_wheel;
    };
}
Pax_Display_Message;

typedef struct Pax_Display_Message_Queue
{
    Pax_Array_Ring array;
}
Pax_Display_Message_Queue;

/* Message */

Pax_Display_Message
pax_display_message_display_destroy();

Pax_Display_Message
pax_display_message_display_rect(paxiword left, paxiword top, paxiword width, paxiword height);

Pax_Display_Message
pax_display_message_keyboard_button(Pax_Keyboard_Button button, paxb8 active, paxiword code);

Pax_Display_Message
pax_display_message_mouse_button(Pax_Mouse_Button button, paxb8 active);

Pax_Display_Message
pax_display_message_mouse_coords(paxiword x, paxiword y);

Pax_Display_Message
pax_display_message_mouse_wheel(paxiword x, paxiword y);

/* Message queue */

Pax_Display_Message_Queue
pax_display_message_queue_create(Pax_Arena* arena, paxiword length);

paxb8
pax_display_message_queue_is_empty(Pax_Display_Message_Queue* self);

paxb8
pax_display_message_queue_is_full(Pax_Display_Message_Queue* self);

paxb8
pax_display_message_queue_insert(Pax_Display_Message_Queue* self, Pax_Display_Message value);

paxb8
pax_display_message_queue_remove(Pax_Display_Message_Queue* self, Pax_Display_Message* value);


#endif // PAX_CORE_DISPLAY_MESSAGE_H
