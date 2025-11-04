#ifndef C4_GAME_PAINTER_C
#define C4_GAME_PAINTER_C

#include "./painter.h"

C4_Console_Buffer
c4_console_buffer_create(Pax_Arena* arena, paxiword width, paxiword height)
{
    C4_Console_Buffer result = {0};

    if (width <= 0 || height <= 0) return result;

    result.items =
        pax_array_create(arena, C4_Console_Item, width * height);

    pax_array_fill(&result.items);

    if (pax_array_elements(&result.items) > 0) {
        result.width  = width;
        result.height = height;
    }

    return result;
}

paxb8
c4_console_buffer_peek(C4_Console_Buffer* self, paxiword x, paxiword y, C4_Console_Item* value)
{
    if (x < 0 || x >= self->width)  return 0;
    if (y < 0 || y >= self->height) return 0;

    paxiword index = x + self->width * y;

    return pax_array_peek(&self->items,
        C4_Console_Item, index, value, 1);
}

C4_Console_Item
c4_console_buffer_peek_or(C4_Console_Buffer* self, paxiword x, paxiword y, C4_Console_Item value)
{
    C4_Console_Item result = {0};

    if (c4_console_buffer_peek(self, x, y, &result) == 0)
        return value;

    return result;
}

paxb8
c4_console_buffer_update(C4_Console_Buffer* self, paxiword x, paxiword y, C4_Console_Item value)
{
    if (x < 0 || x >= self->width)  return 0;
    if (y < 0 || y >= self->height) return 0;

    paxiword index = x + self->width * y;

    return pax_array_update(&self->items,
        C4_Console_Item, index, &value, 1);
}

paxb8
c4_console_buffer_clear(C4_Console_Buffer* self, paxi32 unicode, C4_Color front, C4_Color back)
{
    C4_Console_Item item = {
        .front   = front,
        .back    = back,
        .unicode = pax_between(unicode, 33, 127),
    };

    for (paxiword j = 0; j < self->height; j += 1) {
        for (paxiword i = 0; i < self->width; i += 1) {
            if (c4_console_buffer_update(self, i, j, item) == 0)
                return 0;
        }
    }

    return 1;
}

paxb8
c4_console_buffer_paint(C4_Console_Buffer* self, paxiword x, paxiword y, paxi32 unicode, C4_Color front, C4_Color back)
{
    return c4_console_buffer_update(self, x, y, (C4_Console_Item) {
        .front   = front,
        .back    = back,
        .unicode = pax_between(unicode, 33, 127),
    });
}

paxiword
c4_target_screen_scroll(Pax_Target* self)
{
    return pax_target_write_string8(self, pax_str8("\x1b[2J"));
}

paxiword
c4_target_screen_clear(Pax_Target* self)
{
    return pax_target_write_string8(self, pax_str8("\x1b\x63"));
}

paxiword
c4_target_move_up(Pax_Target* self, Pax_Arena* arena, paxu8 amount)
{
    Pax_Format_Radix radix = PAX_FORMAT_RADIX_10;
    Pax_Format_Flag  flags = PAX_FORMAT_FLAG_NONE;

    paxiword mark = pax_arena_tell(arena);

    if (amount <= 0) return 0;

    paxiword s0 = pax_target_write_string8(self, pax_str8("\x1b["));
    paxiword s1 = 0;

    if (amount > 1) {
        Pax_String8 str0 = pax_string8_from_unsigned(
            arena, amount, radix, flags);

        s1 = pax_target_write_string8(self, str0);
    }

    paxiword s2 = pax_target_write_string8(self, pax_str8("A"));

    pax_arena_rewind(arena, mark, 0);

    return s0 + s1 + s2;
}

paxiword
c4_target_move_down(Pax_Target* self, Pax_Arena* arena, paxu8 amount)
{
    Pax_Format_Radix radix = PAX_FORMAT_RADIX_10;
    Pax_Format_Flag  flags = PAX_FORMAT_FLAG_NONE;

    paxiword mark = pax_arena_tell(arena);

    if (amount <= 0) return 0;

    paxiword s0 = pax_target_write_string8(self, pax_str8("\x1b["));
    paxiword s1 = 0;

    if (amount > 1) {
        Pax_String8 str0 = pax_string8_from_unsigned(
            arena, amount, radix, flags);

        s1 = pax_target_write_string8(self, str0);
    }

    paxiword s2 = pax_target_write_string8(self, pax_str8("B"));

    pax_arena_rewind(arena, mark, 0);

    return s0 + s1 + s2;
}

