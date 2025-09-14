#ifndef C4_MESSAGE_MESSAGE_C
#define C4_MESSAGE_MESSAGE_C

#include "message.h"

C4Msg
c4MsgPlayerJoin(pxb8 player_is_automatic)
{
    return (C4Msg) {
        .type = C4_MESSAGE_PLAYER_JOIN,

        .player_join = {
            .player_is_automatic = player_is_automatic,
        },
    };
}

C4Msg
c4MsgPlayerAccept(pxiword player_number, C4GamePlayer player, pxiword board_width, pxiword board_height)
{
    return (C4Msg) {
        .type = C4_MESSAGE_PLAYER_ACCEPT,

        .player_accept = {
            .player_number = player_number,

            .player_code  = player.code,
            .player_color = player.color,
            .player_text  = player.text,

            .board_width  = board_width,
            .board_height = board_height,
        },
    };
}

C4Msg
c4MsgPlayerData(C4GamePlayer player)
{
    return (C4Msg) {
        .type = C4_MESSAGE_PLAYER_DATA,

        .player_data = {
            .player_code  = player.code,
            .player_color = player.color,
            .player_text  = player.text,
        },
    };
}

C4Msg
c4MsgPlayerTurn(pxuword player_code)
{
    return (C4Msg) {
        .type = C4_MESSAGE_PLAYER_TURN,

        .player_turn = {
            .player_code = player_code,
        },
    };
}

C4Msg
c4MsgPlayerChoice(pxuword player_code, pxiword board_column)
{
    return (C4Msg) {
        .type = C4_MESSAGE_PLAYER_CHOICE,

        .player_choice = {
            .player_code  = player_code,
            .board_column = board_column,
        },
    };
}

C4Msg
c4MsgPlayerSkip(pxuword player_code)
{
    return (C4Msg) {
        .type = C4_MESSAGE_PLAYER_SKIP,

        .player_turn = {
            .player_code = player_code,
        },
    };
}

C4Msg
c4MsgGameStart()
{
    return (C4Msg) {
        .type = C4_MESSAGE_GAME_START,
    };
}

C4Msg
c4MsgGameStop(pxuword player_code)
{
    return (C4Msg) {
        .type = C4_MESSAGE_GAME_STOP,

        .game_stop = {
            .player_code = player_code,
        },
    };
}

pxb8
c4JsonWriteMsg(C4Msg* self, PxJsonWriter* writer, PxArena* arena)
{
    pxJsonWriteMessage(writer, arena, pxJsonMsgObjectOpen());

    switch (self->type) {
        case C4_MESSAGE_PLAYER_JOIN: {
            pxJsonWriteMessage(writer, arena,
                pxJsonMsgName(pxs8("player_join")));

            c4JsonWriteMsgPlayerJoin(
                &self->player_join, writer, arena);
        } break;

        case C4_MESSAGE_PLAYER_ACCEPT: {
            pxJsonWriteMessage(writer, arena,
                pxJsonMsgName(pxs8("player_accept")));

            c4JsonWriteMsgPlayerAccept(
                &self->player_accept, writer, arena);
        } break;

        case C4_MESSAGE_PLAYER_DATA: {
            pxJsonWriteMessage(writer, arena,
                pxJsonMsgName(pxs8("player_data")));

            c4JsonWriteMsgPlayerData(
                &self->player_data, writer, arena);
        } break;

        case C4_MESSAGE_PLAYER_TURN: {
            pxJsonWriteMessage(writer, arena,
                pxJsonMsgName(pxs8("player_turn")));

            c4JsonWriteMsgPlayerTurn(
                &self->player_turn, writer, arena);
        } break;

        case C4_MESSAGE_PLAYER_CHOICE: {
            pxJsonWriteMessage(writer, arena,
                pxJsonMsgName(pxs8("player_choice")));

            c4JsonWriteMsgPlayerChoice(
                &self->player_choice, writer, arena);
        } break;

        case C4_MESSAGE_PLAYER_SKIP: {
            pxJsonWriteMessage(writer, arena,
                pxJsonMsgName(pxs8("player_skip")));

            c4JsonWriteMsgPlayerSkip(
                &self->player_skip, writer, arena);
        } break;

        case C4_MESSAGE_GAME_START: {
            pxJsonWriteMessage(writer, arena,
                pxJsonMsgName(pxs8("game_start")));

            c4JsonWriteMsgGameStart(0, writer, arena);
        } break;

        case C4_MESSAGE_GAME_STOP: {
            pxJsonWriteMessage(writer, arena,
                pxJsonMsgName(pxs8("game_stop")));

            c4JsonWriteMsgGameStop(
                &self->game_stop, writer, arena);
        } break;

        default: break;
    }

    pxJsonWriteMessage(writer, arena, pxJsonMsgObjectClose());

    return 1;
}

