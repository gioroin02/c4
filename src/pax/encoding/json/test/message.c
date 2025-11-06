#include "../export.h"
#include "../../../core/memory/export.h"

#include <stdio.h>

#define RED(x) "\x1b[91m" x "\x1b[0m"
#define GRN(x) "\x1b[92m" x "\x1b[0m"
#define YLW(x) "\x1b[93m" x "\x1b[0m"
#define BLU(x) "\x1b[94m" x "\x1b[0m"
#define MAG(x) "\x1b[95m" x "\x1b[0m"
#define CYA(x) "\x1b[96m" x "\x1b[0m"

#define ENTITY \
    pxs8("{\n\t\"flags\": [16, 32],\n\t\"code\": 156,\n\t\"name\": \"player\",\n\t\"coords\": {\"x\": -1, \"y\": +2, \"z\": null},\n\t\"alive\": true,\n\t\"pause\": false\n}")

void
showJsonMsg(PxJsonReader* reader, PxArena* arena)
{
    PxJsonMsg message = {0};

    while (message.type != PX_JSON_MSG_COUNT) {
        pxiword offset = pxArenaOffset(arena);

        message = pxJsonReaderMsg(reader, arena);

        if (message.type == PX_JSON_MSG_COUNT) break;

        printf("[%4lli] ", offset);

        switch (message.type) {
            case PX_JSON_MSG_ERROR: {
                printf(RED("ERROR"));

                message.type = PX_JSON_MSG_COUNT;
            } break;

            case PX_JSON_MSG_OBJECT_OPEN:
                printf("{");
            break;

            case PX_JSON_MSG_OBJECT_CLOSE:
                printf("}");
            break;

            case PX_JSON_MSG_ARRAY_OPEN:
                printf("[");
            break;

            case PX_JSON_MSG_ARRAY_CLOSE:
                printf("]");
            break;

            case PX_JSON_MSG_NAME:
                printf(CYA("'%.*s'"), px_as(int, message.name.length),
                    message.name.memory);
            break;

            case PX_JSON_MSG_STRING: {
                if (message.name.length > 0) {
                    printf(CYA("'%.*s'") ": ", px_as(int, message.name.length),
                        message.name.memory);
                }

                printf(BLU("'%.*s'"),
                    px_as(int, message.string_8.length), message.string_8.memory);
            } break;

            case PX_JSON_MSG_UNSIGNED: {
                if (message.name.length > 0) {
                    printf(CYA("'%.*s'") ": ", px_as(int, message.name.length),
                        message.name.memory);
                }

                printf(MAG("%llu"), message.unsigned_word);
            } break;

            case PX_JSON_MSG_INTEGER: {
                if (message.name.length > 0) {
                    printf(CYA("'%.*s'") ": ", px_as(int, message.name.length),
                        message.name.memory);
                }

                printf(MAG("%lli"), message.integer_word);
            } break;

            case PX_JSON_MSG_FLOATING: {
                if (message.name.length > 0) {
                    printf(CYA("'%.*s'") ": ", px_as(int, message.name.length),
                        message.name.memory);
                }

                printf(MAG("%lf"), message.floating_word);
            } break;

            case PX_JSON_MSG_BOOLEAN: {
                if (message.name.length > 0) {
                    printf(CYA("'%.*s'") ": ", px_as(int, message.name.length),
                        message.name.memory);
                }

                printf("%s", message.boolean_word != 0 ? GRN("true") : RED("false"));
            } break;

            case PX_JSON_MSG_NULL: {
                if (message.name.length > 0) {
                    printf(CYA("'%.*s'") ": ", px_as(int, message.name.length),
                        message.name.memory);
                }

                printf(YLW("null"));
            } break;

            default: break;
        }

        printf("\n");
    }
}

int
main(int argc, char** argv)
{
    PxArena   arena = pxMemoryReserve(16);
    PxBuffer8 items = pxBuffer8Reserve(&arena, 256);

    PxBuffer8 buffer = pxBuffer8Reserve(&arena, 256);

    PxSource source = pxBufferedSource(pxSourceFromBuffer8(&items), &buffer);

    pxBuffer8WriteString8Tail(&items, ENTITY);

    printf(YLW("[start]") "\n%.*s\n" YLW("[stop]") "\n",
        px_as(int, items.size), items.memory);

    printf("\n");

    PxJsonReader reader = pxJsonReaderReserve(source, &arena, 16);

    showJsonMsg(&reader, &arena);
}
