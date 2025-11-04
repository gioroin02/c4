#ifndef PAX_CORE_NETWORK_ADDR_C
#define PAX_CORE_NETWORK_ADDR_C

#include "./addr.h"

Pax_Addr
pax_addr_any(Pax_Addr_Kind kind)
{
    Pax_Addr result = {.kind = kind};

    switch (result.kind) {
        case PAX_ADDR_KIND_IP4:
            result.ip4 = PAX_ADDR_IP4_ANY;
        break;

        case PAX_ADDR_KIND_IP6:
            result.ip6 = PAX_ADDR_IP6_ANY;
        break;

        default: break;
    }

    return result;
}

Pax_Addr
pax_addr_localhost(Pax_Addr_Kind kind)
{
    Pax_Addr result = {.kind = kind};

    switch (result.kind) {
        case PAX_ADDR_KIND_IP4:
            result.ip4 = PAX_ADDR_IP4_LOCALHOST;
        break;

        case PAX_ADDR_KIND_IP6:
            result.ip6 = PAX_ADDR_IP6_LOCALHOST;
        break;

        default: break;
    }

    return result;
}

paxb8
pax_addr_is_equal(Pax_Addr self, Pax_Addr value)
{
    if (self.kind != value.kind) return 0;

    switch (self.kind) {
        case PAX_ADDR_KIND_IP4:
            return pax_addr_ip4_is_equal(self.ip4, value.ip4);

        case PAX_ADDR_KIND_IP6:
            return pax_addr_ip6_is_equal(self.ip6, value.ip6);

        default: break;
    }

    return 0;
}

paxb8
pax_addr_from_string8(Pax_String8 string, Pax_Addr* value, Pax_Addr_Kind kind)
{
    value->kind = kind;

    switch (value->kind) {
        case PAX_ADDR_KIND_IP4:
            return pax_addr_ip4_from_string8(string, &value->ip4);

        case PAX_ADDR_KIND_IP6:
            return pax_addr_ip6_from_string8(string, &value->ip6);

        default: break;
    }

    return 0;
}

#endif // PAX_CORE_NETWORK_ADDR_C
