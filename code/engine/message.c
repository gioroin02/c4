#ifndef C4_ENGINE_GAME_MESSAGE_C
#define C4_ENGINE_GAME_MESSAGE_C

#include "./message.h"

C4_Console_Message
c4_console_message_quit()
{
    return (C4_Console_Message) {
        .kind = C4_CONSOLE_MESSAGE_QUIT,
    };
}

C4_Console_Message
c4_console_message_unicode(paxi32 value)
{
    return (C4_Console_Message) {
        .kind    = C4_CONSOLE_MESSAGE_UNICODE,
        .unicode = value,
    };
}

C4_Game_Message
c4_game_message_player_join(paxb8 player_is_automatic)
{
    return (C4_Game_Message) {
        .kind = C4_GAME_MESSAGE_KIND_PLAYER_JOIN,

        .player_join = {
            .player_is_automatic = player_is_automatic,
        },
    };
}

C4_Game_Message
c4_game_message_player_accept(paxiword player_number, paxuword player_code, paxu8 piece_color, paxu8 piece_shape, paxiword board_width, paxiword board_height)
{
    return (C4_Game_Message) {
        .kind = C4_GAME_MESSAGE_KIND_PLAYER_ACCEPT,

        .player_accept = {
            .player_number = player_number,
            .player_code   = player_code,
            .piece_color   = piece_color,
            .piece_shape   = piece_shape,
            .board_width   = board_width,
            .board_height  = board_height,
        },
    };
}

C4_Game_Message
c4_game_message_player_data(paxuword player_code, paxu8 piece_color, paxu8 piece_shape)
{
    return (C4_Game_Message) {
        .kind = C4_GAME_MESSAGE_KIND_PLAYER_DATA,

        .player_data = {
            .player_code = player_code,
            .piece_color = piece_color,
            .piece_shape = piece_shape,
        },
    };
}

C4_Game_Message
c4_game_message_player_turn(paxuword player_code)
{
    return (C4_Game_Message) {
        .kind = C4_GAME_MESSAGE_KIND_PLAYER_TURN,

        .player_turn = {
            .player_code = player_code,
        },
    };
}

C4_Game_Message
c4_game_message_player_choice(paxuword player_code, paxiword board_column)
{
    return (C4_Game_Message) {
        .kind = C4_GAME_MESSAGE_KIND_PLAYER_CHOICE,

        .player_choice = {
            .player_code  = player_code,
            .board_column = board_column,
        },
    };
}

C4_Game_Message
c4_game_message_player_skip(paxuword player_code)
{
    return (C4_Game_Message) {
        .kind = C4_GAME_MESSAGE_KIND_PLAYER_SKIP,

        .player_turn = {
            .player_code = player_code,
        },
    };
}

C4_Game_Message
c4_game_message_start(paxiword player_number)
{
    return (C4_Game_Message) {
        .kind = C4_GAME_MESSAGE_KIND_START,

        .start = {
            .player_number = player_number,
        },
    };
}

C4_Game_Message
c4_game_message_stop(paxuword player_code)
{
    return (C4_Game_Message) {
        .kind = C4_GAME_MESSAGE_KIND_STOP,

        .stop = {
            .player_code = player_code,
        },
    };
}

paxb8
c4_game_message_json_write(C4_Game_Message* self, Pax_JSON_Writer* writer, Pax_Arena* arena)
{
    Pax_JSON_Message messages[] = {
        pax_json_message_pair(pax_str8("player_join"), pax_json_message_delegate(
            &self->player_join, &c4_game_message_json_write_player_join)),

        pax_json_message_pair(pax_str8("player_accept"), pax_json_message_delegate(
            &self->player_accept, &c4_game_message_json_write_player_accept)),

        pax_json_message_pair(pax_str8("player_data"), pax_json_message_delegate(
            &self->player_data, &c4_game_message_json_write_player_data)),

        pax_json_message_pair(pax_str8("player_turn"), pax_json_message_delegate(
            &self->player_turn, &c4_game_message_json_write_player_turn)),

        pax_json_message_pair(pax_str8("player_choice"), pax_json_message_delegate(
            &self->player_choice, &c4_game_message_json_write_player_choice)),

        pax_json_message_pair(pax_str8("player_skip"), pax_json_message_delegate(
            &self->player_skip, &c4_game_message_json_write_player_skip)),

        pax_json_message_pair(pax_str8("start"), pax_json_message_delegate(
            &self->start, &c4_game_message_json_write_start)),

        pax_json_message_pair(pax_str8("stop"), pax_json_message_delegate(
            &self->stop, &c4_game_message_json_write_stop)),
    };

    paxiword index = 8;

    switch (self->kind) {
        case  C4_GAME_MESSAGE_KIND_PLAYER_JOIN:   index = 0; break;
        case  C4_GAME_MESSAGE_KIND_PLAYER_ACCEPT: index = 1; break;
        case  C4_GAME_MESSAGE_KIND_PLAYER_DATA:   index = 2; break;
        case  C4_GAME_MESSAGE_KIND_PLAYER_TURN:   index = 3; break;
        case  C4_GAME_MESSAGE_KIND_PLAYER_CHOICE: index = 4; break;
        case  C4_GAME_MESSAGE_KIND_PLAYER_SKIP:   index = 5; break;
        case  C4_GAME_MESSAGE_KIND_START:         index = 6; break;
        case  C4_GAME_MESSAGE_KIND_STOP:          index = 7; break;

        default: break;
    }

    return pax_json_writer_union(writer, arena, index, messages, 8);
}

