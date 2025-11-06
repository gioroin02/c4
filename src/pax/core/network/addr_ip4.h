#ifndef PX_CORE_NETWORK_ADDR_IP4_H
#define PX_CORE_NETWORK_ADDR_IP4_H

#include "import.h"

#define PX_ADDR_IP4_ANY       ((PxAddrIp4) {0})
#define PX_ADDR_IP4_LOCALHOST ((PxAddrIp4) {.a = 127, .d = 1})

#define PX_ADDR_IP4_GROUPS px_as(pxiword, 4)

typedef union PxAddrIp4
{
    struct
    {
        pxu8 a, b, c, d;
    };

    pxu8 items[PX_ADDR_IP4_GROUPS];
}
PxAddrIp4;

pxb8
pxAddrIp4IsEqual(PxAddrIp4 self, PxAddrIp4 value);

pxb8
pxAddrIp4FromString8(PxString8 string, PxAddrIp4* value);

#endif // PX_CORE_NETWORK_ADDR_IP4_H
