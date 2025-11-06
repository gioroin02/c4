#include "../export.h"

void
c4BatchPaintTile(C4Batch* frame, PxArena* arena, pxiword x, pxiword y, pxi32 unicode, PxConsoleColor text, PxConsoleColor back)
{
    c4BatchPaintCell(frame, x + 0, y + 0, PX_ASCII_SHARP, text, back);
    c4BatchPaintCell(frame, x + 4, y + 0, PX_ASCII_SHARP, text, back);
    c4BatchPaintCell(frame, x + 0, y + 2, PX_ASCII_SHARP, text, back);
    c4BatchPaintCell(frame, x + 4, y + 2, PX_ASCII_SHARP, text, back);

    for (pxiword i = 1; i < 4; i += 1)
        c4BatchPaintCell(frame, x + i, y + 0, PX_ASCII_MINUS, text, back);

    for (pxiword i = 1; i < 4; i += 1)
        c4BatchPaintCell(frame, x + i, y + 2, PX_ASCII_MINUS, text, back);

    for (pxiword i = 1; i < 2; i += 1)
        c4BatchPaintCell(frame, x + 0, y + i, PX_ASCII_PIPE, text, back);

    for (pxiword i = 1; i < 2; i += 1)
        c4BatchPaintCell(frame, x + 4, y + i, PX_ASCII_PIPE, text, back);

    if (unicode >= 32)
        c4BatchPaintCell(frame, x + 2, y + 1, unicode, text, back);
}

void
c4BatchPaintBoard(C4Batch* frame, PxArena* arena, pxiword x, pxiword y, C4GameBoard* game_board)
{
    for (pxiword j = 0; j < game_board->height; j += 1) {
        for (pxiword i = 0; i < game_board->width; i += 1) {
            pxuword item    = c4GameBoardGetOr(game_board, i, game_board->height - j - 1, 0);
            pxi32   unicode = 0;

            if (item != 0) unicode = PX_ASCII_COMMERCIAL;

            c4BatchPaintTile(frame, arena, x + i * 4, y + j * 2,
                unicode, C4_COLOR_16_WHITE, C4_COLOR_16_BLACK);
        }
    }
}

void
c4BatchPaintRange(C4Batch* frame, PxArena* arena, pxiword x, pxiword y, pxiword dx, pxiword dy, pxiword start, pxiword stop)
{
    pxiword offset = pxArenaOffset(arena);

    PxFormatRadix radix = PX_FORMAT_RADIX_10;
    PxFormatFlag  flags = PX_FORMAT_FLAG_NONE;

    for (pxiword i = start; i < stop; i += 1) {
        PxString8 string = pxString8FromInteger(arena, i, radix, flags);

        for (pxiword j = 0; j < string.length; j += 1) {
            pxi32 unicode = string.memory[j];

            c4BatchPaintCell(frame, x + 2 + j, y + 1,
                unicode, C4_COLOR_16_WHITE, C4_COLOR_16_BLACK);
        }

        x += dx * 4;
        y += dy * 2;

        pxArenaRewind(arena, offset);
    }
}

typedef struct ReaderThreadCtxt
{
    PxSource  source;
    PxTarget  target;
    PxBuffer8 buffer;
}
ReaderThreadCtxt;

pxuword
readerThreadProc(ReaderThreadCtxt* self)
{
    if (self == 0) return 0;

    while (1) {
        pxiword size = pxSourceReadBuffer8(self->source, &self->buffer);

        if (size > 0)
            size = pxTargetWriteBuffer8(self->target, &self->buffer);

        if (size <= 0) break;
    }

    return 1;
}

typedef struct C4ClientConfig
{
    PxAddr  server_addr;
    pxuword server_port;
    pxb8    automatic;
}
C4ClientConfig;

typedef struct C4Game
{
    /* Engine data */

    C4ClientConfig config;

    PxConsole console;
    PxSource  console_source;
    PxTarget  console_target;

    PxChannel console_chl;
    PxSource  console_chl_source;
    PxTarget  console_chl_target;

    PxSocketTcp socket;
    PxSource    socket_source;
    PxTarget    socket_target;

    PxChannel socket_chl;
    PxSource  socket_chl_source;
    PxTarget  socket_chl_target;

    PxConsoleQueue queue_in;
    PxConsoleQueue queue_out;

    PxBuffer8 request;
    PxBuffer8 response;

    PxJsonWriter json_writer;
    PxJsonReader json_reader;

    /* Game data */

    C4GamePlayerList player_list;

    C4GameBoard game_board;
    C4Batch     game_batch;
    pxiword     game_column;

    pxb8 input_active;
    pxb8 input_insert;
    pxb8 input_move_left;
    pxb8 input_move_right;
}
C4Game;

