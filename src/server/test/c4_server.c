#include "../export.h"

#include <stdio.h>

#define COLOR_RESET "\x1b[0m"

#define FRONT_RED    "\x1b[31m"
#define FRONT_GREEN  "\x1b[32m"
#define FRONT_YELLOW "\x1b[33m"
#define FRONT_BLUE   "\x1b[34m"
#define FRONT_PURPLE "\x1b[35m"
#define FRONT_AZURE  "\x1b[36m"

#define RED(expr)    FRONT_RED    expr COLOR_RESET
#define GREEN(expr)  FRONT_GREEN  expr COLOR_RESET
#define YELLOW(expr) FRONT_YELLOW expr COLOR_RESET
#define BLUE(expr)   FRONT_BLUE   expr COLOR_RESET
#define PURPLE(expr) FRONT_PURPLE expr COLOR_RESET
#define AZURE(expr)  FRONT_AZURE  expr COLOR_RESET

#define FATAL PURPLE("FATAL")
#define ERROR RED("ERROR")
#define WARN  YELLOW("WARN")
#define INFO  BLUE("INFO")
#define DEBUG GREEN("DEBUG")
#define TRACE AZURE("TRACE")

static const char* const FRONTS[] = {
    COLOR_RESET,
    FRONT_RED,
    FRONT_GREEN,
    FRONT_YELLOW,
    FRONT_BLUE,
    FRONT_PURPLE,
    FRONT_AZURE,
};

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

void
c4GameBoardShow(C4GameState* game)
{
    printf("#");

    for (pxiword i = 0; i < game->board.width; i += 1)
        printf("---#");

    printf("\n");

    for (pxiword r = game->board.height; r > 0; r -= 1) {
        printf("| ");

        for (pxiword c = 0; c < game->board.width; c += 1) {
            pxuword item = c4GameBoardReadOr(&game->board, c, r - 1, 0);

            C4GamePlayer player = {0};

            if (item > 0) {
                pxiword index = 0;

                if (c4GamePlayerListFind(&game->players, item, &index))
                    c4GamePlayerListRead(&game->players, index, &player);
            }

            if (player.code != 0)
                printf("%s%c%s | ", FRONTS[player.color], player.shape, FRONTS[0]);
            else
                printf("  | ");
        }

        printf("\n");
    }

    printf("#");

    for (pxiword i = 0; i < game->board.width; i += 1)
        printf("---#");

    printf("\n");
}

C4Message
c4GameAccept(PxArena* arena, C4Server* server, C4GameState* game, C4ServerConfig config)
{
    pxiword    offset  = pxArenaOffset(arena);
    C4Session* session = c4SessionOpen(server, arena);

    if (session == 0) return (C4Message) {0};

    session->request  = pxBuffer8Reserve(arena, PX_MEMORY_KIB);
    session->response = pxBuffer8Reserve(arena, PX_MEMORY_KIB);

    C4Message message = c4SessionRead(session, arena);

    if (message.type == C4_MESSAGE_PLAYER_JOIN)
        return message;

    c4SessionClose(server, session);

    pxArenaRewind(arena, offset);

    return (C4Message) {0};
}

