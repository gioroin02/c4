#ifndef PAX_CORE_NETWORK_ADDR_IP4_H
#define PAX_CORE_NETWORK_ADDR_IP4_H

#include "./import.h"

#define PAX_ADDR_IP4_ANY       ((Pax_Addr_IP4) {0})
#define PAX_ADDR_IP4_LOCALHOST ((Pax_Addr_IP4) {.a = 127, .d = 1})

#define PAX_ADDR_IP4_GROUPS pax_as(paxiword, 4)

typedef union Pax_Addr_IP4
{
    struct
    {
        paxu8 a, b, c, d;
    };

    paxu8 items[PAX_ADDR_IP4_GROUPS];
}
Pax_Addr_IP4;

paxb8
pax_addr_ip4_is_equal(Pax_Addr_IP4 self, Pax_Addr_IP4 value);

paxb8
pax_addr_ip4_from_string8(Pax_String8 string, Pax_Addr_IP4* value);

#endif // PAX_CORE_NETWORK_ADDR_IP4_H
