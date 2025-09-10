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
c4MsgPlayerAccept(pxiword player_number, pxuword player_code, pxu8 piece_color, pxu8 piece_shape, pxiword board_width, pxiword board_height)
{
    return (C4Msg) {
        .type = C4_MESSAGE_PLAYER_ACCEPT,
        .player_accept = {
            .player_number = player_number,
            .player_code   = player_code,
            .piece_color   = piece_color,
            .piece_shape   = piece_shape,
            .board_width  = board_width,
            .board_height  = board_height,
        },
    };
}

C4Msg
c4MsgPlayerData(pxuword player_code, pxu8 piece_color, pxu8 piece_shape)
{
    return (C4Msg) {
        .type = C4_MESSAGE_PLAYER_DATA,
        .player_data = {
            .player_code = player_code,
            .piece_color = piece_color,
            .piece_shape = piece_shape,
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
    pxJsonWriterNext(writer, arena, pxJsonEventObjectOpen());

    switch (self->type) {
        case C4_MESSAGE_PLAYER_JOIN: {
            pxJsonWriterNext(writer, arena,
                pxJsonEventName(pxs8("player_join")));

            c4JsonWriteMsgPlayerJoin(
                &self->player_join, writer, arena);
        } break;

        case C4_MESSAGE_PLAYER_ACCEPT: {
            pxJsonWriterNext(writer, arena,
                pxJsonEventName(pxs8("player_accept")));

            c4JsonWriteMsgPlayerAccept(
                &self->player_accept, writer, arena);
        } break;

        case C4_MESSAGE_PLAYER_DATA: {
            pxJsonWriterNext(writer, arena,
                pxJsonEventName(pxs8("player_data")));

            c4JsonWriteMsgPlayerData(
                &self->player_data, writer, arena);
        } break;

        case C4_MESSAGE_PLAYER_TURN: {
            pxJsonWriterNext(writer, arena,
                pxJsonEventName(pxs8("player_turn")));

            c4JsonWriteMsgPlayerTurn(
                &self->player_turn, writer, arena);
        } break;

        case C4_MESSAGE_PLAYER_CHOICE: {
            pxJsonWriterNext(writer, arena,
                pxJsonEventName(pxs8("player_choice")));

            c4JsonWriteMsgPlayerChoice(
                &self->player_choice, writer, arena);
        } break;

        case C4_MESSAGE_PLAYER_SKIP: {
            pxJsonWriterNext(writer, arena,
                pxJsonEventName(pxs8("player_skip")));

            c4JsonWriteMsgPlayerSkip(
                &self->player_skip, writer, arena);
        } break;

        case C4_MESSAGE_GAME_START: {
            pxJsonWriterNext(writer, arena,
                pxJsonEventName(pxs8("game_start")));

            c4JsonWriteMsgGameStart(0, writer, arena);
        } break;

        case C4_MESSAGE_GAME_STOP: {
            pxJsonWriterNext(writer, arena,
                pxJsonEventName(pxs8("game_stop")));

            c4JsonWriteMsgGameStop(
                &self->game_stop, writer, arena);
        } break;

        default: break;
    }

    pxJsonWriterNext(writer, arena, pxJsonEventObjectClose());

    return 1;
}

pxb8
c4JsonWriteMsgPlayerJoin(C4MsgPlayerJoin* self, PxJsonWriter* writer, PxArena* arena)
{
    pxJsonWriterNext(writer, arena, pxJsonEventObjectOpen());

    pxJsonWriterNext(writer, arena,
        pxJsonEventBoolean(self->player_is_automatic, pxs8("player_is_automatic")));

    pxJsonWriterNext(writer, arena, pxJsonEventObjectClose());

    return 1;
}

pxb8
c4JsonWriteMsgPlayerAccept(C4MsgPlayerAccept* self, PxJsonWriter* writer, PxArena* arena)
{
    pxJsonWriterNext(writer, arena, pxJsonEventObjectOpen());

    pxJsonWriterNext(writer, arena,
        pxJsonEventUnsigned(self->player_number, pxs8("player_number")));

    pxJsonWriterNext(writer, arena,
        pxJsonEventUnsigned(self->player_code, pxs8("player_code")));

    pxJsonWriterNext(writer, arena,
        pxJsonEventUnsigned(self->piece_color, pxs8("piece_color")));

    PxString8 piece_shape = pxString8CopyUnicode(arena, self->piece_shape);

    pxJsonWriterNext(writer, arena,
        pxJsonEventString(piece_shape, pxs8("piece_shape")));

    pxJsonWriterNext(writer, arena,
        pxJsonEventInteger(self->board_width, pxs8("board_width")));

    pxJsonWriterNext(writer, arena,
        pxJsonEventInteger(self->board_height, pxs8("board_height")));

    pxJsonWriterNext(writer, arena, pxJsonEventObjectClose());

    return 1;
}

pxb8
c4JsonWriteMsgPlayerData(C4MsgPlayerData* self, PxJsonWriter* writer, PxArena* arena)
{
    pxJsonWriterNext(writer, arena, pxJsonEventObjectOpen());

    pxJsonWriterNext(writer, arena,
        pxJsonEventUnsigned(self->player_code, pxs8("player_code")));

    pxJsonWriterNext(writer, arena,
        pxJsonEventUnsigned(self->piece_color, pxs8("piece_color")));

    PxString8 piece_shape = pxString8CopyUnicode(arena, self->piece_shape);

    pxJsonWriterNext(writer, arena,
        pxJsonEventString(piece_shape, pxs8("piece_shape")));

    pxJsonWriterNext(writer, arena, pxJsonEventObjectClose());

    return 1;
}

pxb8
c4JsonWriteMsgPlayerTurn(C4MsgPlayerTurn* self, PxJsonWriter* writer, PxArena* arena)
{
    pxJsonWriterNext(writer, arena, pxJsonEventObjectOpen());

    pxJsonWriterNext(writer, arena,
        pxJsonEventUnsigned(self->player_code, pxs8("player_code")));

    pxJsonWriterNext(writer, arena, pxJsonEventObjectClose());

    return 1;
}

pxb8
c4JsonWriteMsgPlayerChoice(C4MsgPlayerChoice* self, PxJsonWriter* writer, PxArena* arena)
{
    pxJsonWriterNext(writer, arena, pxJsonEventObjectOpen());

    pxJsonWriterNext(writer, arena,
        pxJsonEventUnsigned(self->player_code, pxs8("player_code")));

    pxJsonWriterNext(writer, arena,
        pxJsonEventInteger(self->board_column, pxs8("board_column")));

    pxJsonWriterNext(writer, arena, pxJsonEventObjectClose());

    return 1;
}

pxb8
c4JsonWriteMsgPlayerSkip(C4MsgPlayerSkip* self, PxJsonWriter* writer, PxArena* arena)
{
    pxJsonWriterNext(writer, arena, pxJsonEventObjectOpen());

    pxJsonWriterNext(writer, arena,
        pxJsonEventUnsigned(self->player_code, pxs8("player_code")));

    pxJsonWriterNext(writer, arena, pxJsonEventObjectClose());

    return 1;
}

pxb8
c4JsonWriteMsgGameStart(void* self, PxJsonWriter* writer, PxArena* arena)
{
    pxJsonWriterNext(writer, arena, pxJsonEventObjectOpen());
    pxJsonWriterNext(writer, arena, pxJsonEventObjectClose());

    return 1;
}

pxb8
c4JsonWriteMsgGameStop(C4MsgGameStop* self, PxJsonWriter* writer, PxArena* arena)
{
    pxJsonWriterNext(writer, arena, pxJsonEventObjectOpen());

    pxJsonWriterNext(writer, arena,
        pxJsonEventUnsigned(self->player_code, pxs8("player_code")));

    pxJsonWriterNext(writer, arena, pxJsonEventObjectClose());

    return 1;
}

pxb8
c4JsonReadMsg(C4Msg* self, PxJsonReader* reader, PxArena* arena)
{
    PxJsonEvent event = pxJsonReaderNext(reader, arena);

    if (event.type != PX_JSON_EVENT_OBJECT_OPEN) return 0;

    while (event.type != PX_JSON_EVENT_OBJECT_CLOSE) {
        event = pxJsonReaderNext(reader, arena);

        if (event.type == PX_JSON_EVENT_COUNT) return 0;

        switch (event.type) {
            case PX_JSON_EVENT_NAME: {
                self->type = C4_MESSAGE_NONE;

                if (pxString8IsEqual(event.name, pxs8("player_join")) != 0) {
                    self->type = C4_MESSAGE_PLAYER_JOIN;

                    c4JsonReadMsgPlayerJoin(
                        &self->player_join, reader, arena);
                }

                if (pxString8IsEqual(event.name, pxs8("player_accept")) != 0) {
                    self->type = C4_MESSAGE_PLAYER_ACCEPT;

                    c4JsonReadMsgPlayerAccept(
                        &self->player_accept, reader, arena);
                }

                if (pxString8IsEqual(event.name, pxs8("player_data")) != 0) {
                    self->type = C4_MESSAGE_PLAYER_DATA;

                    c4JsonReadMsgPlayerData(
                        &self->player_data, reader, arena);
                }

                if (pxString8IsEqual(event.name, pxs8("player_turn")) != 0) {
                    self->type = C4_MESSAGE_PLAYER_TURN;

                    c4JsonReadMsgPlayerTurn(
                        &self->player_turn, reader, arena);
                }

                if (pxString8IsEqual(event.name, pxs8("player_choice")) != 0) {
                    self->type = C4_MESSAGE_PLAYER_CHOICE;

                    c4JsonReadMsgPlayerChoice(
                        &self->player_choice, reader, arena);
                }

                if (pxString8IsEqual(event.name, pxs8("player_skip")) != 0) {
                    self->type = C4_MESSAGE_PLAYER_SKIP;

                    c4JsonReadMsgPlayerSkip(
                        &self->player_skip, reader, arena);
                }

                if (pxString8IsEqual(event.name, pxs8("game_start")) != 0) {
                    self->type = C4_MESSAGE_GAME_START;

                    c4JsonReadMsgGameStart(
                        0, reader, arena);
                }

                if (pxString8IsEqual(event.name, pxs8("game_stop")) != 0) {
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
    PxJsonEvent event = pxJsonReaderNext(reader, arena);

    if (event.type != PX_JSON_EVENT_OBJECT_OPEN) return 0;

    while (event.type != PX_JSON_EVENT_OBJECT_CLOSE) {
        event = pxJsonReaderNext(reader, arena);

        if (event.type == PX_JSON_EVENT_COUNT) return 0;

        switch (event.type) {
            case PX_JSON_EVENT_BOOLEAN: {
                if (pxString8IsEqual(event.name, pxs8("player_is_automatic")) != 0)
                    self->player_is_automatic = event.value_boolean;
            } break;

            default: break;
        }
    }

    return 1;
}

pxb8
c4JsonReadMsgPlayerAccept(C4MsgPlayerAccept* self, PxJsonReader* reader, PxArena* arena)
{
    PxJsonEvent event = pxJsonReaderNext(reader, arena);

    if (event.type != PX_JSON_EVENT_OBJECT_OPEN) return 0;

    while (event.type != PX_JSON_EVENT_OBJECT_CLOSE) {
        event = pxJsonReaderNext(reader, arena);

        if (event.type == PX_JSON_EVENT_COUNT) return 0;

        switch (event.type) {
            case PX_JSON_EVENT_UNSIGNED: {
                if (pxString8IsEqual(event.name, pxs8("player_number")) != 0)
                    self->player_number = event.value_unsigned;

                if (pxString8IsEqual(event.name, pxs8("player_code")) != 0)
                    self->player_code = event.value_unsigned;

                if (pxString8IsEqual(event.name, pxs8("piece_color")) != 0)
                    self->piece_color = event.value_unsigned;

                if (pxString8IsEqual(event.name, pxs8("board_width")) != 0)
                    self->board_width = event.value_unsigned;

                if (pxString8IsEqual(event.name, pxs8("board_height")) != 0)
                    self->board_height = event.value_unsigned;
            } break;

            case PX_JSON_EVENT_STRING: {
                if (pxString8IsEqual(event.name, pxs8("piece_shape")) != 0)
                    self->piece_shape = pxString8GetOr(event.value_string, 0, PX_ASCII_EXCLAMATION);
            } break;

            case PX_JSON_EVENT_INTEGER: {
                if (pxString8IsEqual(event.name, pxs8("board_width")) != 0)
                    self->board_width = event.value_integer;

                if (pxString8IsEqual(event.name, pxs8("board_height")) != 0)
                    self->board_height = event.value_integer;
            } break;

            default: break;
        }
    }

    return 1;
}

pxb8
c4JsonReadMsgPlayerData(C4MsgPlayerData* self, PxJsonReader* reader, PxArena* arena)
{
    PxJsonEvent event = pxJsonReaderNext(reader, arena);

    if (event.type != PX_JSON_EVENT_OBJECT_OPEN) return 0;

    while (event.type != PX_JSON_EVENT_OBJECT_CLOSE) {
        event = pxJsonReaderNext(reader, arena);

        if (event.type == PX_JSON_EVENT_COUNT) return 0;

        switch (event.type) {
            case PX_JSON_EVENT_UNSIGNED: {
                if (pxString8IsEqual(event.name, pxs8("player_code")) != 0)
                    self->player_code = event.value_unsigned;

                if (pxString8IsEqual(event.name, pxs8("piece_color")) != 0)
                    self->piece_color = event.value_unsigned;
            } break;

            case PX_JSON_EVENT_STRING: {
                if (pxString8IsEqual(event.name, pxs8("piece_shape")) != 0)
                    self->piece_shape = pxString8GetOr(event.value_string, 0, PX_ASCII_EXCLAMATION);
            } break;

            default: break;
        }
    }

    return 1;
}

pxb8
c4JsonReadMsgPlayerTurn(C4MsgPlayerTurn* self, PxJsonReader* reader, PxArena* arena)
{
    PxJsonEvent event = pxJsonReaderNext(reader, arena);

    if (event.type != PX_JSON_EVENT_OBJECT_OPEN) return 0;

    while (event.type != PX_JSON_EVENT_OBJECT_CLOSE) {
        event = pxJsonReaderNext(reader, arena);

        if (event.type == PX_JSON_EVENT_COUNT) return 0;

        switch (event.type) {
            case PX_JSON_EVENT_UNSIGNED: {
                if (pxString8IsEqual(event.name, pxs8("player_code")) != 0)
                    self->player_code = event.value_unsigned;
            } break;

            default: break;
        }
    }

    return 1;
}

pxb8
c4JsonReadMsgPlayerChoice(C4MsgPlayerChoice* self, PxJsonReader* reader, PxArena* arena)
{
    PxJsonEvent event = pxJsonReaderNext(reader, arena);

    if (event.type != PX_JSON_EVENT_OBJECT_OPEN) return 0;

    while (event.type != PX_JSON_EVENT_OBJECT_CLOSE) {
        event = pxJsonReaderNext(reader, arena);

        if (event.type == PX_JSON_EVENT_COUNT) return 0;

        switch (event.type) {
            case PX_JSON_EVENT_UNSIGNED: {
                if (pxString8IsEqual(event.name, pxs8("player_code")) != 0)
                    self->player_code = event.value_unsigned;

                if (pxString8IsEqual(event.name, pxs8("board_column")) != 0)
                    self->board_column = event.value_unsigned;
            } break;

            case PX_JSON_EVENT_INTEGER: {
                if (pxString8IsEqual(event.name, pxs8("board_column")) != 0)
                    self->board_column = event.value_integer;
            } break;

            default: break;
        }
    }

    return 1;
}

pxb8
c4JsonReadMsgPlayerSkip(C4MsgPlayerSkip* self, PxJsonReader* reader, PxArena* arena)
{
    PxJsonEvent event = pxJsonReaderNext(reader, arena);

    if (event.type != PX_JSON_EVENT_OBJECT_OPEN) return 0;

    while (event.type != PX_JSON_EVENT_OBJECT_CLOSE) {
        event = pxJsonReaderNext(reader, arena);

        if (event.type == PX_JSON_EVENT_COUNT) return 0;

        switch (event.type) {
            case PX_JSON_EVENT_UNSIGNED: {
                if (pxString8IsEqual(event.name, pxs8("player_code")) != 0)
                    self->player_code = event.value_unsigned;
            } break;

            default: break;
        }
    }

    return 1;
}

pxb8
c4JsonReadMsgGameStart(void* self, PxJsonReader* reader, PxArena* arena)
{
    PxJsonEvent event = pxJsonReaderNext(reader, arena);

    if (event.type != PX_JSON_EVENT_OBJECT_OPEN) return 0;

    while (event.type != PX_JSON_EVENT_OBJECT_CLOSE)
        event = pxJsonReaderNext(reader, arena);

    return 1;
}

pxb8
c4JsonReadMsgGameStop(C4MsgGameStop* self, PxJsonReader* reader, PxArena* arena)
{
    PxJsonEvent event = pxJsonReaderNext(reader, arena);

    if (event.type != PX_JSON_EVENT_OBJECT_OPEN) return 0;

    while (event.type != PX_JSON_EVENT_OBJECT_CLOSE) {
        event = pxJsonReaderNext(reader, arena);

        if (event.type == PX_JSON_EVENT_COUNT) return 0;

        switch (event.type) {
            case PX_JSON_EVENT_UNSIGNED: {
                if (pxString8IsEqual(event.name, pxs8("player_code")) != 0)
                    self->player_code = event.value_unsigned;
            } break;

            default: break;
        }
    }

    return 1;
}

void
c4LogMsg(C4Msg* self, PxLogger* logger)
{
    switch (self->type) {
        case C4_MESSAGE_PLAYER_JOIN:
            c4LogMsgPlayerJoin(&self->player_join, logger);
        break;

        case C4_MESSAGE_PLAYER_ACCEPT:
            c4LogMsgPlayerAccept(&self->player_accept, logger);
        break;

        case C4_MESSAGE_PLAYER_DATA:
            c4LogMsgPlayerData(&self->player_data, logger);
        break;

        case C4_MESSAGE_PLAYER_TURN:
            c4LogMsgPlayerTurn(&self->player_turn, logger);
        break;

        case C4_MESSAGE_PLAYER_CHOICE:
            c4LogMsgPlayerChoice(&self->player_choice, logger);
        break;

        case C4_MESSAGE_PLAYER_SKIP:
            c4LogMsgPlayerSkip(&self->player_skip, logger);
        break;

        case C4_MESSAGE_GAME_START:
            c4LogMsgGameStart(0, logger);
        break;

        case C4_MESSAGE_GAME_STOP:
            c4LogMsgGameStop(&self->game_stop, logger);
        break;

        default: break;
    }
}

void
c4LogMsgPlayerJoin(C4MsgPlayerJoin* self, PxLogger* logger)
{
    if (self->player_is_automatic != 0)
        pxLoggerString8(logger, 0, pxs8("true"));
    else
        pxLoggerString8(logger, 0, pxs8("false"));

    pxLoggerReport(logger, pxs8("PLAYER_JOIN: {\n"));
    pxLoggerReport(logger, pxs8("    - player_is_automatic: ${0}\n"));
    pxLoggerReport(logger, pxs8("}\n"));

    pxLoggerClear(logger);
}

void
c4LogMsgPlayerAccept(C4MsgPlayerAccept* self, PxLogger* logger)
{
    static const char* const colors[] =
    {
        "white", "red", "green", "yellow", "blue", "purple", "azure",
    };

    pxLoggerInteger64(logger, 0, self->player_number);
    pxLoggerUnsigned64(logger, 1, self->player_code);
    pxLoggerUnsigned8(logger, 2, self->piece_color);

    if (self->piece_color >= 0 && self->piece_color < 7)
        pxLoggerMemory8(logger, 3, pxCast(pxu8*, colors[self->piece_color]));
    else
        pxLoggerString8(logger, 3, pxs8("<empty>"));

    pxLoggerUnsigned8(logger, 4, self->piece_shape);
    pxLoggerInteger64(logger, 5, self->board_width);
    pxLoggerInteger64(logger, 6, self->board_height);

    pxLoggerReport(logger, pxs8("PLAYER_ACCEPT: {\n"));
    pxLoggerReport(logger, pxs8("    - player_number: ${0}\n"));
    pxLoggerReport(logger, pxs8("    - player_code:   ${1}\n"));
    pxLoggerReport(logger, pxs8("    - piece_color:   ${2} ${3}\n"));
    pxLoggerReport(logger, pxs8("    - piece_shape:   ${4}\n"));
    pxLoggerReport(logger, pxs8("    - board_width:   ${5}\n"));
    pxLoggerReport(logger, pxs8("    - board_height:  ${6}\n"));

    pxLoggerReport(logger, pxs8("}\n"));

    pxLoggerClear(logger);
}

void
c4LogMsgPlayerData(C4MsgPlayerData* self, PxLogger* logger)
{
    static const char* const colors[] =
    {
        "white", "red", "green", "yellow", "blue", "purple", "azure",
    };

    pxLoggerUnsigned64(logger, 0, self->player_code);
    pxLoggerUnsigned8(logger, 1, self->piece_color);

    if (self->piece_color >= 0 && self->piece_color < 7)
        pxLoggerMemory8(logger, 2, pxCast(pxu8*, colors[self->piece_color]));
    else
        pxLoggerString8(logger, 2, pxs8("<empty>"));

    pxLoggerUnsigned8(logger, 3, self->piece_shape);

    pxLoggerReport(logger, pxs8("PLAYER_DATA: {\n"));
    pxLoggerReport(logger, pxs8("    - player_code: ${0}\n"));
    pxLoggerReport(logger, pxs8("    - piece_color: ${1} ${2}\n"));
    pxLoggerReport(logger, pxs8("    - piece_shape: ${3}\n"));
    pxLoggerReport(logger, pxs8("}\n"));

    pxLoggerClear(logger);
}

void
c4LogMsgPlayerTurn(C4MsgPlayerTurn* self, PxLogger* logger)
{
    pxLoggerUnsigned64(logger, 0, self->player_code);

    pxLoggerReport(logger, pxs8("PLAYER_TURN: {\n"));
    pxLoggerReport(logger, pxs8("    - player_code: ${0}\n"));
    pxLoggerReport(logger, pxs8("}\n"));

    pxLoggerClear(logger);
}

void
c4LogMsgPlayerChoice(C4MsgPlayerChoice* self, PxLogger* logger)
{
    pxLoggerUnsigned64(logger, 0, self->player_code);
    pxLoggerInteger64(logger, 1, self->board_column);

    pxLoggerReport(logger, pxs8("PLAYER_CHOICE: {\n"));
    pxLoggerReport(logger, pxs8("    - player_code:  ${0}\n"));
    pxLoggerReport(logger, pxs8("    - board_column: ${1}\n"));
    pxLoggerReport(logger, pxs8("}\n"));

    pxLoggerClear(logger);
}

void
c4LogMsgPlayerSkip(C4MsgPlayerSkip* self, PxLogger* logger)
{
    pxLoggerUnsigned64(logger, 0, self->player_code);

    pxLoggerReport(logger, pxs8("PLAYER_SKIP: {\n"));
    pxLoggerReport(logger, pxs8("    - player_code: ${0}\n"));
    pxLoggerReport(logger, pxs8("}\n"));

    pxLoggerClear(logger);
}

void
c4LogMsgGameStart(void* self, PxLogger* logger)
{
    pxLoggerReport(logger, pxs8("PLAYER_TURN: {}\n"));

    pxLoggerClear(logger);
}

void
c4LogMsgGameStop(C4MsgGameStop* self, PxLogger* logger)
{
    pxLoggerUnsigned64(logger, 0, self->player_code);

    pxLoggerReport(logger, pxs8("GAME_STOP: {\n"));
    pxLoggerReport(logger, pxs8("    - player_code: ${0}\n"));
    pxLoggerReport(logger, pxs8("}\n"));

    pxLoggerClear(logger);
}

#endif // C4_MESSAGE_MESSAGE_C
