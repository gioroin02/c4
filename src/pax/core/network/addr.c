#ifndef PX_CORE_NETWORK_ADDR_C
#define PX_CORE_NETWORK_ADDR_C

#include "addr.h"

PxAddr
pxAddrAny(PxAddrType type)
{
    PxAddr result = {.type = type};

    switch (result.type) {
        case PX_ADDR_TYPE_IP4:
            result.ip4 = PX_ADDR_IP4_ANY;
        break;

        case PX_ADDR_TYPE_IP6:
            result.ip6 = PX_ADDR_IP6_ANY;
        break;

        default: break;
    }

    return result;
}

PxAddr
pxAddrLocalhost(PxAddrType type)
{
    PxAddr result = {.type = type};

    switch (result.type) {
        case PX_ADDR_TYPE_IP4:
            result.ip4 = PX_ADDR_IP4_LOCALHOST;
        break;

        case PX_ADDR_TYPE_IP6:
            result.ip6 = PX_ADDR_IP6_LOCALHOST;
        break;

        default: break;
    }

    return result;
}

pxb8
pxAddrIsEqual(PxAddr self, PxAddr value)
{
    if (self.type != value.type) return 0;

    switch (self.type) {
        case PX_ADDR_TYPE_IP4:
            return pxAddrIp4IsEqual(self.ip4, value.ip4);

        case PX_ADDR_TYPE_IP6:
            return pxAddrIp6IsEqual(self.ip6, value.ip6);

        default: break;
    }

    return 0;
}

pxb8
pxAddrFromString8(PxString8 string, PxAddr* value, PxAddrType type)
{
    value->type = type;

    switch (value->type) {
        case PX_ADDR_TYPE_IP4:
            return pxAddrIp4FromString8(string, &value->ip4);

        case PX_ADDR_TYPE_IP6:
            return pxAddrIp6FromString8(string, &value->ip6);

        default: break;
    }

    return 0;
}

#endif // PX_CORE_NETWORK_ADDR_C