pxb8
c4JsonWriteMsgPlayerJoin(C4MsgPlayerJoin* self, PxJsonWriter* writer, PxArena* arena)
{
    pxJsonWriteMessage(writer, arena, pxJsonMsgObjectOpen());

    pxJsonWriteMessage(writer, arena,
        pxJsonMsgBoolean(self->player_is_automatic, pxs8("player_is_automatic")));

    pxJsonWriteMessage(writer, arena, pxJsonMsgObjectClose());

    return 1;
}

pxb8
c4JsonWriteMsgPlayerAccept(C4MsgPlayerAccept* self, PxJsonWriter* writer, PxArena* arena)
{
    pxJsonWriteMessage(writer, arena, pxJsonMsgObjectOpen());

    pxJsonWriteMessage(writer, arena,
        pxJsonMsgUnsigned(self->player_number, pxs8("player_number")));

    pxJsonWriteMessage(writer, arena,
        pxJsonMsgUnsigned(self->player_code, pxs8("player_code")));

    pxJsonWriteMessage(writer, arena, pxJsonMsgName(pxs8("player_color")));

    c4JsonWriteColor(&self->player_color, writer, arena);

    pxJsonWriteMessage(writer, arena,
        pxJsonMsgString(self->player_text, pxs8("player_text")));

    pxJsonWriteMessage(writer, arena,
        pxJsonMsgInteger(self->board_width, pxs8("board_width")));

    pxJsonWriteMessage(writer, arena,
        pxJsonMsgInteger(self->board_height, pxs8("board_height")));

    pxJsonWriteMessage(writer, arena, pxJsonMsgObjectClose());

    return 1;
}

pxb8
c4JsonWriteMsgPlayerData(C4MsgPlayerData* self, PxJsonWriter* writer, PxArena* arena)
{
    pxJsonWriteMessage(writer, arena, pxJsonMsgObjectOpen());

    pxJsonWriteMessage(writer, arena,
        pxJsonMsgUnsigned(self->player_code, pxs8("player_code")));

    pxJsonWriteMessage(writer, arena, pxJsonMsgName(pxs8("player_color")));

    c4JsonWriteColor(&self->player_color, writer, arena);

    pxJsonWriteMessage(writer, arena,
        pxJsonMsgString(self->player_text, pxs8("player_text")));

    pxJsonWriteMessage(writer, arena, pxJsonMsgObjectClose());

    return 1;
}

pxb8
c4JsonWriteMsgPlayerTurn(C4MsgPlayerTurn* self, PxJsonWriter* writer, PxArena* arena)
{
    pxJsonWriteMessage(writer, arena, pxJsonMsgObjectOpen());

    pxJsonWriteMessage(writer, arena,
        pxJsonMsgUnsigned(self->player_code, pxs8("player_code")));

    pxJsonWriteMessage(writer, arena, pxJsonMsgObjectClose());

    return 1;
}

pxb8
c4JsonWriteMsgPlayerChoice(C4MsgPlayerChoice* self, PxJsonWriter* writer, PxArena* arena)
{
    pxJsonWriteMessage(writer, arena, pxJsonMsgObjectOpen());

    pxJsonWriteMessage(writer, arena,
        pxJsonMsgUnsigned(self->player_code, pxs8("player_code")));

    pxJsonWriteMessage(writer, arena,
        pxJsonMsgInteger(self->board_column, pxs8("board_column")));

    pxJsonWriteMessage(writer, arena, pxJsonMsgObjectClose());

    return 1;
}

pxb8
c4JsonWriteMsgPlayerSkip(C4MsgPlayerSkip* self, PxJsonWriter* writer, PxArena* arena)
{
    pxJsonWriteMessage(writer, arena, pxJsonMsgObjectOpen());

    pxJsonWriteMessage(writer, arena,
        pxJsonMsgUnsigned(self->player_code, pxs8("player_code")));

    pxJsonWriteMessage(writer, arena, pxJsonMsgObjectClose());

    return 1;
}

