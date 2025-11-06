#ifndef C4_ENGINE_GAME_PLAYER_C
#define C4_ENGINE_GAME_PLAYER_C

#include "./player.h"

C4_Game_Player_List
c4_game_player_list_create(Pax_Arena* arena, paxiword length)
{
    return (C4_Game_Player_List) {
        .items = pax_array_create(arena, C4_Game_Player, length),
    };
}

paxiword
c4_game_player_list_elements(C4_Game_Player_List* self)
{
    return pax_array_elements(&self->items);
}

paxiword
c4_game_player_list_capacity(C4_Game_Player_List* self)
{
    return pax_array_capacity(&self->items);
}

paxb8
c4_game_player_list_is_empty(C4_Game_Player_List* self)
{
    return pax_array_is_empty(&self->items);
}

paxb8
c4_game_player_list_is_full(C4_Game_Player_List* self)
{
    return pax_array_is_full(&self->items);
}

paxb8
c4_game_player_list_find_linear(C4_Game_Player_List* self, paxuword code, paxiword* index)
{
    C4_Game_Player item = {0};

    paxiword size = pax_array_elements(&self->items);

    for (paxiword i = 0; i < size; i += 1) {
        pax_array_peek(&self->items, C4_Game_Player, i, &item, 1);

        if (item.code == code) {
            if (index != 0)
                *index = i;

            return 1;
        }
    }

    return 0;
}

paxb8
c4_game_player_list_insert(C4_Game_Player_List* self, C4_Game_Player value)
{
    paxiword index = pax_array_tail(&self->items);

    return pax_array_insert(&self->items,
        C4_Game_Player, index, &value, 1);
}

paxb8
c4_game_player_list_remove(C4_Game_Player_List* self, paxuword code, C4_Game_Player* value)
{
    C4_Game_Player item  = {0};
    paxiword       size  = pax_array_elements(&self->items);
    paxiword       index = 0;

    c4_game_player_list_find_linear(self, code, &index);

    if (index >= 0 && index < size) {
        return pax_array_remove(&self->items,
            C4_Game_Player, index, value, 1);
    }

    return 0;
}

paxb8
c4_game_player_list_peek(C4_Game_Player_List* self, paxiword index, C4_Game_Player* value)
{
    return pax_array_peek(&self->items, C4_Game_Player, index, value, 1);
}

#endif // C4_ENGINE_GAME_PLAYER_C
