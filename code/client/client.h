#ifndef C4_CLIENT_CLIENT_H
#define C4_CLIENT_CLIENT_H

#include "./import.h"

typedef enum C4_Game_State
{
    C4_GAME_STATE_NONE,
    C4_GAME_STATE_JOIN,
    C4_GAME_STATE_ACCEPT,
    C4_GAME_STATE_WAIT,
    C4_GAME_STATE_TURN,
    C4_GAME_STATE_WATCH,
    C4_GAME_STATE_FINISH,
    C4_GAME_STATE_QUIT,
}
C4_Game_State;

typedef struct C4_Game_Config
{
    Pax_Addr  server_addr;
    paxuword  server_port;
    paxb8     automatic;
}
C4_Game_Config;

typedef struct C4_Game_Client
{
    C4_Game_State  state;
    C4_Game_Config config;

    Pax_Thread_Pool* pool;

    Pax_Channel network_input;
    Pax_Channel network_output;
    Pax_Channel console_input;

    Pax_Socket_TCP socket;
    Pax_Console    console;

    Pax_JSON_Reader json_reader;
    Pax_JSON_Writer json_writer;

    C4_Game_Board       game_board;
    C4_Game_Player_List game_player_list;
}
C4_Game_Client;

/* Client */

paxb8
c4_game_client_network_connect(C4_Game_Client* self, Pax_Arena* arena);

paxb8
c4_game_client_network_push(C4_Game_Client* self, Pax_Arena* arena, C4_Game_Message value);

paxb8
c4_game_client_network_pull(C4_Game_Client* self, Pax_Arena* arena, C4_Game_Message* value);

paxb8
c4_game_client_network_input(C4_Game_Client* self, Pax_Arena* arena);

void
c4_game_client_network_output(C4_Game_Client* self, Pax_Arena* arena);

paxb8
c4_game_client_console_pull(C4_Game_Client* self, Pax_Arena* arena, C4_Console_Message* value);

paxb8
c4_game_client_console_input(C4_Game_Client* self, Pax_Arena* arena);

void
c4_game_client_console_output(C4_Game_Client* self, Pax_Arena* arena);

/* Engine */

paxb8
c4_game_client_start(C4_Game_Client* self, C4_Engine* engine, Pax_Arena* arena);

paxb8
c4_game_client_input(C4_Game_Client* self, C4_Engine* engine, Pax_Arena* arena);

void
c4_game_client_output(C4_Game_Client* self, C4_Engine* engine, Pax_Arena* arena);

#endif // C4_CLIENT_CLIENT_H