pxb8
c4JsonWriteMsgGameStart(void* self, PxJsonWriter* writer, PxArena* arena)
{
    pxJsonWriteMessage(writer, arena, pxJsonMsgObjectOpen());
    pxJsonWriteMessage(writer, arena, pxJsonMsgObjectClose());

    return 1;
}

pxb8
c4JsonWriteMsgGameStop(C4MsgGameStop* self, PxJsonWriter* writer, PxArena* arena)
{
    pxJsonWriteMessage(writer, arena, pxJsonMsgObjectOpen());

    pxJsonWriteMessage(writer, arena,
        pxJsonMsgUnsigned(self->player_code, pxs8("player_code")));

    pxJsonWriteMessage(writer, arena, pxJsonMsgObjectClose());

    return 1;
}

pxb8
c4JsonReadMsg(C4Msg* self, PxJsonReader* reader, PxArena* arena)
{
    PxJsonMsg message = pxJsonReadMessage(reader, arena);

    if (message.type != PX_JSON_MSG_OBJECT_OPEN) return 0;

    while (message.type != PX_JSON_MSG_OBJECT_CLOSE) {
        message = pxJsonReadMessage(reader, arena);

        if (message.type == PX_JSON_MSG_COUNT) return 0;

        switch (message.type) {
            case PX_JSON_MSG_NAME: {
                self->type = C4_MESSAGE_NONE;

                if (pxString8IsEqual(message.name, pxs8("player_join")) != 0) {
                    self->type = C4_MESSAGE_PLAYER_JOIN;

                    c4JsonReadMsgPlayerJoin(
                        &self->player_join, reader, arena);
                }

                if (pxString8IsEqual(message.name, pxs8("player_accept")) != 0) {
                    self->type = C4_MESSAGE_PLAYER_ACCEPT;

                    c4JsonReadMsgPlayerAccept(
                        &self->player_accept, reader, arena);
                }

                if (pxString8IsEqual(message.name, pxs8("player_data")) != 0) {
                    self->type = C4_MESSAGE_PLAYER_DATA;

                    c4JsonReadMsgPlayerData(
                        &self->player_data, reader, arena);
                }

                if (pxString8IsEqual(message.name, pxs8("player_turn")) != 0) {
                    self->type = C4_MESSAGE_PLAYER_TURN;

                    c4JsonReadMsgPlayerTurn(
                        &self->player_turn, reader, arena);
                }

                if (pxString8IsEqual(message.name, pxs8("player_choice")) != 0) {
                    self->type = C4_MESSAGE_PLAYER_CHOICE;

                    c4JsonReadMsgPlayerChoice(
                        &self->player_choice, reader, arena);
                }

                if (pxString8IsEqual(message.name, pxs8("player_skip")) != 0) {
                    self->type = C4_MESSAGE_PLAYER_SKIP;

                    c4JsonReadMsgPlayerSkip(
                        &self->player_skip, reader, arena);
                }

                if (pxString8IsEqual(message.name, pxs8("game_start")) != 0) {
                    self->type = C4_MESSAGE_GAME_START;

                    c4JsonReadMsgGameStart(
                        0, reader, arena);
                }

                if (pxString8IsEqual(message.name, pxs8("game_stop")) != 0) {
                    self->type = C4_MESSAGE_GAME_STOP;

                    c4JsonReadMsgGameStop(
                        &self->game_stop, reader, arena);
                }
            } break;

            default: break;
        }
    }

    return 1;
}

pxb8
c4JsonReadMsgPlayerJoin(C4MsgPlayerJoin* self, PxJsonReader* reader, PxArena* arena)
{
    PxJsonMsg message = pxJsonReadMessage(reader, arena);

    if (message.type != PX_JSON_MSG_OBJECT_OPEN) return 0;

    while (message.type != PX_JSON_MSG_OBJECT_CLOSE) {
        message = pxJsonReadMessage(reader, arena);

        if (message.type == PX_JSON_MSG_COUNT) return 0;

        switch (message.type) {
            case PX_JSON_MSG_BOOLEAN: {
                if (pxString8IsEqual(message.name, pxs8("player_is_automatic")) != 0)
                    self->player_is_automatic = message.boolean_word;
            } break;

            default: break;
        }
    }

    return 1;
}

