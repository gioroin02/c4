#ifndef C4_SERVER_C
#define C4_SERVER_C

#include "server.h"

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

C4Server
c4ServerMake(PxArena* arena, pxiword length, PxAddressType type)
{
    PxArray sessions =
        pxArrayReserve(arena, C4Session*, length);

    if (sessions.length <= 0) return (C4Server) {0};

    PxSocketTcp socket = pxSocketTcpCreate(arena, type);

    if (socket == 0) return (C4Server) {0};

    return (C4Server) {
        .socket   = socket,
        .sessions = sessions,
    };
}

pxb8
c4ServerStart(C4Server* self, PxAddress address, pxu16 port)
{
    printf(TRACE " Attivazione porta " YELLOW("%u") ": ", port);

    pxb8 state =
        pxSocketTcpBind(self->socket, address, port);

    printf("%s\n", state != 0 ?
        GREEN("SUCCEDED") : RED("FAILED"));

    if (state != 0) {
        printf(TRACE " Ascolto porta: ");

        state = pxSocketTcpListen(self->socket);

        printf("%s\n", state != 0 ?
            GREEN("SUCCEDED") : RED("FAILED"));
    }

    return state;
}

void
c4ServerStop(C4Server* self)
{
    if (self == 0) return;

    for (pxiword i = 0; i < self->sessions.size; i += 1) {
        C4Session* session = 0;

        pxArrayRead(&self->sessions, i,
            C4Session*, &session);

        c4SessionClose(self, session);
    }

    pxSocketTcpDestroy(self->socket);

    self->socket = 0;
}

void
c4ServerBroadcast(C4Server* self, PxArena* arena, C4Session* from, C4Message value)
{
    for (pxiword i = 0; i < self->sessions.size; i += 1) {
        C4Session* session = 0;

        pxArrayRead(&self->sessions, i,
            C4Session*, &session);

        if (session == from) continue;

        c4SessionWrite(session, arena, value);
    }
}

pxiword
c4ServerFind(C4Server* self, C4Session* value)
{
    for (pxiword i = 0; i < self->sessions.size; i += 1) {
        C4Session* session = 0;

        pxArrayRead(&self->sessions, i,
            C4Session*, &session);

        if (session == value) return i + 1;
    }

    return 0;
}

pxb8
c4ServerGet(C4Server* self, pxiword index, C4Session** value)
{
    return pxArrayRead(&self->sessions, index, C4Session*, value);
}

C4Session*
c4ServerGetOr(C4Server* self, pxiword index, C4Session* value)
{
    C4Session* result = 0;

    if (pxArrayRead(&self->sessions, index, C4Session*, &result) == 0)
        return value;

    return result;
}

C4Session*
c4SessionOpen(C4Server* self, PxArena* arena)
{
    printf(TRACE " Apertura sessione... ");

    pxiword size   = self->sessions.size;
    pxiword length = self->sessions.length;
    pxiword offset = pxArenaOffset(arena);

    if (size < 0 || size >= length) return 0;

    C4Session* result = pxArenaReserve(arena, C4Session, 1);

    if (result == 0) return 0;

    result->socket = pxSocketTcpAccept(self->socket, arena);

    if (result->socket != 0) {
        pxArrayInsertTail(&self->sessions,
            C4Session*, &result);

        PxAddress address = pxSocketTcpGetAddress(result->socket);
        pxu16     port    = pxSocketTcpGetPort(result->socket);

        printf("con {addr = [");

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

        printf("], port = " YELLOW("%u") "}: %s\n", port,
            result != 0 ? GREEN("SUCCEDED") : RED("FAILED"));

        return result;
    }

    pxArenaRewind(arena, offset);

    return 0;
}

pxb8
c4SessionClose(C4Server* self, C4Session* session)
{
    pxiword index = c4ServerFind(self, session);
    pxb8    state = 0;

    if (index == 0) return 0;

    state = pxArrayRemove(&self->sessions,
        index - 1, C4Session*, &session);

    if (state != 0)
        pxSocketTcpDestroy(session->socket);

    return state;
}

pxb8
c4SessionWrite(C4Session* self, PxArena* arena, C4Message value)
{
    printf(TRACE " Scrittura di ");

    pxiword offset = pxArenaOffset(arena);

    c4ShowMessage(&value);

    PxJsonWriter writer = pxJsonWriterMake(arena, 4,
        pxSocketTcpWriter(self->socket, &self->request));

    pxb8 state = c4JsonWriteMessage(&value, &writer, arena);

    pxArenaRewind(arena, offset);

    printf("%s\n", state != 0 ?
        GREEN("SUCCEDED") : RED("FAILED"));

    return state;
}

C4Message
c4SessionRead(C4Session* self, PxArena* arena)
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

#endif // C4_SERVER_C
