#ifndef PAX_CORE_NETWORK_ADDR_H
#define PAX_CORE_NETWORK_ADDR_H

#include "./addr_ip4.h"
#include "./addr_ip6.h"

typedef enum Pax_Addr_Kind
{
    PAX_ADDR_KIND_NONE,
    PAX_ADDR_KIND_IP4,
    PAX_ADDR_KIND_IP6,
}
Pax_Addr_Kind;

typedef struct Pax_Addr
{
    Pax_Addr_Kind kind;

    union
    {
        Pax_Addr_IP4 ip4;
        Pax_Addr_IP6 ip6;
    };
}
Pax_Addr;

Pax_Addr
pax_addr_any(Pax_Addr_Kind kind);

Pax_Addr
pax_addr_localhost(Pax_Addr_Kind kind);

paxb8
pax_addr_is_equal(Pax_Addr self, Pax_Addr value);

paxb8
pax_addr_from_string8(Pax_String8 string, Pax_Addr* value, Pax_Addr_Kind kind);

#endif // PAX_CORE_NETWORK_ADDR_H
