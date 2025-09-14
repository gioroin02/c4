#include "../export.h"

typedef struct C4ServerConfig
{
    PxAddressType type;
    pxu16         port;
    pxuword       board_width;
    pxuword       board_height;
    pxuword       players;
}
C4ServerConfig;

typedef struct C4GameState
{
    C4GameBoard      board;
    C4GamePlayerList players;
    pxiword          turn;
}
C4GameState;

pxuword
c4GamePlayerHasWon(C4GameState* self, pxiword x, pxiword y, pxiword length)
{
    #define DIRS 8

    pxiword xs[DIRS] = {+1, +1,  0, -1, -1, -1,  0, +1};
    pxiword ys[DIRS] = { 0, +1, +1, +1,  0, -1, -1, -1};

    pxuword value = 0;

    for (pxiword i = 0; i < DIRS; i += 1) {
        pxiword j = (i + 4) % DIRS;

        pxiword forw = c4GameBoardContainsLine(
            &self->board, x, y, xs[i], ys[i], &value);

        pxiword back = c4GameBoardContainsLine(
            &self->board, x, y, xs[j], ys[j], &value);

        if (forw + back > length) return value;
    }

    return 0;
}

C4Msg
c4GameAccept(C4GameState* self, PxArena* arena, C4Server* server, C4ServerConfig config)
{
    pxiword    offset  = pxArenaOffset(arena);
    C4Session* session = c4SessionOpen(server, arena);

    if (session == 0) return (C4Msg) {0};

    session->reader = pxSocketTcpReader(session->socket, arena, PX_MEMORY_KIB);
    session->writer = pxSocketTcpWriter(session->socket, arena, PX_MEMORY_KIB);

    C4Msg message = c4SessionRead(session, arena);

    if (message.type == C4_MESSAGE_PLAYER_JOIN)
        return message;

    c4SessionClose(server, session);

    pxArenaRewind(arena, offset);

    return (C4Msg) {0};
}

pxb8
c4GameStart(C4GameState *self, PxArena* arena, C4Server* server, C4ServerConfig config)
{
    self->players = c4GamePlayerListReserve(arena, config.players);

    if (c4GamePlayerListLength(&self->players) == 0) return 0;

    self->board = c4GameBoardReserve(arena,
        config.board_width, config.board_height);

    if (c4GameBoardLength(&self->board) == 0) return 0;

    while (c4GamePlayerListIsFull(&self->players) == 0) {
        pxiword size = c4GamePlayerListSize(&self->players);

        C4Msg      message = c4GameAccept(self, arena, server, config);
        C4Session* session = c4ServerGetOr(server, size, 0);

        if (message.type == C4_MESSAGE_NONE || session == 0)
            continue;

        PxString8    text   = pxString8CopyUnicode(arena, PX_ASCII_UPPER_A + size);
        C4GamePlayer player = c4GamePlayer(size + 1, c4Color8(size + 1), text);

        pxb8 state = c4GamePlayerListInsert(&self->players, player);

        if (state == 0) return 0;

        message = c4MsgPlayerAccept(config.players, player,
            config.board_width, config.board_height);

        c4SessionWrite(session, arena, message);

        c4ServerBroadcast(server, arena, session, c4MsgPlayerData(player));

        for (pxiword i = 0; i < size; i += 1) {
            c4GamePlayerListRead(&self->players, i, &player);

            c4SessionWrite(session, arena,
                c4MsgPlayerData(player));
        }
    }

    return 1;
}

