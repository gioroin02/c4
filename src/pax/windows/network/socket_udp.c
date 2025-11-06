#ifndef PX_WINDOWS_NETWORK_SOCKET_UDP_C
#define PX_WINDOWS_NETWORK_SOCKET_UDP_C

#include "socket_udp.h"

#define NOMINMAX
#define NOGDI
#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <ws2tcpip.h>

#ifndef PX_WINDOWS_NETWORK_SOCKET
#define PX_WINDOWS_NETWORK_SOCKET

typedef struct sockaddr_storage PxSockData;
typedef struct sockaddr         PxSock;
typedef struct sockaddr_in      PxSockIp4;
typedef struct sockaddr_in6     PxSockIp6;

#define PX_SOCK_DATA_SIZE px_size(PxSockData)
#define PX_SOCK_IP4_SIZE  px_size(PxSockIp4)
#define PX_SOCK_IP6_SIZE  px_size(PxSockIp6)

#define pxSock(x)    px_as(PxSock*, x)
#define pxSockIp4(x) px_as(PxSockIp4*, x)
#define pxSockIp6(x) px_as(PxSockIp6*, x)

#define pxSockIp4Addr(x) px_as(void*,  &pxSockIp4(x)->sin_addr.s_addr)
#define pxSockIp4Port(x) px_as(pxu16*, &pxSockIp4(x)->sin_port)

#define pxSockIp6Addr(x) px_as(void*,  pxSockIp6(x)->sin6_addr.s6_addr)
#define pxSockIp6Port(x) px_as(pxu16*, &pxSockIp6(x)->sin6_port)

#endif // PX_WINDOWS_NETWORK_SOCKET

struct PxWindowsSocketUdp
{
    SOCKET     handle;
    PxSockData addr;
};

PxWindowsSocketUdp*
pxWindowsSocketUdpCreate(PxArena* arena, PxAddrType type)
{
    pxiword offset = pxArenaOffset(arena);
    pxiword family = 0;

    switch (type) {
        case PX_ADDR_TYPE_IP4: family = AF_INET;  break;
        case PX_ADDR_TYPE_IP6: family = AF_INET6; break;

        default: return 0;
    }

    PxWindowsSocketUdp* result =
        pxArenaReserve(arena, PxWindowsSocketUdp, 1);

    if (result != 0) {
        result->handle = socket(family, SOCK_DGRAM, 0);

        if (result->handle != INVALID_SOCKET) {
            result->addr.ss_family = family;

            return result;
        }
    }

    pxArenaRewind(arena, offset);

    return 0;
}

void
pxWindowsSocketUdpDestroy(PxWindowsSocketUdp* self)
{
    if (self == 0 || self->handle == INVALID_SOCKET)
        return;

    closesocket(self->handle);

    self->handle = INVALID_SOCKET;
    self->addr   = (PxSockData) {0};
}

PxAddr
pxWindowsSocketUdpGetAddr(PxWindowsSocketUdp* self)
{
    PxAddr result = {.type = PX_ADDR_TYPE_NONE};

    switch (self->addr.ss_family) {
        case AF_INET: {
            result.type = PX_ADDR_TYPE_IP4;

            void* addr = pxSockIp4Addr(&self->addr);

            pxMemoryCopy(result.ip4.items, addr,
                PX_ADDR_IP4_GROUPS, 1);
        } break;

        case AF_INET6: {
            result.type = PX_ADDR_TYPE_IP6;

            void* addr = pxSockIp6Addr(&self->addr);

            pxMemoryCopy(result.ip6.items, addr,
                PX_ADDR_IP6_GROUPS, 2);

            pxMemoryFlip(result.ip6.items,
                PX_ADDR_IP6_GROUPS, 2);

            pxMemoryFlip(result.ip6.items,
                PX_ADDR_IP6_GROUPS * 2, 1);
        } break;

        default: break;
    }

    return result;
}

pxu16
pxWindowsSocketUdpGetPort(PxWindowsSocketUdp* self)
{
    pxu16 temp = 0;

    switch (self->addr.ss_family) {
        case AF_INET:
            temp = *pxSockIp4Port(&self->addr);
        break;

        case AF_INET6:
            temp = *pxSockIp6Port(&self->addr);
        break;

        default: break;
    }

    return pxUnsigned16HostFromNet(temp);
}