paxiword
c4_target_move_left(Pax_Target* self, Pax_Arena* arena, paxu8 amount)
{
    Pax_Format_Radix radix = PAX_FORMAT_RADIX_10;
    Pax_Format_Flag  flags = PAX_FORMAT_FLAG_NONE;

    paxiword mark = pax_arena_tell(arena);

    if (amount <= 0) return 0;

    paxiword s0 = pax_target_write_string8(self, pax_str8("\x1b["));
    paxiword s1 = 0;

    if (amount > 1) {
        Pax_String8 str0 = pax_string8_from_unsigned(
            arena, amount, radix, flags);

        s1 = pax_target_write_string8(self, str0);
    }

    paxiword s2 = pax_target_write_string8(self, pax_str8("D"));

    pax_arena_rewind(arena, mark, 0);

    return s0 + s1 + s2;
}

paxiword
c4_target_move_right(Pax_Target* self, Pax_Arena* arena, paxu8 amount)
{
    Pax_Format_Radix radix = PAX_FORMAT_RADIX_10;
    Pax_Format_Flag  flags = PAX_FORMAT_FLAG_NONE;

    paxiword mark = pax_arena_tell(arena);

    if (amount <= 0) return 0;

    paxiword s0 = pax_target_write_string8(self, pax_str8("\x1b["));
    paxiword s1 = 0;

    if (amount > 1) {
        Pax_String8 str0 = pax_string8_from_unsigned(
            arena, amount, radix, flags);

        s1 = pax_target_write_string8(self, str0);
    }

    paxiword s2 = pax_target_write_string8(self, pax_str8("C"));

    pax_arena_rewind(arena, mark, 0);

    return s0 + s1 + s2;
}

paxiword
c4_target_move(Pax_Target* self, Pax_Arena* arena, paxiword x, paxiword y)
{
    Pax_Format_Radix radix = PAX_FORMAT_RADIX_10;
    Pax_Format_Flag  flags = PAX_FORMAT_FLAG_NONE;

    paxiword mark = pax_arena_tell(arena);

    if (x < 0 || y < 0) return 0;

    paxiword s0 = pax_target_write_string8(self, pax_str8("\x1b["));

    paxiword s1 = 0;
    paxiword s2 = 0;
    paxiword s3 = 0;

    if (x != 0 || y != 0) {
        Pax_String8 str0 = pax_string8_from_unsigned(
            arena, y + 1, radix, flags);

        Pax_String8 str1 = pax_string8_from_unsigned(
            arena, x + 1, radix, flags);

        s1 = pax_target_write_string8(self, str0);
        s2 = pax_target_write_string8(self, pax_str8(";"));
        s3 = pax_target_write_string8(self, str1);
    }

    paxiword s4 = pax_target_write_string8(self, pax_str8("H"));

    pax_arena_rewind(arena, mark, 0);

    return s0 + s1 + s2 + s3 + s4;
}

paxiword
c4_target_cursor_show(Pax_Target* self)
{
    return pax_target_write_string8(self, pax_str8("\x1b[?25h"));
}

paxiword
c4_target_cursor_hide(Pax_Target* self)
{
    return pax_target_write_string8(self, pax_str8("\x1b[?25l"));
}

paxiword
c4_target_color_front_index(Pax_Target* self, Pax_Arena* arena, C4_Color_Index color)
{
    Pax_Format_Radix radix = PAX_FORMAT_RADIX_10;
    Pax_Format_Flag  flags = PAX_FORMAT_FLAG_NONE;

    paxiword mark = pax_arena_tell(arena);

    paxiword s0 = pax_target_write_string8(self, pax_str8("\x1b[38;5;"));

    Pax_String8 str0 = pax_string8_from_unsigned(
        arena, color, radix, flags);

    paxiword s1 = pax_target_write_string8(self, str0);

    paxiword s2 = pax_target_write_string8(self, pax_str8("m"));

    pax_arena_rewind(arena, mark, 0);

    return s0 + s1 + s2;
}

paxiword
c4_target_color_front_rgba(Pax_Target* self, Pax_Arena* arena, C4_Color_RGBA color)
{
    Pax_Format_Radix radix = PAX_FORMAT_RADIX_10;
    Pax_Format_Flag  flags = PAX_FORMAT_FLAG_NONE;

    paxiword mark = pax_arena_tell(arena);

    paxiword s0 = pax_target_write_string8(self, pax_str8("\x1b[38;2;"));

    Pax_String8 str0 = pax_string8_from_unsigned(
        arena, color.r, radix, flags);

    Pax_String8 str1 = pax_string8_from_unsigned(
        arena, color.g, radix, flags);

    Pax_String8 str2 = pax_string8_from_unsigned(
        arena, color.b, radix, flags);

    paxiword s1 = pax_target_write_string8(self, str0);

    paxiword s2 = pax_target_write_string8(self, pax_str8(";"));

    paxiword s3 = pax_target_write_string8(self, str1);

    paxiword s4 = pax_target_write_string8(self, pax_str8(";"));

    paxiword s5 = pax_target_write_string8(self, str2);

    paxiword s6 = pax_target_write_string8(self, pax_str8("m"));

    pax_arena_rewind(arena, mark, 0);

    return s0 + s1 + s2 + s3 + s4 + s5 + s6;
}

