#ifndef C4_ENGINE_MESSAGE_C
#define C4_ENGINE_MESSAGE_C

#include "message.h"

C4NetworkMsg
c4NetworkMsgPlayerJoin(pxb8 player_is_automatic)
{
    return (C4NetworkMsg) {
        .type = C4_NETWORK_MSG_PLAYER_JOIN,

        .player_join = {
            .player_is_automatic = player_is_automatic,
        },
    };
}

C4NetworkMsg
c4NetworkMsgPlayerAccept(pxiword player_amount, C4GamePlayer player, pxiword board_width, pxiword board_height)
{
    return (C4NetworkMsg) {
        .type = C4_NETWORK_MSG_PLAYER_ACCEPT,

        .player_accept = {
            .player_amount = player_amount,

            .player_ident = player.ident,
            .player_color = player.color,
            .player_text  = player.text,

            .board_width  = board_width,
            .board_height = board_height,
        },
    };
}

C4NetworkMsg
c4NetworkMsgPlayerData(C4GamePlayer player)
{
    return (C4NetworkMsg) {
        .type = C4_NETWORK_MSG_PLAYER_DATA,

        .player_data = {
            .player_ident = player.ident,
            .player_text  = player.text,
            .player_color = player.color,
        },
    };
}

C4NetworkMsg
c4NetworkMsgPlayerTurn(pxuword player_ident)
{
    return (C4NetworkMsg) {
        .type = C4_NETWORK_MSG_PLAYER_TURN,

        .player_turn = {
            .player_ident = player_ident,
        },
    };
}

C4NetworkMsg
c4NetworkMsgPlayerChoice(pxuword player_ident, pxiword board_column)
{
    return (C4NetworkMsg) {
        .type = C4_NETWORK_MSG_PLAYER_CHOICE,

        .player_choice = {
            .player_ident = player_ident,
            .board_column = board_column,
        },
    };
}

C4NetworkMsg
c4NetworkMsgPlayerSkip(pxuword player_ident)
{
    return (C4NetworkMsg) {
        .type = C4_NETWORK_MSG_PLAYER_SKIP,

        .player_turn = {
            .player_ident = player_ident,
        },
    };
}

C4NetworkMsg
c4NetworkMsgGameStart()
{
    return (C4NetworkMsg) {
        .type = C4_NETWORK_MSG_GAME_START,
    };
}

C4NetworkMsg
c4NetworkMsgGameStop(pxuword player_ident)
{
    return (C4NetworkMsg) {
        .type = C4_NETWORK_MSG_GAME_STOP,

        .game_stop = {
            .player_ident = player_ident,
        },
    };
}

pxb8
c4JsonWriteNetworkMsg(C4NetworkMsg* self, PxJsonWriter* writer, PxArena* arena)
{
    PxJsonMsg message = {0};

    pxJsonWriterObjectOpen(writer, arena);

    switch (self->type) {
        case C4_NETWORK_MSG_PLAYER_JOIN: {
            message = pxJsonMsgPair(pxs8("player_join"),
                pxJsonMsgDelegate(&self->player_join, &c4JsonWriteNetworkMsgPlayerJoin));
        } break;

        case C4_NETWORK_MSG_PLAYER_ACCEPT: {
            message = pxJsonMsgPair(pxs8("player_accept"),
                pxJsonMsgDelegate(&self->player_accept, &c4JsonWriteNetworkMsgPlayerAccept));
        } break;

        case C4_NETWORK_MSG_PLAYER_DATA: {
            message = pxJsonMsgPair(pxs8("player_data"),
                pxJsonMsgDelegate(&self->player_data, &c4JsonWriteNetworkMsgPlayerData));
        } break;

        case C4_NETWORK_MSG_PLAYER_TURN: {
            message = pxJsonMsgPair(pxs8("player_turn"),
                pxJsonMsgDelegate(&self->player_turn, &c4JsonWriteNetworkMsgPlayerTurn));
        } break;

        case C4_NETWORK_MSG_PLAYER_CHOICE: {
            message = pxJsonMsgPair(pxs8("player_choice"),
                pxJsonMsgDelegate(&self->player_choice, &c4JsonWriteNetworkMsgPlayerChoice));
        } break;

        case C4_NETWORK_MSG_PLAYER_SKIP: {
            message = pxJsonMsgPair(pxs8("player_skip"),
                pxJsonMsgDelegate(&self->player_skip, &c4JsonWriteNetworkMsgPlayerSkip));
        } break;

        case C4_NETWORK_MSG_GAME_START: {
            message = pxJsonMsgPair(pxs8("game_start"),
                pxJsonMsgDelegate(&self->game_start, &c4JsonWriteNetworkMsgGameStart));
        } break;

        case C4_NETWORK_MSG_GAME_STOP: {
            message = pxJsonMsgPair(pxs8("game_stop"),
                pxJsonMsgDelegate(&self->game_stop, &c4JsonWriteNetworkMsgGameStop));
        } break;

        default: break;
    }

    pxJsonWriterMsg(writer, arena, message);

    pxJsonWriterObjectClose(writer, arena);

    return 1;
}