pxb8
c4GameLoop(C4GameState* self, PxArena* arena, C4Server* server)
{
    pxiword offset = pxArenaOffset(arena);
    pxiword size   = c4GamePlayerListSize(&self->players);
    pxb8    active = 1;

    c4ServerBroadcast(server, arena, 0, c4MsgGameStart());

    while (active != 0) {
        C4Session* session = c4ServerGetOr(server, self->turn, 0);

        if (session == 0) return 0;

        c4ServerBroadcast(server, arena, 0,
            c4MsgPlayerTurn(self->turn + 1));

        C4Msg message = c4SessionRead(session, arena);

        switch (message.type) {
            case C4_MESSAGE_PLAYER_CHOICE: {
                pxiword column = message.player_choice.board_column;
                pxuword code   = message.player_choice.player_code;

                pxiword height = c4GameBoardHeight(&self->board, column);

                if (c4GameBoardInsert(&self->board, column, code) != 0) {
                    c4ServerBroadcast(server, arena, session, message);

                    if (c4GamePlayerHasWon(self, column, height, 4) == 0) {
                        if (c4GameBoardIsFull(&self->board))
                            message = c4MsgGameStop(0);
                    } else
                        message = c4MsgGameStop(code);

                    if (message.type == C4_MESSAGE_GAME_STOP) {
                        active = 0;

                        c4ServerBroadcast(
                            server, arena, 0, message);
                    }
                } else {
                    c4ServerBroadcast(server, arena, session,
                        c4MsgPlayerSkip(self->turn + 1));
                }
            } break;

            default:
                c4ServerBroadcast(server, arena, session,
                    c4MsgPlayerSkip(self->turn + 1));
            break;
        }

        self->turn = (self->turn + 1) % size;

        pxArenaRewind(arena, offset);
    }

    return 1;
}

pxb8
c4GameStop(C4GameState* self, PxArena* arena, C4Server* server)
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
        .type         = PX_ADDRESS_TYPE_IP4,
        .port         = 50000,
        .board_width  = 5,
        .board_height = 5,
        .players      = 2,
    };

    if (argc > 1) {
        PxFormatOption options = PX_FORMAT_OPTION_NONE;

        for (pxiword i = 1; i < argc; i += 1) {
            PxString8 arg = pxString8FromMemory(argv[i], 32);

            if (pxString8BeginsWith(arg, pxs8("--server-ip-version=")) != 0) {
                arg = pxString8TrimPrefix(arg, pxs8("--server-ip-version="));
                arg = pxString8TrimSpaces(arg);

                if (pxString8IsEqual(arg, pxs8("ipv6")) != 0)
                    config.type = PX_ADDRESS_TYPE_IP6;
            }

            if (pxString8BeginsWith(arg, pxs8("--port=")) != 0) {
                arg = pxString8TrimPrefix(arg, pxs8("--port="));
                arg = pxString8TrimSpaces(arg);

                pxUnsigned16FromString8(&config.port, 10, options, arg);
            }

            if (pxString8BeginsWith(arg, pxs8("--board-width=")) != 0) {
                arg = pxString8TrimPrefix(arg, pxs8("--board-width="));
                arg = pxString8TrimSpaces(arg);

                pxUnsignedFromString8(&config.board_width, 10, options, arg);
            }

            if (pxString8BeginsWith(arg, pxs8("--board-height=")) != 0) {
                arg = pxString8TrimPrefix(arg, pxs8("--board-height="));
                arg = pxString8TrimSpaces(arg);

                pxUnsignedFromString8(&config.board_height, 10, options, arg);
            }

            if (pxString8BeginsWith(arg, pxs8("--players=")) != 0) {
                arg = pxString8TrimPrefix(arg, pxs8("--players="));
                arg = pxString8TrimSpaces(arg);

                pxUnsignedFromString8(&config.players, 10, options, arg);
            }
        }
    }

    PxConsole console = pxConsoleCreate(&arena);
    PxReader  reader  = pxConsoleReader(console, &arena, PX_MEMORY_KIB);
    PxWriter  writer  = pxConsoleWriter(console, &arena, PX_MEMORY_KIB);

    PxLogger logger = pxLoggerReserve(&arena, 1024, &writer);

    pxLoggerSetFlags(&logger, PX_REPORT_FLAG_LEVEL | PX_REPORT_FLAG_COLOR);
    pxLoggerSetLevel(&logger, PX_REPORT_LEVEL_INFO);

    LOGGER = &logger;

    C4Server server = c4ServerMake(&arena,
        config.players, config.type);

    pxb8 state = c4ServerStart(&server,
        pxAddressAny(config.type), config.port);

    if (state == 0) return 1;

    C4GameState game = {0};

    if (c4GameStart(&game, &arena, &server, config) == 0)
        return 1;

    c4GameLoop(&game, &arena, &server);
    c4GameStop(&game, &arena, &server);

    pxNetworkStop();
}
