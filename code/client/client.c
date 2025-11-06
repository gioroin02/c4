#ifndef C4_CLIENT_CLIENT_C
#define C4_CLIENT_CLIENT_C

#include "./client.h"

paxb8
c4_game_client_write(C4_Game_Client* self, Pax_Arena* arena, C4_Game_Message value)
{
    return c4_game_message_json_write(&value, &self->json_writer, arena);
}

paxb8
c4_game_client_read(C4_Game_Client* self, Pax_Arena* arena, C4_Game_Message* value)
{
    return c4_game_message_json_read(value, &self->json_reader, arena);
}

paxb8
c4_game_client_connect(C4_Game_Client* self, Pax_Arena* arena)
{
    Pax_Addr addr = self->config.server_addr;
    paxuword port = self->config.server_port;

    if (pax_socket_tcp_connect(self->socket, addr, port) == 0)
        return 0;

    return 1;
}

paxb8
c4_game_client_join(C4_Game_Client* self, Pax_Arena* arena)
{
    C4_Game_Message message = c4_game_message_player_join(self->config.automatic);

    if (c4_game_client_write(self, arena, message) == 0) return 0;
    if (c4_game_client_read(self, arena, &message) == 0) return 0;

    if (message.kind == C4_GAME_MESSAGE_KIND_PLAYER_ACCEPT) {
        self->game_board = c4_game_board_create(arena,
            message.player_accept.board_width, message.player_accept.board_height);

        if (c4_game_board_capacity(&self->game_board) <= 0) return 0;

        self->game_player_list = c4_game_player_list_create(arena,
            message.player_accept.player_number);

        if (c4_game_player_list_capacity(&self->game_player_list) <= 0)
            return 0;

        C4_Game_Player player = {
            message.player_accept.player_code,
            message.player_accept.piece_shape,
            message.player_accept.piece_color,
        };

        c4_game_player_list_insert(&self->game_player_list, player);
    }

    return 1;
}

paxb8
c4_game_client_wait(C4_Game_Client* self, Pax_Arena* arena)
{
    C4_Game_Message message = {0};

    while (c4_game_client_read(self, arena, &message) != 0) {
        if (message.kind == C4_GAME_MESSAGE_KIND_START)
            break;

        if (message.kind == C4_GAME_MESSAGE_KIND_PLAYER_DATA) {
            C4_Game_Player player = {
                message.player_data.player_code,
                message.player_data.piece_shape,
                message.player_data.piece_color,
            };

            c4_game_player_list_insert(&self->game_player_list, player);
        }
    }

    paxiword elements =
        c4_game_player_list_elements(&self->game_player_list);

    return message.start.player_number == elements ? 1 : 0;
}

paxb8
c4_game_client_start(C4_Game_Client* self, C4_Engine* engine, Pax_Arena* arena)
{
    if (c4_game_client_connect(self, arena) == 0)
        return 0;

    if (c4_game_client_join(self, arena) == 0) return 0;
    if (c4_game_client_wait(self, arena) == 0) return 0;

    return 1;
}

#endif // C4_CLIENT_CLIENT_C
