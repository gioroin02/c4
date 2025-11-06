#ifndef PX_CORE_NETWORK_ADDR_H
#define PX_CORE_NETWORK_ADDR_H

#include "addr_ip4.h"
#include "addr_ip6.h"

typedef enum PxAddrType
{
    PX_ADDR_TYPE_NONE,
    PX_ADDR_TYPE_IP4,
    PX_ADDR_TYPE_IP6,
}
PxAddrType;

typedef struct PxAddr
{
    PxAddrType type;

    union
    {
        PxAddrIp4 ip4;
        PxAddrIp6 ip6;
    };
}
PxAddr;

PxAddr
pxAddrAny(PxAddrType type);

PxAddr
pxAddrLocalhost(PxAddrType type);

pxb8
pxAddrIsEqual(PxAddr self, PxAddr value);

pxb8
pxAddrFromString8(PxString8 string, PxAddr* value, PxAddrType type);

#endif // PX_CORE_NETWORK_ADDR_H
