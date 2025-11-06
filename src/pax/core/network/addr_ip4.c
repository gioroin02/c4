#ifndef PX_CORE_NETWORK_ADDR_IP4_C
#define PX_CORE_NETWORK_ADDR_IP4_C

#include "addr_ip4.h"

pxb8
pxAddrIp4IsEqual(PxAddrIp4 self, PxAddrIp4 value)
{
    return pxMemoryIsEqual(self.items, value.items,
        PX_ADDR_IP4_GROUPS, 1);
}

pxb8
pxAddrIp4FromString8(PxString8 string, PxAddrIp4* value)
{
    PxAddrIp4 temp   = {0};
    pxiword      groups = pxString8Contains(string, pxs8("."));

    if (groups != PX_ADDR_IP4_GROUPS - 1) return 0;

    PxFormatRadix radix = PX_FORMAT_RADIX_10;
    PxFormatFlag  flags = PX_FORMAT_FLAG_NONE;

    PxString8 left  = {0};
    PxString8 right = string;

    for (pxiword i = 0; i < PX_ADDR_IP4_GROUPS; i += 1) {
        pxuword item = 0;

        pxString8Split(right, pxs8("."), &left, &right);

        if (pxUnsignedFromString8(left, &item, radix, flags) == 0)
            return 0;

        if (left.length > 0 && item <= PX_U8_MAX)
            temp.items[i] = item;
        else
            return 0;
    }

    if (value != 0) *value = temp;

    return 1;
}

#endif // PX_CORE_NETWORK_ADDR_IP4_C