pxb8
c4JsonWriteNetworkMsgPlayerJoin(C4NetworkMsgPlayerJoin* self, PxJsonWriter* writer, PxArena* arena)
{
    pxJsonWriterObjectOpen(writer, arena);

    pxJsonWriterList(writer, arena, (PxJsonMsg[]) {
        pxJsonMsgPair(pxs8("player_is_automatic"), pxJsonMsgBoolean(self->player_is_automatic)),
    }, 1);

    pxJsonWriterObjectClose(writer, arena);

    return 1;
}

pxb8
c4JsonWriteNetworkMsgPlayerAccept(C4NetworkMsgPlayerAccept* self, PxJsonWriter* writer, PxArena* arena)
{
    pxJsonWriterObjectOpen(writer, arena);

    pxJsonWriterList(writer, arena, (PxJsonMsg[]) {
        pxJsonMsgPair(pxs8("player_amount"), pxJsonMsgUnsigned(self->player_amount)),
        pxJsonMsgPair(pxs8("player_ident"),  pxJsonMsgUnsigned(self->player_ident)),
        pxJsonMsgPair(pxs8("player_text"),   pxJsonMsgString(self->player_text)),
        pxJsonMsgPair(pxs8("player_color"),  pxJsonMsgDelegate(&self->player_color, &c4JsonWriteConsoleColor)),
        pxJsonMsgPair(pxs8("board_width"),   pxJsonMsgInteger(self->board_width)),
        pxJsonMsgPair(pxs8("board_height"),  pxJsonMsgInteger(self->board_height)),
    }, 6);

    pxJsonWriterObjectClose(writer, arena);

    return 1;
}

pxb8
c4JsonWriteNetworkMsgPlayerData(C4NetworkMsgPlayerData* self, PxJsonWriter* writer, PxArena* arena)
{
    pxJsonWriterObjectOpen(writer, arena);

    pxJsonWriterList(writer, arena, (PxJsonMsg[]) {
        pxJsonMsgPair(pxs8("player_ident"), pxJsonMsgUnsigned(self->player_ident)),
        pxJsonMsgPair(pxs8("player_text"),  pxJsonMsgString(self->player_text)),
        pxJsonMsgPair(pxs8("player_color"), pxJsonMsgDelegate(&self->player_color, &c4JsonWriteConsoleColor)),
    }, 3);

    pxJsonWriterObjectClose(writer, arena);

    return 1;
}