pxb8
c4GameJoin(C4Game* self, PxArena* arena)
{
    PxAddr  addr = self->config.server_addr;
    pxuword port = self->config.server_port;

    if (pxSocketTcpConnect(&self->socket, addr, port) == 0)
        return 0;

    C4GameMsg message = c4GameMsgPlayerJoin(self->config.automatic);

    c4ClientWriteGameMsgJson(&self->json_writer, arena, message);

    message = c4ClientReadGameMsgJson(&self->json_reader, arena);

    if (message.type != C4_GAME_MSG_PLAYER_ACCEPT)
        return 0;

    self->player_list = c4GamePlayerListReserve(arena,
        message.player_accept.player_amount);

    self->game_board = c4GameBoardReserve(arena,
        message.player_accept.board_width,
        message.player_accept.board_height);

    if (c4GamePlayerListLength(&self->player_list) <= 0)
        return 0;

    if (c4GameBoardLength(&self->game_board) <= 0) return 0;

    C4GamePlayer player = c4GamePlayer(
        message.player_accept.player_ident,
        message.player_accept.player_text,
        message.player_accept.player_color);

    if (c4GamePlayerListInsert(&self->player_list, player) == 0)
        return 0;

    return 1;
}

pxb8
c4GameWait(C4Game* self, PxArena* arena)
{
    C4GameMsg message = c4ClientReadGameMsgJson(&self->json_reader, arena);

    while (message.type != C4_GAME_MSG_GAME_START) {
        switch (message.type) {
            case C4_GAME_MSG_PLAYER_DATA: {
                C4GamePlayer player = c4GamePlayer(
                    message.player_data.player_ident,
                    message.player_data.player_text,
                    message.player_data.player_color);

                if (c4GamePlayerListInsert(&self->player_list, player) == 0)
                    return 0;
            } break;

            default: break;
        }

        message = c4ClientReadGameMsgJson(&self->json_reader, arena);
    }

    return 1;
}

pxb8
c4GameStart(C4Game* self, PxArena* arena)
{
    if (c4GameJoin(self, arena) == 0)
        return 0;

    if (c4GameStart(self, arena) == 0)
        return 0;

    return 1;
}

void
c4GameStop(C4Game* self)
{

}

void
c4GameConsoleInput(C4Game* self, PxArena* arena)
{
    PxConsoleMsg message = {0};

    pxSourceReadBuffer8(self->console_chl_source,
        pxConsoleQueueBuffer8(&self->queue_in));

    self->input_active     = 1;
    self->input_insert     = 0;
    self->input_move_left  = 0;
    self->input_move_right = 0;

    while (pxConsoleQueueReadMsg(&self->queue_in, arena, &message) != 0) {
        switch (message.type) {
            case PX_CONSOLE_MSG_UNICODE: {
                if (message.unicode == PX_ASCII_LOWER_Q) self->input_active     = 0;
                if (message.unicode == PX_ASCII_LOWER_S) self->input_insert     = 1;
                if (message.unicode == PX_ASCII_LOWER_A) self->input_move_left  = 1;
                if (message.unicode == PX_ASCII_LOWER_D) self->input_move_right = 1;
            } break;

            default: break;
        }
    }
}

void
c4GameConsoleOutput(C4Game* self, PxArena* arena)
{
    c4BatchReset(&self->game_batch, 0, C4_COLOR_16_WHITE, C4_COLOR_16_BLACK);

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

    pxiword xrect = xpad + self->game_column * (wrect - 1);
    pxiword yrect = ypad;

    pxiword xrange0 = xpad;
    pxiword yrange0 = ypad;
    pxiword xboard  = xpad;
    pxiword yboard  = ypad + hrange;
    pxiword xrange1 = xpad;
    pxiword yrange1 = ypad + hrange + hboard;

    c4BatchPaintRect(&self->game_batch, xrect, yrect, wrect, hrect,
        PX_ASCII_SHARP, C4_COLOR_16_MAGENTA_DARK, C4_COLOR_16_BLACK);

    c4BatchPaintRange(&self->game_batch, arena, xrange0, yrange0,
        1, 0, 1, self->game_board.width + 1);

    c4BatchPaintBoard(&self->game_batch, arena, xboard, yboard, &self->game_board);

    c4BatchPaintRange(&self->game_batch, arena, xrange1, yrange1,
        1, 0, 1, self->game_board.width + 1);

    c4ConsoleQueueWriteBatch(&self->queue_out, &self->game_batch);

    pxTargetWriteBuffer8(self->console_target,
        pxConsoleQueueBuffer8(&self->queue_out));
}


