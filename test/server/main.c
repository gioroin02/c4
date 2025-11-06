#include "../../code/server/export.h"

#include <stdio.h>

typedef struct C4_Server_Config
{
    Pax_Addr_Kind kind;
    paxuword      port;

    paxuword player_amount;

    paxuword board_width;
    paxuword board_height;
}
C4_Server_Config;

typedef struct C4_Game
{
    C4_Game_Board       board;
    C4_Game_Player_List player_list;
    paxiword            player_turn;
}
C4_Game;

/*
pxuword
c4GamePlayerHasWon(C4_Game* self, paxiword x, paxiword y, paxiword length)
{
    #define DIRS 8

    paxiword xs[DIRS] = {+1, +1,  0, -1, -1, -1,  0, +1};
    paxiword ys[DIRS] = { 0, +1, +1, +1,  0, -1, -1, -1};

    pxuword value = 0;

    for (paxiword i = 0; i < DIRS; i += 1) {
        paxiword j = (i + 4) % DIRS;

        paxiword forw = c4GameBoardContainsLine(
            &self->board, x, y, xs[i], ys[i], &value);

        paxiword back = c4GameBoardContainsLine(
            &self->board, x, y, xs[j], ys[j], &value);

        if (forw + back > length) return value;
    }

    return 0;
}

void
c4GameBoardLog(C4_Game* game)
{
    printf("#");

    for (paxiword i = 0; i < game->board.width; i += 1)
        printf("---#");

    printf("\n");

    for (paxiword r = game->board.height; r > 0; r -= 1) {
        printf("| ");

        for (paxiword c = 0; c < game->board.width; c += 1) {
            pxuword item = c4GameBoardReadOr(&game->board, c, r - 1, 0);

            C4_GamePlayer player = {0};

            if (item > 0) {
                paxiword index = 0;

                if (c4GamePlayerListFind(&game->player_amount, item, &index))
                    c4GamePlayerListRead(&game->player_amount, index, &player);
            }

            if (player.code != 0)
                printf("%s%c%s | ", FRONTS[player.color], player.shape, FRONTS[0]);
            else
                printf("  | ");
        }

        printf("\n");
    }

    printf("#");

    for (paxiword i = 0; i < game->board.width; i += 1)
        printf("---#");

    printf("\n");
}

C4Msg
c4GameAccept(PxArena* arena, C4_Server* server, C4_Game* game, C4_Server_Config config)
{
    paxiword    offset  = pxArenaOffset(arena);
    C4Session* session = c4SessionOpen(server, arena);

    if (session == 0) return (C4Msg) {0};

    session->request  = pxBuffer8Reserve(arena, PX_MEMORY_KIB);
    session->response = pxBuffer8Reserve(arena, PX_MEMORY_KIB);

    C4Msg message = c4SessionRead(session, arena);

    if (message.type == C4_MESSAGE_PLAYER_JOIN)
        return message;

    c4SessionClose(server, session);

    pxArenaRewind(arena, offset);

    return (C4Msg) {0};
}

paxb8
c4GameStart(PxArena* arena, C4_Server* server, C4_Game *game, C4_Server_Config config)
{
    game->player_amount = c4GamePlayerListReserve(arena, config.player_amount);

    if (c4GamePlayerListLength(&game->player_amount) == 0) return 0;

    game->board = c4GameBoardReserve(arena, config.board_width,
        config.board_height);

    if (c4GameBoardLength(&game->board) == 0) return 0;

    while (c4GamePlayerListIsFull(&game->player_amount) == 0) {
        paxiword size = c4GamePlayerListSize(&game->player_amount);

        C4Msg  message = c4GameAccept(arena, server, game, config);
        C4Session* session = c4ServerGetOr(server, size, 0);

        if (message.type == C4_MESSAGE_NONE || session == 0)
            continue;

        C4_GamePlayer player = {
            .code  = size + 1,
            .color = size + 1,
            .shape = size + PX_ASCII_LOWER_A,
        };

        paxb8 state = c4GamePlayerListInsert(&game->player_amount, player);

        if (state == 0) return 0;

        message = c4MsgPlayerAccept(config.player_amount,
            player.code, player.color, player.shape,
            config.board_width, config.board_height);

        c4SessionWrite(session, arena, message);

        c4ServerBroadcast(server, arena, session,
            c4MsgPlayerData(player.code, player.color, player.shape));

        for (paxiword i = 0; i < size; i += 1) {
            c4GamePlayerListRead(&game->player_amount, i, &player);

            c4SessionWrite(session, arena,
                c4MsgPlayerData(player.code, player.color, player.shape));
        }
    }

    return 1;
}

paxb8
c4GameLoop(PxArena* arena, C4_Server* server, C4_Game* game)
{
    paxiword offset = pxArenaOffset(arena);
    paxiword size   = c4GamePlayerListSize(&game->player_amount);
    paxb8    active = 1;

    c4GameBoardLog(game);

    c4ServerBroadcast(server, arena, 0, c4MsgGameStart());

    while (active != 0) {
        C4Session* session = c4ServerGetOr(server, game->turn, 0);

        if (session == 0) return 0;

        c4ServerBroadcast(server, arena, 0,
            c4MsgPlayerTurn(game->turn + 1));

        C4Msg message = c4SessionRead(session, arena);

        switch (message.type) {
            case C4_MESSAGE_PLAYER_CHOICE: {
                paxiword column = message.player_choice.board_column;
                pxuword code   = message.player_choice.player_code;

                paxiword height = c4GameBoardHeight(&game->board, column);

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

        c4GameBoardLog(game);

        pxArenaRewind(arena, offset);
    }

    return 1;
}

paxb8
c4GameStop(PxArena* arena, C4_Server* server, C4_Game* game)
{
    c4ServerStop(server);

    return 1;
}
*/

