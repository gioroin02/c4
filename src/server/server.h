#ifndef C4_SERVER_H
#define C4_SERVER_H

#include "import.h"

extern PxLogger* LOGGER;

typedef struct C4Server
{
    PxSocketTcp socket;
    PxArray     sessions;
}
C4Server;

typedef struct C4Session
{
    PxSocketTcp socket;
    PxReader    reader;
    PxWriter    writer;
}
C4Session;

C4Server
c4ServerMake(PxArena* arena, pxiword length, PxAddressType type);

pxb8
c4ServerStart(C4Server* self, PxAddress address, pxu16 port);

void
c4ServerStop(C4Server* self);

void
c4ServerBroadcast(C4Server* self, PxArena* arena, C4Session* from, C4Msg value);

pxiword
c4ServerFind(C4Server* self, C4Session* value);

pxb8
c4ServerGet(C4Server* self, pxiword index, C4Session** value);

C4Session*
c4ServerGetOr(C4Server* self, pxiword index, C4Session* value);

C4Session*
c4SessionOpen(C4Server* self, PxArena* arena);

pxb8
c4SessionClose(C4Server* self, C4Session* session);

pxb8
c4SessionWrite(C4Session* self, PxArena* arena, C4Msg value);

C4Msg
c4SessionRead(C4Session* self, PxArena* arena);

#endif // C4_SERVER_H
