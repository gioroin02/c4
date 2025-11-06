#ifndef C4_ENGINE_PLAYER_H
#define C4_ENGINE_PLAYER_H

#include "import.h"

typedef struct C4GamePlayer
{
    pxuword   ident;
    PxString8 text;

    PxConsoleColor color;
}
C4GamePlayer;

typedef struct C4GamePlayerList
{
    PxArray items;
}
C4GamePlayerList;

C4GamePlayer
c4GamePlayer(pxuword ident, PxString8 text, PxConsoleColor color);

C4GamePlayerList
c4GamePlayerListReserve(PxArena* arena, pxiword length);

pxiword
c4GamePlayerListSize(C4GamePlayerList* self);

pxiword
c4GamePlayerListLength(C4GamePlayerList* self);

pxb8
c4GamePlayerListIsFull(C4GamePlayerList* self);

pxb8
c4GamePlayerListFind(C4GamePlayerList* self, pxuword ident, pxiword* index);

pxb8
c4GamePlayerListInsert(C4GamePlayerList* self, C4GamePlayer value);

pxb8
c4GamePlayerListRemove(C4GamePlayerList* self, pxuword ident, C4GamePlayer* value);

pxb8
c4GamePlayerListGet(C4GamePlayerList* self, pxiword index, C4GamePlayer* value);

C4GamePlayer
c4GamePlayerListGetOr(C4GamePlayerList* self, pxiword index, C4GamePlayer value);

#endif // C4_ENGINE_PLAYER_H
