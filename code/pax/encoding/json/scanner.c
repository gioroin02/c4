#ifndef PAX_ENCODING_JSON_SCANNER_C
#define PAX_ENCODING_JSON_SCANNER_C

#include "./scanner.h"
#include "token.h"

static paxb8
pax_json_byte_is_identifier(paxu8 byte, paxiword index)
{
    if (byte >= PAX_ASCII_LOWER_A && byte <= PAX_ASCII_LOWER_Z)
        return 1;

    if (byte >= PAX_ASCII_UPPER_A && byte <= PAX_ASCII_UPPER_Z)
        return 1;

    if (byte >= PAX_ASCII_ZERO && byte <= PAX_ASCII_NINE)
        return index != 0 ? 1 : 0;

    return 0;
}

static paxb8
pax_json_byte_is_number(paxu8 byte, paxiword index)
{
    if (byte >= PAX_ASCII_ZERO && byte <= PAX_ASCII_NINE)
        return 1;

    switch (byte) {
        case PAX_ASCII_PLUS:
        case PAX_ASCII_MINUS:
        case PAX_ASCII_POINT:
        case PAX_ASCII_LOWER_E:
        case PAX_ASCII_UPPER_E:
            return 1;

        default: break;
    }

    return 0;
}

static paxiword
pax_json_scanner_read_string(Pax_Scanner* self, paxu8* memory, paxiword length)
{
    paxu8    byte = 0;
    paxiword size = 0;

    if (pax_scanner_peek_byte(self, 0, &byte) > 0) {
        if (byte != PAX_ASCII_QUOTE)
            return 0;

        size += pax_scanner_drop(self, 1);
    }

    while (pax_scanner_peek_byte(self, 0, &byte) > 0) {
        if (size >= length) break;

        if (byte == PAX_ASCII_QUOTE)
            return size + pax_scanner_drop(self, 1);

        memory[size - 1]  = byte;
        size             += pax_scanner_drop(self, 1);
    }

    return size;
}

static paxiword
pax_json_scanner_read_number(Pax_Scanner* self, paxu8* memory, paxiword length)
{
    paxu8    byte = 0;
    paxiword size = 0;

    while (pax_scanner_peek_byte(self, 0, &byte) > 0) {
        if (pax_json_byte_is_number(byte, size) == 0)
            break;

        if (size >= length) break;

        memory[size]  = byte;
        size         += pax_scanner_drop(self, 1);
    }

    return size;
}

static paxiword
pax_json_scanner_read_identifier(Pax_Scanner* self, paxu8* memory, paxiword length)
{
    paxu8    byte = 0;
    paxiword size = 0;

    while (pax_scanner_peek_byte(self, 0, &byte) > 0) {
        if (pax_json_byte_is_identifier(byte, size) == 0)
            break;

        if (size >= length) break;

        memory[size]  = byte;
        size         += pax_scanner_drop(self, 1);
    }

    return size;
}

static paxu8
pax_json_scanner_drop_spaces(Pax_Scanner* self)
{
    pax_scanner_drop_cntrls(self);

    paxu8 byte = 0;

    if (pax_scanner_peek_byte(self, 0, &byte) <= 0)
        return 0;

    return byte;
}

Pax_JSON_Token
pax_scanner_read_json_operator(Pax_Scanner* self, Pax_Arena* arena, paxiword length)
{
    Pax_JSON_Token result = pax_json_token_error();
    paxu8          byte   = 0;

    paxiword size = pax_scanner_read_byte(self, 0, &byte);

    switch (byte) {
        case PAX_ASCII_BRACE_LEFT:   result = pax_json_token_object_open();  break;
        case PAX_ASCII_BRACE_RIGHT:  result = pax_json_token_object_close(); break;
        case PAX_ASCII_SQUARE_LEFT:  result = pax_json_token_array_open();   break;
        case PAX_ASCII_SQUARE_RIGHT: result = pax_json_token_array_close();  break;
        case PAX_ASCII_COMMA:        result = pax_json_token_comma();        break;
        case PAX_ASCII_COLON:        result = pax_json_token_colon();        break;

        default: break;
    }

    return result;
}

Pax_JSON_Token
pax_scanner_read_json_string(Pax_Scanner* self, Pax_Arena* arena, paxiword length)
{
    paxiword mark   = pax_arena_tell(arena);
    paxu8*   memory = pax_arena_reserve(arena, paxu8, length + 1);

    Pax_JSON_Token result = pax_json_token_error();

    paxiword size = pax_json_scanner_read_string(self, memory, length);

    if (size > 2 && size <= length) {
        Pax_String8 string = {0};

        string.memory = memory;
        string.length = size - 2;

        pax_arena_rewind(arena, mark, size - 1);

        return pax_json_token_string(string);
    }

    pax_arena_rewind(arena, mark, 0);

    return result;
}

