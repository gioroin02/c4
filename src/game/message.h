#ifndef C4_MESSAGE_MESSAGE_H
#define C4_MESSAGE_MESSAGE_H

#include "player.h"

typedef enum C4MsgType
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
C4MsgType;

typedef struct C4MsgPlayerJoin
{
    pxb8 player_is_automatic;
}
C4MsgPlayerJoin;

typedef struct C4MsgPlayerAccept
{
    pxiword player_number;

    pxuword   player_code;
    C4Color   player_color;
    PxString8 player_text;

    pxiword board_width;
    pxiword board_height;
}
C4MsgPlayerAccept;

typedef struct C4MsgPlayerData
{
    pxuword   player_code;
    C4Color   player_color;
    PxString8 player_text;
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

typedef struct C4Msg
{
    C4MsgType type;

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
C4Msg;

C4Msg
c4MsgPlayerJoin(pxb8 player_is_automatic);

C4Msg
c4MsgPlayerAccept(pxiword player_number, C4GamePlayer player, pxiword board_width, pxiword board_height);

C4Msg
c4MsgPlayerData(C4GamePlayer player);

C4Msg
c4MsgPlayerTurn(pxuword player_code);

C4Msg
c4MsgPlayerChoice(pxuword player_code, pxiword board_column);

C4Msg
c4MsgPlayerSkip(pxuword player_code);

C4Msg
c4MsgGameStart();

C4Msg
c4MsgGameStop(pxuword player_code);

/* JSON writing */

pxb8
c4JsonWriteMsg(C4Msg* self, PxJsonWriter* writer, PxArena* arena);

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
c4JsonReadMsg(C4Msg* self, PxJsonReader* reader, PxArena* arena);

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

pxiword
c4FormatProcMsg(C4Msg* self, PxBuilder* builder);

pxiword
c4FormatProcMsgPlayerJoin(C4MsgPlayerJoin* self, PxBuilder* builder);

pxiword
c4FormatProcMsgPlayerAccept(C4MsgPlayerAccept* self, PxBuilder* builder);

pxiword
c4FormatProcMsgPlayerData(C4MsgPlayerData* self, PxBuilder* builder);

pxiword
c4FormatProcMsgPlayerTurn(C4MsgPlayerTurn* self, PxBuilder* builder);

pxiword
c4FormatProcMsgPlayerChoice(C4MsgPlayerChoice* self, PxBuilder* builder);

pxiword
c4FormatProcMsgPlayerSkip(C4MsgPlayerSkip* self, PxBuilder* builder);

pxiword
c4FormatProcMsgGameStart(void* self, PxBuilder* builder);

pxiword
c4FormatProcMsgGameStop(C4MsgGameStop* self, PxBuilder* builder);

#endif // C4_MESSAGE_MESSAGE_H
