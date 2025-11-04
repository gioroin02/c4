#ifndef PAX_CORE_NETWORK_BYTE_ORDER_C
#define PAX_CORE_NETWORK_BYTE_ORDER_C

#include "./byte_order.h"

Pax_Byte_Order
pax_byte_order()
{
    paxu16 word = 0x0100;

    switch (pax_as(paxu8*, &word)[0]) {
        case 0:
            return PAX_BYTE_ORDER_DEFAULT;

        case 1:
            return PAX_BYTE_ORDER_NETWORK;

        default: break;
    }

    return PAX_BYTE_ORDER_NONE;
}

void*
pax_slice_net_from_host(Pax_Slice self)
{
    self.length = self.length * self.stride;
    self.stride = 1;

    if (pax_byte_order() == PAX_BYTE_ORDER_DEFAULT)
        return pax_slice_flip(self);

    return self.memory;
}

paxu16
pax_u16_net_from_host(paxu16 value)
{
    paxiword length = 1;
    paxiword stride = pax_size(paxu16);

    Pax_Slice slice =
        pax_slice_make(&value, length, stride);

    pax_slice_net_from_host(slice);

    return value;
}

paxu32
pax_u32_net_from_host(paxu32 value)
{
    paxiword length = 1;
    paxiword stride = pax_size(paxu32);

    Pax_Slice slice =
        pax_slice_make(&value, length, stride);

    pax_slice_net_from_host(slice);

    return value;
}

paxu64
pax_u64_net_from_host(paxu64 value)
{
    paxiword length = 1;
    paxiword stride = pax_size(paxu64);

    Pax_Slice slice =
        pax_slice_make(&value, length, stride);

    pax_slice_net_from_host(slice);

    return value;
}

paxuword
pax_unsigned_net_from_host(paxuword value)
{
    paxiword length = 1;
    paxiword stride = pax_size(paxuword);

    Pax_Slice slice =
        pax_slice_make(&value, length, stride);

    pax_slice_net_from_host(slice);

    return value;
}

paxu16
pax_i16_net_from_host(paxi16 value)
{
    paxiword length = 1;
    paxiword stride = pax_size(paxu16);

    Pax_Slice slice =
        pax_slice_make(&value, length, stride);

    pax_slice_net_from_host(slice);

    return *pax_as(paxu16*, &value);
}

paxu32
pax_i32_net_from_host(paxi32 value)
{
    paxiword length = 1;
    paxiword stride = pax_size(paxu32);

    Pax_Slice slice =
        pax_slice_make(&value, length, stride);

    pax_slice_net_from_host(slice);

    return *pax_as(paxu32*, &value);
}

paxu64
pax_i64_net_from_host(paxi64 value)
{
    paxiword length = 1;
    paxiword stride = pax_size(paxu64);

    Pax_Slice slice =
        pax_slice_make(&value, length, stride);

    pax_slice_net_from_host(slice);

    return *pax_as(paxu64*, &value);
}

paxuword
pax_integer_net_from_host(paxiword value)
{
    paxiword length = 1;
    paxiword stride = pax_size(paxuword);

    Pax_Slice slice =
        pax_slice_make(&value, length, stride);

    pax_slice_net_from_host(slice);

    return *pax_as(paxuword*, &value);
}

paxu32
pax_f32_net_from_host(paxf32 value)
{
    paxiword length = 1;
    paxiword stride = pax_size(paxu32);

    Pax_Slice slice =
        pax_slice_make(&value, length, stride);

    pax_slice_net_from_host(slice);

    return *pax_as(paxu32*, &value);
}

paxu64
pax_f64_net_from_host(paxf64 value)
{
    paxiword length = 1;
    paxiword stride = pax_size(paxu64);

    Pax_Slice slice =
        pax_slice_make(&value, length, stride);

    pax_slice_net_from_host(slice);

    return *pax_as(paxu64*, &value);
}