paxb8
c4_game_message_json_write_player_join(C4_Game_Message_Player_Join* self, Pax_JSON_Writer* writer, Pax_Arena* arena)
{
    Pax_JSON_Message messages[] = {
        pax_json_message_pair(pax_str8("player_is_automatic"),
            pax_json_message_boolean(self->player_is_automatic)),
    };

    return pax_json_writer_record(writer, arena, 0, messages, 1);
}

paxb8
c4_game_message_json_write_player_accept(C4_Game_Message_Player_Accept* self, Pax_JSON_Writer* writer, Pax_Arena* arena)
{
    Pax_String8 piece_shape = pax_string8_copy_unicode(arena, self->piece_shape);

    Pax_JSON_Message messages[] = {
        pax_json_message_pair(pax_str8("player_number"), pax_json_message_unsigned(self->player_number)),
        pax_json_message_pair(pax_str8("player_code"),   pax_json_message_unsigned(self->player_code)),
        pax_json_message_pair(pax_str8("pice_color"),    pax_json_message_unsigned(self->piece_color)),
        pax_json_message_pair(pax_str8("piece_shape"),   pax_json_message_string(piece_shape)),
        pax_json_message_pair(pax_str8("board_width"),   pax_json_message_integer(self->board_width)),
        pax_json_message_pair(pax_str8("board_height"),  pax_json_message_integer(self->board_height)),
    };

    return pax_json_writer_record(writer, arena, 0, messages, 6);
}

paxb8
c4_game_message_json_write_player_data(C4_Game_Message_Player_Data* self, Pax_JSON_Writer* writer, Pax_Arena* arena)
{
    Pax_String8 piece_shape = pax_string8_copy_unicode(arena, self->piece_shape);

    Pax_JSON_Message messages[] = {
        pax_json_message_pair(pax_str8("player_code"), pax_json_message_unsigned(self->player_code)),
        pax_json_message_pair(pax_str8("piece_color"), pax_json_message_unsigned(self->piece_color)),
        pax_json_message_pair(pax_str8("piece_shape"), pax_json_message_string(piece_shape)),
    };

    return pax_json_writer_record(writer, arena, 0, messages, 3);
}

paxb8
c4_game_message_json_write_player_turn(C4_Game_Message_Player_Turn* self, Pax_JSON_Writer* writer, Pax_Arena* arena)
{
    Pax_JSON_Message messages[] = {
        pax_json_message_pair(pax_str8("player_code"),
            pax_json_message_unsigned(self->player_code)),
    };

    return pax_json_writer_record(writer, arena, 0, messages, 1);
}

paxb8
c4_game_message_json_write_player_choice(C4_Game_Message_Player_Choice* self, Pax_JSON_Writer* writer, Pax_Arena* arena)
{
    Pax_JSON_Message messages[] = {
        pax_json_message_pair(pax_str8("player_code"),  pax_json_message_unsigned(self->player_code)),
        pax_json_message_pair(pax_str8("board_column"), pax_json_message_integer(self->board_column)),
    };

    return pax_json_writer_record(writer, arena, 0, messages, 2);
}

