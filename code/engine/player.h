#ifndef C4_ENGINE_GAME_PLAYER_H
#define C4_ENGINE_GAME_PLAYER_H

#include "./import.h"

typedef struct C4_Game_Player
{
    paxuword code;
    paxu8   color;
    paxu8   shape;
}
C4_Game_Player;

typedef struct C4_Game_Player_List
{
    Pax_Array items;
}
C4_Game_Player_List;

C4_Game_Player_List
c4_game_player_list_create(Pax_Arena* arena, paxiword length);

paxiword
c4_game_player_list_elements(C4_Game_Player_List* self);

paxiword
c4_game_player_list_capacity(C4_Game_Player_List* self);

paxb8
c4_game_player_list_is_empty(C4_Game_Player_List* self);

paxb8
c4_game_player_list_is_full(C4_Game_Player_List* self);

paxb8
c4_game_player_list_find_linear(C4_Game_Player_List* self, paxuword code, paxiword* index);

paxb8
c4_game_player_list_insert(C4_Game_Player_List* self, C4_Game_Player value);

paxb8
c4_game_player_list_remove(C4_Game_Player_List* self, paxuword code, C4_Game_Player* value);

paxb8
c4_game_player_list_peek(C4_Game_Player_List* self, paxiword index, C4_Game_Player* value);

#endif // C4_ENGINE_GAME_PLAYER_H
