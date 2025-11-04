#include "../../code/game/export.h"

#include <stdio.h>

#define C4_COLOR_DEFAULT_FRONT c4_color_rgba(255, 255, 255, 0)
#define C4_COLOR_DEFAULT_BACK  c4_color_rgba(50, 50, 50, 0)

typedef struct C4_Console_Ctxt
{
    Pax_Console  console;
    Pax_Channel* channel;
}
C4_Console_Ctxt;

void
c4_console_proc(C4_Console_Ctxt* self)
{
    paxu8 byte = 0;

    if (pax_console_read(self, &byte, 1) <= 0) return;

    C4_Console_Message message = {0};

    switch (byte) {
        case PAX_ASCII_LOWER_Q:
            message = c4_console_message_quit();
        break;

        default:
            message = c4_console_message_unicode(byte);
        break;
    }

    pax_channel_insert(self->channel,
        C4_Console_Message, &message);
}

void
c4_console_buffer_paint_board(C4_Console_Buffer* buffer, C4_Game_Board* self)
{
    for (paxiword j = 0; j < self->height; j += 1) {
        for (paxiword i = 0; i < self->width; i += 1) {
            paxuword item = c4_game_board_peek_or(self, i, j, 0);

            if (item != 0) {
                paxi32 unicode = PAX_ASCII_UPPER_A + item + 1;

                c4_console_buffer_paint(buffer, i, j,
                    unicode, C4_COLOR_DEFAULT_FRONT, C4_COLOR_DEFAULT_BACK);
            }
        }
    }
}

paxuword
c4_player_has_won(C4_Game_Board* self, paxiword x, paxiword y, paxiword length)
{
    #define DIRECTIONS 8

    paxiword directions_x[DIRECTIONS] = {+1, +1,  0, -1, -1, -1,  0, +1};
    paxiword directions_y[DIRECTIONS] = { 0, +1, +1, +1,  0, -1, -1, -1};

    paxuword value = 0;

    for (paxiword i = 0; i < DIRECTIONS; i += 1) {
        paxiword line = c4_game_board_contains_line(
            self, x, y, directions_x[i], directions_y[i], &value);

        if (line >= length) return value;
    }

    return 0;
}

int
main(int argc, char** argv)
{
    Pax_Arena arena = pax_memory_reserve(64);

    Pax_Console console = pax_console_create(&arena);
    Pax_Buffer8 surface = pax_buffer8_create(&arena, 100 * 30 * 40);

    Pax_Target* target = pax_target_from_buffer8(&arena, &surface);
    Pax_Target* conout = pax_target_from_console(&arena, console);

    C4_Game_Board     board  = c4_game_board_create(&arena, 7, 5);
    C4_Console_Buffer buffer = c4_console_buffer_create(&arena, 100, 30);

    Pax_Thread_Pool* pool = pax_thread_pool_create(&arena, 8, 16);

    Pax_Channel channel = pax_channel_create(&arena, C4_Console_Message, 16);

    C4_Console_Ctxt console_ctxt = {
        .console = console,
        .channel = &channel,
    };

    Pax_Clock clock = pax_clock_create(&arena);

    if (pax_console_mode_apply(console, PAX_CONSOLE_MODE_RAW) == 0)
        return 1;

    c4_target_screen_clear(target);
    c4_target_cursor_hide(target);

    pax_target_write_buffer8(conout, &surface);

    paxiword mark   = pax_arena_tell(&arena);
    paxb8    active = 1;

    paxiword tick = 0;

    paxf32 total = 0;
    paxf32 slice = 1.0 / 30.0;

    paxf32 elapsed = 0;

    while (active != 0) {
        elapsed = pax_clock_elapsed(clock);

        total += elapsed;

        C4_Console_Message message = {0};

        while (pax_channel_try_remove(&channel, C4_Console_Message, &message) != 0) {
            if (message.kind == C4_CONSOLE_MESSAGE_QUIT)
                active = 0;

            printf("%lli\n", tick++);
        }

        for (paxiword i = 0; i < 8; i += 1)
            pax_thread_pool_try_delegate(pool, &console_ctxt, &c4_console_proc);

        for (; total > slice; total -= slice) {}

        c4_console_buffer_clear(&buffer, PAX_ASCII_COMMERCIAL,
            C4_COLOR_DEFAULT_FRONT, C4_COLOR_DEFAULT_BACK);

        c4_console_buffer_paint_board(&buffer, &board);

        c4_target_screen_clear(target);
        c4_target_console_buffer(target, &arena, &buffer);

        pax_target_write_buffer8(conout, &surface);
    }

    pax_buffer8_clear(&surface);

    c4_target_screen_clear(target);

    pax_target_write_buffer8(conout, &surface);

    pax_console_mode_apply(console, PAX_CONSOLE_MODE_DEFAULT);
}
