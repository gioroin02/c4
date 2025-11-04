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

typedef struct C4ClientConfig
{
    PxAddress server_addr;
    pxu16     server_port;
    pxb32     automatic;
}
C4ClientConfig;

typedef struct C4GameState
{
    C4GameBoard      board;
    C4GamePlayerList players;
}
C4GameState;

pxiword
fileRead(void* self, PxBuffer8* buffer)
{
    pxBuffer8Normalize(buffer);

    pxu8*   memory = buffer->memory + buffer->size;
    pxiword size   = buffer->length - buffer->size;

    if (size <= 0) return 0;

    pxiword amount = 0;

    fgets(pxCast(char*, memory), size, self);

    while (memory[amount] != 0)
        amount += 1;

    buffer->size += amount;
    buffer->tail  = (buffer->tail + amount) % buffer->length;

    return amount;
}

PxReader
fileReader(void* self, PxBuffer8* buffer)
{
    if (self == 0 || buffer == 0)
        return (PxReader) {0};

    return (PxReader) {
        .buffer = buffer,
        .ctxt   = self,
        .proc   = &fileRead,
    };
}

pxiword
fileReadIWord(PxString8 string, PxReader* reader, PxArena* arena, pxuword radix, PxFormatOption options)
{
    pxiword result = 0;
    pxiword offset = pxArenaOffset(arena);
    pxiword length = reader->buffer->length;
    pxb8    state  = 0;

    while (state == 0) {
        printf("%.*s ", pxCast(int, string.length),
            string.memory);

        PxString8 line =
            pxReaderLine(reader, arena, length);

        state = pxIWordFromString8(&result,
            radix, options, line);

        pxArenaOffset(arena);
    }

    return result;
}

void
c4GameBoardLog(C4GameState* game)
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

pxb8
c4GameStart(PxArena* arena, C4Client* client, C4GameState* game, C4ClientConfig config)
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

pxb8
c4GameLoop(PxArena* arena, C4Client* client, C4GameState* game)
{
    PxBuffer8 buffer = pxBuffer8Reserve(arena, PX_MEMORY_KIB);
    PxReader  reader = fileReader(stdin, &buffer);

    C4GamePlayer player = {0};
    pxb8         active = 1;
    pxiword      offset = pxArenaOffset(arena);

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
                            pxiword column = message.player_choice.board_column;
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

                    pxiword column = 0;
                    pxb8    state  = 0;

                    while (state == 0) {
                        column = fileReadIWord(pxs8("->"),
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

pxb8
c4GameStop(PxArena* arena, C4Client* client, C4GameState* game)
{
    c4ClientStop(client);

    return 1;
}

int
main(int argc, char** argv)
{
    PxArena arena = pxMemoryReserve(32);

    if (pxNetworkStart() == 0) return 1;

    C4ClientConfig config = {
        .server_addr = pxAddressLocalhost(PX_ADDRESS_TYPE_IP4),
        .server_port = 50000,
        .automatic   = 0,
    };

    if (argc > 1) {
        PxFormatOption options = PX_FORMAT_OPTION_NONE;

        for (pxiword i = 1; i < argc; i += 1) {
            PxString8 arg = pxString8FromMemory(argv[i], 32);

            if (pxString8BeginsWith(arg, pxs8("--server-addr=")) != 0) {
                arg = pxString8TrimPrefix(arg, pxs8("--server-addr="));
                arg = pxString8TrimSpaces(arg);

                pxAddressFromString8(&config.server_addr,
                    PX_ADDRESS_TYPE_IP4, arg);
            }

            if (pxString8BeginsWith(arg, pxs8("--server-port=")) != 0) {
                arg = pxString8TrimPrefix(arg, pxs8("--server-port="));
                arg = pxString8TrimSpaces(arg);

                pxU16FromString8(&config.server_port, 10, options, arg);
            }

            if (pxString8IsEqual(arg, pxs8("--automatic")) != 0)
                config.automatic = 1;
        }
    }

    C4Client client = c4ClientMake(&arena, PX_ADDRESS_TYPE_IP4);

    pxb8 state = c4ClientStart(&client, config.server_addr,
        config.server_port);

    if (state == 0) return 1;

    client.request  = pxBuffer8Reserve(&arena, PX_MEMORY_KIB);
    client.response = pxBuffer8Reserve(&arena, PX_MEMORY_KIB);

    C4GameState game = {0};

    if (c4GameStart(&arena, &client, &game, config) == 0)
        return 1;

    c4GameLoop(&arena, &client, &game);
    c4GameStop(&arena, &client, &game);

    pxNetworkStop();
}
