#ifndef PAX_CORE_FORMAT_SCANNER_C
#define PAX_CORE_FORMAT_SCANNER_C

#include "./scanner.h"

Pax_Scanner
pax_scanner_create(Pax_Arena* arena, paxiword length, Pax_Source* source)
{
    if (source == 0) return (Pax_Scanner) {0};

    return (Pax_Scanner) {
        .buffer = pax_buffer8_create(arena, length),
        .source = source,
    };
}

paxiword
pax_scanner_peek_memory8(Pax_Scanner* self, paxiword offset, paxu8* memory, paxiword length)
{
    paxiword size = 0;
    paxiword temp = 1;

    if (memory == 0 || length <= 0 || offset < 0) return 0;

    for (; size < length && temp > 0; size += temp) {
        paxiword elements = pax_buffer8_elements(&self->buffer);
        paxiword capacity = pax_buffer8_capacity(&self->buffer);

        if (elements <= offset + size) {
            if (offset + size > capacity - elements)
                break;

            pax_source_read_buffer8(self->source, &self->buffer);
        }

        temp = pax_buffer8_peek_memory8(&self->buffer,
            offset + size, memory + size, length - size);
    }

    return size;
}

paxiword
pax_scanner_peek_byte(Pax_Scanner* self, paxiword offset, paxu8* value)
{
    return pax_scanner_peek_memory8(self, offset, value, 1);
}

paxiword
pax_scanner_peek_unicode(Pax_Scanner* self, paxiword offset, paxi32* value)
{
    return 0;
}

paxiword
pax_scanner_read_memory8(Pax_Scanner* self, paxiword offset, paxu8* memory, paxiword length)
{
    paxiword size = 0;
    paxiword temp = 1;

    if (pax_scanner_drop(self, offset) < offset) return 0;

    for (; size < length && temp > 0; size += temp) {
        paxiword elements = pax_buffer8_elements(&self->buffer);

        if (elements <= 0)
            pax_source_read_buffer8(self->source, &self->buffer);

        temp = pax_buffer8_read_head_memory8(&self->buffer,
            memory + size, length - size);
    }

    return size;
}

paxiword
pax_scanner_read_byte(Pax_Scanner* self, paxiword offset, paxu8* value)
{
    return pax_scanner_read_memory8(self, offset, value, 1);
}

paxiword
pax_scanner_read_unicode(Pax_Scanner* self, paxiword offset, paxi32* value)
{
    return 0;
}

paxiword
pax_scanner_drop(Pax_Scanner* self, paxiword length)
{
    paxiword size = 0;
    paxiword temp = 1;

    for (; size < length && temp > 0; size += temp) {
        paxiword elements = pax_buffer8_elements(&self->buffer);

        if (elements <= 0)
            pax_source_read_buffer8(self->source, &self->buffer);

        temp = pax_buffer8_drop_head(&self->buffer, length - size);
    }

    return size;
}

paxiword
pax_scanner_drop_cntrls(Pax_Scanner* self)
{
    paxiword size = 0;
    paxu8    byte = 0;

    while (pax_scanner_peek_byte(self, 0, &byte) > 0) {
        if (pax_unicode_is_ascii_cntrl(byte) == 0)
            break;

        size += pax_scanner_drop(self, 1);
    }

    return size;
}

#endif // PAX_CORE_FORMAT_SCANNER_C
