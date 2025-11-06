#ifndef PX_CORE_NETWORK_ADDR_IP6_H
#define PX_CORE_NETWORK_ADDR_IP6_H

#include "import.h"

#define PX_ADDR_IP6_ANY       ((PxAddrIp6) {0})
#define PX_ADDR_IP6_LOCALHOST ((PxAddrIp6) {.h = 1})

#define PX_ADDR_IP6_GROUPS px_as(pxiword, 8)

typedef union PxAddrIp6
{
    struct
    {
        pxu16 a, b, c, d;
        pxu16 e, f, g, h;
    };

    pxu16 items[PX_ADDR_IP6_GROUPS];
}
PxAddrIp6;

pxb8
pxAddrIp6IsEqual(PxAddrIp6 self, PxAddrIp6 value);

pxb8
pxAddrIp6FromString8(PxString8 string, PxAddrIp6* value);

#endif // PX_CORE_NETWORK_ADDR_IP6_H