paxb8
c4_game_message_json_write_player_skip(C4_Game_Message_Player_Skip* self, Pax_JSON_Writer* writer, Pax_Arena* arena)
{
    Pax_JSON_Message messages[] = {
        pax_json_message_pair(pax_str8("player_code"),
            pax_json_message_unsigned(self->player_code)),
    };

    return pax_json_writer_record(writer, arena, 0, messages, 1);
}

paxb8
c4_game_message_json_write_start(C4_Game_Message_Start* self, Pax_JSON_Writer* writer, Pax_Arena* arena)
{
    Pax_JSON_Message messages[] = {
        pax_json_message_pair(pax_str8("player_number"),
            pax_json_message_unsigned(self->player_number)),
    };

    return pax_json_writer_record(writer, arena, 0, messages, 1);
}

paxb8
c4_game_message_json_write_stop(C4_Game_Message_Stop* self, Pax_JSON_Writer* writer, Pax_Arena* arena)
{
    Pax_JSON_Message messages[] = {
        pax_json_message_pair(pax_str8("player_code"),
            pax_json_message_unsigned(self->player_code)),
    };

    return pax_json_writer_record(writer, arena, 0, messages, 1);
}

paxb8
c4_game_message_json_read(C4_Game_Message* self, Pax_JSON_Reader* reader, Pax_Arena* arena)
{
    Pax_JSON_Message messages[] = {
        pax_json_message_pair(pax_str8("player_join"),
            pax_json_message_delegate(&self->player_join, &c4_game_message_json_read_player_join)),

        pax_json_message_pair(pax_str8("player_accept"),
            pax_json_message_delegate(&self->player_accept, &c4_game_message_json_read_player_accept)),

        pax_json_message_pair(pax_str8("player_data"),
            pax_json_message_delegate(&self->player_data, &c4_game_message_json_read_player_data)),

        pax_json_message_pair(pax_str8("player_turn"),
            pax_json_message_delegate(&self->player_turn, &c4_game_message_json_read_player_turn)),

        pax_json_message_pair(pax_str8("player_choice"),
            pax_json_message_delegate(&self->player_choice, &c4_game_message_json_read_player_choice)),

        pax_json_message_pair(pax_str8("player_skip"),
            pax_json_message_delegate(&self->player_skip, &c4_game_message_json_read_player_skip)),

        pax_json_message_pair(pax_str8("start"),
            pax_json_message_delegate(&self->start, &c4_game_message_json_read_start)),

        pax_json_message_pair(pax_str8("stop"),
            pax_json_message_delegate(&self->stop, &c4_game_message_json_read_stop)),
    };

    paxiword index = 0;

    if (pax_json_reader_union(reader, arena, &index, messages, 8) == 0)
        return 0;

    switch (index) {
        case 0: self->kind = C4_GAME_MESSAGE_KIND_PLAYER_JOIN;   break;
        case 1: self->kind = C4_GAME_MESSAGE_KIND_PLAYER_ACCEPT; break;
        case 2: self->kind = C4_GAME_MESSAGE_KIND_PLAYER_DATA;   break;
        case 3: self->kind = C4_GAME_MESSAGE_KIND_PLAYER_TURN;   break;
        case 4: self->kind = C4_GAME_MESSAGE_KIND_PLAYER_CHOICE; break;
        case 5: self->kind = C4_GAME_MESSAGE_KIND_PLAYER_SKIP;   break;
        case 6: self->kind = C4_GAME_MESSAGE_KIND_START;         break;
        case 7: self->kind = C4_GAME_MESSAGE_KIND_STOP;          break;

        default: break;
    }

    return 1;
}

paxb8
c4_game_message_json_read_player_join(C4_Game_Message_Player_Join* self, Pax_JSON_Reader* reader, Pax_Arena* arena)
{
    Pax_JSON_Message messages[] = {
        pax_json_message_pair(pax_str8("player_is_automatic"),
            pax_json_message_boolean(0)),
    };

    if (pax_json_reader_record(reader, arena, 0, messages, 1) == 0)
        return 0;

    self->player_is_automatic = messages[0].value_boolean;

    return 1;
}

