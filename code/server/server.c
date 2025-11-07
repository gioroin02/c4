#ifndef C4_SERVER_SERVER_C
#define C4_SERVER_SERVER_C

#include "./server.h"

void
c4_game_console_input_task(C4_Game_Server* self, Pax_Arena _)
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
c4_game_server_peek(C4_Game_Server* self, paxiword index, C4_Game_Client** value)
{
    return pax_array_peek(&self->client_list, C4_Game_Client*, index, value, 1);
}

C4_Game_Client*
c4_game_server_peek_or(C4_Game_Server* self, paxiword index, C4_Game_Client* value)
{
    C4_Game_Client* result = 0;

    if (c4_game_server_peek(self, index, &result) == 0)
        return value;

    return result;
}

paxb8
c4_game_server_find(C4_Game_Server* self, C4_Game_Client* value, paxiword* index)
{
    paxiword elements =
        pax_array_elements(&self->client_list);

    paxiword temp = 0;

    for (; temp < elements; temp += 1) {
        C4_Game_Client* item =
            c4_game_server_peek_or(self, temp, 0);

        if (item == value) break;
    }

    if (temp >= elements) return 0;

    if (index != 0) *index = temp;

    return 1;
}

paxiword
c4_game_server_find_or(C4_Game_Server* self, C4_Game_Client* value, paxiword index)
{
    paxiword result = 0;

    if (c4_game_server_find(self, value, &result) == 0)
        return index;

    return result;
}

paxb8
c4_game_server_network_listen(C4_Game_Server* self, Pax_Arena* arena)
{
    Pax_Addr addr = self->config.server_addr;
    paxuword port = self->config.server_port;

    if (pax_socket_tcp_bind(self->socket, addr, port) == 0)
        return 0;

    if (pax_socket_tcp_listen(self->socket) == 0) return 0;

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
c4_game_server_network_push(C4_Game_Server* self, Pax_Arena* arena, C4_Game_Message value, C4_Game_Client* from)
{
    paxiword elements = pax_array_elements(&self->client_list);
    paxb8    result   = 1;

    for (paxiword i = 0; i < elements; i += 1) {
        C4_Game_Client* client = 0;

        pax_array_peek(&self->client_list,
            C4_Game_Client*, i, &client, 1);

        if (client != 0 && client != from) {
            paxb8 state =
                c4_game_client_network_push(client, arena, value);

            if (state == 0) result = 0;
        }
    }

    return result != 0 ? 1 : 0;
}

paxb8
c4_game_server_network_input(C4_Game_Server* self, Pax_Arena* arena)
{
    paxiword index = self->game_player_turn;

    C4_Game_Message message = {0};
    C4_Game_Client* client  = c4_game_server_peek_or(self, index, 0);

    if (client == 0) return 1;

    if (c4_game_client_network_pull(client, arena, &message) == 0) return 1;

    switch (self->state) {
        default: break;
    }

    return 1;
}

void
c4_game_server_network_output(C4_Game_Server* self, Pax_Arena* arena)
{
    C4_Game_Message message = {0};

    switch (self->state) {
        default: break;
    }
}

paxb8
c4_game_server_console_pull(C4_Game_Server* self, Pax_Arena* arena, C4_Console_Message* value)
{
    return pax_channel_try_remove(&self->console_input, C4_Console_Message, value);
}

paxb8
c4_game_server_console_input(C4_Game_Server* self, Pax_Arena* arena)
{
    Pax_Worker_Data data = {
        .ctxt = self,
        .proc = &c4_game_console_input_task,
    };

    pax_thread_pool_delegate(self->pool, data);

    C4_Console_Message message = {0};

    if (c4_game_server_console_pull(self, arena, &message) == 0)
        return 1;

    if (message.kind == C4_CONSOLE_MESSAGE_QUIT) return 0;

    return 1;
}

void
c4_game_server_console_output(C4_Game_Server* self, Pax_Arena* arena)
{
    Pax_String8 string = pax_str8("\x1b\x63prova\n");

    pax_console_write(self->console,
        string.memory, string.length);
}

paxb8
c4_game_server_start(C4_Game_Server* self, C4_Engine* engine, Pax_Arena* arena)
{
    paxiword cores = pax_process_core_amount() / 2 + 1;
    paxiword tasks = 32;
    Pax_Addr addr  = self->config.server_addr;

    self->pool = pax_thread_pool_create(arena, cores, tasks);

    self->console_input = pax_channel_create(arena, C4_Console_Message, tasks);

    self->socket = pax_socket_tcp_create(arena, addr.kind);

    if (c4_game_server_network_listen(self, arena) == 0)
        return 0;

    self->console = pax_console_create(arena);

    if (pax_console_mode_apply(self->console, PAX_CONSOLE_MODE_RAW) == 0)
        return 0;

    return 1;
}

void
c4_game_server_stop(C4_Game_Server* self, C4_Engine* engine)
{
    pax_console_mode_apply(self, PAX_CONSOLE_MODE_DEFAULT);
}

paxb8
c4_game_server_input(C4_Game_Server* self, C4_Engine* engine, Pax_Arena* arena)
{
    if (c4_game_server_network_input(self, arena) == 0)
        return 0;

    if (c4_game_server_console_input(self, arena) == 0)
        return 0;

    return 1;
}

void
c4_game_server_output(C4_Game_Server* self, C4_Engine* engine, Pax_Arena* arena)
{
    c4_game_server_network_output(self, arena);
    c4_game_server_console_output(self, arena);
}

#endif // C4_SERVER_SERVER_C
