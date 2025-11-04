#include "../../code/game/export.h"

#include <stdio.h>

#define RED(expr) "\x1b[91m" expr "\x1b[0m"
#define GRN(expr) "\x1b[92m" expr "\x1b[0m"
#define YLW(expr) "\x1b[93m" expr "\x1b[0m"
#define BLU(expr) "\x1b[94m" expr "\x1b[0m"
#define MAG(expr) "\x1b[95m" expr "\x1b[0m"
#define CYA(expr) "\x1b[96m" expr "\x1b[0m"

#define MESSAGE \
    pax_str8("{ \"player_accept\": { \"player_number\": 4, \"player_code\": 156, \"board_width\": 5, " \
        "\"board_height\": 5, \"piece_color\": 2, \"piece_shape\": \"ciao\" } }")

int
main(int argc, char** argv)
{
    Pax_Arena   arena  = pax_memory_reserve(16);
    Pax_Buffer8 buffer = pax_buffer8_create(&arena, PAX_MEMORY_KIB);

    Pax_Console console = pax_console_create(&arena);

    Pax_Source* source = pax_source_from_buffer8(&arena, &buffer);
    Pax_Target* target = pax_target_from_console(&arena, console);

    pax_buffer8_write_tail_string8(&buffer, MESSAGE);

    Pax_JSON_Reader reader = pax_json_reader_create(&arena, 8,
        pax_scanner_create(&arena, 16, source));

    Pax_JSON_Writer writer = pax_json_writer_create(&arena, 8, target);

    C4_Game_Message message = {0};

    c4_game_message_json_read(&message, &reader, &arena);
    c4_game_message_json_write(&message, &writer, &arena);
}
