#ifndef PAX_CORE_NETWORK_ADDR_IP6_H
#define PAX_CORE_NETWORK_ADDR_IP6_H

#include "./import.h"

#define PAX_ADDR_IP6_ANY       ((Pax_Addr_IP6) {0})
#define PAX_ADDR_IP6_LOCALHOST ((Pax_Addr_IP6) {.h = 1})

#define PAX_ADDR_IP6_GROUPS pax_as(paxiword, 8)

typedef union Pax_Addr_IP6
{
    struct
    {
        paxu16 a, b, c, d;
        paxu16 e, f, g, h;
    };

    paxu16 items[PAX_ADDR_IP6_GROUPS];
}
Pax_Addr_IP6;

paxb8
pax_addr_ip6_is_equal(Pax_Addr_IP6 self, Pax_Addr_IP6 value);

paxb8
pax_addr_ip6_from_string8(Pax_String8 string, Pax_Addr_IP6* value);

#endif // PAX_CORE_NETWORK_ADDR_IP6_H
