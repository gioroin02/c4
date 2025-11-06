#ifndef C4_CLIENT_CLIENT_H
#define C4_CLIENT_CLIENT_H

#include "./import.h"

typedef struct C4_Client
{
    Pax_Socket_TCP socket;

    Pax_JSON_Reader reader;
    Pax_JSON_Writer writer;
}
C4_Client;

C4_Client
c4_client_create(Pax_Arena* arena, Pax_Addr_Kind kind);

void
c4_client_destroy(C4_Client* self);

paxb8
c4_client_start(C4_Client* self, Pax_Addr addr, paxu16 port);

void
c4_client_stop(C4_Client* self);

paxb8
c4_client_write(C4_Client* self, Pax_Arena* arena, C4_Game_Message value);

paxb8
c4_client_read(C4_Client* self, Pax_Arena* arena, C4_Game_Message* value);

#endif // C4_CLIENT_CLIENT_H