paxb8
c4_game_message_json_read_player_accept(C4_Game_Message_Player_Accept* self, Pax_JSON_Reader* reader, Pax_Arena* arena)
{
    Pax_JSON_Message messages[] = {
        pax_json_message_pair(pax_str8("player_number"), pax_json_message_unsigned(0)),
        pax_json_message_pair(pax_str8("player_code"),   pax_json_message_unsigned(0)),
        pax_json_message_pair(pax_str8("piece_shape"),   pax_json_message_string(pax_str8(""))),
        pax_json_message_pair(pax_str8("piece_color"),   pax_json_message_unsigned(0)),
        pax_json_message_pair(pax_str8("board_width"),   pax_json_message_unsigned(0)),
        pax_json_message_pair(pax_str8("board_height"),  pax_json_message_unsigned(0)),
    };

    if (pax_json_reader_record(reader, arena, 0, messages, 6) == 0)
        return 0;

    self->player_number = messages[0].value_unsigned;
    self->player_code   = messages[1].value_unsigned;
    self->piece_shape   = pax_string8_peek_or_none(messages[2].value_string, 0);
    self->piece_color   = messages[3].value_unsigned;
    self->board_width   = messages[4].value_unsigned;
    self->board_height  = messages[5].value_unsigned;

    return 1;
}

paxb8
c4_game_message_json_read_player_data(C4_Game_Message_Player_Data* self, Pax_JSON_Reader* reader, Pax_Arena* arena)
{
    Pax_JSON_Message messages[] = {
        pax_json_message_pair(pax_str8("player_code"), pax_json_message_unsigned(0)),
        pax_json_message_pair(pax_str8("piece_shape"), pax_json_message_string(pax_str8(""))),
        pax_json_message_pair(pax_str8("piece_color"), pax_json_message_unsigned(0)),
    };

    if (pax_json_reader_record(reader, arena, 0, messages, 3) == 0)
        return 0;

    self->player_code = messages[0].value_unsigned;
    self->piece_shape = pax_string8_peek_or_none(messages[1].value_string, 0);
    self->piece_color = messages[2].value_unsigned;

    return 1;
}

paxb8
c4_game_message_json_read_player_turn(C4_Game_Message_Player_Turn* self, Pax_JSON_Reader* reader, Pax_Arena* arena)
{
    Pax_JSON_Message messages[] = {
        pax_json_message_pair(pax_str8("player_code"),
            pax_json_message_unsigned(0)),
    };

    if (pax_json_reader_record(reader, arena, 0, messages, 1) == 0)
        return 0;

    self->player_code = messages[0].value_unsigned;

    return 1;
}

paxb8
c4_game_message_json_read_player_choice(C4_Game_Message_Player_Choice* self, Pax_JSON_Reader* reader, Pax_Arena* arena)
{
    Pax_JSON_Message messages[] = {
        pax_json_message_pair(pax_str8("player_code"),  pax_json_message_unsigned(0)),
        pax_json_message_pair(pax_str8("board_column"), pax_json_message_unsigned(0)),
    };

    if (pax_json_reader_record(reader, arena, 0, messages, 2) == 0)
        return 0;

    self->player_code  = messages[0].value_unsigned;
    self->board_column = messages[1].value_unsigned;

    return 1;
}

paxb8
c4_game_message_json_read_player_skip(C4_Game_Message_Player_Skip* self, Pax_JSON_Reader* reader, Pax_Arena* arena)
{
    Pax_JSON_Message messages[] = {
        pax_json_message_pair(pax_str8("player_code"), pax_json_message_unsigned(0)),
    };

    if (pax_json_reader_record(reader, arena, 0, messages, 1) == 0)
        return 0;

    self->player_code = messages[0].value_unsigned;

    return 1;
}

paxb8
c4_game_message_json_read_start(C4_Game_Message_Start* self, Pax_JSON_Reader* reader, Pax_Arena* arena)
{
    Pax_JSON_Message messages[] = {
        pax_json_message_pair(pax_str8("player_number"),
            pax_json_message_unsigned(0)),
    };

    if (pax_json_reader_record(reader, arena, 0, messages, 1) == 0)
        return 0;

    self->player_number = messages[0].value_unsigned;

    return 1;
}

paxb8
c4_game_message_json_read_stop(C4_Game_Message_Stop* self, Pax_JSON_Reader* reader, Pax_Arena* arena)
{
    Pax_JSON_Message messages[] = {
        pax_json_message_pair(pax_str8("player_code"),
            pax_json_message_unsigned(0)),
    };

    if (pax_json_reader_record(reader, arena, 0, messages, 1) == 0)
        return 0;

    self->player_code = messages[0].value_unsigned;

    return 1;
}

#endif // C4_ENGINE_GAME_MESSAGE_C