void
c4GameNetworkInput(C4Game* self, PxArena* arena)
{
    // if (self->game_state == C4_GAME_STATE_WAITING)

}

void
c4GameNetworkOutput(C4Game* self, PxArena* arena)
{
}

pxb8
c4EngineStart(C4Game* self, PxArena* arena)
{
    self->console        = pxConsoleCreate(arena);
    self->console_source = pxSourceFromConsole(self->console);
    self->console_target = pxTargetFromConsole(self->console);

    self->console_chl        = pxChannelOpen(arena, PX_MEMORY_KIB);
    self->console_chl_source = pxSourceFromChannel(&self->console_chl);
    self->console_chl_target = pxTargetFromChannel(&self->console_chl);

    self->socket        = pxSocketTcpCreate(arena, self->config.server_addr.type);
    self->socket_source = pxSourceFromSocketTcp(self->socket);
    self->socket_target = pxTargetFromSocketTcp(self->socket);

    self->socket_chl        = pxChannelOpen(arena, PX_MEMORY_KIB);
    self->socket_chl_source = pxSourceFromChannel(&self->socket_chl);
    self->socket_chl_target = pxTargetFromChannel(&self->socket_chl);

    self->queue_in  = pxConsoleQueueReserve(arena, PX_MEMORY_KIB);
    self->queue_out = pxConsoleQueueReserve(arena, PX_MEMORY_KIB * 16);

    self->request  = pxBuffer8Reserve(arena, PX_MEMORY_KIB);
    self->response = pxBuffer8Reserve(arena, PX_MEMORY_KIB);

    PxTarget target = pxBufferedTarget(self->socket_target, &self->request);
    PxSource source = pxBufferedSource(self->socket_source, &self->response);

    self->json_writer = pxJsonWriterReserve(target, arena, 4);
    self->json_reader = pxJsonReaderReserve(source, arena, 4);

    self->game_board = c4GameBoardReserve(arena, 5, 5);
    self->game_batch = c4BatchReserve(arena, 60, 20);

    pxConsoleSetMode(self->console, PX_CONSOLE_MODE_MESSAGE);

    pxConsoleQueueWriteMsg(&self->queue_out, pxConsoleMsgReset());
    pxConsoleQueueWriteMsg(&self->queue_out, pxConsoleMsgCursorHide());

    pxTargetWriteBuffer8(self->console_target,
        pxConsoleQueueBuffer8(&self->queue_out));

    ReaderThreadCtxt* console_reader = pxArenaReserve(arena, ReaderThreadCtxt, 1);

    console_reader->source = self->console_source;
    console_reader->target = self->console_chl_target;
    console_reader->buffer = pxBuffer8Reserve(arena, PX_MEMORY_KIB);

    /*
    ReaderThreadCtxt* socket_reader = pxArenaReserve(arena, ReaderThreadCtxt, 1);

    socket_reader->source = self->socket_source;
    socket_reader->target = self->socket_chl_target;
    socket_reader->buffer = pxBuffer8Reserve(arena, PX_MEMORY_KIB);

    pxThreadDetach(pxThreadCreate(arena, console_reader, &readerThreadProc));
    pxThreadDetach(pxThreadCreate(arena, socket_reader, &readerThreadProc));
    */

    if (c4GameStart(self, arena) == 0) return 0;

    self->input_active = 1;

    return self->input_active;
}

void
c4EngineStop(C4Game* self)
{
    c4GameStop(self);

    pxConsoleQueueWriteMsg(&self->queue_out, pxConsoleMsgStyleClear());
    pxConsoleQueueWriteMsg(&self->queue_out, pxConsoleMsgCursorShow());

    pxTargetWriteBuffer8(self->console_target,
        pxConsoleQueueBuffer8(&self->queue_out));

    pxConsoleSetMode(self->console, PX_CONSOLE_MODE_DEFAULT);
}

