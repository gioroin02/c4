#ifndef PX_WINDOWS_NETWORK_SOCKET_TCP_H
#define PX_WINDOWS_NETWORK_SOCKET_TCP_H

#include "import.h"

typedef struct PxWindowsSocketTcp PxWindowsSocketTcp;

PxWindowsSocketTcp*
pxWindowsSocketTcpCreate(PxArena* arena, PxAddrType type);

void
pxWindowsSocketTcpDestroy(PxWindowsSocketTcp* self);

PxAddr
pxWindowsSocketTcpGetAddr(PxWindowsSocketTcp* self);

pxu16
pxWindowsSocketTcpGetPort(PxWindowsSocketTcp* self);

pxb8
pxWindowsSocketTcpBind(PxWindowsSocketTcp* self, PxAddr addr, pxu16 port);

pxb8
pxWindowsSocketTcpListen(PxWindowsSocketTcp* self);

pxb8
pxWindowsSocketTcpConnect(PxWindowsSocketTcp* self, PxAddr addr, pxu16 port);

PxWindowsSocketTcp*
pxWindowsSocketTcpAccept(PxWindowsSocketTcp* self, PxArena* arena);

pxiword
pxWindowsSocketTcpWrite(PxWindowsSocketTcp* self, pxu8* memory, pxiword length);

pxiword
pxWindowsSocketTcpRead(PxWindowsSocketTcp* self, pxu8* memory, pxiword length);

#endif // PX_WINDOWS_NETWORK_SOCKET_TCP_H
