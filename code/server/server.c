#ifndef C4_SERVER_SERVER_C
#define C4_SERVER_SERVER_C

#include "./server.h"

C4_Game_Server
c4_game_server_create(Pax_Arena* arena, paxiword length, Pax_Addr_Kind kind)
{
    return (C4_Game_Server) {
        .socket      = pax_socket_tcp_create(arena, kind),
        .client_list = pax_array_create(arena, C4_Game_Client*, length),
    };
}

void
c4_game_server_destroy(C4_Game_Server* self)
{
    if (self == 0) return;

    while (pax_array_elements(&self->client_list) > 0) {
        C4_Game_Client* client = 0;

        paxiword index =
            pax_array_tail(&self->client_list);

            pax_array_remove(&self->client_list,
                C4_Game_Client*, index, &client, 1);

            c4_game_client_stop(self, client);
    }

    c4_game_server_stop(self);
}

paxb8
c4_game_server_start(C4_Game_Server* self, Pax_Addr addr, paxu16 port)
{
    if (pax_socket_tcp_bind(self->socket, addr, port) != 0)
        return pax_socket_tcp_listen(self->socket);

    return 0;
}

void
c4_game_server_stop(C4_Game_Server* self)
{
    if (self == 0) return;

    pax_socket_tcp_destroy(self->socket);

    self->socket = 0;
}

paxb8
c4_game_server_peek(C4_Game_Server* self, paxiword index, C4_Game_Client** value)
{
    return pax_array_peek(&self->client_list,
        C4_Game_Client*, index, value, 1);
}

C4_Game_Client*
c4_game_server_peek_or(C4_Game_Server* self, paxiword index, C4_Game_Client* value)
{
    C4_Game_Client* result = 0;

    if (c4_game_server_peek(self, index, &result) == 0)
        return value;

    return result;
}

paxiword
c4_game_server_find(C4_Game_Server* self, C4_Game_Client* value)
{
    paxiword elements =
        pax_array_elements(&self->client_list);

    for (paxiword i = 0; i < elements; i += 1) {
        if (c4_game_server_peek_or(self, i, 0) == value)
            return i;
    }

    return elements;
}

void
c4_game_server_echo(C4_Game_Server* self, Pax_Arena* arena, C4_Game_Client* from, C4_Game_Message value)
{
    paxiword elements =
        pax_array_elements(&self->client_list);

    for (paxiword i = 0; i < elements; i += 1) {
        C4_Game_Client* client = c4_game_server_peek_or(self, i, 0);

        if (client != from)
            c4_game_client_write(client, arena, value);
    }
}

C4_Game_Client*
c4_game_client_start(C4_Game_Server* self, Pax_Arena* arena)
{
    paxiword mark = pax_arena_tell(arena);

    if (pax_array_is_full(&self->client_list) != 0)
        return 0;

    C4_Game_Client* result = pax_arena_reserve(arena, C4_Game_Client, 1);

    if (result == 0) return 0;

    result->socket = pax_socket_tcp_accept(self->socket, arena);

    if (result->socket != 0) {
        paxiword index =
            pax_array_tail(&self->client_list);

            pax_array_insert(&self->client_list,
            C4_Game_Client*, index + 1, &result, 1);

        return result;
    }

    pax_arena_rewind(arena, mark, 0);

    return 0;
}

paxb8
c4_game_client_stop(C4_Game_Server* self, C4_Game_Client* client)
{
    paxiword index = c4_game_server_find(self, client);
    paxiword size  = pax_array_elements(&self->client_list);
    paxb8    state = 0;

    if (index < 0 || index >= size) return 0;

    state = pax_array_remove(&self->client_list,
        C4_Game_Client*, index, 0, 1);

    if (state != 0)
        pax_socket_tcp_destroy(client->socket);

    return state;
}

paxb8
c4_game_client_write(C4_Game_Client* self, Pax_Arena* arena, C4_Game_Message value)
{
    return c4_game_message_json_write(&value, &self->writer, arena);
}

paxb8
c4_game_client_Read(C4_Game_Client* self, Pax_Arena* arena, C4_Game_Message* value)
{
    return c4_game_message_json_write(value, &self->writer, arena);
}

#endif // C4_SERVER_SERVER_C
