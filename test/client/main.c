#include "../../code/client/export.h"

#include <stdio.h>

#define C4_ARG_SERVER_IPV4 pax_str8("server-ipv4:")
#define C4_ARG_SERVER_IPV6 pax_str8("server-ipv6:")
#define C4_ARG_SERVER_PORT pax_str8("server-port:")
#define C4_ARG_AUTOMATIC   pax_str8("auto")

int
main(int argc, char** argv)
{
    C4_Game_Config config = {0};

    config.server_addr = pax_addr_localhost(PAX_ADDR_KIND_IP4);
    config.server_port = 50000;
    config.automatic   = 0;

    Pax_Format_Radix radix = PAX_FORMAT_RADIX_10;
    Pax_Format_Flag  flags = PAX_FORMAT_FLAG_NONE;

    for (paxiword i = 1; i < argc; i += 1) {
        Pax_String8 arg =
            pax_string8_from_memory(argv[i], 32, pax_size(paxu8));

        if (pax_string8_begins_with(arg, C4_ARG_SERVER_IPV4) != 0) {
            arg = pax_string8_trim_prefix(arg, C4_ARG_SERVER_IPV4);
            arg = pax_string8_trim_spaces(arg);

            pax_addr_from_string8(arg, &config.server_addr, PAX_ADDR_KIND_IP4);
        }

        if (pax_string8_begins_with(arg, C4_ARG_SERVER_IPV6) != 0) {
            arg = pax_string8_trim_prefix(arg, C4_ARG_SERVER_IPV6);
            arg = pax_string8_trim_spaces(arg);

            pax_addr_from_string8(arg, &config.server_addr, PAX_ADDR_KIND_IP6);
        }

        if (pax_string8_begins_with(arg, C4_ARG_SERVER_PORT) != 0) {
            arg = pax_string8_trim_prefix(arg, C4_ARG_SERVER_PORT);
            arg = pax_string8_trim_spaces(arg);

            pax_unsigned_from_string8(arg, &config.server_port, radix, flags);
        }

        if (pax_string8_is_equal(arg, C4_ARG_AUTOMATIC) != 0)
            config.automatic = 1;
    }

    Pax_Arena arena = pax_memory_reserve(32);

    if (pax_network_load() == 0) return 1;

    C4_Game_Client client = {0};

    client.config = config;

    C4_Engine engine = {0};

    engine.ctxt       = &client;
    engine.proc_start = &c4_game_client_start;

    c4_engine_play(&engine, &arena, 30);

    pax_network_unload();
}
