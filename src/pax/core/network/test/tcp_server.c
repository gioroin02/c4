#include "../export.h"

#include <stdio.h>

#define RED(x) "\x1b[91m" x "\x1b[0m"
#define GRN(x) "\x1b[92m" x "\x1b[0m"
#define YLW(x) "\x1b[93m" x "\x1b[0m"
#define BLU(x) "\x1b[94m" x "\x1b[0m"
#define MAG(x) "\x1b[95m" x "\x1b[0m"
#define CYA(x) "\x1b[96m" x "\x1b[0m"

#define FATAL MAG("FATAL")
#define ERROR RED("ERROR")
#define WARN  YLW("WARN")
#define INFO  BLU("INFO")
#define DEBUG GRN("DEBUG")
#define TRACE CYA("TRACE")

#define SERVER_MSG pxs8("Hello client!")

#define SERVER_ARG_IP4      pxs8("--server-ipv4")
#define SERVER_ARG_IP6      pxs8("--server-ipv6")
#define SERVER_ARG_PORT     pxs8("--server-port=")
#define SERVER_ARG_LIFETIME pxs8("--server-lifetime=")

typedef struct ServerConfig
{
    PxAddrType type;
    pxuword    port;
    pxuword    lifetime;
}
ServerConfig;

typedef struct Server
{
    PxSocketTcp socket;
}
Server;

typedef struct ServerSession
{
    PxSocketTcp socket;

    PxBuffer8 request;
    PxBuffer8 response;
}
ServerSession;

int
main(int argc, char** argv)
{
    PxArena arena = pxMemoryReserve(16);

    if (pxNetworkStart() == 0) return 1;

    ServerConfig config = {
        .type     = PX_ADDR_TYPE_IP4,
        .port     = 8000,
        .lifetime = 1,
    };

    if (argc > 1) {
        for (pxiword i = 1; i < argc; i += 1) {
            PxString8 arg = pxString8FromMemory(argv[i], 32);

            if (pxString8IsEqual(arg, SERVER_ARG_IP4) != 0) config.type = PX_ADDR_TYPE_IP4;
            if (pxString8IsEqual(arg, SERVER_ARG_IP6) != 0) config.type = PX_ADDR_TYPE_IP6;

            if (pxString8BeginsWith(arg, SERVER_ARG_PORT) != 0) {
                arg = pxString8TrimPrefix(arg, SERVER_ARG_PORT);
                arg = pxString8TrimSpaces(arg);

                pxUnsignedFromString8(arg, &config.port, PX_FORMAT_RADIX_10, 0);
            }

            if (pxString8BeginsWith(arg, SERVER_ARG_LIFETIME) != 0) {
                arg = pxString8TrimPrefix(arg, SERVER_ARG_LIFETIME);
                arg = pxString8TrimSpaces(arg);

                pxUnsignedFromString8(arg, &config.lifetime, PX_FORMAT_RADIX_10, 0);
            }
        }
    }

    Server server = {0};

    server.socket = pxSocketTcpCreate(&arena, config.type);

    if (server.socket == 0) return 1;

    PxAddr addr = pxAddrAny(config.type);

    if (pxSocketTcpBind(server.socket, addr, config.port) == 0)
        return 1;

    if (pxSocketTcpListen(server.socket) == 0) return 1;

    pxiword offset = pxArenaOffset(&arena);

    for (pxu32 i = 0; i < config.lifetime; i += 1) {
        ServerSession session = {0};

        session.socket = pxSocketTcpAccept(server.socket, &arena);

        if (session.socket == 0) continue;

        session.request  = pxBuffer8Reserve(&arena, PX_MEMORY_KIB);
        session.response = pxBuffer8Reserve(&arena, PX_MEMORY_KIB);

        PxSource source = pxSourceFromSocketTcp(session.socket);
        PxTarget target = pxTargetFromSocketTcp(session.socket);

        pxiword size = pxSourceReadBuffer8(source, &session.request);

        if (size != 0) {
            PxString8 string = pxBuffer8ReadString8Head(
                &session.request, &arena, session.request.size);

            printf(INFO " " BLU("'%s'") "\n", string.memory);

            pxBuffer8WriteString8Tail(&session.response, SERVER_MSG);

            pxTargetWriteBuffer8(target, &session.response);
        }

        pxSocketTcpDestroy(session.socket);

        pxArenaRewind(&arena, offset);
    }

    pxSocketTcpDestroy(server.socket);

    pxNetworkStop();
}
