#include "../export.h"
#include "../../../core/memory/export.h"

#include <stdio.h>

#define COLOR_RESET "\x1b[0m"

#define FRONT_RED    "\x1b[31m"
#define FRONT_GREEN  "\x1b[32m"
#define FRONT_YELLOW "\x1b[33m"
#define FRONT_BLUE   "\x1b[34m"
#define FRONT_PURPLE "\x1b[35m"
#define FRONT_AZURE  "\x1b[36m"

#define RED(expr)    FRONT_RED    expr COLOR_RESET
#define GREEN(expr)  FRONT_GREEN  expr COLOR_RESET
#define YELLOW(expr) FRONT_YELLOW expr COLOR_RESET
#define BLUE(expr)   FRONT_BLUE   expr COLOR_RESET
#define PURPLE(expr) FRONT_PURPLE expr COLOR_RESET
#define AZURE(expr)  FRONT_AZURE  expr COLOR_RESET

#define ENTITY \
    pxs8("{ \"flags\": [16, 32], \"code\": 156, \"name\": \"player\", \"coords\": {\"x\": -1, \"y\": +2, \"z\": null}, \"alive\": true, \"pause\": false }")

void
showJsonMsg(PxJsonReader* reader, PxArena* arena)
{
    PxJsonMsg message = pxJsonMsgNone();

    while (message.type != PX_JSON_MSG_COUNT) {
        message = pxJsonReadMessage(reader, arena);

        if (message.type == PX_JSON_MSG_COUNT) break;

        switch (message.type) {
            case PX_JSON_MSG_ERROR: {
                PxString8 content = message.error.content;
                PxString8 subject = message.error.subject;

                printf(RED("%.*s: %.*s"),
                    pxCast(int, content.length), content.memory,
                    pxCast(int, subject.length), subject.memory);

                message.type = PX_JSON_MSG_COUNT;
            } break;

            case PX_JSON_MSG_OBJECT_OPEN:
                printf("OBJECT_OPEN");
            break;

            case PX_JSON_MSG_OBJECT_CLOSE:
                printf("OBJECT_CLOSE");
            break;

            case PX_JSON_MSG_ARRAY_OPEN:
                printf("ARRAY_OPEN");
            break;

            case PX_JSON_MSG_ARRAY_CLOSE:
                printf("ARRAY_CLOSE");
            break;

            case PX_JSON_MSG_NAME:
                printf(AZURE("%.*s"), pxCast(int, message.name.length),
                    message.name.memory);
            break;

            case PX_JSON_MSG_STRING: {
                if (message.name.length > 0) {
                    printf(AZURE("'%.*s'") ": ", pxCast(int, message.name.length),
                        message.name.memory);
                }

                printf(BLUE("'%.*s'"),
                    pxCast(int, message.string_8.length), message.string_8.memory);
            } break;

            case PX_JSON_MSG_UNSIGNED: {
                if (message.name.length > 0) {
                    printf(AZURE("'%.*s'") ": ", pxCast(int, message.name.length),
                        message.name.memory);
                }

                printf(PURPLE("%llu"), message.unsigned_word);
            } break;

            case PX_JSON_MSG_INTEGER: {
                if (message.name.length > 0) {
                    printf(AZURE("'%.*s'") ": ", pxCast(int, message.name.length),
                        message.name.memory);
                }

                printf(PURPLE("%lli"), message.integer_word);
            } break;

            case PX_JSON_MSG_FLOATING: {
                if (message.name.length > 0) {
                    printf(AZURE("'%.*s'") ": ", pxCast(int, message.name.length),
                        message.name.memory);
                }

                printf(PURPLE("%lf"), message.floating_word);
            } break;

            case PX_JSON_MSG_BOOLEAN: {
                if (message.name.length > 0) {
                    printf(AZURE("'%.*s'") ": ", pxCast(int, message.name.length),
                        message.name.memory);
                }

                printf("%s", message.boolean_word != 0 ? GREEN("true") : RED("false"));
            } break;

            case PX_JSON_MSG_NULL: {
                if (message.name.length > 0) {
                    printf(AZURE("'%.*s'") ": ", pxCast(int, message.name.length),
                        message.name.memory);
                }

                printf(PURPLE("null"));
            } break;

            default: break;
        }

        printf("\n");
    }
}

int
main(int argc, char** argv)
{
    PxArena   arena       = pxMemoryReserve(16);
    PxBuffer8 source      = pxBuffer8Reserve(&arena, 256);
    PxReader  buff_reader = pxBufferReader(&source, &arena, 256);

    pxBuffer8WriteString8Tail(&source, ENTITY);

    printf(YELLOW("[start]") "\n%.*s\n" YELLOW("[stop]") "\n",
        pxCast(int, source.size), source.memory);

    printf("\n");

    PxJsonReader reader =
        pxJsonReaderMake(&arena, 16, &buff_reader);

    showJsonMsg(&reader, &arena);
}
