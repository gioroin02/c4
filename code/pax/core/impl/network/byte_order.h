#ifndef PAX_CORE_NETWORK_BYTE_ORDER_H
#define PAX_CORE_NETWORK_BYTE_ORDER_H

#include "./import.h"

typedef enum Pax_Byte_Order
{
    PAX_BYTE_ORDER_NONE,
    PAX_BYTE_ORDER_DEFAULT,
    PAX_BYTE_ORDER_NETWORK,
    PAX_BYET_ORDER_COUNT,
}
Pax_Byte_Order;

Pax_Byte_Order
pax_byte_order();

/* Memory network from host */

void*
pax_slice_net_from_host(Pax_Slice self);

/* Numbers network from host */

paxu16
pax_u16_net_from_host(paxu16 value);

paxu32
pax_u32_net_from_host(paxu32 value);

paxu64
pax_u64_net_from_host(paxu64 value);

paxuword
pax_unsigned_net_from_host(paxuword value);

paxu16
pax_i16_net_from_host(paxi16 value);

paxu32
pax_i32_net_from_host(paxi32 value);

paxu64
pax_i64_net_from_host(paxi64 value);

paxuword
pax_integer_net_from_host(paxiword value);

paxu32
pax_f32_net_from_host(paxf32 value);

paxu64
pax_f64_net_from_host(paxf64 value);

paxuword
pax_floating_net_from_host(paxfword value);

/* Memory host from network */

void*
pax_memory_host_from_net(Pax_Slice self);

/* Number host from network */

paxu16
pax_u16_host_from_net(paxu16 value);

paxu32
pax_u32_host_from_net(paxu32 value);

paxu64
pax_u64_host_from_net(paxu64 value);

paxuword
pax_unsigned_host_from_net(paxuword value);

paxi16
pax_i16_host_from_net(paxu16 value);

paxi32
pax_i32_host_from_net(paxu32 value);

paxi64
pax_i64_host_from_net(paxu64 value);

paxiword
pax_integer_host_from_net(paxuword value);

paxf32
pax_f32_host_from_net(paxu32 value);

paxf64
pax_f64_host_from_net(paxu64 value);

paxfword
pax_floating_host_from_net(paxuword value);

#endif // PAX_CORE_NETWORK_BYTE_ORDER_H
