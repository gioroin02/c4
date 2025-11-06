#ifndef PX_LINUX_NETWORK_SOCKET_UDP_H
#define PX_LINUX_NETWORK_SOCKET_UDP_H

#include "import.h"

typedef struct PxLinuxSocketUdp PxLinuxSocketUdp;

PxLinuxSocketUdp*
pxLinuxSocketUdpCreate(PxArena* arena, PxAddrType type);

void
pxLinuxSocketUdpDestroy(PxLinuxSocketUdp* self);

PxAddr
pxLinuxSocketUdpGetAddr(PxLinuxSocketUdp* self);

pxu16
pxLinuxSocketUdpGetPort(PxLinuxSocketUdp* self);

pxb8
pxLinuxSocketUdpBind(PxLinuxSocketUdp* self, PxAddr addr, pxu16 port);

pxb8
pxLinuxSocketUdpListen(PxLinuxSocketUdp* self);

pxb8
pxLinuxSocketUdpConnect(PxLinuxSocketUdp* self, PxAddr addr, pxu16 port);

PxLinuxSocketUdp*
pxLinuxSocketUdpAccept(PxLinuxSocketUdp* self, PxArena* arena);

pxiword
pxLinuxSocketUdpWrite(PxLinuxSocketUdp* self, pxu8* memory, pxiword length);

pxiword
pxLinuxSocketUdpWriteHost(PxLinuxSocketUdp* self, pxu8* memory, pxiword length, PxAddr addr, pxu16 port);

pxiword
pxLinuxSocketUdpRead(PxLinuxSocketUdp* self, pxu8* memory, pxiword length);

pxiword
pxLinuxSocketUdpReadHost(PxLinuxSocketUdp* self, pxu8* memory, pxiword length, PxAddr* addr, pxu16* port);

#endif // PX_LINUX_NETWORK_SOCKET_UDP_H
