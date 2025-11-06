#ifndef C4_ENGINE_GAME_MESSAGE_H
#define C4_ENGINE_GAME_MESSAGE_H

#include "./import.h"

typedef enum C4_Console_Message_Kind
{
    C4_CONSOLE_MESSAGE_NONE,
    C4_CONSOLE_MESSAGE_QUIT,
    C4_CONSOLE_MESSAGE_UNICODE,
}
C4_Console_Message_Kind;

typedef paxi32 C4_Console_Message_Unicode;

typedef struct C4_Console_Message
{
    C4_Console_Message_Kind kind;

    union
    {
        C4_Console_Message_Unicode unicode;
    };
}
C4_Console_Message;

typedef enum C4_Game_Message_Kind
{
    C4_GAME_MESSAGE_KIND_NONE,

    C4_GAME_MESSAGE_KIND_PLAYER_JOIN,
    C4_GAME_MESSAGE_KIND_PLAYER_ACCEPT,

    C4_GAME_MESSAGE_KIND_PLAYER_DATA,

    C4_GAME_MESSAGE_KIND_PLAYER_TURN,
    C4_GAME_MESSAGE_KIND_PLAYER_CHOICE,
    C4_GAME_MESSAGE_KIND_PLAYER_SKIP,

    C4_GAME_MESSAGE_KIND_START,
    C4_GAME_MESSAGE_KIND_STOP,

    C4_GAME_MESSAGE_KIND_COUNT,
}
C4_Game_Message_Kind;

typedef struct C4_Game_Message_Player_Join
{
    paxb8 player_is_automatic;
}
C4_Game_Message_Player_Join;

typedef struct C4_Game_Message_Player_Accept
{
    paxiword player_number;

    paxuword player_code;
    paxu8    piece_color;
    paxu8    piece_shape;

    paxiword board_width;
    paxiword board_height;
}
C4_Game_Message_Player_Accept;

typedef struct C4_Game_Message_Player_Data
{
    paxuword player_code;
    paxu8    piece_color;
    paxu8    piece_shape;
}
C4_Game_Message_Player_Data;

typedef struct C4_Game_Message_Player_Turn
{
    paxuword player_code;
}
C4_Game_Message_Player_Turn;

typedef struct C4_Game_Message_Player_Choice
{
    paxuword player_code;
    paxiword board_column;
}
C4_Game_Message_Player_Choice;

typedef struct C4_Game_Message_Player_Skip
{
    paxuword player_code;
}
C4_Game_Message_Player_Skip;

typedef struct C4_Game_Message_Start
{
    paxuword player_number;
}
C4_Game_Message_Start;

typedef struct C4_Game_Message_Stop
{
    paxuword player_code;
}
C4_Game_Message_Stop;

typedef struct C4_Game_Message
{
    C4_Game_Message_Kind kind;

    union
    {
        C4_Game_Message_Player_Join   player_join;
        C4_Game_Message_Player_Accept player_accept;
        C4_Game_Message_Player_Data   player_data;
        C4_Game_Message_Player_Turn   player_turn;
        C4_Game_Message_Player_Choice player_choice;
        C4_Game_Message_Player_Skip   player_skip;

        C4_Game_Message_Start start;
        C4_Game_Message_Stop  stop;
    };
} C4_Game_Message;

/* Console */

C4_Console_Message
c4_console_message_quit();

C4_Console_Message
c4_console_message_unicode(paxi32 value);

/* Game */

C4_Game_Message
c4_game_message_player_join(paxb8 player_is_automatic);

C4_Game_Message
c4_game_message_player_accept(paxiword player_number, paxuword player_code, paxu8 piece_color, paxu8 piece_shape, paxiword board_width, paxiword board_height);

C4_Game_Message
c4_game_message_player_data(paxuword player_code, paxu8 piece_color, paxu8 piece_shape);

C4_Game_Message
c4_game_message_player_turn(paxuword player_code);

C4_Game_Message
c4_game_message_player_choice(paxuword player_code, paxiword board_column);

C4_Game_Message
c4_game_message_player_skip(paxuword player_code);

C4_Game_Message
c4_game_message_start(paxiword player_number);

C4_Game_Message
c4_game_message_stop(paxuword player_code);

/* JSON writing */

paxb8
c4_game_message_json_write(C4_Game_Message* self, Pax_JSON_Writer* writer, Pax_Arena* arena);

paxb8
c4_game_message_json_write_player_join(C4_Game_Message_Player_Join* self, Pax_JSON_Writer* writer, Pax_Arena* arena);

paxb8
c4_game_message_json_write_player_accept(C4_Game_Message_Player_Accept* self, Pax_JSON_Writer* writer, Pax_Arena* arena);

paxb8
c4_game_message_json_write_player_data(C4_Game_Message_Player_Data* self, Pax_JSON_Writer* writer, Pax_Arena* arena);

paxb8
c4_game_message_json_write_player_turn(C4_Game_Message_Player_Turn* self, Pax_JSON_Writer* writer, Pax_Arena* arena);

paxb8
c4_game_message_json_write_player_choice(C4_Game_Message_Player_Choice* self, Pax_JSON_Writer* writer, Pax_Arena* arena);

paxb8
c4_game_message_json_write_player_skip(C4_Game_Message_Player_Skip* self, Pax_JSON_Writer* writer, Pax_Arena* arena);

paxb8
c4_game_message_json_write_start(C4_Game_Message_Start* self, Pax_JSON_Writer* writer, Pax_Arena* arena);

paxb8
c4_game_message_json_write_stop(C4_Game_Message_Stop* self, Pax_JSON_Writer* writer, Pax_Arena* arena);

/* JSON reading */

paxb8
c4_game_message_json_read(C4_Game_Message* self, Pax_JSON_Reader* reader, Pax_Arena* arena);

paxb8
c4_game_message_json_read_player_join(C4_Game_Message_Player_Join* self, Pax_JSON_Reader* reader, Pax_Arena* arena);

paxb8
c4_game_message_json_read_player_accept(C4_Game_Message_Player_Accept* self, Pax_JSON_Reader* reader, Pax_Arena* arena);

paxb8
c4_game_message_json_read_player_data(C4_Game_Message_Player_Data* self, Pax_JSON_Reader* reader, Pax_Arena* arena);

paxb8
c4_game_message_json_read_player_turn(C4_Game_Message_Player_Turn* self, Pax_JSON_Reader* reader, Pax_Arena* arena);

paxb8
c4_game_message_json_read_player_choice(C4_Game_Message_Player_Choice* self, Pax_JSON_Reader* reader, Pax_Arena* arena);

paxb8
c4_game_message_json_read_player_skip(C4_Game_Message_Player_Skip* self, Pax_JSON_Reader* reader, Pax_Arena* arena);

paxb8
c4_game_message_json_read_start(C4_Game_Message_Start* self, Pax_JSON_Reader* reader, Pax_Arena* arena);

paxb8
c4_game_message_json_read_stop(C4_Game_Message_Stop* self, Pax_JSON_Reader* reader, Pax_Arena* arena);

#endif // C4_ENGINE_GAME_MESSAGE_H