pxb8
c4JsonWriteNetworkMsgPlayerTurn(C4NetworkMsgPlayerTurn* self, PxJsonWriter* writer, PxArena* arena)
{
    pxJsonWriterObjectOpen(writer, arena);

    pxJsonWriterList(writer, arena, (PxJsonMsg[]) {
        pxJsonMsgPair(pxs8("player_ident"), pxJsonMsgUnsigned(self->player_ident)),
    }, 1);

    pxJsonWriterObjectClose(writer, arena);

    return 1;
}

pxb8
c4JsonWriteNetworkMsgPlayerChoice(C4NetworkMsgPlayerChoice* self, PxJsonWriter* writer, PxArena* arena)
{
    pxJsonWriterObjectOpen(writer, arena);

    pxJsonWriterList(writer, arena, (PxJsonMsg[]) {
        pxJsonMsgPair(pxs8("player_ident"), pxJsonMsgUnsigned(self->player_ident)),
        pxJsonMsgPair(pxs8("board_column"), pxJsonMsgUnsigned(self->board_column)),
    }, 2);

    pxJsonWriterObjectClose(writer, arena);

    return 1;
}

pxb8
c4JsonWriteNetworkMsgPlayerSkip(C4NetworkMsgPlayerSkip* self, PxJsonWriter* writer, PxArena* arena)
{
    pxJsonWriterObjectOpen(writer, arena);

    pxJsonWriterList(writer, arena, (PxJsonMsg[]) {
        pxJsonMsgPair(pxs8("player_ident"), pxJsonMsgUnsigned(self->player_ident)),
    }, 1);

    pxJsonWriterObjectClose(writer, arena);

    return 1;
}

pxb8
c4JsonWriteNetworkMsgGameStart(C4NetworkMsgGameStart* self, PxJsonWriter* writer, PxArena* arena)
{
    pxJsonWriterObjectOpen(writer, arena);
    pxJsonWriterObjectClose(writer, arena);

    return 1;
}

pxb8
c4JsonWriteNetworkMsgGameStop(C4NetworkMsgGameStop* self, PxJsonWriter* writer, PxArena* arena)
{
    pxJsonWriterObjectOpen(writer, arena);

    pxJsonWriterList(writer, arena, (PxJsonMsg[]) {
        pxJsonMsgPair(pxs8("player_ident"), pxJsonMsgUnsigned(self->player_ident)),
    }, 1);

    pxJsonWriterObjectClose(writer, arena);

    return 1;
}

pxb8
c4JsonReadNetworkMsg(C4NetworkMsg* self, PxJsonReader* reader, PxArena* arena)
{
    PxJsonMsg message = {0};

    if (pxJsonReaderObjectOpen(reader, arena, &message) == 0)
        return 0;

    while (pxJsonReaderObjectClose(reader, arena, &message) == 0) {
        switch (message.type) {
            case PX_JSON_MSG_NAME: {
                self->type = C4_NETWORK_MSG_NONE;

                if (pxString8IsEqual(message.name, pxs8("player_join")) != 0) {
                    self->type = C4_NETWORK_MSG_PLAYER_JOIN;

                    c4JsonReadNetworkMsgPlayerJoin(
                        &self->player_join, reader, arena);
                }

                if (pxString8IsEqual(message.name, pxs8("player_accept")) != 0) {
                    self->type = C4_NETWORK_MSG_PLAYER_ACCEPT;

                    c4JsonReadNetworkMsgPlayerAccept(
                        &self->player_accept, reader, arena);
                }

                if (pxString8IsEqual(message.name, pxs8("player_data")) != 0) {
                    self->type = C4_NETWORK_MSG_PLAYER_DATA;

                    c4JsonReadNetworkMsgPlayerData(
                        &self->player_data, reader, arena);
                }

                if (pxString8IsEqual(message.name, pxs8("player_turn")) != 0) {
                    self->type = C4_NETWORK_MSG_PLAYER_TURN;

                    c4JsonReadNetworkMsgPlayerTurn(
                        &self->player_turn, reader, arena);
                }

                if (pxString8IsEqual(message.name, pxs8("player_choice")) != 0) {
                    self->type = C4_NETWORK_MSG_PLAYER_CHOICE;

                    c4JsonReadNetworkMsgPlayerChoice(
                        &self->player_choice, reader, arena);
                }

                if (pxString8IsEqual(message.name, pxs8("player_skip")) != 0) {
                    self->type = C4_NETWORK_MSG_PLAYER_SKIP;

                    c4JsonReadNetworkMsgPlayerSkip(
                        &self->player_skip, reader, arena);
                }

                if (pxString8IsEqual(message.name, pxs8("game_start")) != 0) {
                    self->type = C4_NETWORK_MSG_GAME_START;

                    c4JsonReadNetworkMsgGameStart(
                        0, reader, arena);
                }

                if (pxString8IsEqual(message.name, pxs8("game_stop")) != 0) {
                    self->type = C4_NETWORK_MSG_GAME_STOP;

                    c4JsonReadNetworkMsgGameStop(
                        &self->game_stop, reader, arena);
                }
            } break;

            default: break;
        }
    }

    return 1;
}

