#include "../export.h"

typedef struct C4ClientConfig
{
    PxAddress server_addr;
    pxu16     server_port;
    pxb32     automatic;
}
C4ClientConfig;

typedef struct C4Game
{
    C4FrameBuffer frame;

    C4GameBoard      board;
    C4GamePlayerList players;

    pxb8 active;
    pxb8 turn;
    pxb8 result;

    pxf32 timer;
    pxf32 elapsed;

    pxiword column;

    pxb8 stop;
    pxb8 move_left;
    pxb8 move_right;
    pxb8 send;
}
C4Game;

void
c4FrameBufferPaintTile(C4FrameBuffer* frame, PxArena* arena, pxiword x, pxiword y, PxString8 text, C4Color front, C4Color back)
{
    c4FrameBufferPaintCell(frame, x + 0, y + 0, pxs8("#"), front, back);
    c4FrameBufferPaintCell(frame, x + 4, y + 0, pxs8("#"), front, back);
    c4FrameBufferPaintCell(frame, x + 0, y + 2, pxs8("#"), front, back);
    c4FrameBufferPaintCell(frame, x + 4, y + 2, pxs8("#"), front, back);

    for (pxiword i = 1; i < 4; i += 1)
        c4FrameBufferPaintCell(frame, x + i, y + 0, pxs8("-"), front, back);

    for (pxiword i = 1; i < 4; i += 1)
        c4FrameBufferPaintCell(frame, x + i, y + 2, pxs8("-"), front, back);

    for (pxiword i = 1; i < 2; i += 1)
        c4FrameBufferPaintCell(frame, x + 0, y + i, pxs8("|"), front, back);

    for (pxiword i = 1; i < 2; i += 1)
        c4FrameBufferPaintCell(frame, x + 4, y + i, pxs8("|"), front, back);

    if (text.length > 0)
        c4FrameBufferPaintCell(frame, x + 2, y + 1, text, front, back);
}

void
c4FrameBufferPaintBoard(C4FrameBuffer* frame, PxArena* arena, pxiword x, pxiword y, C4GameBoard* board)
{
    for (pxiword j = 0; j < board->height; j += 1) {
        for (pxiword i = 0; i < board->width; i += 1) {
            pxuword   item = c4GameBoardReadOr(board, i, board->height - j - 1, 0);
            PxString8 text = pxs8("");

            if (item != 0) text = pxs8("@");

            c4FrameBufferPaintTile(frame, arena, x + i * 4, y + j * 2,
                text, C4_COLOR_8_WHITE, C4_COLOR_8_BLACK);
        }
    }
}

void
c4FrameBufferPaintRange(C4FrameBuffer* frame, PxArena* arena, pxiword x, pxiword y, pxiword dx, pxiword dy, pxiword start, pxiword stop)
{
    for (pxiword i = start; i < stop; i += 1) {
        PxString8 text = pxString8FromInteger(arena,
            10, PX_FORMAT_OPTION_NONE, i);

        c4FrameBufferPaintCell(frame, x + 2, y + 1,
            text, C4_COLOR_8_WHITE, C4_COLOR_8_BLACK);

        x += dx * 4;
        y += dy * 2;
    }
}

pxb8
c4GameJoin(C4Game* self, PxArena* arena, C4Client* client, C4ClientConfig config)
{
    C4Msg     message = {0};
    PxAddress address = config.server_addr;
    pxu16     port    = config.server_port;

    if (c4ClientStart(client, address, port) == 0)
        return 0;

    c4ClientWrite(client, arena, c4MsgPlayerJoin(config.automatic));

    message = c4ClientRead(client, arena);

    if (message.type != C4_MESSAGE_PLAYER_ACCEPT) return 0;

    self->players = c4GamePlayerListReserve(arena,
        message.player_accept.player_number);

    if (c4GamePlayerListLength(&self->players) == 0) return 0;

    self->board = c4GameBoardReserve(arena,
        message.player_accept.board_width,
        message.player_accept.board_height);

    if (c4GameBoardLength(&self->board) == 0) return 0;

    C4GamePlayer player = c4GamePlayer(
        message.player_accept.player_code,
        message.player_accept.player_color,
        message.player_accept.player_text);

    if (c4GamePlayerListInsert(&self->players, player) == 0)
        return 0;

    return 1;
}

