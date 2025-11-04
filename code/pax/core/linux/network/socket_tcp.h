#ifndef PAX_LINUX_NETWORK_SOCKET_TCP_H
#define PAX_LINUX_NETWORK_SOCKET_TCP_H

#include "./import.h"

typedef struct Px_Linux_Socket_TCP Px_Linux_Socket_TCP;

Px_Linux_Socket_TCP*
pax_linux_socket_tcp_create(Pax_Arena* arena, Pax_Addr_Kind kind);

void
pax_linux_socket_tcp_destroy(Px_Linux_Socket_TCP* self);

Pax_Addr
pax_linux_socket_tcp_get_addr(Px_Linux_Socket_TCP* self);

paxu16
pax_linux_socket_tcp_get_port(Px_Linux_Socket_TCP* self);

paxb8
pax_linux_socket_tcp_bind(Px_Linux_Socket_TCP* self, Pax_Addr addr, paxu16 port);

paxb8
pax_linux_socket_tcp_listen(Px_Linux_Socket_TCP* self);

paxb8
pax_linux_socket_tcp_connect(Px_Linux_Socket_TCP* self, Pax_Addr addr, paxu16 port);

Px_Linux_Socket_TCP*
pax_linux_socket_tcp_accept(Px_Linux_Socket_TCP* self, Pax_Arena* arena);

paxiword
pax_linux_socket_tcp_write(Px_Linux_Socket_TCP* self, paxu8* memory, paxiword length);

paxiword
pax_linux_socket_tcp_read(Px_Linux_Socket_TCP* self, paxu8* memory, paxiword length);

#endif // PAX_LINUX_NETWORK_SOCKET_TCP_H
