#include "../../code/client/export.h"

#include <stdio.h>

typedef struct C4_Client_Config
{
    Pax_Addr server_addr;
    paxuword server_port;
    paxiword automatic;
}
C4_Client_Config;

typedef struct C4_Game
{
    C4_Game_Board       board;
    C4_Game_Player_List player_list;
}
C4_Game;

/*
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

            C4GamePlayer player = {0};

            if (item > 0) {
                paxiword index = 0;

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

    for (paxiword i = 0; i < game->board.width; i += 1)
        printf("---#");

    printf("\n");
}

paxb8
c4GameStart(PxArena* arena, C4_Client* client, C4_Game* game, C4_Client_Config config)
{
    C4Msg message = {0};

    c4ClientWrite(client, arena, c4MsgPlayerJoin(config.automatic));

    message = c4ClientRead(client, arena);

    if (message.type != C4_MESSAGE_PLAYER_ACCEPT) return 0;

    game->players = c4GamePlayerListReserve(arena,
        message.player_accept.player_number);

    if (c4GamePlayerListLength(&game->players) == 0) return 0;

    game->board = c4GameBoardReserve(arena,
        message.player_accept.board_width,
        message.player_accept.board_height);

    if (c4GameBoardLength(&game->board) == 0) return 0;

    C4GamePlayer player = {
        .code  = message.player_accept.player_code,
        .color = message.player_accept.piece_color,
        .shape = message.player_accept.piece_shape,
    };

    if (c4GamePlayerListInsert(&game->players, player) == 0)
        return 0;

    message = c4ClientRead(client, arena);

    while (message.type != C4_MESSAGE_GAME_START) {
        if (message.type != C4_MESSAGE_PLAYER_DATA)
            return 0;

        player = (C4GamePlayer) {
            .code  = message.player_data.player_code,
            .color = message.player_data.piece_color,
            .shape = message.player_data.piece_shape,
        };

        if (c4GamePlayerListInsert(&game->players, player) == 0)
            return 0;

        message = c4ClientRead(client, arena);
    }

    return 1;
}

paxb8
c4GameLoop(PxArena* arena, C4_Client* client, C4_Game* game)
{
    PxBuffer8 buffer = pxBuffer8Reserve(arena, PX_MEMORY_KIB);
    PxReader  reader = fileReader(stdin, &buffer);

    C4GamePlayer player = {0};
    paxb8         active = 1;
    paxiword      offset = pxArenaOffset(arena);

    c4GamePlayerListRead(&game->players, 0, &player);

    c4GameBoardLog(game);

    while (active != 0) {
        C4Msg message = c4ClientRead(client, arena);

        switch (message.type) {
            case C4_MESSAGE_PLAYER_TURN: {
                if (message.player_turn.player_code != player.code) {
                    message = c4ClientRead(client, arena);

                    switch (message.type) {
                        case C4_MESSAGE_PLAYER_CHOICE: {
                            paxiword column = message.player_choice.board_column;
                            pxuword code   = message.player_choice.player_code;

                            c4GameBoardInsert(&game->board, column, code);
                        } break;

                        case C4_MESSAGE_PLAYER_SKIP: break;

                        default: active = 0; break;
                    }
                } else {
                    PxFormatOption options =
                        PX_FORMAT_OPTION_LEADING_PLUS |
                        PX_FORMAT_OPTION_LEADING_ZERO;

                    paxiword column = 0;
                    paxb8    state  = 0;

                    while (state == 0) {
                        column = fileReadIWord(pax_str8("->"),
                            &reader, arena, 10, options) - 1;

                        state = c4GameBoardInsert(&game->board, column,
                            player.code);
                    }

                    c4ClientWrite(client, arena,
                        c4MsgPlayerChoice(player.code, column));
                }
            } break;

            case C4_MESSAGE_GAME_STOP: {
                if (message.game_stop.player_code == player.code)
                    printf("YOU WON!!!\n");
                else
                    printf("You lost...\n");

                active = 0;
            } break;

            default: active = 0; break;
        }

        c4GameBoardLog(game);

        pxArenaRewind(arena, offset);
    }

    return 1;
}

paxb8
c4GameStop(PxArena* arena, C4_Client* client, C4_Game* game)
{
    c4ClientStop(client);

    return 1;
}
*/

int
main(int argc, char** argv)
{
    Pax_Arena arena = pax_memory_reserve(32);

    if (pax_network_load() == 0) return 1;

    C4_Client_Config config = {0};

    config.server_addr = pax_addr_localhost(PAX_ADDR_KIND_IP4);
    config.server_port = 50000;
    config.automatic   = 0;

    Pax_Format_Radix radix = PAX_FORMAT_RADIX_10;
    Pax_Format_Flag  flags = PAX_FORMAT_FLAG_NONE;

    for (paxiword i = 1; i < argc; i += 1) {
        Pax_String8 argument =
            pax_string8_from_memory(argv[i], 32, pax_size(paxu8));

        if (pax_string8_begins_with(argument, pax_str8("--server-ipv4=")) != 0) {
            argument = pax_string8_trim_prefix(argument, pax_str8("--server-ipv4="));
            argument = pax_string8_trim_spaces(argument);

            pax_addr_from_string8(argument, &config.server_addr, PAX_ADDR_KIND_IP4);
        }

        if (pax_string8_begins_with(argument, pax_str8("--server-ipv6=")) != 0) {
            argument = pax_string8_trim_prefix(argument, pax_str8("--server-ipv6="));
            argument = pax_string8_trim_spaces(argument);

            pax_addr_from_string8(argument, &config.server_addr, PAX_ADDR_KIND_IP6);
        }

        if (pax_string8_begins_with(argument, pax_str8("--server-port=")) != 0) {
            argument = pax_string8_trim_prefix(argument, pax_str8("--server-port="));
            argument = pax_string8_trim_spaces(argument);

            pax_unsigned_from_string8(argument, &config.server_port, radix, flags);
        }

        if (pax_string8_is_equal(argument, pax_str8("--automatic")) != 0)
            config.automatic = 1;
    }

    C4_Client client =
        c4_client_create(&arena, config.server_addr.kind);

    paxb8 state = c4_client_start(&client,
        config.server_addr, config.server_port);

    if (state == 0) return 1;

    Pax_Scanner scanner = pax_scanner_create(&arena, 1024,
        pax_source_from_socket_tcp(&arena, client.socket));

    client.reader = pax_json_reader_create(&arena, 4, scanner);

    client.writer = pax_json_writer_create(&arena, 4,
        pax_target_from_socket_tcp(&arena, client.socket));

    C4_Game game = {0};

    printf("CREATE, sleeping...\n");

    pax_current_thread_sleep(5000);

    printf("DESTROY\n");

    pax_network_unload();
}
