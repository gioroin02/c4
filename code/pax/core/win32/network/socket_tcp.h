#ifndef PAX_WIN32_NETWORK_SOCKET_TCP_H
#define PAX_WIN32_NETWORK_SOCKET_TCP_H

#include "./import.h"

typedef struct Pax_Win32_Socket_TCP Pax_Win32_Socket_TCP;

Pax_Win32_Socket_TCP*
pax_win32_socket_tcp_create(Pax_Arena* arena, Pax_Addr_Kind kind);

void
pax_win32_socket_tcp_destroy(Pax_Win32_Socket_TCP* self);

Pax_Addr
pax_win32_socket_tcp_get_addr(Pax_Win32_Socket_TCP* self);

paxu16
pax_win32_socket_tcp_get_port(Pax_Win32_Socket_TCP* self);

paxb8
pax_win32_socket_tcp_bind(Pax_Win32_Socket_TCP* self, Pax_Addr addr, paxu16 port);

paxb8
pax_win32_socket_tcp_listen(Pax_Win32_Socket_TCP* self);

paxb8
pax_win32_socket_tcp_connect(Pax_Win32_Socket_TCP* self, Pax_Addr addr, paxu16 port);

Pax_Win32_Socket_TCP*
pax_win32_socket_tcp_accept(Pax_Win32_Socket_TCP* self, Pax_Arena* arena);

paxiword
pax_win32_socket_tcp_write(Pax_Win32_Socket_TCP* self, paxu8* memory, paxiword length);

paxiword
pax_win32_socket_tcp_read(Pax_Win32_Socket_TCP* self, paxu8* memory, paxiword length);

#endif // PAX_WIN32_NETWORK_SOCKET_TCP_H
