#include "../import.h"

typedef struct C4GameConfig
{
    PxAddr  server_addr;
    pxuword server_port;

    pxiword player_amount;

    pxiword board_width;
    pxiword board_height;
}
C4GameConfig;

typedef enum C4GameState
{
    C4_GAME_NONE,

    C4_GAME_JOINING,
    C4_GAME_STARTING,
    C4_GAME_PLAYING,
    C4_GAME_WAITING,
    C4_GAME_CHOOSING,
    C4_GAME_STOPPING,
}
C4GameState;

typedef struct C4Game
{
    C4NetworkServer network_server;

    C4GameConfig game_config;
    C4GameState  game_state;
    C4GameBoard  game_board;

    C4GamePlayerList game_player_list;
}
C4Game;

pxb8
c4GameStart(C4Game* self, PxArena* arena)
{
    self->network_server = c4NetworkServerCreate(arena, 16, self->game_config.server_addr.type);

    if (c4NetworkServerStart(&self->network_server, self->game_config.server_addr, self->game_config.server_port) == 0)
        return 0;

    for (pxiword i = 0;i < self->game_config.player_amount; i += 1) {
        C4NetworkAcceptorCtxt* network_acceptor_ctxt =
            c4NetworkServerAcceptorCtxt(&self->network_server, arena);


    }

    self->game_player_list = c4GamePlayerListReserve(arena, self->game_config.player_amount);

    if (c4GamePlayerListLength(&self->game_player_list) <= 0) return 0;

    self->game_board = c4GameBoardReserve(arena,
        self->game_config.board_width, self->game_config.board_height);

    if (c4GameBoardLength(&self->game_board) <= 0) return 0;

    return 1;
}

void
c4GameStop(C4Game* self)
{

}

pxb8
c4GameIsActive(C4Game* self)
{
    return 0;
}

void
c4GameNetworkInput(C4Game* self, PxArena* arena, C4NetworkMsg message)
{

}

void
c4GameNetworkOutput(C4Game* self, PxArena* arena, pxf32 time)
{

}

void
c4GameInput(C4Game* self, PxArena* arena)
{
    C4NetworkMsg network = {0};

    while (c4networkServerReadMsg(&self->network_server, &network) != 0)
        c4GameNetworkInput(self, arena, network);
}

void
c4GameOutput(C4Game* self, PxArena* arena, pxf32 time)
{
    c4GameNetworkOutput(self, arena, time);
}

void
c4GameTick(C4Game* self, PxArena* arena, pxf32 time, pxf32 slice)
{

}

void
c4GameUpdate(C4Game* self, PxArena* arena, pxf32 time)
{

}

pxb8
c4GamePlay(C4Game* self, PxArena* arena, pxf32 ticks)
{
    PxClock clock = pxClockCreate(arena);

    if (c4GameStart(self, arena) == 0) return 0;

    pxf32 total = 0;
    pxf32 slice = 1.0 / px_max(1.0, ticks);
    pxf32 time  = 0;

    while (c4GameIsActive(self) != 0) {
        time += pxClockElapsed(clock);

        c4GameInput(self, arena);

        while (time >= slice) {
            c4GameTick(self, arena, total, slice);

            time  -= slice;
            total += slice;
        }

        c4GameUpdate(self, arena, total);
        c4GameOutput(self, arena, total);

        pxCurrentThreadSleep(10);
    }

    c4GameStop(self);

    return 1;
}

#define C4_SERVER_ARG_AUTOMATIC   pxs8("+auto")
#define C4_SERVER_ARG_SERVER_IP4  pxs8("+server-ipv4")
#define C4_SERVER_ARG_SERVER_IP6  pxs8("+server-ipv6")
#define C4_SERVER_ARG_SERVER_PORT pxs8("+server-port:")

#define C4_SERVER_ARG_PLAYER_AMOUNT pxs8("+player-amount:")

#define C4_SERVER_ARG_BOARD_WIDTH  pxs8("+board-width:")
#define C4_SERVER_ARG_BOARD_HEIGHT pxs8("+board-height:")

int
main(int argc, char** argv)
{
    C4Game game = {0};

    game.game_config.server_addr   = pxAddrLocalhost(PX_ADDR_TYPE_IP4);
    game.game_config.server_port   = 8000;
    game.game_config.player_amount = 2;
    game.game_config.board_width   = 7;
    game.game_config.board_height  = 5;

    for (pxiword i = 1; i < argc; i += 1) {
        PxFormatRadix radix = PX_FORMAT_RADIX_10;
        PxFormatFlag  flags = PX_FORMAT_FLAG_NONE;

        PxString8 argument = pxString8FromMemory(argv[i], 32);

        if (pxString8IsEqual(argument, C4_SERVER_ARG_SERVER_IP4) != 0)
            game.game_config.server_addr = pxAddrLocalhost(PX_ADDR_TYPE_IP4);

        if (pxString8IsEqual(argument, C4_SERVER_ARG_SERVER_IP6) != 0)
            game.game_config.server_addr = pxAddrLocalhost(PX_ADDR_TYPE_IP6);

        if (pxString8BeginsWith(argument, C4_SERVER_ARG_SERVER_PORT) != 0) {
            argument = pxString8TrimPrefix(argument, C4_SERVER_ARG_SERVER_PORT);
            argument = pxString8TrimSpaces(argument);

            pxUnsignedFromString8(argument,
                &game.game_config.server_port, radix, flags);
        }

        if (pxString8BeginsWith(argument, C4_SERVER_ARG_PLAYER_AMOUNT) != 0) {
            argument = pxString8TrimPrefix(argument, C4_SERVER_ARG_PLAYER_AMOUNT);
            argument = pxString8TrimSpaces(argument);

            pxUnsignedFromString8(argument,
                &game.game_config.player_amount, radix, flags);
        }

        if (pxString8BeginsWith(argument, C4_SERVER_ARG_BOARD_WIDTH) != 0) {
            argument = pxString8TrimPrefix(argument, C4_SERVER_ARG_BOARD_WIDTH);
            argument = pxString8TrimSpaces(argument);

            pxUnsignedFromString8(argument,
                &game.game_config.board_width, radix, flags);
        }

        if (pxString8BeginsWith(argument, C4_SERVER_ARG_BOARD_HEIGHT) != 0) {
            argument = pxString8TrimPrefix(argument, C4_SERVER_ARG_BOARD_HEIGHT);
            argument = pxString8TrimSpaces(argument);

            pxUnsignedFromString8(argument,
                &game.game_config.board_height, radix, flags);
        }
    }

    PxArena arena = pxMemoryReserve(16);

    if (pxNetworkStart() == 0) return 1;

    if (c4GamePlay(&game, &arena, 64.0) == 0)
        return 1;

    pxNetworkStop();

    return 0;
}
