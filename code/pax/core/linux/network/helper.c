#ifndef PAX_LINUX_NETWORK_HELPER_C
#define PAX_LINUX_NETWORK_HELPER_C

#include "./import.h"

#include <unistd.h>
#include <errno.h>

#include <sys/socket.h>
#include <netinet/in.h>

typedef socklen_t Pax_Sock_Size;

typedef struct sockaddr_storage Pax_Sock_Data;
typedef struct sockaddr         Pax_Sock;
typedef struct sockaddr_in      Pax_Sock4;
typedef struct sockaddr_in6     Pax_Sock6;

#define PAX_SOCK_DATA_SIZE pax_size(Pax_Sock_Data)
#define PAX_SOCK4_SIZE     pax_size(Pax_Sock4)
#define PAX_SOCK6_SIZE     pax_size(Pax_Sock6)

#define pax_sock(x)  pax_as(Pax_Sock*, x)
#define pax_sock4(x) pax_as(Pax_Sock4*, x)
#define pax_sock6(x) pax_as(Pax_Sock6*, x)

#define pax_sock4_addr(x) pax_as(void*,   &pax_sock4(x)->sin_addr.s_addr)
#define pax_sock4_port(x) pax_as(paxu16*, &pax_sock4(x)->sin_port)

#define pax_sock6_addr(x) pax_as(void*,   pax_sock6(x)->sin6_addr.s6_addr)
#define pax_sock6_port(x) pax_as(paxu16*, &pax_sock6(x)->sin6_port)

Pax_Sock_Data
pax_sock_data_make(Pax_Addr_Kind kind)
{
    Pax_Sock_Data result = {0};

    switch (kind) {
        case PAX_ADDR_KIND_IP4: result.ss_family = AF_INET;  break;
        case PAX_ADDR_KIND_IP6: result.ss_family = AF_INET6; break;

        default: break;
    }

    return result;
}

paxiword
pax_sock_data_set(Pax_Sock_Data* self, Pax_Addr addr, paxu16 port)
{
    port = pax_u16_net_from_host(port);

    switch (addr.kind) {
        case PAX_ADDR_KIND_IP4: {
            self->ss_family = AF_INET;

            paxiword length = PAX_ADDR_IP4_GROUPS;
            paxiword stride = pax_size(paxu8);

            Pax_Slice slice =
                pax_slice_make(pax_sock4_addr(self), length, stride);

            Pax_Slice other = pax_slice_make(addr.ip4.items, length, stride);

            pax_slice_copy(slice, other);

            *pax_sock4_port(self) = port;

            return PAX_SOCK4_SIZE;
        } break;

        case PAX_ADDR_KIND_IP6: {
            self->ss_family = AF_INET6;

            paxiword length = PAX_ADDR_IP6_GROUPS;
            paxiword stride = pax_size(paxu16);

            Pax_Slice slice =
                pax_slice_make(pax_sock6_addr(self), length, stride);

            Pax_Slice other = pax_slice_make(addr.ip6.items, length, stride);

            pax_slice_copy(slice, other);
            pax_slice_flip(slice);
            pax_slice_net_from_host(slice);

            *pax_sock6_port(self) = port;

            return PAX_SOCK6_SIZE;
        } break;

        default: break;
    }

    return 0;
}

Pax_Addr
pax_sock_data_get_addr(Pax_Sock_Data* self)
{
    Pax_Addr result = {.kind = PAX_ADDR_KIND_NONE};

    switch (self->ss_family) {
        case AF_INET: {
            paxiword length = PAX_ADDR_IP4_GROUPS;
            paxiword stride = pax_size(paxu8);

            result.kind = PAX_ADDR_KIND_IP4;

            Pax_Slice slice = pax_slice_make(result.ip4.items, length, stride);

            Pax_Slice other =
                pax_slice_make(pax_sock4_addr(self), length, stride);

            pax_slice_copy(slice, other);
        } break;

        case AF_INET6: {
            paxiword length = PAX_ADDR_IP6_GROUPS;
            paxiword stride = pax_size(paxu16);

            result.kind = PAX_ADDR_KIND_IP6;

            Pax_Slice slice = pax_slice_make(result.ip6.items, length, stride);

            Pax_Slice other =
                pax_slice_make(pax_sock6_addr(self), length, stride);

            pax_slice_copy(slice, other);
            pax_slice_flip(slice);
            pax_slice_host_from_net(slice);
        } break;

        default: break;
    }

    return result;
}

paxu16
pax_sock_data_get_port(Pax_Sock_Data* self)
{
    paxu16 result = 0;

    switch (self->ss_family) {
        case AF_INET:  result = *pax_sock4_port(self); break;
        case AF_INET6: result = *pax_sock6_port(self); break;

        default: break;
    }

    return pax_u16_host_from_net(result);
}

#endif // PAX_LINUX_NETWORK_HELPER_C
