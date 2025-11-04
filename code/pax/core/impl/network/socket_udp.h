#ifndef PAX_CORE_NETWORK_SOCKET_UDP_H
#define PAX_CORE_NETWORK_SOCKET_UDP_H

#include "./addr.h"

typedef void* Pax_Socket_UDP;

Pax_Socket_UDP
pax_socket_udp_create(Pax_Arena* arena, Pax_Addr_Kind kind);

void
pax_socket_udp_destroy(Pax_Socket_UDP self);

Pax_Addr
pax_socket_udp_get_addr(Pax_Socket_UDP self);

paxu16
pax_socket_udp_get_port(Pax_Socket_UDP self);

paxb8
pax_socket_udp_bind(Pax_Socket_UDP self, Pax_Addr addr, paxu16 port);

paxb8
pax_socket_udp_listen(Pax_Socket_UDP self);

paxb8
pax_socket_udp_connect(Pax_Socket_UDP self, Pax_Addr addr, paxu16 port);

Pax_Socket_UDP
pax_socket_udp_accept(Pax_Socket_UDP self, Pax_Arena* arena);

paxiword
pax_socket_udp_write(Pax_Socket_UDP self, paxu8* memory, paxiword length);

paxiword
pax_socket_udp_write_host(Pax_Socket_UDP self, paxu8* memory, paxiword length, Pax_Addr addr, paxu16 port);

paxiword
pax_socket_udp_read(Pax_Socket_UDP self, paxu8* memory, paxiword length);

paxiword
pax_socket_udp_read_host(Pax_Socket_UDP self, paxu8* memory, paxiword length, Pax_Addr* addr, paxu16* port);

#endif // PAX_CORE_NETWORK_SOCKET_UDP_H