pxb8
c4GameStart(C4Game* self, PxArena* arena, C4Client* client)
{
    C4Msg message = c4ClientRead(client, arena);

    while (message.type != C4_MESSAGE_GAME_START) {
        if (message.type != C4_MESSAGE_PLAYER_DATA)
            return 0;

        C4GamePlayer player = c4GamePlayer(
            message.player_data.player_code,
            message.player_data.player_color,
            message.player_data.player_text);

        if (c4GamePlayerListInsert(&self->players, player) == 0)
            return 0;

        message = c4ClientRead(client, arena);
    }

    return 1;
}

void
c4GameConsoleRead(C4Game* self, PxArena* arena, PxReader* reader)
{
    PxConsoleMsg message = pxConsolePollMessage(reader);

    self->stop       = 0;
    self->move_left  = 0;
    self->move_right = 0;
    self->send       = 0;

    while (message.type != PX_CONSOLE_MSG_NONE) {
        switch (message.type) {
            case PX_CONSOLE_MSG_KEYBD_PRESS: {
                switch (message.keybd_press.button) {
                    case PX_CONSOLE_KEYBD_ESCAPE: self->stop = 1; break;

                    case PX_CONSOLE_KEYBD_A:
                    case PX_CONSOLE_KEYBD_ARROW_LEFT:
                        self->move_left = 1;
                    break;

                    case PX_CONSOLE_KEYBD_D:
                    case PX_CONSOLE_KEYBD_ARROW_RIGHT:
                        self->move_right = 1;
                    break;

                    case PX_CONSOLE_KEYBD_ENTER:
                    case PX_CONSOLE_KEYBD_SPACE:
                        self->send = 1;
                    break;

                    default: break;
                }
            } break;

            default: break;
        }

        message = pxConsolePollMessage(reader);
    }

    if (self->stop != 0) self->active = 0;

    pxiword column = self->column +
        self->move_right - self->move_left;

    self->column = pxClamp(column, 0, self->board.width);
}

void
c4GameConsoleWrite(C4Game* self, PxArena* arena, PxWriter* writer)
{
    pxiword width  = self->board.width;
    pxiword height = self->board.height;
    pxiword column = self->column;

    c4FrameBufferReset(&self->frame, pxs8(""), C4_COLOR_8_WHITE, C4_COLOR_8_BLACK);

    pxiword xpad = 3;
    pxiword ypad = 1;

    pxiword wrange = 4 * width + 1;
    pxiword hrange = 3;

    pxiword wboard = 4 * width + 1;
    pxiword hboard = 2 * height + 1;

    pxiword wrect = 4 * 1 + 1;
    pxiword hrect = hboard + 2 * hrange;

    pxiword xrect = xpad + (column - 1) * (wrect - 1);
    pxiword yrect = ypad;

    pxiword xrange0 = xpad;
    pxiword yrange0 = ypad;
    pxiword xboard  = xpad;
    pxiword yboard  = ypad + hrange;
    pxiword xrange1 = xpad;
    pxiword yrange1 = ypad + hrange + hboard;

    c4FrameBufferPaintRect(&self->frame, xrect, yrect, wrect, hrect,
        pxs8("/"), c4ColorRGB(0xff, 0, 0), C4_COLOR_8_BLACK);

    c4FrameBufferPaintRange(&self->frame,
        arena, xrange0, yrange0, 1, 0, 1, width + 1);

    c4FrameBufferPaintBoard(&self->frame,
        arena, xboard, yboard, &self->board);

    c4FrameBufferPaintRange(&self->frame,
        arena, xrange1, yrange1, 1, 0, 1, width + 1);

    c4WriterFrame(writer, &self->frame);

    pxWriterFlush(writer);
}

