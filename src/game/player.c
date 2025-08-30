#ifndef C4_GAME_PLAYER_C
#define C4_GAME_PLAYER_C

#include "player.h"

C4GamePlayerList
c4GamePlayerListReserve(PxArena* arena, pxiword length)
{
    return (C4GamePlayerList) {
        .items = pxArrayReserve(arena, C4GamePlayer, length),
    };
}

pxiword
c4GamePlayerListSize(C4GamePlayerList* self)
{
    return self->items.size;
}

pxiword
c4GamePlayerListLength(C4GamePlayerList* self)
{
    return self->items.length;
}

pxb8
c4GamePlayerListIsFull(C4GamePlayerList* self)
{
    return self->items.size >= self->items.length ? 1 : 0;
}

pxb8
c4GamePlayerListFind(C4GamePlayerList* self, pxuword code, pxiword* index)
{
    C4GamePlayer item = {0};

    for (pxiword i = 0; i < self->items.size; i += 1) {
        pxArrayRead(&self->items, i, C4GamePlayer, &item);

        if (item.code == code) {
            if (index != 0) *index = i;

            return 1;
        }
    }

    return 0;
}

pxb8
c4GamePlayerListInsert(C4GamePlayerList* self, C4GamePlayer value)
{
    return pxArrayInsertTail(&self->items, C4GamePlayer, &value);
}

pxb8
c4GamePlayerListRemove(C4GamePlayerList* self, pxuword code, C4GamePlayer* value)
{
    C4GamePlayer item = {0};

    for (pxiword i = 0; i < self->items.size; i += 1) {
        pxArrayRead(&self->items, i, C4GamePlayer, &item);

        if (item.code != code) continue;

        return pxArrayRemove(&self->items, i,
            C4GamePlayer, value);
    }

    return 0;
}

pxb8
c4GamePlayerListRead(C4GamePlayerList* self, pxiword index, C4GamePlayer* value)
{
    return pxArrayRead(&self->items, index, C4GamePlayer, value);
}

#endif // C4_GAME_PLAYER_C
