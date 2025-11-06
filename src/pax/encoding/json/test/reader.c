#include "../export.h"
#include "../../../core/memory/export.h"

#include <stdio.h>

#define RED(x) "\x1b[91m" x "\x1b[0m"
#define GRN(x) "\x1b[92m" x "\x1b[0m"
#define YLW(x) "\x1b[93m" x "\x1b[0m"
#define BLU(x) "\x1b[94m" x "\x1b[0m"
#define MAG(x) "\x1b[95m" x "\x1b[0m"
#define CYA(x) "\x1b[96m" x "\x1b[0m"

typedef pxiword EntityTag;

#define ENTITY_TAGS_ITEMS px_as(pxiword, 16)

typedef struct EntityTags
{
    EntityTag items[ENTITY_TAGS_ITEMS];
    pxiword   size;
}
EntityTags;

typedef struct Entity
{
    PxString8 name;
    pxuword   code;

    EntityTags tags;
}
Entity;

#define ENTITY \
    pxs8("{\"name\": \"gio\", \"code\": 156, \"tags\": [1, -2, true, null, false, \"something\"]}")

pxb8
entityTagsReadJson(EntityTags* self, PxJsonReader* reader, PxArena* arena)
{
    PxJsonMsg message = {0};

    if (pxJsonReaderArrayOpen(reader, arena, &message) == 0) return 0;

    while (pxJsonReaderArrayClose(reader, arena, &message) == 0) {
        if (self->size < 0 || self->size >= ENTITY_TAGS_ITEMS)
            continue;

        switch (message.type) {
            case PX_JSON_MSG_STRING: {
                if (message.string_8.length > 0)
                    self->items[self->size] = message.string_8.memory[0];
            } break;

            case PX_JSON_MSG_UNSIGNED: {
                self->items[self->size] = message.unsigned_word;
            } break;

            case PX_JSON_MSG_INTEGER: {
                self->items[self->size] = message.integer_word;
            } break;

            case PX_JSON_MSG_BOOLEAN: {
                self->items[self->size] = message.boolean_word;
            } break;

            default: break;
        }

        self->size += 1;
    }

    return 1;
}

pxb8
entityReadJson(Entity* self, PxJsonReader* reader, PxArena* arena)
{
    PxJsonMsg message = {0};

    if (pxJsonReaderObjectOpen(reader, arena, &message) == 0) return 0;

    while (pxJsonReaderObjectClose(reader, arena, &message) == 0) {
        switch (message.type) {
            case PX_JSON_MSG_NAME: {
                if (pxString8IsEqual(message.name, pxs8("tags")) != 0)
                    entityTagsReadJson(&self->tags, reader, arena);
            } break;

            case PX_JSON_MSG_STRING: {
                if (pxString8IsEqual(message.name, pxs8("name")) != 0)
                    self->name = message.string_8;
            } break;

            case PX_JSON_MSG_UNSIGNED: {
                if (pxString8IsEqual(message.name, pxs8("code")) != 0)
                    self->code = message.unsigned_word;
            } break;

            default: break;
        }
    }

    return 1;
}

int
main(int argc, char** argv)
{
    PxArena   arena = pxMemoryReserve(16);
    PxBuffer8 items = pxBuffer8Reserve(&arena, 256);

    PxBuffer8 buffer = pxBuffer8Reserve(&arena, 256);

    PxSource source = pxBufferedSource(pxSourceFromBuffer8(&items), &buffer);

    Entity entity = {0};

    pxBuffer8WriteString8Tail(&items, ENTITY);

    printf(YLW("[start]") "\n%.*s\n" YLW("[stop]") "\n",
        px_as(int, items.size), items.memory);

    printf("\n");

    PxJsonReader reader =
        pxJsonReaderReserve(source, &arena, 16);

    entityReadJson(&entity, &reader, &arena);

    printf("name = %.*s\n",
        px_as(int, entity.name.length), entity.name.memory);

    printf("code = %llu\n", entity.code);

    for (pxiword i = 0; i < entity.tags.size; i += 1)
        printf("tag  = %lli\n", entity.tags.items[i]);
}
