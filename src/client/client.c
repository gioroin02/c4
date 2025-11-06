#include "import.h"

void
c4ConsoleBatchPaintTile(C4ConsoleBatch* frame, PxArena* arena, pxiword x, pxiword y, pxi32 unicode, PxConsoleColor text, PxConsoleColor back)
{
    c4ConsoleBatchPaintCell(frame, x + 0, y + 0, PX_ASCII_SHARP, text, back);
    c4ConsoleBatchPaintCell(frame, x + 4, y + 0, PX_ASCII_SHARP, text, back);
    c4ConsoleBatchPaintCell(frame, x + 0, y + 2, PX_ASCII_SHARP, text, back);
    c4ConsoleBatchPaintCell(frame, x + 4, y + 2, PX_ASCII_SHARP, text, back);

    for (pxiword i = 1; i < 4; i += 1)
        c4ConsoleBatchPaintCell(frame, x + i, y + 0, PX_ASCII_MINUS, text, back);

    for (pxiword i = 1; i < 4; i += 1)
        c4ConsoleBatchPaintCell(frame, x + i, y + 2, PX_ASCII_MINUS, text, back);

    for (pxiword i = 1; i < 2; i += 1)
        c4ConsoleBatchPaintCell(frame, x + 0, y + i, PX_ASCII_PIPE, text, back);

    for (pxiword i = 1; i < 2; i += 1)
        c4ConsoleBatchPaintCell(frame, x + 4, y + i, PX_ASCII_PIPE, text, back);

    if (unicode >= 32)
        c4ConsoleBatchPaintCell(frame, x + 2, y + 1, unicode, text, back);
}

void
c4ConsoleBatchPaintBoard(C4ConsoleBatch* frame, PxArena* arena, pxiword x, pxiword y, C4GameBoard* game_board)
{
    for (pxiword j = 0; j < game_board->height; j += 1) {
        for (pxiword i = 0; i < game_board->width; i += 1) {
            pxuword item    = c4GameBoardGetOr(game_board, i, game_board->height - j - 1, 0);
            pxi32   unicode = 0;

            if (item != 0) unicode = PX_ASCII_COMMERCIAL;

            c4ConsoleBatchPaintTile(frame, arena, x + i * 4, y + j * 2,
                unicode, C4_COLOR_16_WHITE, C4_COLOR_16_BLACK);
        }
    }
}

void
c4ConsoleBatchPaintRange(C4ConsoleBatch* frame, PxArena* arena, pxiword x, pxiword y, pxiword dx, pxiword dy, pxiword start, pxiword stop)
{
    pxiword offset = pxArenaOffset(arena);

    PxFormatRadix radix = PX_FORMAT_RADIX_10;
    PxFormatFlag  flags = PX_FORMAT_FLAG_NONE;

    for (pxiword i = start; i < stop; i += 1) {
        PxString8 string = pxString8FromInteger(arena, i, radix, flags);

        for (pxiword j = 0; j < string.length; j += 1) {
            pxi32 unicode = string.memory[j];

            c4ConsoleBatchPaintCell(frame, x + 2 + j, y + 1,
                unicode, C4_COLOR_16_WHITE, C4_COLOR_16_BLACK);
        }

        x += dx * 4;
        y += dy * 2;

        pxArenaRewind(arena, offset);
    }
}

typedef struct C4GameConfig
{
    PxAddr  server_addr;
    pxuword server_port;
    pxb8    automatic;
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
    C4NetworkSession network_session;

    C4ConsoleBatch console_batch;
    C4Console      console;

    C4GameConfig game_config;
    C4GameState  game_state;
    C4GameBoard  game_board;

    C4GamePlayerList game_player_list;

    pxb8    input_insert;
    pxiword input_column;
    pxb8    input_move_left;
    pxb8    input_move_right;
}
C4Game;