paxiword
c4_target_color_front(Pax_Target* self, Pax_Arena* arena, C4_Color color)
{
    switch (color.kind) {
        case C4_COLOR_KIND_INDEX:
            return c4_target_color_front_index(self, arena, color.color_index);

        case C4_COLOR_KIND_RGBA:
            return c4_target_color_front_rgba(self, arena, color.color_rgba);

        default: break;
    }

    return 0;
}

paxiword
c4_target_color_back_index(Pax_Target* self, Pax_Arena* arena, C4_Color_Index color)
{
    Pax_Format_Radix radix = PAX_FORMAT_RADIX_10;
    Pax_Format_Flag  flags = PAX_FORMAT_FLAG_NONE;

    paxiword mark = pax_arena_tell(arena);

    paxiword s0 = pax_target_write_string8(self, pax_str8("\x1b[48;5;"));

    Pax_String8 str0 = pax_string8_from_unsigned(
        arena, color, radix, flags);

    paxiword s1 = pax_target_write_string8(self, str0);

    paxiword s2 = pax_target_write_string8(self, pax_str8("m"));

    pax_arena_rewind(arena, mark, 0);

    return s0 + s1 + s2;
}

paxiword
c4_target_color_back_rgba(Pax_Target* self, Pax_Arena* arena, C4_Color_RGBA color)
{
    Pax_Format_Radix radix = PAX_FORMAT_RADIX_10;
    Pax_Format_Flag  flags = PAX_FORMAT_FLAG_NONE;

    paxiword mark = pax_arena_tell(arena);

    paxiword s0 = pax_target_write_string8(self, pax_str8("\x1b[48;2;"));

    Pax_String8 str0 = pax_string8_from_unsigned(
        arena, color.r, radix, flags);

    Pax_String8 str1 = pax_string8_from_unsigned(
        arena, color.g, radix, flags);

    Pax_String8 str2 = pax_string8_from_unsigned(
        arena, color.b, radix, flags);

    paxiword s1 = pax_target_write_string8(self, str0);

    paxiword s2 = pax_target_write_string8(self, pax_str8(";"));

    paxiword s3 = pax_target_write_string8(self, str1);

    paxiword s4 = pax_target_write_string8(self, pax_str8(";"));

    paxiword s5 = pax_target_write_string8(self, str2);

    paxiword s6 = pax_target_write_string8(self, pax_str8("m"));

    pax_arena_rewind(arena, mark, 0);

    return s0 + s1 + s2 + s3 + s4 + s5 + s6;
}

paxiword
c4_target_color_back(Pax_Target* self, Pax_Arena* arena, C4_Color color)
{
    switch (color.kind) {
        case C4_COLOR_KIND_INDEX:
            return c4_target_color_back_index(self, arena, color.color_index);

        case C4_COLOR_KIND_RGBA:
            return c4_target_color_back_rgba(self, arena, color.color_rgba);

        default: break;
    }

    return 0;
}

paxiword
c4_target_unicode(Pax_Target* self, Pax_Arena* arena, paxi32 value)
{
    paxiword mark = pax_arena_tell(arena);

    Pax_String8 str0 = pax_string8_copy_unicode(arena, value);

    paxiword s0 = pax_target_write_string8(self, str0);

    pax_arena_rewind(arena, mark, 0);

    return s0;
}

void
c4_target_console_buffer(Pax_Target* self, Pax_Arena* arena, C4_Console_Buffer* buffer)
{
    c4_target_move(self, arena, 0, 0);

    for (paxiword j = 0; j < buffer->height; j += 1) {
        for (paxiword i = 0; i < buffer->width; i += 1) {
            C4_Console_Item item = c4_console_buffer_peek_or(
                buffer, i, j, (C4_Console_Item) {0});

            c4_target_color_front(self, arena, item.front);
            c4_target_color_back(self, arena, item.back);

            c4_target_unicode(self, arena, item.unicode);
        }

        c4_target_move(self, arena, 0, j + 1);
    }
}

#endif // C4_GAME_PAINTER_C