Pax_JSON_Token
pax_scanner_read_json_number(Pax_Scanner* self, Pax_Arena* arena, paxiword length)
{
    paxiword mark   = pax_arena_tell(arena);
    paxu8*   memory = pax_arena_reserve(arena, paxu8, length + 1);

    Pax_JSON_Token result = pax_json_token_error();

    Pax_Format_Radix radix = PAX_FORMAT_RADIX_10;
    Pax_Format_Flag  flags = PAX_FORMAT_FLAG_PLUS;

    paxiword size = pax_json_scanner_read_number(self, memory, length);

    Pax_JSON_Token_Kind kind = PAX_JSON_TOKEN_KIND_UNSIGNED;

    for (paxiword i = 0; i < size; i += 1) {
        switch (memory[i]) {
            case PAX_ASCII_MINUS:
                if (kind < PAX_JSON_TOKEN_KIND_INTEGER)
                    kind = PAX_JSON_TOKEN_KIND_INTEGER;
            break;

            case PAX_ASCII_POINT:
            case PAX_ASCII_LOWER_E:
            case PAX_ASCII_UPPER_E:
                if (kind < PAX_JSON_TOKEN_KIND_FLOATING)
                    kind = PAX_JSON_TOKEN_KIND_FLOATING;
            break;

            default: break;
        }
    }

    switch (kind) {
        case PAX_JSON_TOKEN_KIND_UNSIGNED: {
            paxuword value = 0;

            if (pax_memory8_read_unsigned(memory, size, &value, radix, flags) != 0)
                result = pax_json_token_unsigned(value);
        } break;

        case PAX_JSON_TOKEN_KIND_INTEGER: {
            paxiword value = 0;

            if (pax_memory8_read_integer(memory, size, &value, radix, flags) != 0)
                result = pax_json_token_integer(value);
        } break;

        case PAX_JSON_TOKEN_KIND_FLOATING: {
            paxfword value = 0;

            // if (pax_memory8_read_floating(memory, size, &value, radix, flags) != 0)
            //     result = pax_json_token_floating(value);
        } break;

        default: break;
    }

    pax_arena_rewind(arena, mark, 0);

    return result;
}

Pax_JSON_Token
pax_scanner_read_json_identifier(Pax_Scanner* self, Pax_Arena* arena, paxiword length)
{
    paxiword mark   = pax_arena_tell(arena);
    paxu8*   memory = pax_arena_reserve(arena, paxu8, length + 1);

    Pax_JSON_Token result = pax_json_token_error();

    paxiword size = pax_json_scanner_read_identifier(self, memory, length);

    if (pax_string8_is_equal_memory8(pax_str8("true"), memory, size) != 0)
        result = pax_json_token_boolean(1);

    if (pax_string8_is_equal_memory8(pax_str8("false"), memory, size) != 0)
        result = pax_json_token_boolean(0);

    if (pax_string8_is_equal_memory8(pax_str8("null"), memory, size) != 0)
        result = pax_json_token_null();

    pax_arena_rewind(arena, mark, 0);

    return result;
}

Pax_JSON_Token
pax_scanner_read_json_token(Pax_Scanner* self, Pax_Arena* arena)
{
    Pax_JSON_Token result = pax_json_token_end();

    paxu8 byte = pax_json_scanner_drop_spaces(self);

    switch (byte) {
        case PAX_ASCII_NULL: return result;

        case PAX_ASCII_BRACE_LEFT:
        case PAX_ASCII_BRACE_RIGHT:
        case PAX_ASCII_SQUARE_LEFT:
        case PAX_ASCII_SQUARE_RIGHT:
        case PAX_ASCII_COMMA:
        case PAX_ASCII_COLON:
            result = pax_scanner_read_json_operator(self, arena, 256);
        break;

        case PAX_ASCII_QUOTE:
            result = pax_scanner_read_json_string(self, arena, PAX_MEMORY_KIB);
        break;

        case PAX_ASCII_PLUS:
        case PAX_ASCII_MINUS:
        case PAX_ASCII_ZERO:
        case PAX_ASCII_ONE:
        case PAX_ASCII_TWO:
        case PAX_ASCII_THREE:
        case PAX_ASCII_FOUR:
        case PAX_ASCII_FIVE:
        case PAX_ASCII_SIX:
        case PAX_ASCII_SEVEN:
        case PAX_ASCII_EIGHT:
        case PAX_ASCII_NINE:
            result = pax_scanner_read_json_number(self, arena, 256);
        break;

        case PAX_ASCII_LOWER_T:
        case PAX_ASCII_LOWER_F:
        case PAX_ASCII_LOWER_N:
            result = pax_scanner_read_json_identifier(self, arena, 256);
        break;

        default: result = pax_json_token_error(); break;
    }

    return result;
}

#endif // PAX_ENCODING_JSON_SCANNER_C