pxb8
c4GameStart(C4Game* self, PxArena* arena)
{
    self->network_session = c4NetworkSessionCreate(arena, 16, self->game_config.server_addr.type);

    if (c4NetworkSessionConnect(&self->network_session, self->game_config.server_addr, self->game_config.server_port) == 0)
        return 0;

    C4NetworkReaderCtxt* network_reader_ctxt =
        c4NetworkSessionReaderCtxt(&self->network_session, arena, PX_MEMORY_KIB);

    C4NetworkWriterCtxt* network_writer_ctxt =
        c4NetworkSessionWriterCtxt(&self->network_session, arena, PX_MEMORY_KIB);

    PxThread network_reader = pxThreadCreate(arena, network_reader_ctxt, &c4NetworkReaderProc);
    PxThread network_writer = pxThreadCreate(arena, network_writer_ctxt, &c4NetworkWriterProc);

    if (network_reader == 0 || network_reader == 0) return 0;

    self->console = c4ConsoleCreate(arena, 16);

    C4ConsoleReaderCtxt* console_reader_ctxt =
        c4ConsoleReaderCtxt(&self->console, arena, PX_MEMORY_KIB);

    PxThread console_reader = pxThreadCreate(arena, console_reader_ctxt, &c4ConsoleReaderProc);

    if (console_reader == 0) return 0;

    pxThreadDetach(network_reader);
    pxThreadDetach(network_writer);
    pxThreadDetach(console_reader);

    return 1;
}

void
c4GameStop(C4Game* self)
{

}

pxb8
c4GameIsActive(C4Game* self)
{
    return self->game_state != C4_GAME_STOPPING ? 1 : 0;
}

void
c4GameNetworkInput(C4Game* self, PxArena* arena, C4NetworkMsg message)
{
    switch (self->game_state) {
        case C4_GAME_JOINING: {
            if (message.type == C4_NETWORK_MSG_PLAYER_ACCEPT) {
                self->game_player_list = c4GamePlayerListReserve(arena,
                    message.player_accept.player_amount);

                C4GamePlayer player = c4GamePlayer(
                    message.player_accept.player_ident,
                    message.player_accept.player_text,
                    message.player_accept.player_color);

                if (c4GamePlayerListLength(&self->game_player_list) <= 0)
                    self->game_state = C4_GAME_STOPPING;

                if (c4GamePlayerListInsert(&self->game_player_list, player) == 0)
                    self->game_state = C4_GAME_STOPPING;

                self->game_board = c4GameBoardReserve(arena,
                    message.player_accept.board_width,
                    message.player_accept.board_height);

                if (c4GameBoardLength(&self->game_board) <= 0)
                    self->game_state = C4_GAME_STOPPING;

                self->game_state = C4_GAME_STARTING;
            } else
                self->game_state = C4_GAME_STOPPING;
        } break;

        case C4_GAME_STARTING: {
            if (message.type == C4_NETWORK_MSG_PLAYER_DATA) {
                C4GamePlayer player = c4GamePlayer(
                    message.player_data.player_ident,
                    message.player_data.player_text,
                    message.player_data.player_color);

                if (c4GamePlayerListInsert(&self->game_player_list, player) == 0)
                    self->game_state = C4_GAME_STOPPING;
            }

            if (message.type == C4_NETWORK_MSG_GAME_START)
                self->game_state = C4_GAME_PLAYING;

            if (self->game_state == C4_GAME_STARTING)
                self->game_state = C4_GAME_STOPPING;
        } break;

        case C4_GAME_PLAYING: {
            if (message.type == C4_NETWORK_MSG_PLAYER_TURN) {
                C4GamePlayer player = c4GamePlayerListGetOr(
                    &self->game_player_list, 0, (C4GamePlayer) {0});

                if (message.player_turn.player_ident == player.ident)
                    self->game_state = C4_GAME_CHOOSING;
                else
                    self->game_state = C4_GAME_WAITING;
            }

            if (message.type == C4_NETWORK_MSG_GAME_STOP)
                self->game_state = C4_GAME_STOPPING;

            if (self->game_state == C4_GAME_PLAYING)
                self->game_state = C4_GAME_STOPPING;
        } break;

        case C4_GAME_WAITING: {
            if (message.type == C4_NETWORK_MSG_PLAYER_CHOICE) {
                pxiword ident  = message.player_choice.player_ident;
                pxiword column = message.player_choice.board_column;

                if (c4GameBoardInsert(&self->game_board, column, ident) != 0)
                    self->game_state = C4_GAME_PLAYING;
                else
                    self->game_state = C4_GAME_STOPPING;
            }

            if (message.type == C4_NETWORK_MSG_PLAYER_SKIP)
                self->game_state = C4_GAME_PLAYING;

            if (self->game_state == C4_GAME_WAITING)
                self->game_state = C4_GAME_STOPPING;
        } break;

        default: break;
    }
}

