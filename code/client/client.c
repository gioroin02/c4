#ifndef C4_CLIENT_CLIENT_C
#define C4_CLIENT_CLIENT_C

#include "./client.h"

C4_Client
c4_client_create(Pax_Arena* arena, Pax_Addr_Kind kind)
{
    return (C4_Client) {
        .socket = pax_socket_tcp_create(arena, kind),
    };
}

void
c4_client_destroy(C4_Client* self)
{
    c4_client_stop(self);
}

paxb8
c4_client_start(C4_Client* self, Pax_Addr addr, paxu16 port)
{
    return pax_socket_tcp_connect(self->socket, addr, port);
}

void
c4_client_stop(C4_Client* self)
{
    if (self == 0) return;

    pax_socket_tcp_destroy(self->socket);

    self->socket = 0;
}

paxb8
c4_client_write(C4_Client* self, Pax_Arena* arena, C4_Game_Message value)
{
    return c4_game_message_json_write(&value, &self->writer, arena);
}

paxb8
c4_client_read(C4_Client* self, Pax_Arena* arena, C4_Game_Message* value)
{
    return c4_game_message_json_read(value, &self->reader, arena);
}

#endif // C4_CLIENT_CLIENT_C
