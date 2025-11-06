#ifndef PX_LINUX_NETWORK_SOCKET_TCP_H
#define PX_LINUX_NETWORK_SOCKET_TCP_H

#include "import.h"

typedef struct PxLinuxSocketTcp PxLinuxSocketTcp;

PxLinuxSocketTcp*
pxLinuxSocketTcpCreate(PxArena* arena, PxAddrType type);

void
pxLinuxSocketTcpDestroy(PxLinuxSocketTcp* self);

PxAddr
pxLinuxSocketTcpGetAddr(PxLinuxSocketTcp* self);

pxu16
pxLinuxSocketTcpGetPort(PxLinuxSocketTcp* self);

pxb8
pxLinuxSocketTcpBind(PxLinuxSocketTcp* self, PxAddr addr, pxu16 port);

pxb8
pxLinuxSocketTcpListen(PxLinuxSocketTcp* self);

pxb8
pxLinuxSocketTcpConnect(PxLinuxSocketTcp* self, PxAddr addr, pxu16 port);

PxLinuxSocketTcp*
pxLinuxSocketTcpAccept(PxLinuxSocketTcp* self, PxArena* arena);

pxiword
pxLinuxSocketTcpWrite(PxLinuxSocketTcp* self, pxu8* memory, pxiword length);

pxiword
pxLinuxSocketTcpRead(PxLinuxSocketTcp* self, pxu8* memory, pxiword length);

#endif // PX_LINUX_NETWORK_SOCKET_TCP_H
