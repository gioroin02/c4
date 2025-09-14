#ifndef C4_GAME_PLAYER_H
#define C4_GAME_PLAYER_H

#include "color.h"

typedef struct C4GamePlayer
{
    pxuword   code;
    C4Color   color;
    PxString8 text;
}
C4GamePlayer;

typedef struct C4GamePlayerList
{
    PxArray items;
}
C4GamePlayerList;

C4GamePlayer
c4GamePlayer(pxuword code, C4Color color, PxString8 text);

C4GamePlayerList
c4GamePlayerListReserve(PxArena* arena, pxiword length);

pxiword
c4GamePlayerListSize(C4GamePlayerList* self);

pxiword
c4GamePlayerListLength(C4GamePlayerList* self);

pxb8
c4GamePlayerListIsFull(C4GamePlayerList* self);

pxb8
c4GamePlayerListFind(C4GamePlayerList* self, pxuword code, pxiword* index);

pxb8
c4GamePlayerListInsert(C4GamePlayerList* self, C4GamePlayer value);

pxb8
c4GamePlayerListRemove(C4GamePlayerList* self, pxuword code, C4GamePlayer* value);

pxb8
c4GamePlayerListRead(C4GamePlayerList* self, pxiword index, C4GamePlayer* value);

C4GamePlayer
c4GamePlayerListReadOr(C4GamePlayerList* self, pxiword index, C4GamePlayer value);

#endif // C4_GAME_PLAYER_H
