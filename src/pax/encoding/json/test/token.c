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
showJsonToken(PxSource source, PxArena* arena)
{
    PxJsonToken token = {0};

    while (token.type != PX_JSON_TOKEN_COUNT) {
        pxiword offset = pxArenaOffset(arena);

        token = pxSourceReadJsonToken(source, arena);

        if (token.type == PX_JSON_TOKEN_COUNT) break;

        printf("[%4lli] ", offset);

        switch (token.type) {
            case PX_JSON_TOKEN_ERROR: {
                printf(RED("ERROR"));

                token.type = PX_JSON_TOKEN_COUNT;
            } break;

            case PX_JSON_TOKEN_OBJECT_OPEN:
                printf("{");
            break;

            case PX_JSON_TOKEN_OBJECT_CLOSE:
                printf("}");
            break;

            case PX_JSON_TOKEN_ARRAY_OPEN:
                printf("[");
            break;

            case PX_JSON_TOKEN_ARRAY_CLOSE:
                printf("]");
            break;

            case PX_JSON_TOKEN_COLON:
                printf(":");
            break;

            case PX_JSON_TOKEN_COMMA:
                printf(",");
            break;

            case PX_JSON_TOKEN_STRING:
                printf(BLU("'%.*s'"),
                    px_as(int, token.string_8.length), token.string_8.memory);
            break;

            case PX_JSON_TOKEN_UNSIGNED:
                printf(MAG("%llu"), token.unsigned_word);
            break;

            case PX_JSON_TOKEN_INTEGER:
                printf(MAG("%lli"), token.integer_word);
            break;

            case PX_JSON_TOKEN_FLOATING:
                printf(MAG("%lf"), token.floating_word);
            break;

            case PX_JSON_TOKEN_BOOLEAN:
                printf("%s", token.boolean_word != 0 ? GRN("true") : RED("false"));
            break;

            case PX_JSON_TOKEN_NULL:
                printf(YLW("null"));
            break;

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

    pxBuffer8WriteString8Tail(&items, ENTITY);

    printf(YLW("[start]") "\n%.*s\n" YLW("[stop]") "\n",
        px_as(int, items.size), items.memory);

    printf("\n");

    PxBuffer8 buffer = pxBuffer8Reserve(&arena, 256);

    PxSource source = pxBufferedSource(
        pxSourceFromBuffer8(&items), &buffer);

    showJsonToken(source, &arena);
}
