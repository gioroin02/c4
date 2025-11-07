#ifndef C4_SERVER_SERVER_H
#define C4_SERVER_SERVER_H

#include "./import.h"

typedef struct C4_Game_Server
{
    Pax_Socket_TCP socket;

    Pax_Array client_list;
}
C4_Game_Server;

typedef struct C4_Game_Client
{
    Pax_Socket_TCP socket;

    Pax_JSON_Reader reader;
    Pax_JSON_Writer writer;
}
C4_Game_Client;

C4_Game_Server
c4_game_server_create(Pax_Arena* arena, paxiword length, Pax_Addr_Kind kind);

paxb8
c4_game_server_start(C4_Game_Server* self, Pax_Addr addr, paxu16 port);

void
c4_game_server_stop(C4_Game_Server* self);

paxb8
c4_game_server_peek(C4_Game_Server* self, paxiword index, C4_Game_Client** value);

C4_Game_Client*
c4_game_server_peek_or(C4_Game_Server* self, paxiword index, C4_Game_Client* value);

paxiword
c4_game_server_find(C4_Game_Server* self, C4_Game_Client* value);

void
c4_game_server_echo(C4_Game_Server* self, Pax_Arena* arena, C4_Game_Client* from, C4_Game_Message value);

C4_Game_Client*
c4_game_client_start(C4_Game_Server* self, Pax_Arena* arena);

paxb8
c4_game_client_stop(C4_Game_Server* self, C4_Game_Client* client);

paxb8
c4_game_client_write(C4_Game_Client* self, Pax_Arena* arena, C4_Game_Message value);

paxb8
c4_game_client_read(C4_Game_Client* self, Pax_Arena* arena, C4_Game_Message* value);

#endif // C4_SERVER_SERVER_H
