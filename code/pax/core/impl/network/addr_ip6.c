#ifndef PAX_CORE_NETWORK_ADDR_IP6_C
#define PAX_CORE_NETWORK_ADDR_IP6_C

#include "./addr_ip6.h"

static paxb8
paxPartIp6_from_string8(Pax_String8 string, Pax_Addr_IP6* value, paxiword start, paxiword stop)
{
    paxiword groups = pax_string8_contains(string, pax_str8(":"));

    if (groups != stop - start - 1) return 0;

    Pax_Format_Radix radix = PAX_FORMAT_RADIX_16;
    Pax_Format_Flag  flags = PAX_FORMAT_FLAG_NONE;

    Pax_String8 left  = {0};
    Pax_String8 right = string;

    for (paxiword i = start; i < stop; i += 1) {
        paxuword item = 0;

        pax_string8_split(right, pax_str8(":"), &left, &right);

        if (pax_unsigned_from_string8(left, &item, radix, flags) == 0)
            return 0;

        if (left.length > 0 && item <= PAX_U16_MAX)
            value->items[i] = item;
        else
            return 0;
    }

    return 1;
}

paxb8
pax_addr_ip6_is_equal(Pax_Addr_IP6 self, Pax_Addr_IP6 value)
{
    paxiword length = PAX_ADDR_IP6_GROUPS;
    paxiword stride = pax_size(paxu16);

    Pax_Slice slice = pax_slice_make(self.items,  length, stride);
    Pax_Slice other = pax_slice_make(value.items, length, stride);

    return pax_slice_is_equal(slice, other);
}

paxb8
pax_addr_ip6_from_string8(Pax_String8 string, Pax_Addr_IP6* value)
{
    Pax_Addr_IP6 temp = {0};

    paxiword start = 0;
    paxiword stop  = PAX_ADDR_IP6_GROUPS;

    switch (pax_string8_contains(string, pax_str8("::"))) {
        case 0: {
            paxiword groups = pax_string8_contains(string, pax_str8(":"));

            if (groups != PAX_ADDR_IP6_GROUPS - 1) return 0;

            if (paxPartIp6_from_string8(string, &temp, start, stop) == 0)
                return 0;
        } break;

        case 1: {
            Pax_String8 left  = {0};
            Pax_String8 right = {0};

            pax_string8_split(string, pax_str8("::"), &left, &right);

            paxiword head = pax_string8_contains(left, pax_str8(":"));
            paxiword tail = pax_string8_contains(right, pax_str8(":"));

            if (head + tail > PAX_ADDR_IP6_GROUPS - 3) return 0;

            if (left.length > 0) {
                paxiword pivot = start + head + 1;

                if (paxPartIp6_from_string8(left, &temp, start, pivot) == 0)
                    return 0;
            }

            if (right.length > 0) {
                paxiword pivot = stop - tail - 1;

                if (paxPartIp6_from_string8(right, &temp, pivot, stop) == 0)
                    return 0;
            }
        } break;

        default: return 0;
    }

    if (value != 0) *value = temp;

    return 1;
}

#endif // PAX_CORE_NETWORK_ADDR_IP6_C
