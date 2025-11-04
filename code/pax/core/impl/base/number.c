#ifndef PAX_CORE_BASE_NUMBER_C
#define PAX_CORE_BASE_NUMBER_C

#include "./number.h"

paxu8
pax_magn_i8(paxi8 value)
{
    if (value < 0)
        return -pax_as(paxu8, value);

    return pax_as(paxu8, value);
}

paxu16
pax_magn_i16(paxi16 value)
{
    if (value < 0)
        return -pax_as(paxu16, value);

    return pax_as(paxu16, value);
}

paxu32
pax_magn_i32(paxi32 value)
{
    if (value < 0)
        return -pax_as(paxu32, value);

    return pax_as(paxu32, value);
}

paxu64
pax_magn_i64(paxi64 value)
{
    if (value < 0)
        return -pax_as(paxu64, value);

    return pax_as(paxu64, value);
}

paxuword
pax_magn_integer(paxiword value)
{
    if (value < 0)
        return -pax_as(paxuword, value);

    return pax_as(paxuword, value);
}

paxf32
pax_magn_f32(paxf32 value)
{
    paxu32* bits =
        pax_as(paxu32*, &value);

    *bits &= ~PAX_F32_SIGN_MASK;

    return value;
}

paxf64
pax_magn_f64(paxf64 value)
{
    paxu64* bits =
        pax_as(paxu64*, &value);

    *bits &= ~PAX_F64_SIGN_MASK;

    return value;
}

paxfword
pax_magn_floating(paxfword value)
{
    paxuword* bits =
        pax_as(paxuword*, &value);

    *bits &= ~PAX_FWORD_SIGN_MASK;

    return value;
}

paxi8
pax_sign_u8(paxu8 value)
{
    return value > 0 ? 1 : 0;
}

paxi8
pax_sign_u16(paxu16 value)
{
    return value > 0 ? 1 : 0;
}

paxi8
pax_sign_u32(paxu32 value)
{
    return value > 0 ? 1 : 0;
}

paxi8
pax_sign_u64(paxu64 value)
{
    return value > 0 ? 1 : 0;
}

paxi8
pax_sign_unsigned(paxuword value)
{
    return value > 0 ? 1 : 0;
}

paxi8
pax_sign_i8(paxi8 value)
{
    if (value > 0) return +1;
    if (value < 0) return -1;

    return 0;
}

paxi8
pax_sign_i16(paxi16 value)
{
    if (value > 0) return +1;
    if (value < 0) return -1;

    return 0;
}

paxi8
pax_sign_i32(paxi32 value)
{
    if (value > 0) return +1;
    if (value < 0) return -1;

    return 0;
}

paxi8
pax_sign_i64(paxi64 value)
{
    if (value > 0) return +1;
    if (value < 0) return -1;

    return 0;
}

paxi8
pax_sign_integer(paxiword value)
{
    if (value > 0) return +1;
    if (value < 0) return -1;

    return 0;
}

paxi8
pax_sign_f32(paxf32 value)
{
    if (value > 0) return +1;
    if (value < 0) return -1;

    return 0;
}

paxi8
pax_sign_f64(paxf64 value)
{
    if (value > 0) return +1;
    if (value < 0) return -1;

    return 0;
}

paxi8
pax_sign_floating(paxfword value)
{
    if (value > 0) return +1;
    if (value < 0) return -1;

    return 0;
}

#endif // PAX_CORE_BASE_NUMBER_C
