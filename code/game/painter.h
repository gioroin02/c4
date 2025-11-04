#ifndef C4_GAME_PAINTER_H
#define C4_GAME_PAINTER_H

#include "./color.h"

typedef struct C4_Console_Item
{
    C4_Color front;
    C4_Color back;

    paxi32 unicode;
}
C4_Console_Item;

typedef struct C4_Console_Buffer
{
    Pax_Array items;

    paxiword width;
    paxiword height;
}
C4_Console_Buffer;

C4_Console_Buffer
c4_console_buffer_create(Pax_Arena* arena, paxiword width, paxiword height);

paxb8
c4_console_buffer_peek(C4_Console_Buffer* self, paxiword x, paxiword y, C4_Console_Item* value);

C4_Console_Item
c4_console_buffer_peek_or(C4_Console_Buffer* self, paxiword x, paxiword y, C4_Console_Item value);

paxb8
c4_console_buffer_update(C4_Console_Buffer* self, paxiword x, paxiword y, C4_Console_Item value);

paxb8
c4_console_buffer_clear(C4_Console_Buffer* self, paxi32 unicode, C4_Color front, C4_Color back);

paxb8
c4_console_buffer_paint(C4_Console_Buffer* self, paxiword x, paxiword y, paxi32 unicode, C4_Color front, C4_Color back);

paxiword
c4_target_screen_scroll(Pax_Target* self);

paxiword
c4_target_screen_clear(Pax_Target* self);

paxiword
c4_target_move_up(Pax_Target* self, Pax_Arena* arena, paxu8 amount);

paxiword
c4_target_move_down(Pax_Target* self, Pax_Arena* arena, paxu8 amount);

paxiword
c4_target_move_left(Pax_Target* self, Pax_Arena* arena, paxu8 amount);

paxiword
c4_target_move_right(Pax_Target* self, Pax_Arena* arena, paxu8 amount);

paxiword
c4_target_move(Pax_Target* self, Pax_Arena* arena, paxiword x, paxiword y);

paxiword
c4_target_cursor_show(Pax_Target* self);

paxiword
c4_target_cursor_hide(Pax_Target* self);

paxiword
c4_target_color_front(Pax_Target* self, Pax_Arena* arena, C4_Color color);

paxiword
c4_target_color_back(Pax_Target* self, Pax_Arena* arena, C4_Color color);

paxiword
c4_target_unicode(Pax_Target* self, Pax_Arena* arena, paxi32 value);

void
c4_target_console_buffer(Pax_Target* self, Pax_Arena* arena, C4_Console_Buffer* buffer);

#endif // C4_GAME_PAINTER_H