pxb8
c4JsonReadNetworkMsgPlayerJoin(C4NetworkMsgPlayerJoin* self, PxJsonReader* reader, PxArena* arena)
{
    PxJsonMsg message = {0};

    if (pxJsonReaderObjectOpen(reader, arena, &message) == 0)
        return 0;

    while (pxJsonReaderObjectClose(reader, arena, &message) == 0) {
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
c4JsonReadNetworkMsgPlayerAccept(C4NetworkMsgPlayerAccept* self, PxJsonReader* reader, PxArena* arena)
{
    PxJsonMsg message = {0};

    if (pxJsonReaderObjectOpen(reader, arena, &message) == 0)
        return 0;

    while (pxJsonReaderObjectClose(reader, arena, &message) == 0) {
        switch (message.type) {
            case PX_JSON_MSG_NAME: {
                if (pxString8IsEqual(message.name, pxs8("player_color")) != 0)
                    c4JsonReadConsoleColor(&self->player_color, reader, arena);
            } break;

            case PX_JSON_MSG_UNSIGNED: {
                if (pxString8IsEqual(message.name, pxs8("player_amount")) != 0)
                    self->player_amount = message.unsigned_word;

                if (pxString8IsEqual(message.name, pxs8("player_ident")) != 0)
                    self->player_ident = message.unsigned_word;

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
c4JsonReadNetworkMsgPlayerData(C4NetworkMsgPlayerData* self, PxJsonReader* reader, PxArena* arena)
{
    PxJsonMsg message = {0};

    if (pxJsonReaderObjectOpen(reader, arena, &message) == 0)
        return 0;

    while (pxJsonReaderObjectClose(reader, arena, &message) == 0) {
        switch (message.type) {
            case PX_JSON_MSG_NAME: {
                if (pxString8IsEqual(message.name, pxs8("player_color")) != 0)
                    c4JsonReadConsoleColor(&self->player_color, reader, arena);
            } break;

            case PX_JSON_MSG_UNSIGNED: {
                if (pxString8IsEqual(message.name, pxs8("player_ident")) != 0)
                    self->player_ident = message.unsigned_word;
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
c4JsonReadNetworkMsgPlayerTurn(C4NetworkMsgPlayerTurn* self, PxJsonReader* reader, PxArena* arena)
{
    PxJsonMsg message = {0};

    if (pxJsonReaderObjectOpen(reader, arena, &message) == 0)
        return 0;

    while (pxJsonReaderObjectClose(reader, arena, &message) == 0) {
        switch (message.type) {
            case PX_JSON_MSG_UNSIGNED: {
                if (pxString8IsEqual(message.name, pxs8("player_ident")) != 0)
                    self->player_ident = message.unsigned_word;
            } break;

            default: break;
        }
    }

    return 1;
}

pxb8
c4JsonReadNetworkMsgPlayerChoice(C4NetworkMsgPlayerChoice* self, PxJsonReader* reader, PxArena* arena)
{
    PxJsonMsg message = {0};

    if (pxJsonReaderObjectOpen(reader, arena, &message) == 0)
        return 0;

    while (pxJsonReaderObjectClose(reader, arena, &message) == 0) {
        switch (message.type) {
            case PX_JSON_MSG_UNSIGNED: {
                if (pxString8IsEqual(message.name, pxs8("player_ident")) != 0)
                    self->player_ident = message.unsigned_word;

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
c4JsonReadNetworkMsgPlayerSkip(C4NetworkMsgPlayerSkip* self, PxJsonReader* reader, PxArena* arena)
{
    PxJsonMsg message = {0};

    if (pxJsonReaderObjectOpen(reader, arena, &message) == 0)
        return 0;

    while (pxJsonReaderObjectClose(reader, arena, &message) == 0) {
        switch (message.type) {
            case PX_JSON_MSG_UNSIGNED: {
                if (pxString8IsEqual(message.name, pxs8("player_ident")) != 0)
                    self->player_ident = message.unsigned_word;
            } break;

            default: break;
        }
    }

    return 1;
}

pxb8
c4JsonReadNetworkMsgGameStart(C4NetworkMsgGameStart* self, PxJsonReader* reader, PxArena* arena)
{
    PxJsonMsg message = {0};

    if (pxJsonReaderObjectOpen(reader, arena, &message) == 0)
        return 0;

    while (pxJsonReaderObjectClose(reader, arena, &message) == 0)
        ;

    return 1;
}

pxb8
c4JsonReadNetworkMsgGameStop(C4NetworkMsgGameStop* self, PxJsonReader* reader, PxArena* arena)
{
    PxJsonMsg message = {0};

    if (pxJsonReaderObjectOpen(reader, arena, &message) == 0)
        return 0;

    while (pxJsonReaderObjectClose(reader, arena, &message) == 0) {
        switch (message.type) {
            case PX_JSON_MSG_UNSIGNED: {
                if (pxString8IsEqual(message.name, pxs8("player_ident")) != 0)
                    self->player_ident = message.unsigned_word;
            } break;

            default: break;
        }
    }

    return 1;
}

/*
pxiword
c4FormatProcMsg(C4NetworkMsg* self)
{
    switch (self->type) {
        case C4_NETWORK_MSG_PLAYER_JOIN:
            return c4FormatProcMsgPlayerJoin(&self->player_join, builder);

        case C4_NETWORK_MSG_PLAYER_ACCEPT:
            return c4FormatProcMsgPlayerAccept(&self->player_accept, builder);

        case C4_NETWORK_MSG_PLAYER_DATA:
            return c4FormatProcMsgPlayerData(&self->player_data, builder);

        case C4_NETWORK_MSG_PLAYER_TURN:
            return c4FormatProcMsgPlayerTurn(&self->player_turn, builder);

        case C4_NETWORK_MSG_PLAYER_CHOICE:
            return c4FormatProcMsgPlayerChoice(&self->player_choice, builder);

        case C4_NETWORK_MSG_PLAYER_SKIP:
            return c4FormatProcMsgPlayerSkip(&self->player_skip, builder);

        case C4_NETWORK_MSG_GAME_START:
            return c4FormatProcMsgGameStart(0, builder);

        case C4_NETWORK_MSG_GAME_STOP:
            return c4FormatProcMsgGameStop(&self->game_stop, builder);

        default: break;
    }

    return 0;
}

pxiword
c4FormatProcMsgPlayerJoin(C4NetworkMsgPlayerJoin* self)
{
    pxu8 format[] = "PlayerJoin = {.player_is_automatic = ${0}}";

    PxFormatCmd list[] = {
        pxFormatCmdBoolean(self->player_is_automatic),
    };

    return pxBuilderFormat(builder, pxs8(format),
        0, pxarraylen(PxFormatCmd, list), list);
}

pxiword
c4FormatProcMsgPlayerAccept(C4NetworkMsgPlayerAccept* self)
{
    pxu8 format[] = "PlayerAccept = {\n"
        "    .player_amount = ${0}\n"
        "    .player_ident   = ${1}\n"
        "    .player_color  = ${2}\n"
        "    .player_text   = '${3}'\n"
        "    .board_width   = ${4}\n"
        "    .board_height  = ${5}\n"
        "}";

    PxFormatCmd list[] = {
        pxFormatCmdInteger(10, 0, self->player_amount),
        pxFormatCmdUnsigned(10, 0, self->player_ident),
        pxFormatCmdDelegate(&self->player_color, &c4FormatProcColor),
        pxFormatCmdString8(self->player_text),
        pxFormatCmdInteger(10, 0, self->board_width),
        pxFormatCmdInteger(10, 0, self->board_height),
    };

    return pxBuilderFormat(builder, pxs8(format),
        0, pxarraylen(PxFormatCmd, list), list);
}

pxiword
c4FormatProcMsgPlayerData(C4NetworkMsgPlayerData* self)
{
    pxu8 format[] = "PlayerData = {\n"
        "    .player_ident  = ${0}\n"
        "    .player_color = ${1}\n"
        "    .player_text  = '${2}'\n"
        "}";

    PxFormatCmd list[] = {
        pxFormatCmdUnsigned(10, 0, self->player_ident),
        pxFormatCmdDelegate(&self->player_color, &c4FormatProcColor),
        pxFormatCmdString8(self->player_text),
    };

    return pxBuilderFormat(builder, pxs8(format),
        0, pxarraylen(PxFormatCmd, list), list);
}

pxiword
c4FormatProcMsgPlayerTurn(C4NetworkMsgPlayerTurn* self)
{
    pxu8 format[] = "PlayerTurn = {.player_ident = ${0}}";

    PxFormatCmd list[] = {
        pxFormatCmdUnsigned(10, 0, self->player_ident),
    };

    return pxBuilderFormat(builder, pxs8(format),
        0, pxarraylen(PxFormatCmd, list), list);
}

pxiword
c4FormatProcMsgPlayerChoice(C4NetworkMsgPlayerChoice* self)
{
    pxu8 format[] = "PlayerChoice = {\n"
        "    .player_ident  = ${0}\n"
        "    .board_column = ${1}\n"
        "}";

    PxFormatCmd list[] = {
        pxFormatCmdUnsigned(10, 0, self->player_ident),
        pxFormatCmdInteger(10, 0, self->board_column),
    };

    return pxBuilderFormat(builder, pxs8(format),
        0, pxarraylen(PxFormatCmd, list), list);
}

pxiword
c4FormatProcMsgPlayerSkip(C4NetworkMsgPlayerSkip* self)
{
    pxu8 format[] = "PlayerSkip = {.player_ident = ${0}}";

    PxFormatCmd list[] = {
        pxFormatCmdUnsigned(10, 0, self->player_ident),
    };

    return pxBuilderFormat(builder, pxs8(format),
        0, pxarraylen(PxFormatCmd, list), list);
}

pxiword
c4FormatProcMsgGameStart(void* self)
{
    pxu8 format[] = "GameStart = {}";

    return pxBuilderFormat(builder, pxs8(format),
        0, 0, 0);
}

pxiword
c4FormatProcMsgGameStop(C4NetworkMsgGameStop* self)
{
    pxu8 format[] = "GameStop = {.player_ident = ${0}}";

    PxFormatCmd list[] = {
        pxFormatCmdUnsigned(10, 0, self->player_ident),
    };

    return pxBuilderFormat(builder, pxs8(format),
        0, pxarraylen(PxFormatCmd, list), list);
}
*/

#endif // C4_ENGINE_MESSAGE_C
