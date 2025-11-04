#ifndef PAX_CORE_NETWORK_SOCKET_UDP_C
#define PAX_CORE_NETWORK_SOCKET_UDP_C

#include "./socket_udp.h"

#if PAX_SYSTEM == PAX_SYSTEM_WINDOWS

    #include "../../win32/network/socket_udp.c"

    #define __pax_socket_udp_create__     pax_win32_socket_udp_create
    #define __pax_socket_udp_destroy__    pax_win32_socket_udp_destroy
    #define __pax_socket_udp_get_addr__   pax_win32_socket_udp_get_addr
    #define __pax_socket_udp_get_port__   pax_win32_socket_udp_get_port
    #define __pax_socket_udp_bind__       pax_win32_socket_udp_bind
    #define __pax_socket_udp_listen__     pax_win32_socket_udp_listen
    #define __pax_socket_udp_connect__    pax_win32_socket_udp_connect
    #define __pax_socket_udp_accept__     pax_win32_socket_udp_accept
    #define __pax_socket_udp_write__      pax_win32_socket_udp_write
    #define __pax_socket_udp_write_host__ pax_win32_socket_udp_write_host
    #define __pax_socket_udp_read__       pax_win32_socket_udp_read
    #define __pax_socket_udp_read_host__  pax_win32_socket_udp_read_host

#elif PAX_SYSTEM == PAX_SYSTEM_LINUX

    #include "../../linux/network/socket_udp.c"

    #define __pax_socket_udp_create__     pax_linux_socket_udp_create
    #define __pax_socket_udp_destroy__    pax_linux_socket_udp_destroy
    #define __pax_socket_udp_get_addr__   pax_linux_socket_udp_get_addr
    #define __pax_socket_udp_get_port__   pax_linux_socket_udp_get_port
    #define __pax_socket_udp_bind__       pax_linux_socket_udp_bind
    #define __pax_socket_udp_listen__     pax_linux_socket_udp_listen
    #define __pax_socket_udp_connect__    pax_linux_socket_udp_connect
    #define __pax_socket_udp_accept__     pax_linux_socket_udp_accept
    #define __pax_socket_udp_write__      pax_linux_socket_udp_write
    #define __pax_socket_udp_write_host__ pax_linux_socket_udp_write_host
    #define __pax_socket_udp_read__       pax_linux_socket_udp_read
    #define __pax_socket_udp_read_host__  pax_linux_socket_udp_read_host

#else

    #error "Unknown platform"

#endif

Pax_Socket_UDP
pax_socket_udp_create(Pax_Arena* arena, Pax_Addr_Kind kind)
{
    return __pax_socket_udp_create__(arena, kind);
}

void
pax_socket_udp_destroy(Pax_Socket_UDP self)
{
    __pax_socket_udp_destroy__(self);
}

Pax_Addr
pax_socket_udp_get_addr(Pax_Socket_UDP self)
{
    return __pax_socket_udp_get_addr__(self);
}

paxu16
pax_socket_udp_get_port(Pax_Socket_UDP self)
{
    return __pax_socket_udp_get_port__(self);
}

paxb8
pax_socket_udp_bind(Pax_Socket_UDP self, Pax_Addr addr, paxu16 port)
{
    return __pax_socket_udp_bind__(self, addr, port);
}

paxb8
pax_socket_udp_listen(Pax_Socket_UDP self)
{
    return __pax_socket_udp_listen__(self);
}

paxb8
pax_socket_udp_connect(Pax_Socket_UDP self, Pax_Addr addr, paxu16 port)
{
    return __pax_socket_udp_connect__(self, addr, port);
}

Pax_Socket_UDP
pax_socket_udp_accept(Pax_Socket_UDP self, Pax_Arena* arena)
{
    return __pax_socket_udp_accept__(self, arena);
}

paxiword
pax_socket_udp_write(Pax_Socket_UDP self, paxu8* memory, paxiword length)
{
    return __pax_socket_udp_write__(self, memory, length);
}

paxiword
pax_socket_udp_write_host(Pax_Socket_UDP self, paxu8* memory, paxiword length, Pax_Addr addr, paxu16 port)
{
    return __pax_socket_udp_write_host__(self, memory, length, addr, port);
}

paxiword
pax_socket_udp_read(Pax_Socket_UDP self, paxu8* memory, paxiword length)
{
    return __pax_socket_udp_read__(self, memory, length);
}

paxiword
pax_socket_udp_read_host(Pax_Socket_UDP self, paxu8* memory, paxiword length, Pax_Addr* addr, paxu16* port)
{
    return __pax_socket_udp_read_host__(self, memory, length, addr, port);
}

#endif // PAX_CORE_NETWORK_SOCKET_UDP_C
