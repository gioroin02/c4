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
entityTagsWriteJson(EntityTags* self, PxJsonWriter* writer, PxArena* arena)
{
    pxJsonWriterArrayOpen(writer, arena);

    for (pxiword i = 0; i < self->size; i += 1)
        pxJsonWriterMsg(writer, arena, pxJsonMsgUnsigned(self->items[i]));

    pxJsonWriterArrayClose(writer, arena);

    return 1;
}

pxb8
entityWriteJson(Entity* self, PxJsonWriter* writer, PxArena* arena)
{
    pxJsonWriterObjectOpen(writer, arena);

    pxJsonWriterList(writer, arena, (PxJsonMsg[]) {
        pxJsonMsgPair(pxs8("tags"), pxJsonMsgDelegate(&self->tags, &entityTagsWriteJson)),
        pxJsonMsgPair(pxs8("name"), pxJsonMsgString(self->name)),
        pxJsonMsgPair(pxs8("code"), pxJsonMsgUnsigned(self->code)),
    }, 2);

    pxJsonWriterObjectClose(writer, arena);

    return 1;
}

int
main(int argc, char** argv)
{
    PxArena   arena  = pxMemoryReserve(16);
    PxBuffer8 buffer = pxBuffer8Reserve(&arena, 256);
    PxTarget  target = pxTargetFromBuffer8(&buffer);

    PxJsonWriter writer = pxJsonWriterReserve(target, &arena, 16);

    entityWriteJson(&(Entity) {
        .name = pxs8("gio"),
        .code = 156,
        .tags = {
            .items = {1, 2, 3},
            .size = 3
        }
    }, &writer, &arena);

    printf(YLW("[start]") "\n%.*s\n" YLW("[stop]") "\n",
        px_as(int, buffer.size), buffer.memory);
}
