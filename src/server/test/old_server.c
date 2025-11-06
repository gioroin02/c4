#include "../export.h"

typedef struct C4ServerConfig
{
    PxAddrType server_addr_type;
    pxuword    server_port;

    pxuword game_board_width;
    pxuword game_board_height;

    pxuword player_amount;
}
C4ServerConfig;

typedef struct C4Game
{
    C4ServerConfig config;

    PxBuffer8 request;
    PxBuffer8 response;

    PxJsonWriter json_writer;
    PxJsonReader json_reader;

    C4GamePlayerList player_list;
    pxiword          player_turn;

    C4GameBoard game_board;
}
C4Game;

pxuword
c4GamePlayerHasWon(C4Game* self, pxiword x, pxiword y, pxiword length)
{
    #define DIRS 8

    pxiword xs[DIRS] = {+1, +1,  0, -1, -1, -1,  0, +1};
    pxiword ys[DIRS] = { 0, +1, +1, +1,  0, -1, -1, -1};

    pxuword value = 0;

    for (pxiword i = 0; i < DIRS; i += 1) {
        pxiword j = (i + 4) % DIRS;

        pxiword forw = c4GameBoardContainsLine(
            &self->game_board, x, y, xs[i], ys[i], &value);

        pxiword back = c4GameBoardContainsLine(
            &self->game_board, x, y, xs[j], ys[j], &value);

        if (forw + back > length) return value;
    }

    return 0;
}

C4GameMsg
c4GameAccept(C4Game* self, PxArena* arena, C4Server* server, C4ServerConfig config)
{
    pxiword    offset  = pxArenaOffset(arena);
    C4Session* session = c4SessionOpen(server, arena);

    if (session == 0) return (C4GameMsg) {0};

    session->reader = pxSocketTcpReader(session->socket, arena, PX_MEMORY_KIB);
    session->writer = pxSocketTcpWriter(session->socket, arena, PX_MEMORY_KIB);

    C4GameMsg message = c4SessionRead(session, arena);

    if (message.type == C4_GAME_MSG_PLAYER_JOIN)
        return message;

    c4SessionClose(server, session);

    pxArenaRewind(arena, offset);

    return (C4GameMsg) {0};
}

pxb8
c4GameStart(C4Game *self, PxArena* arena, C4Server* server, C4ServerConfig config)
{
    self->player_list = c4GamePlayerListReserve(arena, config.player_list);

    if (c4GamePlayerListLength(&self->player_list) == 0) return 0;

    self->game_board = c4GameBoardReserve(arena,
        config.game_board_width, config.game_board_height);

    if (c4GameBoardLength(&self->game_board) == 0) return 0;

    while (c4GamePlayerListIsFull(&self->player_list) == 0) {
        pxiword size = c4GamePlayerListSize(&self->player_list);

        C4GameMsg      message = c4GameAccept(self, arena, server, config);
        C4Session* session = c4ServerGetOr(server, size, 0);

        if (message.type == C4_GAME_MSG_NONE || session == 0)
            continue;

        PxString8    text   = pxString8CopyUnicode(arena, PX_ASCII_UPPER_A + size);
        C4GamePlayer player = c4GamePlayer(size + 1, text, pxConsoleColor16(size + 1));

        pxb8 state = c4GamePlayerListInsert(&self->player_list, player);

        if (state == 0) return 0;

        message = c4GameMsgPlayerAccept(config.player_list, player,
            config.game_board_width, config.game_board_height);

        c4SessionWrite(session, arena, message);

        c4ServerBroadcast(server, arena, session, c4GameMsgPlayerData(player));

        for (pxiword i = 0; i < size; i += 1) {
            c4GamePlayerListRead(&self->player_list, i, &player);

            c4SessionWrite(session, arena,
                c4GameMsgPlayerData(player));
        }
    }

    return 1;
}

