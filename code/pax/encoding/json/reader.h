#ifndef PAX_ENCODING_JSON_READER_H
#define PAX_ENCODING_JSON_READER_H

#include "./scanner.h"
#include "./message.h"

typedef enum Pax_JSON_Reader_Flag
{
    PAX_JSON_READER_NONE  = 0,
    PAX_JSON_READER_COMMA = 1 << 0,
    PAX_JSON_READER_COLON = 1 << 1,
}
Pax_JSON_Reader_Flag;

typedef struct Pax_JSON_Reader
{
    Pax_Array_Ring stack;
    Pax_Scanner    scanner;

    Pax_JSON_Reader_Flag flags;
    Pax_JSON_Token       token;

    Pax_String8 name;
}
Pax_JSON_Reader;

typedef paxb8 (Pax_JSON_Reader_Proc) (void*, Pax_JSON_Reader*, Pax_Arena*);

Pax_JSON_Reader
pax_json_reader_create(Pax_Arena* arena, paxiword length, Pax_Scanner scanner);

Pax_JSON_Message
pax_json_reader_message(Pax_JSON_Reader* self, Pax_Arena* arena);

paxb8
pax_json_reader_record(Pax_JSON_Reader* self, Pax_Arena* arena, paxiword* size, Pax_JSON_Message* values, paxiword length);

paxb8
pax_json_reader_union(Pax_JSON_Reader* self, Pax_Arena* arena, paxiword* index, Pax_JSON_Message* values, paxiword length);

paxb8
pax_json_reader_array(Pax_JSON_Reader* self, Pax_Arena* arena, paxiword* size, Pax_JSON_Message* values, paxiword length);

#endif // PAX_ENCODING_JSON_READER_H
