#ifndef C4_MESSAGE_C
#define C4_MESSAGE_C

#include "message.h"

#include <stdio.h>

C4Message
c4MsgPlayerJoin(pxb8 player_is_automatic)
{
    return (C4Message) {
        .type = C4_MESSAGE_PLAYER_JOIN,
        .player_join = {
            .player_is_automatic = player_is_automatic,
        },
    };
}

C4Message
c4MsgPlayerAccept(pxiword player_number, pxuword player_code, pxu8 piece_color, pxu8 piece_shape, pxiword board_width, pxiword board_height)
{
    return (C4Message) {
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

C4Message
c4MsgPlayerData(pxuword player_code, pxu8 piece_color, pxu8 piece_shape)
{
    return (C4Message) {
        .type = C4_MESSAGE_PLAYER_DATA,
        .player_data = {
            .player_code = player_code,
            .piece_color = piece_color,
            .piece_shape = piece_shape,
        },
    };
}

C4Message
c4MsgPlayerTurn(pxuword player_code)
{
    return (C4Message) {
        .type = C4_MESSAGE_PLAYER_TURN,
        .player_turn = {
            .player_code = player_code,
        },
    };
}

C4Message
c4MsgPlayerChoice(pxuword player_code, pxiword board_column)
{
    return (C4Message) {
        .type = C4_MESSAGE_PLAYER_CHOICE,
        .player_choice = {
            .player_code  = player_code,
            .board_column = board_column,
        },
    };
}

C4Message
c4MsgPlayerSkip(pxuword player_code)
{
    return (C4Message) {
        .type = C4_MESSAGE_PLAYER_SKIP,
        .player_turn = {
            .player_code = player_code,
        },
    };
}

C4Message
c4MsgGameStart()
{
    return (C4Message) {
        .type = C4_MESSAGE_GAME_START,
    };
}

C4Message
c4MsgGameStop(pxuword player_code)
{
    return (C4Message) {
        .type = C4_MESSAGE_GAME_STOP,
        .game_stop = {
            .player_code = player_code,
        },
    };
}

pxb8
c4JsonWriteMessage(C4Message* self, PxJsonWriter* writer, PxArena* arena)
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
c4JsonReadMessage(C4Message* self, PxJsonReader* reader, PxArena* arena)
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
                    self->player_is_automatic = event.bvalue;
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
                    self->player_number = event.uvalue;

                if (pxString8IsEqual(event.name, pxs8("player_code")) != 0)
                    self->player_code = event.uvalue;

                if (pxString8IsEqual(event.name, pxs8("piece_color")) != 0)
                    self->piece_color = event.uvalue;

                if (pxString8IsEqual(event.name, pxs8("board_width")) != 0)
                    self->board_width = event.uvalue;

                if (pxString8IsEqual(event.name, pxs8("board_height")) != 0)
                    self->board_height = event.uvalue;
            } break;

            case PX_JSON_EVENT_STRING: {
                if (pxString8IsEqual(event.name, pxs8("piece_shape")) != 0)
                    self->piece_shape = pxString8GetOr(event.svalue, 0, PX_ASCII_EXCLAMATION);
            } break;

            case PX_JSON_EVENT_INTEGER: {
                if (pxString8IsEqual(event.name, pxs8("board_width")) != 0)
                    self->board_width = event.ivalue;

                if (pxString8IsEqual(event.name, pxs8("board_height")) != 0)
                    self->board_height = event.ivalue;
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
                    self->player_code = event.uvalue;

                if (pxString8IsEqual(event.name, pxs8("piece_color")) != 0)
                    self->piece_color = event.uvalue;
            } break;

            case PX_JSON_EVENT_STRING: {
                if (pxString8IsEqual(event.name, pxs8("piece_shape")) != 0)
                    self->piece_shape = pxString8GetOr(event.svalue, 0, PX_ASCII_EXCLAMATION);
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
                    self->player_code = event.uvalue;
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
                    self->player_code = event.uvalue;

                if (pxString8IsEqual(event.name, pxs8("board_column")) != 0)
                    self->board_column = event.uvalue;
            } break;

            case PX_JSON_EVENT_INTEGER: {
                if (pxString8IsEqual(event.name, pxs8("board_column")) != 0)
                    self->board_column = event.ivalue;
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
                    self->player_code = event.uvalue;
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
                    self->player_code = event.uvalue;
            } break;

            default: break;
        }
    }

    return 1;
}