pxb8
c4GameLoop(C4Game* self, PxArena* arena, C4Server* server)
{
    pxiword offset = pxArenaOffset(arena);
    pxiword size   = c4GamePlayerListSize(&self->player_list);
    pxb8    active = 1;

    c4ServerBroadcast(server, arena, 0, c4GameMsgGameStart());

    while (active != 0) {
        C4Session* session = c4ServerGetOr(server, self->player_turn, 0);

        if (session == 0) return 0;

        c4ServerBroadcast(server, arena, 0,
            c4GameMsgPlayerTurn(self->player_turn + 1));

        C4GameMsg message = c4SessionRead(session, arena);

        switch (message.type) {
            case C4_GAME_MSG_PLAYER_CHOICE: {
                pxiword column = message.player_choice.board_column;
                pxuword ident  = message.player_choice.player_ident;

                pxiword height = c4GameBoardHeight(&self->game_board, column);

                if (c4GameBoardInsert(&self->game_board, column, ident) != 0) {
                    c4ServerBroadcast(server, arena, session, message);

                    if (c4GamePlayerHasWon(self, column, height, 4) == 0) {
                        if (c4GameBoardIsFull(&self->game_board))
                            message = c4GameMsgGameStop(0);
                    } else
                        message = c4GameMsgGameStop(ident);

                    if (message.type == C4_GAME_MSG_GAME_STOP) {
                        active = 0;

                        c4ServerBroadcast(
                            server, arena, 0, message);
                    }
                } else {
                    c4ServerBroadcast(server, arena, session,
                        c4GameMsgPlayerSkip(self->player_turn + 1));
                }
            } break;

            default:
                c4ServerBroadcast(server, arena, session,
                    c4GameMsgPlayerSkip(self->player_turn + 1));
            break;
        }

        self->player_turn = (self->player_turn + 1) % size;

        pxArenaRewind(arena, offset);
    }

    return 1;
}

pxb8
c4GameStop(C4Game* self, PxArena* arena, C4Server* server)
{
    c4ServerStop(server);

    return 1;
}

PxLogger* LOGGER = 0;

int
main(int argc, char** argv)
{
    PxArena arena = pxMemoryReserve(32);

    if (pxNetworkStart() == 0) return 1;

    C4ServerConfig config = {
        .type              = PX_ADDR_TYPE_IP4,
        .port              = 50000,
        .game_board_width  = 5,
        .game_board_height = 5,
        .player_list       = 2,
    };

    for (pxiword i = 1; i < argc; i += 1) {
        PxFormatRadix radix = PX_FORMAT_RADIX_10;
        PxFormatFlag  flags = PX_FORMAT_FLAG_NONE;

        PxString8 arg = pxString8FromMemory(argv[i], 32);

        if (pxString8IsEqual(arg, pxs8("--server-ipv4")) != 0) config.type = PX_ADDR_TYPE_IP4;
        if (pxString8IsEqual(arg, pxs8("--server-ipv6")) != 0) config.type = PX_ADDR_TYPE_IP6;

        if (pxString8BeginsWith(arg, pxs8("--port=")) != 0) {
            arg = pxString8TrimPrefix(arg, pxs8("--port="));
            arg = pxString8TrimSpaces(arg);

            pxUnsignedFromString8(arg, &config.port, radix, flags);
        }

        if (pxString8BeginsWith(arg, pxs8("--game_board-width=")) != 0) {
            arg = pxString8TrimPrefix(arg, pxs8("--game_board-width="));
            arg = pxString8TrimSpaces(arg);

            pxUnsignedFromString8(arg, &config.game_board_width, radix, flags);
        }

        if (pxString8BeginsWith(arg, pxs8("--game_board-height=")) != 0) {
            arg = pxString8TrimPrefix(arg, pxs8("--game_board-height="));
            arg = pxString8TrimSpaces(arg);

            pxUnsignedFromString8(arg, &config.game_board_height, radix, flags);
        }

        if (pxString8BeginsWith(arg, pxs8("--player_list=")) != 0) {
            arg = pxString8TrimPrefix(arg, pxs8("--player_list="));
            arg = pxString8TrimSpaces(arg);

            pxUnsignedFromString8(arg, &config.player_list, radix, flags);
        }
    }

    C4Server server = c4ServerMake(&arena,
        config.player_list, config.type);

    pxb8 state = c4ServerStart(&server,
        pxAddressAny(config.type), config.port);

    if (state == 0) return 1;

    C4Game game = {0};

    if (c4GameStart(&game, &arena, &server, config) == 0)
        return 1;

    c4ServerClose(&server);

    c4GameLoop(&game, &arena, &server);
    c4GameStop(&game, &arena, &server);

    pxNetworkStop();
}