void
c4GameNetworkReadTurn(C4Game* self, PxArena* arena, C4Client* client)
{
    C4GamePlayer player = c4GamePlayerListReadOr(
        &self->players, 0, (C4GamePlayer) {0});

    if (self->turn == 1) return;

    C4Msg message = c4ClientRead(client, arena);

    switch (message.type) {
        case C4_MESSAGE_PLAYER_TURN: {
            self->turn = 0;

            if (message.player_turn.player_code == player.code)
                self->turn = 1;
        } break;

        case C4_MESSAGE_GAME_STOP: {
            self->result = 0;

            if (message.game_stop.player_code == player.code)
                self->result = 1;

            self->active = 0;
        } break;

        default: self->active = 0; break;
    }
}

void
c4GameNetworkReadChoice(C4Game* self, PxArena* arena, C4Client* client)
{
    C4Msg message = c4ClientRead(client, arena);

    switch (message.type) {
        case C4_MESSAGE_PLAYER_CHOICE: {
            c4GameBoardInsert(&self->board,
                message.player_choice.board_column,
                message.player_choice.player_code);
        } break;

        case C4_MESSAGE_PLAYER_SKIP: break;

        default: self->active = 0; break;
    }
}

void
c4GameNetworkWriteChoice(C4Game* self, PxArena* arena, C4Client* client)
{
    C4GamePlayer player = c4GamePlayerListReadOr(&self->players,
        0, (C4GamePlayer) {0});

    if (self->send == 0) return;

    c4GameBoardInsert(&self->board, self->column, player.code);

    c4ClientWrite(client, arena,
        c4MsgPlayerChoice(player.code, self->column));
}

void
c4GameStop(C4Game* self, PxArena* arena, C4Client* client)
{
    c4ClientStop(client);
}

PxLogger* LOGGER = 0;

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

                pxUnsigned16FromString8(&config.server_port, 10, options, arg);
            }

            if (pxString8IsEqual(arg, pxs8("--automatic")) != 0)
                config.automatic = 1;
        }
    }

    C4Client client = c4ClientMake(&arena, PX_MEMORY_KIB, PX_ADDRESS_TYPE_IP4);

    PxConsole console = pxConsoleCreate(&arena);
    PxReader  reader  = pxConsoleReader(console, &arena, PX_MEMORY_KIB);
    PxWriter  writer  = pxConsoleWriter(console, &arena, PX_MEMORY_KIB * 16);

    PxLogger logger = pxLoggerReserve(&arena, PX_MEMORY_KIB, &writer);

    pxLoggerSetFlags(&logger, PX_REPORT_FLAG_LEVEL | PX_REPORT_FLAG_COLOR);
    pxLoggerSetLevel(&logger, PX_REPORT_LEVEL_TRACE);

    LOGGER = &logger;

    PxClock clock = pxClockCreate(&arena);

    C4Game game = {.active = 1, .timer = 1 / 64.0};

    if (c4GameJoin(&game, &arena, &client, config) == 0)
        return 1;

    if (c4GameStart(&game, &arena, &client) == 0) return 1;

    pxConsoleSetMode(console, PX_CONSOLE_MODE_MESSAGE);

    while (game.active != 0) {
        game.elapsed += pxClockElapsed(&clock);

        c4GameConsoleRead(&game, &arena, &reader);

        c4GameNetworkReadTurn(&game, &arena, &client);

        if (game.turn != 0)
            c4GameNetworkWriteChoice(&game, &arena, &client);
        else
            c4GameNetworkReadChoice(&game, &arena, &client);

        for (pxiword i = 0; i < 5; i += 1) {
            if (game.timer <= game.elapsed)
                c4GameConsoleWrite(&game, &arena, &writer);
            else
                break;

            game.timer -= game.elapsed;
        }
    }

    c4GameStop(&game, &arena, &client);

    pxConsoleSetMode(console, PX_CONSOLE_MODE_DEFAULT);

    pxNetworkStop();
}
