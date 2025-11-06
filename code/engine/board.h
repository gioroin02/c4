#ifndef C4_ENGINE_GAME_BOARD_H
#define C4_ENGINE_GAME_BOARD_H

#include "./import.h"

typedef struct C4_Game_Board
{
    Pax_Array items;

    paxiword width;
    paxiword height;
}
C4_Game_Board;

C4_Game_Board
c4_game_board_create(Pax_Arena* arena, paxiword width, paxiword height);

paxiword
c4_game_board_elements(C4_Game_Board* self);

paxiword
c4_game_board_capacity(C4_Game_Board* self);

paxiword
c4_game_board_height(C4_Game_Board* self, paxiword column);

paxb8
c4_game_board_is_empty(C4_Game_Board* self);

paxb8
c4_game_board_is_full(C4_Game_Board* self);

void
c4_game_board_clear(C4_Game_Board* self);

paxb8
c4_game_board_insert(C4_Game_Board* self, paxiword column, paxuword value);

paxb8
c4_game_board_peek(C4_Game_Board* self, paxiword col, paxiword row, paxuword* value);

paxuword
c4_game_board_peek_or(C4_Game_Board* self, paxiword col, paxiword row, paxuword value);

paxiword
c4_game_board_contains_point(C4_Game_Board* self, paxiword col, paxiword row, paxuword* value);

paxiword
c4_game_board_contains_line(C4_Game_Board* self, paxiword col, paxiword row, paxiword dcol, paxiword drow, paxuword* value);

#endif // C4_ENGINE_GAME_BOARD_H
