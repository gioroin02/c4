#ifndef C4_ENGINE_NETWORK_H
#define C4_ENGINE_NETWORK_H

#include "message.h"

typedef struct C4NetworkReaderCtxt
{
    PxArena  arena;
    PxQueue* queue;

    PxLock lock;

    PxSource source;
}
C4NetworkReaderCtxt;

typedef struct C4NetworkWriterCtxt
{
    PxArena  arena;
    PxQueue* queue;

    PxLock lock;

    PxTarget target;
}
C4NetworkWriterCtxt;

typedef struct C4NetworkSession
{
    PxSocketTcp socket;

    PxLock  input_lock;
    PxQueue input_queue;

    PxLock  output_lock;
    PxQueue output_queue;
}
C4NetworkSession;

typedef struct C4NetworkServer
{
    PxSocketTcp socket;
    PxArray     items;
}
C4NetworkServer;

pxuword
c4NetworkReaderProc(C4NetworkReaderCtxt* self);

pxuword
c4NetworkWriterProc(C4NetworkWriterCtxt* self);

C4NetworkSession
c4NetworkSessionCreate(PxArena* arena, pxiword length, PxAddrType type);

pxb8
c4NetworkSessionConnect(C4NetworkSession* self, PxAddr addr, pxu16 port);

pxb8
c4NetworkSessionReadMsg(C4NetworkSession* self, C4NetworkMsg* value);

pxb8
c4NetworkSessionWriteMsg(C4NetworkSession* self, C4NetworkMsg value);

C4NetworkServer
c4NetworkServerCreate(PxArena* arena, pxiword length, PxAddrType type);

pxb8
c4NetworkServerStart(C4NetworkServer* self, PxAddr addr, pxu16 port);

void
c4NetworkServerStop(C4NetworkServer* self);

pxiword
c4NetworkServerConnect(C4NetworkServer* self, PxArena* arena, pxiword length);

pxb8
c4NetworkServerGet(C4NetworkServer* self, pxiword index, C4NetworkSession* value);

C4NetworkSession
c4NetworkServerGetOr(C4NetworkServer* self, pxiword index, C4NetworkSession value);

pxb8
c4NetworkServerEchoMsg(C4NetworkServer* self, pxiword index, C4NetworkMsg value);

pxb8
c4NetworkServerWriteMsg(C4NetworkServer* self, pxiword index, C4NetworkMsg value);

pxb8
c4NetworkServerReadMsg(C4NetworkServer* self, pxiword index, C4NetworkMsg* value);

C4NetworkReaderCtxt*
c4NetworkSessionReaderCtxt(C4NetworkSession* self, PxArena* arena, pxiword length);

C4NetworkWriterCtxt*
c4NetworkSessionWriterCtxt(C4NetworkSession* self, PxArena* arena, pxiword length);

#endif // C4_ENGINE_NETWORK_H
