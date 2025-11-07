#ifndef C4_CLIENT_CLIENT_C
#define C4_CLIENT_CLIENT_C

#include "./client.h"

void
c4_game_console_input_task(C4_Game_Client* self, Pax_Arena _)
{
    paxu8 byte = 0;

    if (pax_console_poll(self, &byte, 1) <= 0) return;

    C4_Console_Message message = c4_console_message_unicode(byte);

    if (byte == PAX_ASCII_LOWER_Q)
        message = c4_console_message_quit();

    pax_channel_insert(&self->console_input,
        C4_Console_Message, &message);
}

void
c4_game_network_input_task(C4_Game_Client* self, Pax_Arena _)
{
    paxu8 memory[256] = {0};

    C4_Game_Message message = {0};
    Pax_Arena       arena   = pax_arena_make(memory, pax_size_block(paxu8, memory));

    if (c4_game_message_json_read(&message, &self->json_reader, &arena) == 0)
        return;

    pax_channel_insert(&self->network_input, C4_Game_Message, &message);
}

void
c4_game_network_output_task(C4_Game_Client* self, Pax_Arena _)
{
    paxu8 memory[256] = {0};

    C4_Game_Message message = {0};
    Pax_Arena       arena   = pax_arena_make(memory, pax_size_block(paxu8, memory));

    if (pax_channel_remove(&self->network_output, C4_Game_Message, &message) == 0)
        return;

    c4_game_message_json_write(&message, &self->json_writer, &arena);
}

paxb8
c4_game_client_network_connect(C4_Game_Client* self, Pax_Arena* arena)
{
    Pax_Addr addr = self->config.server_addr;
    paxuword port = self->config.server_port;

    if (pax_socket_tcp_connect(self->socket, addr, port) == 0)
        return 0;

    return 1;
}

paxb8
c4_game_client_network_push(C4_Game_Client* self, Pax_Arena* arena, C4_Game_Message value)
{
    return pax_channel_insert(&self->network_output, C4_Game_Message, &value);
}

paxb8
c4_game_client_network_pull(C4_Game_Client* self, Pax_Arena* arena, C4_Game_Message* value)
{
    return pax_channel_try_remove(&self->network_input, C4_Game_Message, value);
}

paxb8
c4_game_client_network_input(C4_Game_Client* self, Pax_Arena* arena)
{
    C4_Game_Message message = {0};

    if (c4_game_client_network_pull(self, arena, &message) == 0) return 1;

    switch (self->state) {
        case C4_GAME_STATE_JOIN: {
            if (message.kind != C4_GAME_MESSAGE_KIND_PLAYER_ACCEPT)
                break;

            self->game_board = c4_game_board_create(arena,
                message.player_accept.board_width,
                message.player_accept.board_height);

            if (c4_game_board_capacity(&self->game_board) <= 0)
                return 0;

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

            self->state = C4_GAME_STATE_ACCEPT;
        } break;

        case C4_GAME_STATE_ACCEPT: {
            paxiword elements = c4_game_player_list_elements(&self->game_player_list);
            paxiword capacity = c4_game_player_list_capacity(&self->game_player_list);

            if (message.kind == C4_GAME_MESSAGE_KIND_PLAYER_DATA) {
                if (elements < 0 || elements >= capacity) return 0;

                C4_Game_Player player = {
                    message.player_data.player_code,
                    message.player_data.piece_shape,
                    message.player_data.piece_color,
                };

                c4_game_player_list_insert(&self->game_player_list, player);
            }

            if (message.kind == C4_GAME_MESSAGE_KIND_START) {
                self->state = C4_GAME_STATE_WAIT;

                if (message.start.player_number != elements)
                    return 0;
            }
        } break;

        case C4_GAME_STATE_WAIT: {
            C4_Game_Player player = c4_game_player_list_peek_or(
                &self->game_player_list, 0, (C4_Game_Player) {0});

            if (message.kind == C4_GAME_MESSAGE_KIND_PLAYER_TURN) {
                self->state = C4_GAME_STATE_WATCH;

                if (message.player_turn.player_code == player.code)
                    self->state = C4_GAME_STATE_TURN;
            }

            if (message.kind == C4_GAME_MESSAGE_KIND_STOP)
                self->state = C4_GAME_STATE_FINISH;
        } break;

        case C4_GAME_STATE_WATCH: {
            if (message.kind == C4_GAME_MESSAGE_KIND_PLAYER_CHOICE) {
                // update board

                self->state = C4_GAME_STATE_WAIT;
            }
        } break;

        default: break;
    }

    return 1;
}

