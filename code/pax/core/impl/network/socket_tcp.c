#ifndef PAX_CORE_NETWORK_SOCKET_TCP_C
#define PAX_CORE_NETWORK_SOCKET_TCP_C

#include "./socket_tcp.h"

#if PAX_SYSTEM == PAX_SYSTEM_WINDOWS

    #include "../../win32/network/socket_tcp.c"

    #define __pax_socket_tcp_create__   pax_win32_socket_tcp_create
    #define __pax_socket_tcp_destroy__  pax_win32_socket_tcp_destroy
    #define __pax_socket_tcp_get_addr__ pax_win32_socket_tcp_get_addr
    #define __pax_socket_tcp_get_port__ pax_win32_socket_tcp_get_port
    #define __pax_socket_tcp_bind__     pax_win32_socket_tcp_bind
    #define __pax_socket_tcp_listen__   pax_win32_socket_tcp_listen
    #define __pax_socket_tcp_connect__  pax_win32_socket_tcp_connect
    #define __pax_socket_tcp_accept__   pax_win32_socket_tcp_accept
    #define __pax_socket_tcp_write__    pax_win32_socket_tcp_write
    #define __pax_socket_tcp_read__     pax_win32_socket_tcp_read

#elif PAX_SYSTEM == PAX_SYSTEM_LINUX

    #include "../../linux/network/socket_tcp.c"

    #define __pax_socket_tcp_create__   pax_linux_socket_tcp_create
    #define __pax_socket_tcp_destroy__  pax_linux_socket_tcp_destroy
    #define __pax_socket_tcp_get_addr__ pax_linux_socket_tcp_get_addr
    #define __pax_socket_tcp_get_port__ pax_linux_socket_tcp_get_port
    #define __pax_socket_tcp_bind__     pax_linux_socket_tcp_bind
    #define __pax_socket_tcp_listen__   pax_linux_socket_tcp_listen
    #define __pax_socket_tcp_connect__  pax_linux_socket_tcp_connect
    #define __pax_socket_tcp_accept__   pax_linux_socket_tcp_accept
    #define __pax_socket_tcp_write__    pax_linux_socket_tcp_write
    #define __pax_socket_tcp_read__     pax_linux_socket_tcp_read

#else

    #error "Unknown platform"

#endif

Pax_Socket_TCP
pax_socket_tcp_create(Pax_Arena* arena, Pax_Addr_Kind kind)
{
    return __pax_socket_tcp_create__(arena, kind);
}

void
pax_socket_tcp_destroy(Pax_Socket_TCP self)
{
    __pax_socket_tcp_destroy__(self);
}

Pax_Addr
pax_socket_tcp_get_addr(Pax_Socket_TCP self)
{
    return __pax_socket_tcp_get_addr__(self);
}

paxu16
pax_socket_tcp_get_port(Pax_Socket_TCP self)
{
    return __pax_socket_tcp_get_port__(self);
}

paxb8
pax_socket_tcp_bind(Pax_Socket_TCP self, Pax_Addr addr, paxu16 port)
{
    return __pax_socket_tcp_bind__(self, addr, port);
}

paxb8
pax_socket_tcp_listen(Pax_Socket_TCP self)
{
    return __pax_socket_tcp_listen__(self);
}

paxb8
pax_socket_tcp_connect(Pax_Socket_TCP self, Pax_Addr addr, paxu16 port)
{
    return __pax_socket_tcp_connect__(self, addr, port);
}

Pax_Socket_TCP
pax_socket_tcp_accept(Pax_Socket_TCP self, Pax_Arena* arena)
{
    return __pax_socket_tcp_accept__(self, arena);
}

paxiword
pax_socket_tcp_write(Pax_Socket_TCP self, paxu8* memory, paxiword length)
{
    return __pax_socket_tcp_write__(self, memory, length);
}

paxiword
pax_socket_tcp_read(Pax_Socket_TCP self, paxu8* memory, paxiword length)
{
    return __pax_socket_tcp_read__(self, memory, length);
}

Pax_Source*
pax_source_from_socket_tcp(Pax_Arena* arena, Pax_Socket_TCP self)
{
    Pax_Source result = {0};

    if (self == 0) return 0;

    result.ctxt = self;
    result.proc = &pax_socket_tcp_read;

    return pax_arena_clone(arena, Pax_Source, &result, 1);
}

Pax_Target*
pax_target_from_socket_tcp(Pax_Arena* arena, Pax_Socket_TCP self)
{
    Pax_Target result = {0};

    if (self == 0) return 0;

    result.ctxt = self;
    result.proc = &pax_socket_tcp_write;

    return pax_arena_clone(arena, Pax_Target, &result, 1);
}

#endif // PAX_CORE_NETWORK_SOCKET_TCP_C
