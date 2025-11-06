#ifndef PX_CORE_NETWORK_SOCKET_UDP_H
#define PX_CORE_NETWORK_SOCKET_UDP_H

#include "addr.h"

typedef void* PxSocketUdp;

PxSocketUdp
pxSocketUdpCreate(PxArena* arena, PxAddrType type);

void
pxSocketUdpDestroy(PxSocketUdp self);

PxAddr
pxSocketUdpGetAddr(PxSocketUdp self);

pxu16
pxSocketUdpGetPort(PxSocketUdp self);

pxb8
pxSocketUdpBind(PxSocketUdp self, PxAddr addr, pxu16 port);

pxb8
pxSocketUdpListen(PxSocketUdp self);

pxb8
pxSocketUdpConnect(PxSocketUdp self, PxAddr addr, pxu16 port);

PxSocketUdp
pxSocketUdpAccept(PxSocketUdp self, PxArena* arena);

pxiword
pxSocketUdpWrite(PxSocketUdp self, pxu8* memory, pxiword length);

pxiword
pxSocketUdpWriteHost(PxSocketUdp self, pxu8* memory, pxiword length, PxAddr addr, pxu16 port);

pxiword
pxSocketUdpRead(PxSocketUdp self, pxu8* memory, pxiword length);

pxiword
pxSocketUdpReadHost(PxSocketUdp self, pxu8* memory, pxiword length, PxAddr* addr, pxu16* port);

#endif // PX_CORE_NETWORK_SOCKET_UDP_H
