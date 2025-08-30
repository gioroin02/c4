#ifndef C4_CLIENT_H
#define C4_CLIENT_H

#include "import.h"

typedef struct C4Client
{
    PxSocketTcp socket;
    PxBuffer8   request;
    PxBuffer8   response;
}
C4Client;

C4Client
c4ClientMake(PxArena* arena, PxAddressType type);

pxb8
c4ClientStart(C4Client* self, PxAddress address, pxu16 port);

void
c4ClientStop(C4Client* self);

pxb8
c4ClientWrite(C4Client* self, PxArena* arena, C4Message value);

C4Message
c4ClientRead(C4Client* self, PxArena* arena);

#endif // C4_CLIENT_H