pxb8
c4EngineIsActive(C4Game* self)
{
    return self->input_active != 0 ? 1 : 0;
}

void
c4EngineInput(C4Game* self, PxArena* arena, pxf32 frame)
{
    c4GameConsoleInput(self, arena);
    c4GameNetworkInput(self, arena);
}

void
c4EngineFrame(C4Game* self, PxArena* arena, pxf32 frame)
{
    pxiword movement = self->input_move_right - self->input_move_left;

    self->game_column = px_between(self->game_column + movement, 0, self->game_board.width - 1);

    if (self->input_insert != 0)
        c4GameBoardInsert(&self->game_board, self->game_column, 1);
}

void
c4EngineTick(C4Game* self, PxArena* arena, pxf32 frame, pxf32 slice)
{

}

void
c4EngineOutput(C4Game* self, PxArena* arena)
{
    c4GameConsoleOutput(self, arena);
    c4GameNetworkOutput(self, arena);
}

pxb8
c4EnginePlay(C4Game* self, PxArena* arena, pxuword steps)
{
    PxClock clock = pxClockCreate(arena);

    if (c4EngineStart(self, arena) == 0) return 0;

    pxf32 frame = 0;
    pxf32 slice = 1.0 / px_as(pxf32, steps);
    pxf32 time  = 0;

    while (c4EngineIsActive(self) != 0) {
        time += pxClockElapsed(clock);

        c4EngineInput(self, arena, frame);
        c4EngineFrame(self, arena, frame);

        while (time >= slice) {
            c4EngineTick(self, arena, frame, slice);

            time  -= slice;
            frame += 1;
        }

        c4EngineOutput(self, arena);

        pxCurrentThreadSleep(10);
    }

    c4EngineStop(self);

    return 1;
}

#define C4_CLIENT_ARG_SERVER_IP4  pxs8("server-ipv4:")
#define C4_CLIENT_ARG_SERVER_IP6  pxs8("server-ipv6:")
#define C4_CLIENT_ARG_SERVER_PORT pxs8("server-port:")
#define C4_CLIENT_ARG_AUTOMATIC   pxs8("auto")

int
main(int argc, char** argv)
{
    C4Game engine = {0};

    PxArena arena = pxMemoryReserve(32);

    engine.config.server_addr = pxAddrLocalhost(PX_ADDR_TYPE_IP4);
    engine.config.server_port = 5000;
    engine.config.automatic   = 0;

    for (pxiword i = 1; i < argc; i += 1) {
        PxFormatRadix radix = PX_FORMAT_RADIX_10;
        PxFormatFlag  flags = PX_FORMAT_FLAG_NONE;

        PxString8 argument = pxString8FromMemory(argv[i], 32);

        if (pxString8BeginsWith(argument, C4_CLIENT_ARG_SERVER_IP4) != 0) {
            argument = pxString8TrimPrefix(argument, C4_CLIENT_ARG_SERVER_IP4);
            argument = pxString8TrimSpaces(argument);

            pxAddrFromString8(argument,
                &engine.config.server_addr, PX_ADDR_TYPE_IP4);
        }

        if (pxString8BeginsWith(argument, C4_CLIENT_ARG_SERVER_IP6) != 0) {
            argument = pxString8TrimPrefix(argument, C4_CLIENT_ARG_SERVER_IP6);
            argument = pxString8TrimSpaces(argument);

            pxAddrFromString8(argument,
                &engine.config.server_addr, PX_ADDR_TYPE_IP6);
        }

        if (pxString8BeginsWith(argument, C4_CLIENT_ARG_SERVER_PORT) != 0) {
            argument = pxString8TrimPrefix(argument, C4_CLIENT_ARG_SERVER_PORT);
            argument = pxString8TrimSpaces(argument);

            pxUnsignedFromString8(argument,
                &engine.config.server_port, radix, flags);
        }

        if (pxString8IsEqual(argument, C4_CLIENT_ARG_AUTOMATIC) != 0)
            engine.config.automatic = 1;
    }

    if (pxNetworkStart() == 0) return 1;

    if (c4EnginePlay(&engine, &arena, 60) == 0)
        return 1;

    pxNetworkStop();
}
