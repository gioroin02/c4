#ifndef PAX_LINUX_NETWORK_SOCKET_UDP_C
#define PAX_LINUX_NETWORK_SOCKET_UDP_C

#include "./socket_udp.h"
#include "./helper.c"

struct Pax_Linux_Socket_UDP
{
    int           handle;
    Pax_Sock_Data data;
};

Pax_Linux_Socket_UDP*
pax_linux_socket_udp_create(Pax_Arena* arena, Pax_Addr_Kind kind)
{
    paxiword mark = pax_arena_tell(arena);

    Pax_Linux_Socket_UDP* result =
        pax_arena_reserve(arena, Pax_Linux_Socket_UDP, 1);

    if (result != 0) {
        result->data = pax_sock_data_make(kind);

        result->handle = socket(result->data.ss_family,
            SOCK_DGRAM, 0);

        if (result->handle != -1)
            return result;
    }

    pax_arena_rewind(arena, mark, 0);

    return 0;
}

void
pax_linux_socket_udp_destroy(Pax_Linux_Socket_UDP* self)
{
    if (self == 0 || self->handle == -1)
        return;

    paxiword result = 0;

    do {
        result = close(self->handle);
    } while (result == -1 && errno == EINTR);

    self->handle = -1;
    self->data   = (Pax_Sock_Data) {0};
}

Pax_Addr
pax_linux_socket_udp_get_addr(Pax_Linux_Socket_UDP* self)
{
    return pax_sock_data_get_addr(&self->data);
}

paxu16
pax_linux_socket_udp_get_port(Pax_Linux_Socket_UDP* self)
{
    return pax_sock_data_get_port(&self->data);
}

paxb8
pax_linux_socket_udp_bind(Pax_Linux_Socket_UDP* self, Pax_Addr addr, paxu16 port)
{
    Pax_Sock_Data data = {0};
    paxiword      size = pax_sock_data_set(&data, addr, port);

    if (bind(self->handle, pax_sock(&data), size) == -1)
        return 0;

    self->data = data;

    return 1;
}

paxb8
pax_linux_socket_udp_listen(Pax_Linux_Socket_UDP* self)
{
    if (listen(self->handle, SOMAXCONN) == -1)
        return 0;

    return 1;
}

paxb8
pax_linux_socket_udp_connect(Pax_Linux_Socket_UDP* self, Pax_Addr addr, paxu16 port)
{
    Pax_Sock_Data data = {0};
    paxiword      size = pax_sock_data_set(&data, addr, port);

    paxiword result = 0;

    do {
        result = connect(self->handle, pax_sock(&data), size);
    } while (result == -1 && errno == EINTR);

    if (result == -1) return 0;

    return 1;
}

Pax_Linux_Socket_UDP*
pax_linux_socket_udp_accept(Pax_Linux_Socket_UDP* self, Pax_Arena* arena)
{
    paxiword mark = pax_arena_tell(arena);

    Pax_Linux_Socket_UDP* result =
        pax_arena_reserve(arena, Pax_Linux_Socket_UDP, 1);

    if (result != 0) {
        paxiword size = PAX_SOCK_DATA_SIZE;

        do {
            result->handle = accept(self->handle,
                pax_sock(&result->data), pax_as(Pax_Sock_Size*, &size));
        } while (result->handle == -1 && errno == EINTR);

        if (result->handle != -1)
            return result;
    }

    pax_arena_rewind(arena, mark, 0);

    return 0;
}

paxiword
pax_linux_socket_udp_write(Pax_Linux_Socket_UDP* self, paxu8* memory, paxiword length)
{
    paxiword temp = 0;

    for (paxiword i = 0; i < length;) {
        char* mem = pax_as(char*, memory + i);
        int   len = pax_as(int,   length - i);

        do {
            temp = send(self->handle, mem, len, 0);
        } while (temp == -1 && errno == EINTR);

        if (temp > 0 && temp <= length - i)
            i += temp;
        else
            return i;
    }

    return length;
}

paxiword
pax_linux_socket_udp_write_host(Pax_Linux_Socket_UDP* self, paxu8* memory, paxiword length, Pax_Addr addr, paxu16 port)
{
    Pax_Sock_Data data = {0};
    paxiword      size = pax_sock_data_set(&data, addr, port);

    paxiword temp = 0;

    for (paxiword i = 0; i < length;) {
        char* mem = pax_as(char*, memory + i);
        int   len = pax_as(int,   length - i);

        do {
            temp = sendto(self->handle, mem, len, 0,
                pax_sock(&data), size);
        } while (temp == -1 && errno == EINTR);

        if (temp > 0 && temp <= length - i)
            i += temp;
        else
            return i;
    }

    return length;
}

paxiword
pax_linux_socket_udp_read(Pax_Linux_Socket_UDP* self, paxu8* memory, paxiword length)
{
    paxiword temp = 0;

    char* mem = pax_as(char*, memory);
    int   len = pax_as(int,   length);

    do {
        temp = recv(self->handle, mem, len, 0);
    } while (temp == - 1 && errno == EINTR);

    if (temp > 0 && temp <= length)
        return temp;

    return 0;
}

paxiword
pax_linux_socket_udp_read_host(Pax_Linux_Socket_UDP* self, paxu8* memory, paxiword length, Pax_Addr* addr, paxu16* port)
{
    Pax_Sock_Data data = {0};
    paxiword      size = PAX_SOCK_DATA_SIZE;
    paxiword      temp = 0;

    char* mem = pax_as(char*, memory);
    int   len = pax_as(int,   length);

    do {
        temp = recvfrom(self->handle, mem, len, 0,
            pax_sock(&data), pax_as(Pax_Sock_Size*, &size));
    } while (temp == -1 && errno == EINTR);

    if (temp <= 0 || temp > length) return 0;

    if (addr != 0) *addr = pax_sock_data_get_addr(&data);
    if (port != 0) *port = pax_sock_data_get_port(&data);

    return temp;
}

#endif // PAX_LINUX_NETWORK_SOCKET_UDP_C