void
c4ShowMessage(C4Message* self)
{
    switch (self->type) {
        case C4_MESSAGE_PLAYER_JOIN:
            c4ShowMsgPlayerJoin(&self->player_join);
        break;

        case C4_MESSAGE_PLAYER_ACCEPT:
            c4ShowMsgPlayerAccept(&self->player_accept);
        break;

        case C4_MESSAGE_PLAYER_DATA:
            c4ShowMsgPlayerData(&self->player_data);
        break;

        case C4_MESSAGE_PLAYER_TURN:
            c4ShowMsgPlayerTurn(&self->player_turn);
        break;

        case C4_MESSAGE_PLAYER_CHOICE:
            c4ShowMsgPlayerChoice(&self->player_choice);
        break;

        case C4_MESSAGE_PLAYER_SKIP:
            c4ShowMsgPlayerSkip(&self->player_skip);
        break;

        case C4_MESSAGE_GAME_START:
            c4ShowMsgGameStart(0);
        break;

        case C4_MESSAGE_GAME_STOP:
            c4ShowMsgGameStop(&self->game_stop);
        break;

        default: break;
    }
}

void
c4ShowMsgPlayerJoin(C4MsgPlayerJoin* self)
{
    printf("PLAYER_JOIN:\n");

    printf("    - player_is_automatic: %s\n",
        self->player_is_automatic != 0 ? "true" : "false");
}

void
c4ShowMsgPlayerAccept(C4MsgPlayerAccept* self)
{
    static const char* const colors[] =
    {
        "white", "red", "green", "yellow", "blue", "purple", "azure",
    };

    printf("PLAYER_ACCEPT:\n");

    printf("    - player_number: %lli\n",
        self->player_number);

    printf("    - player_code: %llu\n",
        self->player_code);

    printf("    - piece_color: %u", self->piece_color);

    if (self->piece_color >= 0 && self->piece_color < 7)
        printf(" '%s'", colors[self->piece_color]);

    printf("\n");

    printf("    - piece_shape: '%c'\n",
        self->piece_shape);

    printf("    - board_width: %lli\n",
        self->board_width);

    printf("    - board_height: %lli\n",
        self->board_height);
}

void
c4ShowMsgPlayerData(C4MsgPlayerData* self)
{
    static const char* const colors[] =
    {
        "white", "red", "green", "yellow", "blue", "purple", "azure",
    };

    printf("PLAYER_DATA:\n");

    printf("    - player_code: %llu\n",
        self->player_code);

    printf("    - piece_color: %u", self->piece_color);

    if (self->piece_color >= 0 && self->piece_color < 7)
        printf(" '%s'", colors[self->piece_color]);

    printf("\n");

    printf("    - piece_shape: '%c'\n",
        self->piece_shape);
}

void
c4ShowMsgPlayerTurn(C4MsgPlayerTurn* self)
{
    printf("PLAYER_TURN:\n");

    printf("    - player_code: %llu\n",
        self->player_code);
}

void
c4ShowMsgPlayerChoice(C4MsgPlayerChoice* self)
{
    printf("PLAYER_CHOICE:\n");

    printf("    - player_code: %llu\n",
        self->player_code);

    printf("    - board_column: %lli\n",
        self->board_column);
}

void
c4ShowMsgPlayerSkip(C4MsgPlayerSkip* self)
{
    printf("PLAYER_SKIP:\n");

    printf("    - player_code: %llu\n",
        self->player_code);
}

void
c4ShowMsgGameStart(void* self)
{
    printf("GAME_START:\n");
}

void
c4ShowMsgGameStop(C4MsgGameStop* self)
{
    printf("GAME_STOP:\n");

    printf("    - player_code: %llu\n",
        self->player_code);
}

#endif // C4_MESSAGE_C
