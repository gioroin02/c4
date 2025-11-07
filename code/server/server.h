#ifndef C4_SERVER_SERVER_H
#define C4_SERVER_SERVER_H

#include "./import.h"

typedef enum C4_Game_State
{
    C4_GAME_STATE_NONE,
}
C4_Game_State;

typedef struct C4_Game_Config
{
    Pax_Addr server_addr;
    paxuword server_port;
    paxuword board_width;
    paxuword board_height;
    paxuword player_number;
}
C4_Game_Config;

typedef struct C4_Game_Server
{
    C4_Game_State  state;
    C4_Game_Config config;

    Pax_Thread_Pool* pool;

    Pax_Channel console_input;

    Pax_Console    console;
    Pax_Socket_TCP socket;

    Pax_Array client_list;

    C4_Game_Board       game_board;
    C4_Game_Player_List game_player_list;
    paxiword            game_player_turn;
}
C4_Game_Server;

typedef struct C4_Game_Client
{
    Pax_Channel network_input;
    Pax_Channel network_output;

    Pax_Socket_TCP socket;

    Pax_JSON_Reader json_reader;
    Pax_JSON_Writer json_writer;
}
C4_Game_Client;

/* Server */

paxb8
c4_game_server_peek(C4_Game_Server* self, paxiword index, C4_Game_Client** value);

C4_Game_Client*
c4_game_server_peek_or(C4_Game_Server* self, paxiword index, C4_Game_Client* value);

paxb8
c4_game_server_find(C4_Game_Server* self, C4_Game_Client* value, paxiword* index);

paxiword
c4_game_server_find_or(C4_Game_Server* self, C4_Game_Client* value, paxiword index);

paxb8
c4_game_server_network_listen(C4_Game_Server* self, Pax_Arena* arena);

paxb8
c4_game_client_network_push(C4_Game_Client* self, Pax_Arena* arena, C4_Game_Message value);

paxb8
c4_game_client_network_pull(C4_Game_Client* self, Pax_Arena* arena, C4_Game_Message* value);

paxb8
c4_game_server_network_push(C4_Game_Server* self, Pax_Arena* arena, C4_Game_Message value, C4_Game_Client* from);

paxb8
c4_game_server_network_input(C4_Game_Server* self, Pax_Arena* arena);

void
c4_game_server_network_output(C4_Game_Server* self, Pax_Arena* arena);

paxb8
c4_game_server_console_pull(C4_Game_Server* self, Pax_Arena* arena, C4_Console_Message* value);

paxb8
c4_game_server_console_input(C4_Game_Server* self, Pax_Arena* arena);

void
c4_game_server_console_output(C4_Game_Server* self, Pax_Arena* arena);

/* Engine */

paxb8
c4_game_server_start(C4_Game_Server* self, C4_Engine* engine, Pax_Arena* arena);

void
c4_game_server_stop(C4_Game_Server* self, C4_Engine* engine);

paxb8
c4_game_server_input(C4_Game_Server* self, C4_Engine* engine, Pax_Arena* arena);

void
c4_game_server_output(C4_Game_Server* self, C4_Engine* engine, Pax_Arena* arena);

#endif // C4_SERVER_SERVER_H