void
c4_game_client_network_output(C4_Game_Client* self, Pax_Arena* arena)
{
    C4_Game_Message message = {0};

    switch (self->state) {
        case C4_GAME_STATE_NONE: {
            message = c4_game_message_player_join(self->config.automatic);

            if (c4_game_client_network_push(self, arena, message) == 0)
                break;

            self->state = C4_GAME_STATE_JOIN;
        } break;

        case C4_GAME_STATE_TURN: {
            // if (ready) {
            //     if (send() == 0)
            //         break;
            //
            //     self->state = C4_GAME_STATE_WAIT;
            // }
        } break;

        default: break;
    }
}

paxb8
c4_game_client_console_pull(C4_Game_Client* self, Pax_Arena* arena, C4_Console_Message* value)
{
    return pax_channel_try_remove(&self->console_input, C4_Console_Message, value);
}

paxb8
c4_game_client_console_input(C4_Game_Client* self, Pax_Arena* arena)
{
    Pax_Worker_Data data = {
        .ctxt = self,
        .proc = &c4_game_console_input_task,
    };

    pax_thread_pool_delegate(self->pool, data);

    C4_Console_Message message = {0};

    if (c4_game_client_console_pull(self, arena, &message) == 0)
        return 1;

    if (message.kind == C4_CONSOLE_MESSAGE_QUIT) return 0;

    return 1;
}

void
c4_game_client_console_output(C4_Game_Client* self, Pax_Arena* arena)
{
    Pax_String8 string = pax_str8("\x1b\x63prova\n");

    pax_console_write(self->console,
        string.memory, string.length);
}

paxb8
c4_game_client_start(C4_Game_Client* self, C4_Engine* engine, Pax_Arena* arena)
{
    paxiword cores = pax_process_core_amount() / 2 + 1;
    paxiword tasks = 32;
    Pax_Addr addr  = self->config.server_addr;

    self->pool = pax_thread_pool_create(arena, cores, tasks);

    self->network_input  = pax_channel_create(arena, C4_Game_Message, tasks);
    self->network_output = pax_channel_create(arena, C4_Game_Message, tasks);
    self->console_input  = pax_channel_create(arena, C4_Console_Message, tasks);

    self->socket = pax_socket_tcp_create(arena, addr.kind);

    if (c4_game_client_network_connect(self, arena) == 0)
        return 0;

    self->console = pax_console_create(arena);

    if (pax_console_mode_apply(self->console, PAX_CONSOLE_MODE_RAW) == 0)
        return 0;

    Pax_Scanner scanner = pax_scanner_create(arena, 32,
        pax_source_from_socket_tcp(arena, self->socket));

    self->json_reader = pax_json_reader_create(arena, 4, scanner);

    self->json_writer = pax_json_writer_create(arena, 4,
        pax_target_from_socket_tcp(arena, self->socket));

    return 1;
}

void
c4_game_client_stop(C4_Game_Client* self, C4_Engine* engine)
{
    pax_console_mode_apply(self, PAX_CONSOLE_MODE_DEFAULT);
}

paxb8
c4_game_client_input(C4_Game_Client* self, C4_Engine* engine, Pax_Arena* arena)
{
    if (c4_game_client_network_input(self, arena) == 0)
        return 0;

    if (c4_game_client_console_input(self, arena) == 0)
        return 0;

    return 1;
}

void
c4_game_client_output(C4_Game_Client* self, C4_Engine* engine, Pax_Arena* arena)
{
    c4_game_client_network_output(self, arena);
    c4_game_client_console_output(self, arena);
}

#endif // C4_CLIENT_CLIENT_C
