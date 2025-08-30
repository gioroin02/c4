#ifndef C4_MESSAGE_H
#define C4_MESSAGE_H

#include "import.h"

typedef enum C4MessageType
{
    C4_MESSAGE_NONE,

    C4_MESSAGE_PLAYER_JOIN,
    C4_MESSAGE_PLAYER_ACCEPT,

    C4_MESSAGE_PLAYER_DATA,

    C4_MESSAGE_PLAYER_TURN,
    C4_MESSAGE_PLAYER_CHOICE,
    C4_MESSAGE_PLAYER_SKIP,

    C4_MESSAGE_GAME_START,
    C4_MESSAGE_GAME_STOP,

    C4_MESSAGE_COUNT,
}
C4MessageType;

typedef struct C4MsgPlayerJoin
{
    pxb8 player_is_automatic;
}
C4MsgPlayerJoin;

typedef struct C4MsgPlayerAccept
{
    pxiword player_number;

    pxuword player_code;
    pxu8    piece_color;
    pxu8    piece_shape;

    pxiword board_width;
    pxiword board_height;
}
C4MsgPlayerAccept;

typedef struct C4MsgPlayerListItem
{
    pxuword player_code;
    pxu8    piece_color;
    pxu8    piece_shape;
}
C4MsgPlayerData;

typedef struct C4MsgPlayerTurn
{
    pxuword player_code;
}
C4MsgPlayerTurn;

typedef struct C4MsgPlayerChoice
{
    pxuword player_code;
    pxiword board_column;
}
C4MsgPlayerChoice;

typedef struct C4MsgPlayerSkip
{
    pxuword player_code;
}
C4MsgPlayerSkip;

typedef struct C4MsgGameStop
{
    pxuword player_code;
}
C4MsgGameStop;

typedef struct C4Message
{
    C4MessageType type;

    union
    {
        C4MsgPlayerJoin   player_join;
        C4MsgPlayerAccept player_accept;
        C4MsgPlayerData   player_data;
        C4MsgPlayerTurn   player_turn;
        C4MsgPlayerChoice player_choice;
        C4MsgPlayerSkip   player_skip;
        C4MsgGameStop     game_stop;
    };
}
C4Message;

C4Message
c4MsgPlayerJoin(pxb8 player_is_automatic);

C4Message
c4MsgPlayerAccept(pxiword player_number, pxuword player_code, pxu8 piece_color, pxu8 piece_shape, pxiword board_width, pxiword board_height);

C4Message
c4MsgPlayerData(pxuword player_code, pxu8 piece_color, pxu8 piece_shape);

C4Message
c4MsgPlayerTurn(pxuword player_code);

C4Message
c4MsgPlayerChoice(pxuword player_code, pxiword board_column);

C4Message
c4MsgPlayerSkip(pxuword player_code);

C4Message
c4MsgGameStart();

C4Message
c4MsgGameStop(pxuword player_code);

/* JSON writing */

pxb8
c4JsonWriteMessage(C4Message* self, PxJsonWriter* writer, PxArena* arena);

pxb8
c4JsonWriteMsgPlayerJoin(C4MsgPlayerJoin* self, PxJsonWriter* writer, PxArena* arena);

pxb8
c4JsonWriteMsgPlayerAccept(C4MsgPlayerAccept* self, PxJsonWriter* writer, PxArena* arena);

pxb8
c4JsonWriteMsgPlayerData(C4MsgPlayerData* self, PxJsonWriter* writer, PxArena* arena);

pxb8
c4JsonWriteMsgPlayerTurn(C4MsgPlayerTurn* self, PxJsonWriter* writer, PxArena* arena);

pxb8
c4JsonWriteMsgPlayerChoice(C4MsgPlayerChoice* self, PxJsonWriter* writer, PxArena* arena);

pxb8
c4JsonWriteMsgPlayerSkip(C4MsgPlayerSkip* self, PxJsonWriter* writer, PxArena* arena);

pxb8
c4JsonWriteMsgGameStart(void* self, PxJsonWriter* writer, PxArena* arena);

pxb8
c4JsonWriteMsgGameStop(C4MsgGameStop* self, PxJsonWriter* writer, PxArena* arena);

/* JSON reading */

pxb8
c4JsonReadMessage(C4Message* self, PxJsonReader* reader, PxArena* arena);

pxb8
c4JsonReadMsgPlayerJoin(C4MsgPlayerJoin* self, PxJsonReader* reader, PxArena* arena);

pxb8
c4JsonReadMsgPlayerAccept(C4MsgPlayerAccept* self, PxJsonReader* reader, PxArena* arena);

pxb8
c4JsonReadMsgPlayerData(C4MsgPlayerData* self, PxJsonReader* reader, PxArena* arena);

pxb8
c4JsonReadMsgPlayerTurn(C4MsgPlayerTurn* self, PxJsonReader* reader, PxArena* arena);

pxb8
c4JsonReadMsgPlayerChoice(C4MsgPlayerChoice* self, PxJsonReader* reader, PxArena* arena);

pxb8
c4JsonReadMsgPlayerSkip(C4MsgPlayerSkip* self, PxJsonReader* reader, PxArena* arena);

pxb8
c4JsonReadMsgGameStart(void* self, PxJsonReader* reader, PxArena* arena);

pxb8
c4JsonReadMsgGameStop(C4MsgGameStop* self, PxJsonReader* reader, PxArena* arena);

/* Console output */

void
c4ShowMessage(C4Message* self);

void
c4ShowMsgPlayerJoin(C4MsgPlayerJoin* self);

void
c4ShowMsgPlayerAccept(C4MsgPlayerAccept* self);

void
c4ShowMsgPlayerData(C4MsgPlayerData* self);

void
c4ShowMsgPlayerTurn(C4MsgPlayerTurn* self);

void
c4ShowMsgPlayerChoice(C4MsgPlayerChoice* self);

void
c4ShowMsgPlayerSkip(C4MsgPlayerSkip* self);

void
c4ShowMsgGameStart(void* self);

void
c4ShowMsgGameStop(C4MsgGameStop* self);

#endif // C4_MESSAGE_H