pxb8
pxWindowsSocketUdpBind(PxWindowsSocketUdp* self, PxAddr addr, pxu16 port)
{
    pxiword family = 0;

    switch (addr.type) {
        case PX_ADDR_TYPE_IP4: family = AF_INET;  break;
        case PX_ADDR_TYPE_IP6: family = AF_INET6; break;

        default: return 0;
    }

    if (self->addr.ss_family != family) return 0;

    PxSockData data = {0};
    pxiword    size = 0;

    switch (addr.type) {
        case PX_ADDR_TYPE_IP4: {
            data.ss_family = AF_INET;
            size           = PX_SOCK_IP4_SIZE;

            pxMemoryCopy(pxSockIp4Addr(&data),
                addr.ip4.items, PX_ADDR_IP4_GROUPS, 1);

            pxMemoryCopyNetFromHost(pxSockIp4Port(&data),
                &port, 1, 2);
        } break;

        case PX_ADDR_TYPE_IP6: {
            data.ss_family = AF_INET6;
            size           = PX_SOCK_IP6_SIZE;

            pxMemoryCopy(pxSockIp6Addr(&data),
                addr.ip6.items, PX_ADDR_IP6_GROUPS, 2);

            pxMemoryFlip(pxSockIp6Addr(&data),
                PX_ADDR_IP6_GROUPS, 2);

            pxMemoryFlip(pxSockIp6Addr(&data),
                PX_ADDR_IP6_GROUPS * 2, 1);

            pxMemoryCopyNetFromHost(pxSockIp6Port(&data),
                &port, 1, 2);
        } break;

        default: return 0;
    }

    if (bind(self->handle, pxSock(&data), size) == SOCKET_ERROR)
        return 0;

    self->addr = data;

    return 1;
}

pxb8
pxWindowsSocketUdpListen(PxWindowsSocketUdp* self)
{
    if (listen(self->handle, SOMAXCONN) == SOCKET_ERROR)
        return 0;

    return 1;
}

pxb8
pxWindowsSocketUdpConnect(PxWindowsSocketUdp* self, PxAddr addr, pxu16 port)
{
    PxSockData data = {0};
    pxiword    size = 0;

    switch (addr.type) {
        case PX_ADDR_TYPE_IP4: {
            data.ss_family = AF_INET;
            size           = PX_SOCK_IP4_SIZE;

            pxMemoryCopy(pxSockIp4Addr(&data),
                addr.ip4.items, PX_ADDR_IP4_GROUPS, 1);

            pxMemoryCopyNetFromHost(pxSockIp4Port(&data),
                &port, 1, 2);
        } break;

        case PX_ADDR_TYPE_IP6: {
            data.ss_family = AF_INET6;
            size           = PX_SOCK_IP6_SIZE;

            pxMemoryCopy(pxSockIp6Addr(&data),
                addr.ip6.items, PX_ADDR_IP6_GROUPS, 2);

            pxMemoryFlip(pxSockIp6Addr(&data),
                PX_ADDR_IP6_GROUPS, 2);

            pxMemoryFlip(pxSockIp6Addr(&data),
                PX_ADDR_IP6_GROUPS * 2, 1);

            pxMemoryCopyNetFromHost(pxSockIp6Port(&data),
                &port, 1, 2);
        } break;

        default: return 0;
    }

    if (connect(self->handle, pxSock(&data), size) == SOCKET_ERROR)
        return 0;

    self->addr = data;

    return 1;
}

PxWindowsSocketUdp*
pxWindowsSocketUdpAccept(PxWindowsSocketUdp* self, PxArena* arena)
{
    pxiword offset = pxArenaOffset(arena);

    PxWindowsSocketUdp* result =
        pxArenaReserve(arena, PxWindowsSocketUdp, 1);

    if (result != 0) {
        PxSockData data = {0};
        pxiword    size = PX_SOCK_DATA_SIZE;

        result->handle = accept(self->handle,
            pxSock(&data), px_as(int*, &size));

        if (result->handle != INVALID_SOCKET) {
            result->addr = data;

            return result;
        }
    }

    pxArenaRewind(arena, offset);

    return 0;
}

