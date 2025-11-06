#ifndef PX_CORE_PROCESS_CHANNEL_H
#define PX_CORE_PROCESS_CHANNEL_H

#include "lock.h"

typedef struct PxChannel
{
    PxLock    lock;
    PxBuffer8 buffer;
}
PxChannel;

PxChannel
pxChannelOpen(PxArena* arena, pxiword length);

void
pxChannelClose(PxChannel* self);

pxb8
pxChannelIsOpen(PxChannel* self);

pxiword
pxChannelWrite(PxChannel* self, pxu8* memory, pxiword length);

pxiword
pxChannelRead(PxChannel* self, pxu8* memory, pxiword length);

PxSource
pxSourceFromChannel(PxChannel* self);

PxTarget
pxTargetFromChannel(PxChannel* self);

#endif // PX_CORE_PROCESS_CHANNEL_H
