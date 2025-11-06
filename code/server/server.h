#ifndef C4_SERVER_SERVER_H
#define C4_SERVER_SERVER_H

#include "./import.h"

typedef struct C4_Server
{
    Pax_Socket_TCP socket;
    Pax_Array      session_list;
}
C4_Server;

typedef struct C4_Session
{
    Pax_Socket_TCP socket;

    Pax_JSON_Reader reader;
    Pax_JSON_Writer writer;
}
C4_Session;

C4_Server
c4_server_create(Pax_Arena* arena, paxiword length, Pax_Addr_Kind kind);

paxb8
c4_server_start(C4_Server* self, Pax_Addr addr, paxu16 port);

void
c4_server_stop(C4_Server* self);

paxb8
c4_server_peek(C4_Server* self, paxiword index, C4_Session** value);

C4_Session*
c4_server_peek_or(C4_Server* self, paxiword index, C4_Session* value);

paxiword
c4_server_find(C4_Server* self, C4_Session* value);

void
c4_server_echo(C4_Server* self, Pax_Arena* arena, C4_Session* from, C4_Game_Message value);

C4_Session*
c4_session_start(C4_Server* self, Pax_Arena* arena);

paxb8
c4_session_stop(C4_Server* self, C4_Session* session);

paxb8
c4_session_write(C4_Session* self, Pax_Arena* arena, C4_Game_Message value);

paxb8
c4_session_read(C4_Session* self, Pax_Arena* arena, C4_Game_Message* value);

#endif // C4_SERVER_SERVER_H
