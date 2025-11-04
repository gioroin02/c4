#ifndef PAX_CORE_NETWORK_SOCKET_TCP_H
#define PAX_CORE_NETWORK_SOCKET_TCP_H

#include "./addr.h"

typedef void* Pax_Socket_TCP;

Pax_Socket_TCP
pax_socket_tcp_create(Pax_Arena* arena, Pax_Addr_Kind kind);

void
pax_socket_tcp_destroy(Pax_Socket_TCP self);

Pax_Addr
pax_socket_tcp_get_addr(Pax_Socket_TCP self);

paxu16
pax_socket_tcp_get_port(Pax_Socket_TCP self);

paxb8
pax_socket_tcp_bind(Pax_Socket_TCP self, Pax_Addr addr, paxu16 port);

paxb8
pax_socket_tcp_listen(Pax_Socket_TCP self);

paxb8
pax_socket_tcp_connect(Pax_Socket_TCP self, Pax_Addr addr, paxu16 port);

Pax_Socket_TCP
pax_socket_tcp_accept(Pax_Socket_TCP self, Pax_Arena* arena);

paxiword
pax_socket_tcp_write(Pax_Socket_TCP self, paxu8* memory, paxiword length);

paxiword
pax_socket_tcp_read(Pax_Socket_TCP self, paxu8* memory, paxiword length);

Pax_Source*
pax_source_from_socket_tcp(Pax_Arena* arena, Pax_Socket_TCP self);

Pax_Target*
pax_target_from_socket_tcp(Pax_Arena* arena, Pax_Socket_TCP self);

#endif // PAX_CORE_NETWORK_SOCKET_TCP_H