int
main(int argc, char** argv)
{
    Pax_Arena arena = pax_memory_reserve(32);

    if (pax_network_load() == 0) return 1;

    C4_Server_Config config = {0};

    config.kind         = PAX_ADDR_KIND_IP4;
    config.port         = 50000;
    config.board_width  = 7;
    config.board_height = 5;
    config.player_amount      = 2;

    Pax_Format_Radix radix = PAX_FORMAT_RADIX_10;
    Pax_Format_Flag  flags = PAX_FORMAT_FLAG_NONE;

    for (paxiword i = 1; i < argc; i += 1) {
        Pax_String8 argument = pax_string8_from_memory(argv[i], 32, pax_size(paxu8));

        if (pax_string8_begins_with(argument, pax_str8("--server-ipv6")) != 0)
            config.kind = PAX_ADDR_KIND_IP6;

        if (pax_string8_begins_with(argument, pax_str8("--port=")) != 0) {
            argument = pax_string8_trim_prefix(argument, pax_str8("--port="));
            argument = pax_string8_trim_spaces(argument);

            pax_unsigned_from_string8(argument, &config.port, radix, flags);
        }

        if (pax_string8_begins_with(argument, pax_str8("--board-width=")) != 0) {
            argument = pax_string8_trim_prefix(argument, pax_str8("--board-width="));
            argument = pax_string8_trim_spaces(argument);

            pax_unsigned_from_string8(argument, &config.board_width, radix, flags);
        }

        if (pax_string8_begins_with(argument, pax_str8("--board-height=")) != 0) {
            argument = pax_string8_trim_prefix(argument, pax_str8("--board-height="));
            argument = pax_string8_trim_spaces(argument);

            pax_unsigned_from_string8(argument, &config.board_height, radix, flags);
        }

        if (pax_string8_begins_with(argument, pax_str8("--player-amount=")) != 0) {
            argument = pax_string8_trim_prefix(argument, pax_str8("--player-amount="));
            argument = pax_string8_trim_spaces(argument);

            pax_unsigned_from_string8(argument, &config.player_amount, radix, flags);
        }
    }

    C4_Server server =
        c4_server_create(&arena, config.player_amount, config.kind);

    paxb8 state = c4_server_start(&server,
        pax_addr_any(config.kind), config.port);

    if (state == 0) return 1;

    C4_Game game = {0};

    printf("CREATE, sleeping...\n");

    pax_current_thread_sleep(5000);

    printf("DESTROY\n");

    pax_network_unload();
}
