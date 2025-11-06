#ifndef PX_CORE_NETWORK_ADDR_IP6_C
#define PX_CORE_NETWORK_ADDR_IP6_C

#include "addr_ip6.h"

static pxb8
pxPartIp6FromString8(PxString8 string, PxAddrIp6* value, pxiword start, pxiword stop)
{
    pxiword groups = pxString8Contains(string, pxs8(":"));

    if (groups != stop - start - 1) return 0;

    PxFormatRadix radix = PX_FORMAT_RADIX_16;
    PxFormatFlag  flags = PX_FORMAT_FLAG_NONE;

    PxString8 left  = {0};
    PxString8 right = string;

    for (pxiword i = start; i < stop; i += 1) {
        pxuword item = 0;

        pxString8Split(right, pxs8(":"), &left, &right);

        if (pxUnsignedFromString8(left, &item, radix, flags) == 0)
            return 0;

        if (left.length > 0 && item <= PX_U16_MAX)
            value->items[i] = item;
        else
            return 0;
    }

    return 1;
}

pxb8
pxAddrIp6IsEqual(PxAddrIp6 self, PxAddrIp6 value)
{
    return pxMemoryIsEqual(self.items, value.items,
        PX_ADDR_IP6_GROUPS, 2);
}

pxb8
pxAddrIp6FromString8(PxString8 string, PxAddrIp6* value)
{
    PxAddrIp6 temp = {0};

    pxiword start = 0;
    pxiword stop  = PX_ADDR_IP6_GROUPS;

    switch (pxString8Contains(string, pxs8("::"))) {
        case 0: {
            pxiword groups = pxString8Contains(string, pxs8(":"));

            if (groups != PX_ADDR_IP6_GROUPS - 1) return 0;

            if (pxPartIp6FromString8(string, &temp, start, stop) == 0)
                return 0;
        } break;

        case 1: {
            PxString8 left  = {0};
            PxString8 right = {0};

            pxString8Split(string, pxs8("::"), &left, &right);

            pxiword head = pxString8Contains(left, pxs8(":"));
            pxiword tail = pxString8Contains(right, pxs8(":"));

            if (head + tail > PX_ADDR_IP6_GROUPS - 3) return 0;

            if (left.length > 0) {
                pxiword pivot = start + head + 1;

                if (pxPartIp6FromString8(left, &temp, start, pivot) == 0)
                    return 0;
            }

            if (right.length > 0) {
                pxiword pivot = stop - tail - 1;

                if (pxPartIp6FromString8(right, &temp, pivot, stop) == 0)
                    return 0;
            }
        } break;

        default: return 0;
    }

    if (value != 0) *value = temp;

    return 1;
}

#endif // PX_CORE_NETWORK_ADDR_IP6_C
