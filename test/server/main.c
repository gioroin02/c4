#include "../../code/server/export.h"

#define C4_ARG_SERVER_IPV4   pax_str8("server-ipv4")
#define C4_ARG_SERVER_IPV6   pax_str8("server-ipv6")
#define C4_ARG_SERVER_PORT   pax_str8("server-port=")
#define C4_ARG_BOARD_WIDTH   pax_str8("board-width=")
#define C4_ARG_BOARD_HEIGHT  pax_str8("board-height=")
#define C4_ARG_PLAYER_NUMBER pax_str8("player-number=")

int
main(int argc, char** argv)
{
    C4_Game_Config config = {0};

    config.server_addr = pax_addr_any(PAX_ADDR_KIND_IP4);
    config.server_port = 50000;

    Pax_Format_Radix radix = PAX_FORMAT_RADIX_10;
    Pax_Format_Flag  flags = PAX_FORMAT_FLAG_NONE;

    for (paxiword i = 1; i < argc; i += 1) {
        Pax_String8 arg =
            pax_string8_from_memory(argv[i], 32, pax_size(paxu8));

        if (pax_string8_is_equal(arg, C4_ARG_SERVER_IPV4) != 0)
            config.server_addr = pax_addr_any(PAX_ADDR_KIND_IP4);

        if (pax_string8_is_equal(arg, C4_ARG_SERVER_IPV6) != 0)
            config.server_addr = pax_addr_any(PAX_ADDR_KIND_IP6);

        if (pax_string8_begins_with(arg, C4_ARG_SERVER_PORT) != 0) {
            arg = pax_string8_trim_prefix(arg, C4_ARG_SERVER_PORT);
            arg = pax_string8_trim_spaces(arg);

            pax_unsigned_from_string8(arg, &config.server_port, radix, flags);
        }

        if (pax_string8_begins_with(arg, C4_ARG_BOARD_WIDTH) != 0) {
            arg = pax_string8_trim_prefix(arg, C4_ARG_BOARD_WIDTH);
            arg = pax_string8_trim_spaces(arg);

            pax_unsigned_from_string8(arg, &config.board_width, radix, flags);
        }

        if (pax_string8_begins_with(arg, C4_ARG_BOARD_HEIGHT) != 0) {
            arg = pax_string8_trim_prefix(arg, C4_ARG_BOARD_HEIGHT);
            arg = pax_string8_trim_spaces(arg);

            pax_unsigned_from_string8(arg, &config.board_height, radix, flags);
        }

        if (pax_string8_begins_with(arg, C4_ARG_PLAYER_NUMBER) != 0) {
            arg = pax_string8_trim_prefix(arg, C4_ARG_PLAYER_NUMBER);
            arg = pax_string8_trim_spaces(arg);

            pax_unsigned_from_string8(arg, &config.player_number, radix, flags);
        }
    }

    Pax_Arena arena = pax_memory_reserve(32);

    if (pax_network_load() == 0) return 1;

    C4_Game_Server server = {0};

    server.config = config;

    C4_Engine engine = {0};

    engine.ctxt        = &server;
    engine.proc_start  = &c4_game_server_start;
    engine.proc_stop   = &c4_game_server_stop;
    engine.proc_input  = &c4_game_server_input;
    engine.proc_output = &c4_game_server_output;

    c4_engine_play(&engine, &arena, 30);

    pax_network_unload();
}
