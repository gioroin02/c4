#ifndef C4_CLIENT_H
#define C4_CLIENT_H

#include "import.h"

extern PxLogger* LOGGER;

typedef struct C4Client
{
    PxSocketTcp socket;
    PxReader    reader;
    PxWriter    writer;
}
C4Client;

C4Client
c4ClientMake(PxArena* arena, pxiword length, PxAddressType type);

pxb8
c4ClientStart(C4Client* self, PxAddress address, pxu16 port);

void
c4ClientStop(C4Client* self);

pxb8
c4ClientWrite(C4Client* self, PxArena* arena, C4Msg value);

C4Msg
c4ClientRead(C4Client* self, PxArena* arena);

#endif // C4_CLIENT_H
