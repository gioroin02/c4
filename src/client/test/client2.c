#include "../export.h"

typedef struct C4ClientConfig
{
    PxAddress server_addr;
    pxu16     server_port;
    pxb32     automatic;
}
C4ClientConfig;

typedef struct C4GameState
{
    C4FrameBuffer    frame;
    C4GameBoard      board;
    C4GamePlayerList players;

    pxb8 stop;
    pxb8 column_chosen;
    pxb8 move_left;
    pxb8 move_right;

    pxb8    active;
    pxiword column;
}
C4GameState;

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
c4GameStart(C4GameState* self, PxArena* arena, C4Client* client, C4ClientConfig config)
{
    C4Msg message = {0};

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

    message = c4ClientRead(client, arena);

    while (message.type != C4_MESSAGE_GAME_START) {
        if (message.type != C4_MESSAGE_PLAYER_DATA)
            return 0;

        player = c4GamePlayer(
            message.player_data.player_code,
            message.player_data.player_color,
            message.player_data.player_text);

        if (c4GamePlayerListInsert(&self->players, player) == 0)
            return 0;

        message = c4ClientRead(client, arena);
    }

    return 1;
}

pxb8
c4GameNetworkInput(C4GameState* self, PxArena* arena, C4Client* client)
{

}

pxb8
c4GameConsoleInput(C4GameState* self, PxArena* arena, PxReader* reader)
{
    PxConsoleMsg message = pxConsoleReadMessage(reader);

    pxb8 result = 0;

    self->stop          = 0;
    self->column_chosen = 0;
    self->move_left     = 0;
    self->move_right    = 0;

    switch (message.type) {
        case PX_CONSOLE_MSG_KEYBD_PRESS: {
            switch (message.keybd_press.button) {
                case PX_CONSOLE_KEYBD_ESCAPE:
                    self->stop = 1;
                break;

                case PX_CONSOLE_KEYBD_A:
                case PX_CONSOLE_KEYBD_ARROW_LEFT:
                    self->move_left = 1;
                break;

                case PX_CONSOLE_KEYBD_D:
                case PX_CONSOLE_KEYBD_ARROW_RIGHT:
                    self->move_right = 1;
                break;

                case PX_CONSOLE_KEYBD_ENTER:
                    self->column_chosen = 1;
                break;

                default: break;
            }

            result = 1;
        } break;

        default: break;
    }

    return result;
}

void
gameUpdate()
{}

/*
void
c4GameUpdate(C4GameState* self, PxArena* arena, C4Client* client)
{
    C4GamePlayer player = {0};
    pxiword      offset = pxArenaOffset(arena);

    c4GamePlayerListRead(&self->players, 0, &player);

    C4Msg message = c4ClientRead(client, arena);

    switch (message.type) {
        case C4_MESSAGE_PLAYER_TURN: {
            if (message.player_turn.player_code != player.code) {
                message = c4ClientRead(client, arena);

                switch (message.type) {
                    case C4_MESSAGE_PLAYER_CHOICE: {
                        pxiword column = message.player_choice.board_column;
                        pxuword code   = message.player_choice.player_code;

                        c4GameBoardInsert(&self->board, column, code);
                    } break;

                    case C4_MESSAGE_PLAYER_SKIP: break;

                    default: self->active = 0; break;
                }
            } else {
                c4GameBoardInsert(&self->board, self->column - 1, player.code);

                c4ClientWrite(client, arena,
                    c4MsgPlayerChoice(player.code, self->column - 1));
            }
        } break;

        default: self->active = 0; break;
    }

    pxArenaRewind(arena, offset);
}
*/

void
c4GamePaint(C4GameState* self, PxArena* arena, C4Client* client, PxWriter* writer)
{
    pxiword offset = pxArenaOffset(arena);

    pxiword width  = self->board.width;
    pxiword height = self->board.height;

    c4FrameBufferReset(&self->frame, pxs8(""), C4_COLOR_8_WHITE, C4_COLOR_8_BLACK);

    c4FrameBufferPaintRect(&self->frame,
        3 + (self->column - 1) * 4, 1, 5, (height + 2) * 2 + 3,
        pxs8("/"), c4ColorRGB(0xff, 0, 0), C4_COLOR_8_BLACK
    );

    c4FrameBufferPaintRange(&self->frame, arena, 3, 1, 1, 0, 1, width + 1);
    c4FrameBufferPaintBoard(&self->frame, arena, 3, 4, &self->board);
    c4FrameBufferPaintRange(&self->frame, arena, 3, (height + 2) * 2 + 1, 1, 0, 1, width + 1);

    c4WriterFrame(writer, &self->frame);
    pxWriterFlush(writer);

    pxArenaRewind(arena, offset);
}

void
c4GameStop(C4GameState* self, PxArena* arena, C4Client* client)
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

    PxConsole console = pxConsoleCreate(&arena);
    PxReader  reader  = pxConsoleReader(console, &arena, PX_MEMORY_KIB);
    PxWriter  writer  = pxConsoleWriter(console, &arena, PX_MEMORY_KIB * 16);

    PxLogger logger = pxLoggerReserve(&arena, 1024, &writer);

    pxLoggerSetFlags(&logger, PX_REPORT_FLAG_LEVEL | PX_REPORT_FLAG_COLOR);
    pxLoggerSetLevel(&logger, PX_REPORT_LEVEL_TRACE);

    LOGGER = &logger;

    C4Client client = c4ClientMake(&arena,
        PX_MEMORY_KIB, PX_MEMORY_KIB, PX_ADDRESS_TYPE_IP4);

    pxb8 state = c4ClientStart(&client, config.server_addr, config.server_port);

    if (state == 0) return 1;

    C4GameState game = {.active = 1};

    if (c4GameStart(&game, &arena, &client, config) == 0)
        return 1;

    pxLoggerSetLevel(&logger, PX_REPORT_LEVEL_NONE);
    pxConsoleSetMode(console, PX_CONSOLE_MODE_MESSAGE);

    pxConsoleWriteCommand(&writer, pxConsoleCmdReset());
    pxConsoleWriteCommand(&writer, pxConsoleCmdCursorHide());
    pxWriterFlush(&writer);

    while (game.active != 0) {
        pxb8 state = c4GameInput(&game, &arena, &client, &reader);

        if (state != 0) {
            c4GameUpdate(&game, &arena, &client);
            c4GamePaint(&game, &arena, &client, &writer);
        }
    }

    c4GameStop(&game, &arena, &client);

    pxConsoleWriteCommand(&writer, pxConsoleCmdCursorShow());
    pxConsoleWriteCommand(&writer, pxConsoleCmdReset());
    pxWriterFlush(&writer);

    pxConsoleSetMode(console, PX_CONSOLE_MODE_DEFAULT);

    pxNetworkStop();
}
