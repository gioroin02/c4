#ifndef PAX_CORE_NETWORK_ADDR_IP4_C
#define PAX_CORE_NETWORK_ADDR_IP4_C

#include "./addr_ip4.h"

paxb8
pax_addr_ip4_is_equal(Pax_Addr_IP4 self, Pax_Addr_IP4 value)
{
    paxiword length = PAX_ADDR_IP4_GROUPS;
    paxiword stride = pax_size(paxu8);

    Pax_Slice slice = pax_slice_make(self.items,  length, stride);
    Pax_Slice other = pax_slice_make(value.items, length, stride);

    return pax_slice_is_equal(slice, other);
}

paxb8
pax_addr_ip4_from_string8(Pax_String8 string, Pax_Addr_IP4* value)
{
    Pax_Addr_IP4 temp   = {0};
    paxiword     groups = pax_string8_contains(string, pax_str8("."));

    if (groups != PAX_ADDR_IP4_GROUPS - 1) return 0;

    Pax_Format_Radix radix = PAX_FORMAT_RADIX_10;
    Pax_Format_Flag  flags = PAX_FORMAT_FLAG_NONE;

    Pax_String8 left  = {0};
    Pax_String8 right = string;

    for (paxiword i = 0; i < PAX_ADDR_IP4_GROUPS; i += 1) {
        paxuword item = 0;

        pax_string8_split(right, pax_str8("."), &left, &right);

        if (pax_unsigned_from_string8(left, &item, radix, flags) == 0)
            return 0;

        if (left.length > 0 && item <= PAX_U8_MAX)
            temp.items[i] = item;
        else
            return 0;
    }

    if (value != 0) *value = temp;

    return 1;
}

#endif // PAX_CORE_NETWORK_ADDR_IP4_C