pxiword
pxWindowsSocketUdpWrite(PxWindowsSocketUdp* self, pxu8* memory, pxiword length)
{
    pxiword temp = 0;

    for (pxiword i = 0; i < length;) {
        char* mem = px_as(char*, memory + i);
        int   len = px_as(int,   length - i);

        temp = send(self->handle, mem, len, 0);

        if (temp > 0 && temp <= length - i)
            i += temp;
        else
            return i;
    }

    return length;
}

pxiword
pxWindowsSocketUdpWriteHost(PxWindowsSocketUdp* self, pxu8* memory, pxiword length, PxAddr addr, pxu16 port)
{
    PxSockData data = {0};
    pxiword    size = 0;

    switch (addr.type) {
        case PX_ADDR_TYPE_IP4: {
            data.ss_family = AF_INET;
            size           = PX_SOCK_IP4_SIZE;

            pxMemoryCopy(pxSockIp4Addr(&data),
                addr.ip4.items, PX_ADDR_IP4_GROUPS, 1);

            pxMemoryCopyNetFromHost(pxSockIp4Port(&data),
                &port, 1, 2);
        } break;

        case PX_ADDR_TYPE_IP6: {
            data.ss_family = AF_INET6;
            size           = PX_SOCK_IP6_SIZE;

            pxMemoryCopy(pxSockIp6Addr(&data),
                addr.ip6.items, PX_ADDR_IP6_GROUPS, 2);

            pxMemoryFlip(pxSockIp6Addr(&data),
                PX_ADDR_IP6_GROUPS, 2);

            pxMemoryFlip(pxSockIp6Addr(&data),
                PX_ADDR_IP6_GROUPS * 2, 1);

            pxMemoryCopyNetFromHost(pxSockIp6Port(&data),
                &port, 1, 2);
        } break;

        default: return 0;
    }

    pxiword temp = 0;

    for (pxiword i = 0; i < length;) {
        char* mem = px_as(char*, memory + i);
        int   len = px_as(int,   length - i);

        temp = sendto(self->handle, mem, len, 0,
            pxSock(&data), size);

        if (temp > 0 && temp <= length - i)
            i += temp;
        else
            return i;
    }

    return length;
}

pxiword
pxWindowsSocketUdpRead(PxWindowsSocketUdp* self, pxu8* memory, pxiword length)
{
    pxiword temp = 0;

    char* mem = px_as(char*, memory);
    int   len = px_as(int,   length);

    temp = recv(self->handle, mem, len, 0);

    if (temp > 0 && temp <= length)
        return temp;

    return 0;
}

pxiword
pxWindowsSocketUdpReadHost(PxWindowsSocketUdp* self, pxu8* memory, pxiword length, PxAddr* addr, pxu16* port)
{
    PxSockData data = {0};
    pxiword    size = PX_SOCK_DATA_SIZE;
    pxiword    temp = 0;

    char* mem = px_as(char*, memory);
    int   len = px_as(int,   length);

    temp = recvfrom(self->handle, mem, len, 0,
        pxSock(&data), px_as(int*, &size));

    if (temp <= 0 || temp > length) return 0;

    switch (data.ss_family) {
        case AF_INET: {
            if (port != 0)
                pxMemoryCopyHostFromNet(port, pxSockIp4Port(&data), 1, 2);

            if (addr != 0) {
                addr->type = PX_ADDR_TYPE_IP4;

                pxMemoryCopy(addr->ip4.items,
                    pxSockIp4Addr(&data), PX_ADDR_IP4_GROUPS, 1);
            }
        } break;

        case AF_INET6: {
            if (port != 0)
                pxMemoryCopyHostFromNet(port, pxSockIp6Port(&data), 1, 2);

            if (addr != 0) {
                addr->type = PX_ADDR_TYPE_IP6;

                pxMemoryCopy(addr->ip6.items,
                    pxSockIp6Addr(&data), PX_ADDR_IP6_GROUPS, 2);

                pxMemoryFlip(addr->ip6.items,
                    PX_ADDR_IP6_GROUPS, 2);

                pxMemoryFlip(addr->ip6.items,
                    PX_ADDR_IP6_GROUPS * 2, 1);
            }
        } break;

        default: break;
    }

    return temp;
}

#endif // PX_WINDOWS_NETWORK_SOCKET_UDP_C
