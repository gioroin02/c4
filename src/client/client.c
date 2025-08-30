#ifndef C4_CLIENT_C
#define C4_CLIENT_C

#include "client.h"

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

#define FATAL PURPLE("FATAL")
#define ERROR RED("ERROR")
#define WARN  YELLOW("WARN")
#define INFO  BLUE("INFO")
#define DEBUG GREEN("DEBUG")
#define TRACE AZURE("TRACE")

C4Client
c4ClientMake(PxArena* arena, PxAddressType type)
{
    return (C4Client) {
        .socket = pxSocketTcpCreate(arena, type),
    };
}

pxb8
c4ClientStart(C4Client* self, PxAddress address, pxu16 port)
{
    printf(TRACE " Apertura sessione con {addr = [");

    switch (address.type) {
        case PX_ADDRESS_TYPE_IP4: {
            for (pxiword i = 0; i < PX_ADDRESS_IP4_GROUPS; i += 1) {
                printf(YELLOW("%u"), address.ip4.memory[i]);

                if (i + 1 != PX_ADDRESS_IP4_GROUPS)
                    printf(YELLOW("."));
            }
        } break;

        case PX_ADDRESS_TYPE_IP6: {
            for (pxiword i = 0; i < PX_ADDRESS_IP6_GROUPS; i += 1) {
                printf(YELLOW("%x"), address.ip6.memory[i]);

                if (i + 1 != PX_ADDRESS_IP6_GROUPS)
                    printf(YELLOW(":"));
            }
        } break;

        default: break;
    }

    printf("], port = " YELLOW("%u") "}: ", port);

    pxb8 state = pxSocketTcpConnect(self->socket, address, port);

    printf("%s\n", state != 0 ?
        GREEN("SUCCEDED") : RED("FAILED"));

    return state;
}

void
c4ClientStop(C4Client* self)
{
    if (self == 0) return;

    pxSocketTcpDestroy(self->socket);

    self->socket = 0;
}

pxb8
c4ClientWrite(C4Client* self, PxArena* arena, C4Message value)
{
    printf(TRACE " Scrittura di ");

    pxiword offset = pxArenaOffset(arena);

    c4ShowMessage(&value);

    PxJsonWriter writer = pxJsonWriterMake(arena, 4,
        pxSocketTcpWriter(self->socket, &self->response));

    pxb8 state = c4JsonWriteMessage(&value, &writer, arena);

    pxArenaRewind(arena, offset);

    printf("%s\n", state != 0 ?
        GREEN("SUCCEDED") : RED("FAILED"));

    return state;
}

C4Message
c4ClientRead(C4Client* self, PxArena* arena)
{
    printf(TRACE " Lettura di... ");

    C4Message result = {0};
    pxiword   offset = pxArenaOffset(arena);

    PxJsonReader reader = pxJsonReaderMake(arena, 4,
        pxSocketTcpReader(self->socket, &self->request));

    pxb8 state = c4JsonReadMessage(&result, &reader, arena);

    c4ShowMessage(&result);

    pxArenaRewind(arena, offset);

    printf("%s\n", state != 0 ?
        GREEN("SUCCEDED") : RED("FAILED"));

    return result;
}

#endif // C4_CLIENT_C