pxb8
c4JsonReadMsgPlayerAccept(C4MsgPlayerAccept* self, PxJsonReader* reader, PxArena* arena)
{
    PxJsonMsg message = pxJsonReadMessage(reader, arena);

    if (message.type != PX_JSON_MSG_OBJECT_OPEN) return 0;

    while (message.type != PX_JSON_MSG_OBJECT_CLOSE) {
        message = pxJsonReadMessage(reader, arena);

        if (message.type == PX_JSON_MSG_COUNT) return 0;

        switch (message.type) {
            case PX_JSON_MSG_NAME: {
                if (pxString8IsEqual(message.name, pxs8("player_color")) != 0)
                    c4JsonReadColor(&self->player_color, reader, arena);
            } break;

            case PX_JSON_MSG_UNSIGNED: {
                if (pxString8IsEqual(message.name, pxs8("player_number")) != 0)
                    self->player_number = message.unsigned_word;

                if (pxString8IsEqual(message.name, pxs8("player_code")) != 0)
                    self->player_code = message.unsigned_word;

                if (pxString8IsEqual(message.name, pxs8("board_width")) != 0)
                    self->board_width = message.unsigned_word;

                if (pxString8IsEqual(message.name, pxs8("board_height")) != 0)
                    self->board_height = message.unsigned_word;
            } break;

            case PX_JSON_MSG_STRING: {
                if (pxString8IsEqual(message.name, pxs8("player_text")) != 0)
                    self->player_text = message.string_8;
            } break;

            case PX_JSON_MSG_INTEGER: {
                if (pxString8IsEqual(message.name, pxs8("board_width")) != 0)
                    self->board_width = message.integer_word;

                if (pxString8IsEqual(message.name, pxs8("board_height")) != 0)
                    self->board_height = message.integer_word;
            } break;

            default: break;
        }
    }

    return 1;
}

pxb8
c4JsonReadMsgPlayerData(C4MsgPlayerData* self, PxJsonReader* reader, PxArena* arena)
{
    PxJsonMsg message = pxJsonReadMessage(reader, arena);

    if (message.type != PX_JSON_MSG_OBJECT_OPEN) return 0;

    while (message.type != PX_JSON_MSG_OBJECT_CLOSE) {
        message = pxJsonReadMessage(reader, arena);

        if (message.type == PX_JSON_MSG_COUNT) return 0;

        switch (message.type) {
            case PX_JSON_MSG_NAME: {
                if (pxString8IsEqual(message.name, pxs8("player_color")) != 0)
                    c4JsonReadColor(&self->player_color, reader, arena);
            } break;

            case PX_JSON_MSG_UNSIGNED: {
                if (pxString8IsEqual(message.name, pxs8("player_code")) != 0)
                    self->player_code = message.unsigned_word;
            } break;

            case PX_JSON_MSG_STRING: {
                if (pxString8IsEqual(message.name, pxs8("player_text")) != 0)
                    self->player_text = message.string_8;
            } break;

            default: break;
        }
    }

    return 1;
}

pxb8
c4JsonReadMsgPlayerTurn(C4MsgPlayerTurn* self, PxJsonReader* reader, PxArena* arena)
{
    PxJsonMsg message = pxJsonReadMessage(reader, arena);

    if (message.type != PX_JSON_MSG_OBJECT_OPEN) return 0;

    while (message.type != PX_JSON_MSG_OBJECT_CLOSE) {
        message = pxJsonReadMessage(reader, arena);

        if (message.type == PX_JSON_MSG_COUNT) return 0;

        switch (message.type) {
            case PX_JSON_MSG_UNSIGNED: {
                if (pxString8IsEqual(message.name, pxs8("player_code")) != 0)
                    self->player_code = message.unsigned_word;
            } break;

            default: break;
        }
    }

    return 1;
}

