#ifndef C4_ENGINE_MESSAGE_H
#define C4_ENGINE_MESSAGE_H

#include "color.h"
#include "player.h"

typedef enum C4NetworkMsgType
{
    C4_NETWORK_MSG_NONE,

    C4_NETWORK_MSG_PLAYER_JOIN,
    C4_NETWORK_MSG_PLAYER_ACCEPT,

    C4_NETWORK_MSG_PLAYER_DATA,

    C4_NETWORK_MSG_PLAYER_TURN,
    C4_NETWORK_MSG_PLAYER_CHOICE,
    C4_NETWORK_MSG_PLAYER_SKIP,

    C4_NETWORK_MSG_GAME_START,
    C4_NETWORK_MSG_GAME_STOP,

    C4_NETWORK_MSG_COUNT,
}
C4NetworkMsgType;

typedef struct C4NetworkMsgPlayerJoin
{
    pxb8 player_is_automatic;
}
C4NetworkMsgPlayerJoin;

typedef struct C4NetworkMsgPlayerAccept
{
    pxiword player_amount;

    pxuword   player_ident;
    PxString8 player_text;

    PxConsoleColor player_color;

    pxiword board_width;
    pxiword board_height;
}
C4NetworkMsgPlayerAccept;

typedef struct C4NetworkMsgPlayerData
{
    pxuword   player_ident;
    PxString8 player_text;

    PxConsoleColor player_color;
}
C4NetworkMsgPlayerData;

typedef struct C4NetworkMsgPlayerTurn
{
    pxuword player_ident;
}
C4NetworkMsgPlayerTurn;

typedef struct C4NetworkMsgPlayerChoice
{
    pxuword player_ident;
    pxiword board_column;
}
C4NetworkMsgPlayerChoice;

typedef struct C4NetworkMsgPlayerSkip
{
    pxuword player_ident;
}
C4NetworkMsgPlayerSkip;

typedef pxu8 C4NetworkMsgGameStart;

typedef struct C4NetworkMsgGameStop
{
    pxuword player_ident;
}
C4NetworkMsgGameStop;

typedef struct C4NetworkMsg
{
    C4NetworkMsgType type;

    union
    {
        C4NetworkMsgPlayerJoin   player_join;
        C4NetworkMsgPlayerAccept player_accept;
        C4NetworkMsgPlayerData   player_data;
        C4NetworkMsgPlayerTurn   player_turn;
        C4NetworkMsgPlayerChoice player_choice;
        C4NetworkMsgPlayerSkip   player_skip;

        C4NetworkMsgGameStart game_start;
        C4NetworkMsgGameStop  game_stop;
    };
}
C4NetworkMsg;

C4NetworkMsg
c4NetworkMsgPlayerJoin(pxb8 player_is_automatic);

C4NetworkMsg
c4NetworkMsgPlayerAccept(pxiword player_amount, C4GamePlayer player, pxiword board_width, pxiword board_height);

C4NetworkMsg
c4NetworkMsgPlayerData(C4GamePlayer player);

C4NetworkMsg
c4NetworkMsgPlayerTurn(pxuword player_ident);

C4NetworkMsg
c4NetworkMsgPlayerChoice(pxuword player_ident, pxiword board_column);

C4NetworkMsg
c4NetworkMsgPlayerSkip(pxuword player_ident);

C4NetworkMsg
c4NetworkMsgGameStart();

C4NetworkMsg
c4NetworkMsgGameStop(pxuword player_ident);

/* JSON writing */

pxb8
c4JsonWriteNetworkMsg(C4NetworkMsg* self, PxJsonWriter* writer, PxArena* arena);

pxb8
c4JsonWriteNetworkMsgPlayerJoin(C4NetworkMsgPlayerJoin* self, PxJsonWriter* writer, PxArena* arena);

pxb8
c4JsonWriteNetworkMsgPlayerAccept(C4NetworkMsgPlayerAccept* self, PxJsonWriter* writer, PxArena* arena);

pxb8
c4JsonWriteNetworkMsgPlayerData(C4NetworkMsgPlayerData* self, PxJsonWriter* writer, PxArena* arena);

pxb8
c4JsonWriteNetworkMsgPlayerTurn(C4NetworkMsgPlayerTurn* self, PxJsonWriter* writer, PxArena* arena);

pxb8
c4JsonWriteNetworkMsgPlayerChoice(C4NetworkMsgPlayerChoice* self, PxJsonWriter* writer, PxArena* arena);

pxb8
c4JsonWriteNetworkMsgPlayerSkip(C4NetworkMsgPlayerSkip* self, PxJsonWriter* writer, PxArena* arena);

pxb8
c4JsonWriteNetworkMsgGameStart(C4NetworkMsgGameStart* self, PxJsonWriter* writer, PxArena* arena);

pxb8
c4JsonWriteNetworkMsgGameStop(C4NetworkMsgGameStop* self, PxJsonWriter* writer, PxArena* arena);

/* JSON reading */

pxb8
c4JsonReadNetworkMsg(C4NetworkMsg* self, PxJsonReader* reader, PxArena* arena);

pxb8
c4JsonReadNetworkMsgPlayerJoin(C4NetworkMsgPlayerJoin* self, PxJsonReader* reader, PxArena* arena);

pxb8
c4JsonReadNetworkMsgPlayerAccept(C4NetworkMsgPlayerAccept* self, PxJsonReader* reader, PxArena* arena);

pxb8
c4JsonReadNetworkMsgPlayerData(C4NetworkMsgPlayerData* self, PxJsonReader* reader, PxArena* arena);

pxb8
c4JsonReadNetworkMsgPlayerTurn(C4NetworkMsgPlayerTurn* self, PxJsonReader* reader, PxArena* arena);

pxb8
c4JsonReadNetworkMsgPlayerChoice(C4NetworkMsgPlayerChoice* self, PxJsonReader* reader, PxArena* arena);

pxb8
c4JsonReadNetworkMsgPlayerSkip(C4NetworkMsgPlayerSkip* self, PxJsonReader* reader, PxArena* arena);

pxb8
c4JsonReadNetworkMsgGameStart(C4NetworkMsgGameStart* self, PxJsonReader* reader, PxArena* arena);

pxb8
c4JsonReadNetworkMsgGameStop(C4NetworkMsgGameStop* self, PxJsonReader* reader, PxArena* arena);

#endif // C4_ENGINE_MESSAGE_H