paxuword
pax_floating_net_from_host(paxfword value)
{
    paxiword length = 1;
    paxiword stride = pax_size(paxuword);

    Pax_Slice slice =
        pax_slice_make(&value, length, stride);

    pax_slice_net_from_host(slice);

    return *pax_as(paxuword*, &value);
}

void*
pax_slice_host_from_net(Pax_Slice self)
{
    self.length = self.length * self.stride;
    self.stride = 1;

    if (pax_byte_order() == PAX_BYTE_ORDER_DEFAULT)
        return pax_slice_flip(self);

    return self.memory;
}

paxu16
pax_u16_host_from_net(paxu16 value)
{
    paxiword length = 1;
    paxiword stride = pax_size(paxu16);

    Pax_Slice slice =
        pax_slice_make(&value, length, stride);

    pax_slice_host_from_net(slice);

    return value;
}

paxu32
pax_u32_host_from_net(paxu32 value)
{
    paxiword length = 1;
    paxiword stride = pax_size(paxu32);

    Pax_Slice slice =
        pax_slice_make(&value, length, stride);

    pax_slice_host_from_net(slice);

    return value;
}

paxu64
pax_u64_host_from_net(paxu64 value)
{
    paxiword length = 1;
    paxiword stride = pax_size(paxu64);

    Pax_Slice slice =
        pax_slice_make(&value, length, stride);

    pax_slice_host_from_net(slice);

    return value;
}

paxuword
pax_unsigned_host_from_net(paxuword value)
{
    paxiword length = 1;
    paxiword stride = pax_size(paxuword);

    Pax_Slice slice =
        pax_slice_make(&value, length, stride);

    pax_slice_host_from_net(slice);

    return value;
}

paxi16
pax_i16_host_from_net(paxu16 value)
{
    paxiword length = 1;
    paxiword stride = pax_size(paxi16);

    Pax_Slice slice =
        pax_slice_make(&value, length, stride);

    pax_slice_host_from_net(slice);

    return *pax_as(paxi16*, &value);
}

paxi32
pax_i32_host_from_net(paxu32 value)
{
    paxiword length = 1;
    paxiword stride = pax_size(paxi32);

    Pax_Slice slice =
        pax_slice_make(&value, length, stride);

    pax_slice_host_from_net(slice);

    return *pax_as(paxi32*, &value);
}

paxi64
pax_i64_host_from_net(paxu64 value)
{
    paxiword length = 1;
    paxiword stride = pax_size(paxi64);

    Pax_Slice slice =
        pax_slice_make(&value, length, stride);

    pax_slice_host_from_net(slice);

    return *pax_as(paxi64*, &value);
}

paxiword
pax_integer_host_from_net(paxuword value)
{
    paxiword length = 1;
    paxiword stride = pax_size(paxiword);

    Pax_Slice slice =
        pax_slice_make(&value, length, stride);

    pax_slice_host_from_net(slice);

    return *pax_as(paxiword*, &value);
}

paxf32
pax_f32_host_from_net(paxu32 value)
{
    paxiword length = 1;
    paxiword stride = pax_size(paxf32);

    Pax_Slice slice =
        pax_slice_make(&value, length, stride);

    pax_slice_host_from_net(slice);

    return *pax_as(paxf32*, &value);
}

paxf64
pax_f64_host_from_net(paxu64 value)
{
    paxiword length = 1;
    paxiword stride = pax_size(paxf64);

    Pax_Slice slice =
        pax_slice_make(&value, length, stride);

    pax_slice_host_from_net(slice);

    return *pax_as(paxf64*, &value);
}

paxfword
pax_floating_host_from_net(paxuword value)
{
    paxiword length = 1;
    paxiword stride = pax_size(paxfword);

    Pax_Slice slice =
        pax_slice_make(&value, length, stride);

    pax_slice_host_from_net(slice);

    return *pax_as(paxfword*, &value);
}

#endif // PAX_CORE_NETWORK_BYTE_ORDER_C