pxb8
c4JsonReadMsgPlayerChoice(C4MsgPlayerChoice* self, PxJsonReader* reader, PxArena* arena)
{
    PxJsonMsg message = pxJsonReadMessage(reader, arena);

    if (message.type != PX_JSON_MSG_OBJECT_OPEN) return 0;

    while (message.type != PX_JSON_MSG_OBJECT_CLOSE) {
        message = pxJsonReadMessage(reader, arena);

        if (message.type == PX_JSON_MSG_COUNT) return 0;

        switch (message.type) {
            case PX_JSON_MSG_UNSIGNED: {
                if (pxString8IsEqual(message.name, pxs8("player_code")) != 0)
                    self->player_code = message.unsigned_word;

                if (pxString8IsEqual(message.name, pxs8("board_column")) != 0)
                    self->board_column = message.unsigned_word;
            } break;

            case PX_JSON_MSG_INTEGER: {
                if (pxString8IsEqual(message.name, pxs8("board_column")) != 0)
                    self->board_column = message.integer_word;
            } break;

            default: break;
        }
    }

    return 1;
}

pxb8
c4JsonReadMsgPlayerSkip(C4MsgPlayerSkip* self, PxJsonReader* reader, PxArena* arena)
{
    PxJsonMsg message = pxJsonReadMessage(reader, arena);

    if (message.type != PX_JSON_MSG_OBJECT_OPEN) return 0;

    while (message.type != PX_JSON_MSG_OBJECT_CLOSE) {
        message = pxJsonReadMessage(reader, arena);

        if (message.type == PX_JSON_MSG_COUNT) return 0;

        switch (message.type) {
            case PX_JSON_MSG_UNSIGNED: {
                if (pxString8IsEqual(message.name, pxs8("player_code")) != 0)
                    self->player_code = message.unsigned_word;
            } break;

            default: break;
        }
    }

    return 1;
}

pxb8
c4JsonReadMsgGameStart(void* self, PxJsonReader* reader, PxArena* arena)
{
    PxJsonMsg message = pxJsonReadMessage(reader, arena);

    if (message.type != PX_JSON_MSG_OBJECT_OPEN) return 0;

    while (message.type != PX_JSON_MSG_OBJECT_CLOSE)
        message = pxJsonReadMessage(reader, arena);

    return 1;
}

pxb8
c4JsonReadMsgGameStop(C4MsgGameStop* self, PxJsonReader* reader, PxArena* arena)
{
    PxJsonMsg message = pxJsonReadMessage(reader, arena);

    if (message.type != PX_JSON_MSG_OBJECT_OPEN) return 0;

    while (message.type != PX_JSON_MSG_OBJECT_CLOSE) {
        message = pxJsonReadMessage(reader, arena);

        if (message.type == PX_JSON_MSG_COUNT) return 0;

        switch (message.type) {
            case PX_JSON_MSG_UNSIGNED: {
                if (pxString8IsEqual(message.name, pxs8("player_code")) != 0)
                    self->player_code = message.unsigned_word;
            } break;

            default: break;
        }
    }

    return 1;
}

pxiword
c4FormatProcMsg(C4Msg* self, PxBuilder* builder)
{
    switch (self->type) {
        case C4_MESSAGE_PLAYER_JOIN:
            return c4FormatProcMsgPlayerJoin(&self->player_join, builder);

        case C4_MESSAGE_PLAYER_ACCEPT:
            return c4FormatProcMsgPlayerAccept(&self->player_accept, builder);

        case C4_MESSAGE_PLAYER_DATA:
            return c4FormatProcMsgPlayerData(&self->player_data, builder);

        case C4_MESSAGE_PLAYER_TURN:
            return c4FormatProcMsgPlayerTurn(&self->player_turn, builder);

        case C4_MESSAGE_PLAYER_CHOICE:
            return c4FormatProcMsgPlayerChoice(&self->player_choice, builder);

        case C4_MESSAGE_PLAYER_SKIP:
            return c4FormatProcMsgPlayerSkip(&self->player_skip, builder);

        case C4_MESSAGE_GAME_START:
            return c4FormatProcMsgGameStart(0, builder);

        case C4_MESSAGE_GAME_STOP:
            return c4FormatProcMsgGameStop(&self->game_stop, builder);

        default: break;
    }

    return 0;
}

pxiword
c4FormatProcMsgPlayerJoin(C4MsgPlayerJoin* self, PxBuilder* builder)
{
    pxu8 format[] = "PlayerJoin = {.player_is_automatic = ${0}}";

    PxFormatCmd list[] = {
        pxFormatCmdBoolean8(self->player_is_automatic),
    };

    return pxBuilderFormat(builder, pxs8(format),
        0, pxSizeArray(PxFormatCmd, list), list);
}

