#ifndef PAX_LINUX_NETWORK_SOCKET_TCP_C
#define PAX_LINUX_NETWORK_SOCKET_TCP_C

#include "./socket_tcp.h"
#include "./helper.c"

struct Px_Linux_Socket_TCP
{
    int           handle;
    Pax_Sock_Data data;
};

Px_Linux_Socket_TCP*
pax_linux_socket_tcp_create(Pax_Arena* arena, Pax_Addr_Kind kind)
{
    paxiword mark = pax_arena_tell(arena);

    Px_Linux_Socket_TCP* result =
        pax_arena_reserve(arena, Px_Linux_Socket_TCP, 1);

    if (result != 0) {
        result->data = pax_sock_data_make(kind);

        result->handle = socket(result->data.ss_family,
            SOCK_STREAM, 0);

        if (result->handle != -1)
            return result;
    }

    pax_arena_rewind(arena, mark, 0);

    return 0;
}

void
pax_linux_socket_tcp_destroy(Px_Linux_Socket_TCP* self)
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
pax_linux_socket_tcp_get_addr(Px_Linux_Socket_TCP* self)
{
    return pax_sock_data_get_addr(&self->data);
}

paxu16
pax_linux_socket_tcp_get_port(Px_Linux_Socket_TCP* self)
{
    return pax_sock_data_get_port(&self->data);
}

paxb8
pax_linux_socket_tcp_bind(Px_Linux_Socket_TCP* self, Pax_Addr addr, paxu16 port)
{
    Pax_Sock_Data data = {0};
    paxiword      size = pax_sock_data_set(&data, addr, port);

    if (bind(self->handle, pax_sock(&data), size) == -1)
        return 0;

    self->data = data;

    return 1;
}

paxb8
pax_linux_socket_tcp_listen(Px_Linux_Socket_TCP* self)
{
    if (listen(self->handle, SOMAXCONN) == -1)
        return 0;

    return 1;
}

paxb8
pax_linux_socket_tcp_connect(Px_Linux_Socket_TCP* self, Pax_Addr addr, paxu16 port)
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

Px_Linux_Socket_TCP*
pax_linux_socket_tcp_accept(Px_Linux_Socket_TCP* self, Pax_Arena* arena)
{
    paxiword mark = pax_arena_tell(arena);

    Px_Linux_Socket_TCP* result =
        pax_arena_reserve(arena, Px_Linux_Socket_TCP, 1);

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
pax_linux_socket_tcp_write(Px_Linux_Socket_TCP* self, paxu8* memory, paxiword length)
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
pax_linux_socket_tcp_read(Px_Linux_Socket_TCP* self, paxu8* memory, paxiword length)
{
    paxiword temp = 0;

    char* mem = pax_as(char*, memory);
    int   len = pax_as(int,   length);

    do {
        temp = recv(self->handle, mem, len, 0);
    } while (temp == -1 && errno == EINTR);

    if (temp > 0 && temp <= length)
        return temp;

    return 0;
}

#endif // PAX_LINUX_NETWORK_SOCKET_TCP_C
