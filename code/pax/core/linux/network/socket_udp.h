#ifndef PAX_LINUX_NETWORK_SOCKET_UDP_H
#define PAX_LINUX_NETWORK_SOCKET_UDP_H

#include "./import.h"

typedef struct Pax_Linux_Socket_UDP Pax_Linux_Socket_UDP;

Pax_Linux_Socket_UDP*
pax_linux_socket_udp_create(Pax_Arena* arena, Pax_Addr_Kind kind);

void
pax_linux_socket_udp_destroy(Pax_Linux_Socket_UDP* self);

Pax_Addr
pax_linux_socket_udp_get_addr(Pax_Linux_Socket_UDP* self);

paxu16
pax_linux_socket_udp_get_port(Pax_Linux_Socket_UDP* self);

paxb8
pax_linux_socket_udp_bind(Pax_Linux_Socket_UDP* self, Pax_Addr addr, paxu16 port);

paxb8
pax_linux_socket_udp_listen(Pax_Linux_Socket_UDP* self);

paxb8
pax_linux_socket_udp_connect(Pax_Linux_Socket_UDP* self, Pax_Addr addr, paxu16 port);

Pax_Linux_Socket_UDP*
pax_linux_socket_udp_accept(Pax_Linux_Socket_UDP* self, Pax_Arena* arena);

paxiword
pax_linux_socket_udp_write(Pax_Linux_Socket_UDP* self, paxu8* memory, paxiword length);

paxiword
pax_linux_socket_udp_write_host(Pax_Linux_Socket_UDP* self, paxu8* memory, paxiword length, Pax_Addr addr, paxu16 port);

paxiword
pax_linux_socket_udp_read(Pax_Linux_Socket_UDP* self, paxu8* memory, paxiword length);

paxiword
pax_linux_socket_udp_read_host(Pax_Linux_Socket_UDP* self, paxu8* memory, paxiword length, Pax_Addr* addr, paxu16* port);

#endif // PAX_LINUX_NETWORK_SOCKET_UDP_H