void
c4GameNetworkOutput(C4Game* self, PxArena* arena, pxf32 time)
{
    switch (self->game_state) {
        case C4_GAME_NONE: {
            pxb8 automatic = self->game_config.automatic;

            C4NetworkMsg message = c4NetworkMsgPlayerJoin(automatic);

            if (c4NetworkSessionWriteMsg(&self->network_session, message) != 0)
                self->game_state = C4_GAME_JOINING;
            else
                self->game_state = C4_GAME_STOPPING;
        } break;

        case C4_GAME_CHOOSING: {
            C4GamePlayer player = c4GamePlayerListGetOr(
                &self->game_player_list, 0, (C4GamePlayer) {0});

            if (self->input_insert == 0) break;

            pxiword ident  = player.ident;
            pxiword column = self->input_column;

            if (c4GameBoardInsert(&self->game_board, column, ident) == 0)
                break;

            C4NetworkMsg message = c4NetworkMsgPlayerChoice(ident, column);

            if (c4NetworkSessionWriteMsg(&self->network_session, message) != 0)
                self->game_state = C4_GAME_PLAYING;
            else
                self->game_state = C4_GAME_STOPPING;
        } break;

        default: break;
    }
}

void
c4GameConsoleInput(C4Game* self, PxArena* arena, PxConsoleMsg message)
{
    switch (message.type) {
        case PX_CONSOLE_MSG_UNICODE: {
            if (message.unicode == PX_ASCII_LOWER_Q) self->game_state = C4_GAME_STOPPING;

            if (message.unicode == PX_ASCII_LOWER_S) self->input_insert = 1;

            if (message.unicode == PX_ASCII_LOWER_A) self->input_move_left  = 1;
            if (message.unicode == PX_ASCII_LOWER_D) self->input_move_right = 1;
        } break;

        default: break;
    }
}

void
c4GameConsoleOutput(C4Game* self, PxArena* arena, pxf32 time)
{
    if (self->game_state == C4_GAME_NONE) {
        pxConsoleSetMode(self->console.console, PX_CONSOLE_MODE_MESSAGE);

        c4ConsoleWriteMsg(&self->console, pxConsoleMsgReset());
        c4ConsoleWriteMsg(&self->console, pxConsoleMsgCursorHide());

        c4ConsoleFlush(&self->console);
    }

    if (self->game_state == C4_GAME_STOPPING) {
        c4ConsoleWriteMsg(&self->console, pxConsoleMsgStyleClear());
        c4ConsoleWriteMsg(&self->console, pxConsoleMsgCursorShow());

        c4ConsoleFlush(&self->console);

        pxConsoleSetMode(self->console.console, PX_CONSOLE_MODE_DEFAULT);
    }

    c4ConsoleBatchReset(&self->console_batch, 0, C4_COLOR_16_WHITE, C4_COLOR_16_BLACK);

    pxiword width  = self->game_board.width;
    pxiword height = self->game_board.height;

    pxiword xpad = 3;
    pxiword ypad = 1;

    pxiword wrange = 4 * width + 1;
    pxiword hrange = 3;

    pxiword wboard = 4 * width + 1;
    pxiword hboard = 2 * height + 1;

    pxiword wrect = 4 * 1 + 1;
    pxiword hrect = hboard + 2 * hrange;

    pxiword xrect = xpad + self->input_column * (wrect - 1);
    pxiword yrect = ypad;

    pxiword xrange0 = xpad;
    pxiword yrange0 = ypad;
    pxiword xboard  = xpad;
    pxiword yboard  = ypad + hrange;
    pxiword xrange1 = xpad;
    pxiword yrange1 = ypad + hrange + hboard;

    c4ConsoleBatchPaintRect(&self->console_batch, xrect, yrect, wrect, hrect,
        PX_ASCII_SHARP, C4_COLOR_16_MAGENTA_DARK, C4_COLOR_16_BLACK);

    c4ConsoleBatchPaintRange(&self->console_batch, arena, xrange0, yrange0,
        1, 0, 1, self->game_board.width + 1);

    c4ConsoleBatchPaintBoard(&self->console_batch, arena, xboard, yboard, &self->game_board);

    c4ConsoleBatchPaintRange(&self->console_batch, arena, xrange1, yrange1,
        1, 0, 1, self->game_board.width + 1);

    c4ConsoleWriteBatch(&self->console, &self->console_batch);

    c4ConsoleFlush(&self->console);
}