pxiword
c4FormatProcMsgPlayerAccept(C4MsgPlayerAccept* self, PxBuilder* builder)
{
    pxu8 format[] = "PlayerAccept = {\n"
        "    .player_number = ${0}\n"
        "    .player_code   = ${1}\n"
        "    .player_color  = ${2}\n"
        "    .player_text   = '${3}'\n"
        "    .board_width   = ${4}\n"
        "    .board_height  = ${5}\n"
        "}";

    PxFormatCmd list[] = {
        pxFormatCmdInteger(10, PX_FORMAT_OPTION_NONE, self->player_number),
        pxFormatCmdUnsigned(10, PX_FORMAT_OPTION_NONE, self->player_code),
        pxFormatCmdDelegate(&self->player_color, &c4FormatProcColor),
        pxFormatCmdString8(self->player_text),
        pxFormatCmdInteger(10, PX_FORMAT_OPTION_NONE, self->board_width),
        pxFormatCmdInteger(10, PX_FORMAT_OPTION_NONE, self->board_height),
    };

    return pxBuilderFormat(builder, pxs8(format),
        0, pxSizeArray(PxFormatCmd, list), list);
}

pxiword
c4FormatProcMsgPlayerData(C4MsgPlayerData* self, PxBuilder* builder)
{
    pxu8 format[] = "PlayerData = {\n"
        "    .player_code  = ${0}\n"
        "    .player_color = ${1}\n"
        "    .player_text  = '${2}'\n"
        "}";

    PxFormatCmd list[] = {
        pxFormatCmdUnsigned(10, PX_FORMAT_OPTION_NONE, self->player_code),
        pxFormatCmdDelegate(&self->player_color, &c4FormatProcColor),
        pxFormatCmdString8(self->player_text),
    };

    return pxBuilderFormat(builder, pxs8(format),
        0, pxSizeArray(PxFormatCmd, list), list);
}

pxiword
c4FormatProcMsgPlayerTurn(C4MsgPlayerTurn* self, PxBuilder* builder)
{
    pxu8 format[] = "PlayerTurn = {.player_code = ${0}}";

    PxFormatCmd list[] = {
        pxFormatCmdUnsigned(10, PX_FORMAT_OPTION_NONE, self->player_code),
    };

    return pxBuilderFormat(builder, pxs8(format),
        0, pxSizeArray(PxFormatCmd, list), list);
}

pxiword
c4FormatProcMsgPlayerChoice(C4MsgPlayerChoice* self, PxBuilder* builder)
{
    pxu8 format[] = "PlayerChoice = {\n"
        "    .player_code  = ${0}\n"
        "    .board_column = ${1}\n"
        "}";

    PxFormatCmd list[] = {
        pxFormatCmdUnsigned(10, PX_FORMAT_OPTION_NONE, self->player_code),
        pxFormatCmdInteger(10, PX_FORMAT_OPTION_NONE, self->board_column),
    };

    return pxBuilderFormat(builder, pxs8(format),
        0, pxSizeArray(PxFormatCmd, list), list);
}

pxiword
c4FormatProcMsgPlayerSkip(C4MsgPlayerSkip* self, PxBuilder* builder)
{
    pxu8 format[] = "PlayerSkip = {.player_code = ${0}}";

    PxFormatCmd list[] = {
        pxFormatCmdUnsigned(10, PX_FORMAT_OPTION_NONE, self->player_code),
    };

    return pxBuilderFormat(builder, pxs8(format),
        0, pxSizeArray(PxFormatCmd, list), list);
}

pxiword
c4FormatProcMsgGameStart(void* self, PxBuilder* builder)
{
    pxu8 format[] = "GameStart = {}";

    return pxBuilderFormat(builder, pxs8(format),
        0, 0, 0);
}

pxiword
c4FormatProcMsgGameStop(C4MsgGameStop* self, PxBuilder* builder)
{
    pxu8 format[] = "GameStop = {.player_code = ${0}}";

    PxFormatCmd list[] = {
        pxFormatCmdUnsigned(10, PX_FORMAT_OPTION_NONE, self->player_code),
    };

    return pxBuilderFormat(builder, pxs8(format),
        0, pxSizeArray(PxFormatCmd, list), list);
}

#endif // C4_MESSAGE_MESSAGE_C
