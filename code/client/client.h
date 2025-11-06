#ifndef C4_CLIENT_CLIENT_H
#define C4_CLIENT_CLIENT_H

#include "./import.h"

typedef struct C4_Game_Config
{
    Pax_Addr  server_addr;
    paxuword  server_port;
    paxb8     automatic;
}
C4_Game_Config;

typedef struct C4_Game_Client
{
    C4_Game_Config config;

    Pax_Socket_TCP socket;

    Pax_JSON_Reader json_reader;
    Pax_JSON_Writer json_writer;

    C4_Game_Board       game_board;
    C4_Game_Player_List game_player_list;
}
C4_Game_Client;

/* Client */

paxb8
c4_game_client_write(C4_Game_Client* self, Pax_Arena* arena, C4_Game_Message value);

paxb8
c4_game_client_read(C4_Game_Client* self, Pax_Arena* arena, C4_Game_Message* value);

paxb8
c4_game_client_connect(C4_Game_Client* self, Pax_Arena* arena);

paxb8
c4_game_client_join(C4_Game_Client* self, Pax_Arena* arena);

paxb8
c4_game_client_wait(C4_Game_Client* self, Pax_Arena* arena);

/* Engine */

paxb8
c4_game_client_start(C4_Game_Client* self, C4_Engine* engine, Pax_Arena* arena);

#endif // C4_CLIENT_CLIENT_H
