#ifndef PX_CORE_NETWORK_SOCKET_TCP_H
#define PX_CORE_NETWORK_SOCKET_TCP_H

#include "addr.h"

typedef void* PxSocketTcp;

PxSocketTcp
pxSocketTcpCreate(PxArena* arena, PxAddrType type);

void
pxSocketTcpDestroy(PxSocketTcp self);

PxAddr
pxSocketTcpGetAddr(PxSocketTcp self);

pxu16
pxSocketTcpGetPort(PxSocketTcp self);

pxb8
pxSocketTcpBind(PxSocketTcp self, PxAddr addr, pxu16 port);

pxb8
pxSocketTcpListen(PxSocketTcp self);

pxb8
pxSocketTcpConnect(PxSocketTcp self, PxAddr addr, pxu16 port);

PxSocketTcp
pxSocketTcpAccept(PxSocketTcp self, PxArena* arena);

pxiword
pxSocketTcpWrite(PxSocketTcp self, pxu8* memory, pxiword length);

pxiword
pxSocketTcpRead(PxSocketTcp self, pxu8* memory, pxiword length);

PxSource
pxSourceFromSocketTcp(PxSocketTcp self);

PxTarget
pxTargetFromSocketTcp(PxSocketTcp self);

#endif // PX_CORE_NETWORK_SOCKET_TCP_H
