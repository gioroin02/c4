#ifndef PX_CORE_NETWORK_SOCKET_UDP_C
#define PX_CORE_NETWORK_SOCKET_UDP_C

#include "socket_udp.h"

#if PX_SYSTEM == PX_SYSTEM_WINDOWS

    #include "../../windows/network/socket_udp.c"

    #define __pxSocketUdpCreate__    pxWindowsSocketUdpCreate
    #define __pxSocketUdpDestroy__   pxWindowsSocketUdpDestroy
    #define __pxSocketUdpGetAddr__   pxWindowsSocketUdpGetAddr
    #define __pxSocketUdpGetPort__   pxWindowsSocketUdpGetPort
    #define __pxSocketUdpBind__      pxWindowsSocketUdpBind
    #define __pxSocketUdpListen__    pxWindowsSocketUdpListen
    #define __pxSocketUdpConnect__   pxWindowsSocketUdpConnect
    #define __pxSocketUdpAccept__    pxWindowsSocketUdpAccept
    #define __pxSocketUdpWrite__     pxWindowsSocketUdpWrite
    #define __pxSocketUdpWriteHost__ pxWindowsSocketUdpWriteHost
    #define __pxSocketUdpRead__      pxWindowsSocketUdpRead
    #define __pxSocketUdpReadHost__  pxWindowsSocketUdpReadHost

#elif PX_SYSTEM == PX_SYSTEM_LINUX

    #include "../../linux/network/socket_udp.c"

    #define __pxSocketUdpCreate__    pxLinuxSocketUdpCreate
    #define __pxSocketUdpDestroy__   pxLinuxSocketUdpDestroy
    #define __pxSocketUdpGetAddr__   pxLinuxSocketUdpGetAddr
    #define __pxSocketUdpGetPort__   pxLinuxSocketUdpGetPort
    #define __pxSocketUdpBind__      pxLinuxSocketUdpBind
    #define __pxSocketUdpListen__    pxLinuxSocketUdpListen
    #define __pxSocketUdpConnect__   pxLinuxSocketUdpConnect
    #define __pxSocketUdpAccept__    pxLinuxSocketUdpAccept
    #define __pxSocketUdpWrite__     pxLinuxSocketUdpWrite
    #define __pxSocketUdpWriteHost__ pxLinuxSocketUdpWriteHost
    #define __pxSocketUdpRead__      pxLinuxSocketUdpRead
    #define __pxSocketUdpReadHost__  pxLinuxSocketUdpReadHost

#else

    #error "Unknown platform"

#endif

PxSocketUdp
pxSocketUdpCreate(PxArena* arena, PxAddrType type)
{
    return __pxSocketUdpCreate__(arena, type);
}

void
pxSocketUdpDestroy(PxSocketUdp self)
{
    __pxSocketUdpDestroy__(self);
}

PxAddr
pxSocketUdpGetAddr(PxSocketUdp self)
{
    return __pxSocketUdpGetAddr__(self);
}

pxu16
pxSocketUdpGetPort(PxSocketUdp self)
{
    return __pxSocketUdpGetPort__(self);
}

pxb8
pxSocketUdpBind(PxSocketUdp self, PxAddr addr, pxu16 port)
{
    return __pxSocketUdpBind__(self, addr, port);
}

pxb8
pxSocketUdpListen(PxSocketUdp self)
{
    return __pxSocketUdpListen__(self);
}

pxb8
pxSocketUdpConnect(PxSocketUdp self, PxAddr addr, pxu16 port)
{
    return __pxSocketUdpConnect__(self, addr, port);
}

PxSocketUdp
pxSocketUdpAccept(PxSocketUdp self, PxArena* arena)
{
    return __pxSocketUdpAccept__(self, arena);
}

pxiword
pxSocketUdpWrite(PxSocketUdp self, pxu8* memory, pxiword length)
{
    return __pxSocketUdpWrite__(self, memory, length);
}

pxiword
pxSocketUdpWriteHost(PxSocketUdp self, pxu8* memory, pxiword length, PxAddr addr, pxu16 port)
{
    return __pxSocketUdpWriteHost__(self, memory, length, addr, port);
}

pxiword
pxSocketUdpRead(PxSocketUdp self, pxu8* memory, pxiword length)
{
    return __pxSocketUdpRead__(self, memory, length);
}

pxiword
pxSocketUdpReadHost(PxSocketUdp self, pxu8* memory, pxiword length, PxAddr* addr, pxu16* port)
{
    return __pxSocketUdpReadHost__(self, memory, length, addr, port);
}

#endif // PX_CORE_NETWORK_SOCKET_UDP_C
