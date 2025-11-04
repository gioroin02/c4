#ifndef C4_GAME_BOARD_C
#define C4_GAME_BOARD_C

#include "./board.h"

C4_Game_Board
c4_game_board_create(Pax_Arena* arena, paxiword width, paxiword height)
{
    C4_Game_Board result = {0};

    if (width <= 0 || height <= 0) return result;

    result.items =
        pax_array_create(arena, paxuword, width * height);

    pax_array_fill(&result.items);

    if (pax_array_elements(&result.items) > 0) {
        result.width  = width;
        result.height = height;
    }

    return result;
}

paxiword
c4_game_board_elements(C4_Game_Board* self)
{
    paxiword result = 0;

    for (paxiword i = 0; i < self->width; i += 1) {
        for (paxiword j = 0; j < self->height; j += 1) {
            paxiword index = j + self->width * i;
            paxuword item  = 0;

            pax_array_peek(&self->items,
                paxuword, index, &item, 1);

            if (item != 0) result += 1;
        }
    }

    return result;
}

paxiword
c4_game_board_capacity(C4_Game_Board* self)
{
    return pax_array_capacity(&self->items);
}

paxb8
c4_game_board_is_empty(C4_Game_Board* self)
{
    if (c4_game_board_elements(self) == 0)
        return 1;

    return 0;
}

paxb8
c4_game_board_is_full(C4_Game_Board* self)
{
    paxiword length = c4_game_board_capacity(self);

    if (c4_game_board_elements(self) >= length)
        return 1;

    return 0;
}

paxiword
c4_game_board_height(C4_Game_Board* self, paxiword column)
{
    if (column < 0 || column >= self->width) return 0;

    for (paxiword i = 0; i < self->height; i += 1) {
        paxiword index = i + self->height * column;
        paxiword other = 0;

        pax_array_peek(&self->items,
            paxuword, index, &other, 1);

        if (other == 0) return i;
    }

    return self->height;
}

void
c4_game_board_clear(C4_Game_Board* self)
{
    for (paxiword i = 0; i < self->width; i += 1) {
        for (paxiword j = 0; j < self->height; j += 1) {
            paxiword index = j + self->width * i;
            paxuword item  = 0;

            pax_array_update(&self->items,
                paxuword, index, &item, 1);
        }
    }
}

paxb8
c4_game_board_insert(C4_Game_Board* self, paxiword column, paxuword value)
{
    if (column < 0 || column >= self->width || value <= 0)
        return 0;

    paxiword height = c4_game_board_height(self, column);

    if (height >= 0) {
        paxiword index = self->height * column + height;

        return pax_array_update(&self->items,
            paxuword, index, &value, 1);
    }

    return 0;
}

paxb8
c4_game_board_peek(C4_Game_Board* self, paxiword x, paxiword y, paxuword* value)
{
    if (c4_game_board_contains_point(self, x, y, value) != 0)
        return 1;

    return 0;
}

paxuword
c4_game_board_peek_or(C4_Game_Board* self, paxiword x, paxiword y, paxuword value)
{
    paxuword result = 0;

    if (c4_game_board_contains_point(self, x, y, &result) == 0)
        return value;

    return result;
}

paxiword
c4_game_board_contains_point(C4_Game_Board* self, paxiword x, paxiword y, paxuword* value)
{
    if (x < 0 || x >=  self->width) return 0;
    if (y < 0 || y >= self->height) return 0;

    if (value != 0) {
        paxiword index = y + self->height * x;

        pax_array_peek(&self->items,
            paxuword, index, value, 1);
    }

    return 1;
}

paxiword
c4_game_board_contains_line(C4_Game_Board* self, paxiword x, paxiword y, paxiword dx, paxiword dy, paxuword* value)
{
    paxuword temp   = 0;
    paxuword other  = 0;
    paxiword result = c4_game_board_contains_point(self, x, y, &other);

    if (dx == 0 && dy == 0) return result;

    x += pax_sign_integer(dx);
    y += pax_sign_integer(dy);

    while (c4_game_board_contains_point(self, x, y, &temp) != 0) {
        if (temp != other) break;

        result += 1;

        x += pax_sign_integer(dx);
        y += pax_sign_integer(dy);
    }

    if (value != 0) *value = other;

    return result;
}

#endif // C4_GAME_BOARD_C