pxb8
c4GameStart(PxArena* arena, C4Server* server, C4GameState *game, C4ServerConfig config)
{
    game->players = c4GamePlayerListReserve(arena, config.players);

    if (c4GamePlayerListLength(&game->players) == 0) return 0;

    game->board = c4GameBoardReserve(arena, config.board_width,
        config.board_height);

    if (c4GameBoardLength(&game->board) == 0) return 0;

    while (c4GamePlayerListIsFull(&game->players) == 0) {
        pxiword size = c4GamePlayerListSize(&game->players);

        C4Message  message = c4GameAccept(arena, server, game, config);
        C4Session* session = c4ServerGetOr(server, size, 0);

        if (message.type == C4_MESSAGE_NONE || session == 0)
            continue;

        C4GamePlayer player = {
            .code  = size + 1,
            .color = size + 1,
            .shape = size + PX_ASCII_LOWER_A,
        };

        pxb8 state = c4GamePlayerListInsert(&game->players, player);

        if (state == 0) return 0;

        message = c4MsgPlayerAccept(config.players,
            player.code, player.color, player.shape,
            config.board_width, config.board_height);

        c4SessionWrite(session, arena, message);

        c4ServerBroadcast(server, arena, session,
            c4MsgPlayerData(player.code, player.color, player.shape));

        for (pxiword i = 0; i < size; i += 1) {
            c4GamePlayerListRead(&game->players, i, &player);

            c4SessionWrite(session, arena,
                c4MsgPlayerData(player.code, player.color, player.shape));
        }
    }

    return 1;
}

pxb8
c4GameLoop(PxArena* arena, C4Server* server, C4GameState* game)
{
    pxiword offset = pxArenaOffset(arena);
    pxiword size   = c4GamePlayerListSize(&game->players);
    pxb8    active = 1;

    c4GameBoardShow(game);

    c4ServerBroadcast(server, arena, 0, c4MsgGameStart());

    while (active != 0) {
        C4Session* session = c4ServerGetOr(server, game->turn, 0);

        if (session == 0) return 0;

        c4ServerBroadcast(server, arena, 0,
            c4MsgPlayerTurn(game->turn + 1));

        C4Message message = c4SessionRead(session, arena);

        switch (message.type) {
            case C4_MESSAGE_PLAYER_CHOICE: {
                pxiword column = message.player_choice.board_column;
                pxuword code   = message.player_choice.player_code;

                pxiword height = c4GameBoardHeight(&game->board, column);

                if (c4GameBoardInsert(&game->board, column, code) != 0) {
                    c4ServerBroadcast(server, arena, session, message);

                    if (c4GamePlayerHasWon(game, column, height, 4) == 0) {
                        if (c4GameBoardIsFull(&game->board))
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
                        c4MsgPlayerSkip(game->turn + 1));
                }
            } break;

            default:
                c4ServerBroadcast(server, arena, session,
                    c4MsgPlayerSkip(game->turn + 1));
            break;
        }

        game->turn = (game->turn + 1) % size;

        c4GameBoardShow(game);

        pxArenaRewind(arena, offset);
    }

    return 1;
}

pxb8
c4GameStop(PxArena* arena, C4Server* server, C4GameState* game)
{
    c4ServerStop(server);

    return 1;
}

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

                pxU16FromString8(&config.port, 10, options, arg);
            }

            if (pxString8BeginsWith(arg, pxs8("--board-width=")) != 0) {
                arg = pxString8TrimPrefix(arg, pxs8("--board-width="));
                arg = pxString8TrimSpaces(arg);

                pxUWordFromString8(&config.board_width, 10, options, arg);
            }

            if (pxString8BeginsWith(arg, pxs8("--board-height=")) != 0) {
                arg = pxString8TrimPrefix(arg, pxs8("--board-height="));
                arg = pxString8TrimSpaces(arg);

                pxUWordFromString8(&config.board_height, 10, options, arg);
            }

            if (pxString8BeginsWith(arg, pxs8("--players=")) != 0) {
                arg = pxString8TrimPrefix(arg, pxs8("--players="));
                arg = pxString8TrimSpaces(arg);

                pxUWordFromString8(&config.players, 10, options, arg);
            }
        }
    }

    C4Server server = c4ServerMake(&arena, config.players,
        config.type);

    pxb8 state = c4ServerStart(&server,
        pxAddressAny(config.type), config.port);

    if (state == 0) return 1;

    C4GameState game = {0};

    if (c4GameStart(&arena, &server, &game, config) == 0)
        return 1;

    c4GameLoop(&arena, &server, &game);
    c4GameStop(&arena, &server, &game);

    pxNetworkStop();
}