void
c4GameInput(C4Game* self, PxArena* arena)
{
    C4NetworkMsg network = {0};

    while (c4NetworkSessionReadMsg(&self->network_session, &network) != 0)
        c4GameNetworkInput(self, arena, network);

    PxConsoleMsg console = {0};

    while (c4ConsoleReadMsg(&self->console, &console) != 0)
        c4GameConsoleInput(self, arena, console);
}

void
c4GameOutput(C4Game* self, PxArena* arena, pxf32 time)
{
    c4GameNetworkOutput(self, arena, time);
    c4GameConsoleOutput(self, arena, time);
}

void
c4GameTick(C4Game* self, PxArena* arena, pxf32 time, pxf32 slice)
{

}

void
c4GameUpdate(C4Game* self, PxArena* arena, pxf32 time)
{
    pxiword diff = self->input_move_right - self->input_move_left;

    self->input_column = px_between(
        self->input_column + diff, 0, self->game_board.width - 1);

    self->input_insert     = 0;
    self->input_move_left  = 0;
    self->input_move_right = 0;
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

#define C4_CLIENT_ARG_AUTOMATIC   pxs8("+auto")
#define C4_CLIENT_ARG_SERVER_IP4  pxs8("+server-ipv4:")
#define C4_CLIENT_ARG_SERVER_IP6  pxs8("+server-ipv6:")
#define C4_CLIENT_ARG_SERVER_PORT pxs8("+server-port:")

int
main(int argc, char** argv)
{
    C4Game game = {0};

    game.game_config.server_addr = pxAddrLocalhost(PX_ADDR_TYPE_IP4);
    game.game_config.server_port = 8000;

    for (pxiword i = 1; i < argc; i += 1) {
        PxFormatRadix radix = PX_FORMAT_RADIX_10;
        PxFormatFlag  flags = PX_FORMAT_FLAG_NONE;

        PxString8 argument = pxString8FromMemory(argv[i], 32);

        if (pxString8IsEqual(argument, C4_CLIENT_ARG_AUTOMATIC) != 0)
            game.game_config.automatic = 1;

        if (pxString8BeginsWith(argument, C4_CLIENT_ARG_SERVER_IP4) != 0) {
            argument = pxString8TrimPrefix(argument, C4_CLIENT_ARG_SERVER_IP4);
            argument = pxString8TrimSpaces(argument);

            pxAddrFromString8(argument,
                &game.game_config.server_addr, PX_ADDR_TYPE_IP4);
        }

        if (pxString8BeginsWith(argument, C4_CLIENT_ARG_SERVER_IP6) != 0) {
            argument = pxString8TrimPrefix(argument, C4_CLIENT_ARG_SERVER_IP6);
            argument = pxString8TrimSpaces(argument);

            pxAddrFromString8(argument,
                &game.game_config.server_addr, PX_ADDR_TYPE_IP6);
        }

        if (pxString8BeginsWith(argument, C4_CLIENT_ARG_SERVER_PORT) != 0) {
            argument = pxString8TrimPrefix(argument, C4_CLIENT_ARG_SERVER_PORT);
            argument = pxString8TrimSpaces(argument);

            pxUnsignedFromString8(argument,
                &game.game_config.server_port, radix, flags);
        }
    }

    PxArena arena = pxMemoryReserve(16);

    if (pxNetworkStart() == 0) return 1;

    if (c4GamePlay(&game, &arena, 64.0) == 0)
        return 1;

    pxNetworkStop();

    return 0;
}
