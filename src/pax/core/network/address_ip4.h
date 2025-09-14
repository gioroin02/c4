#ifndef PX_CORE_NETWORK_ADDRESS_IP4_H
#define PX_CORE_NETWORK_ADDRESS_IP4_H

#include "import.h"

#define PX_ADDRESS_IP4_ANY       ((PxAddressIp4) {0})
#define PX_ADDRESS_IP4_LOCALHOST ((PxAddressIp4) {.a = 127, .d = 1})

#define PX_ADDRESS_IP4_GROUPS pxCast(pxiword, 4)

typedef union PxAddressIp4
{
    struct
    {
        pxu8 a, b, c, d;
    };

    pxu8 items[PX_ADDRESS_IP4_GROUPS];
}
PxAddressIp4;

pxb8
pxAddressIp4FromString8(PxAddressIp4* self, PxString8 string);

pxb8
pxAddressIp4IsEqual(PxAddressIp4 self, PxAddressIp4 value);

#endif // PX_CORE_NETWORK_ADDRESS_IP4_H
