#ifndef PX_CORE_BASE_NUMBER_C
#define PX_CORE_BASE_NUMBER_C

#include "number.h"

pxu8
pxMagnitudeInteger8(pxi8 value)
{
    if (value < 0)
        return -px_as(pxu8, value);

    return px_as(pxu8, value);
}

pxu16
pxMagnitudeInteger16(pxi16 value)
{
    if (value < 0)
        return -px_as(pxu16, value);

    return px_as(pxu16, value);
}

pxu32
pxMagnitudeInteger32(pxi32 value)
{
    if (value < 0)
        return -px_as(pxu32, value);

    return px_as(pxu32, value);
}

pxu64
pxMagnitudeInteger64(pxi64 value)
{
    if (value < 0)
        return -px_as(pxu64, value);

    return px_as(pxu64, value);
}

pxuword
pxMagnitudeInteger(pxiword value)
{
    if (value < 0)
        return -px_as(pxuword, value);

    return px_as(pxuword, value);
}

pxf32
pxMagnitudeFloating32(pxf32 value)
{
    pxu32* bits =
        px_as(pxu32*, &value);

    *bits &= ~PX_F32_SIGN_MASK;

    return value;
}

pxf64
pxMagnitudeFloating64(pxf64 value)
{
    pxu64* bits =
        px_as(pxu64*, &value);

    *bits &= ~PX_F64_SIGN_MASK;

    return value;
}

pxfword
pxMagnitudeFloating(pxfword value)
{
    pxuword* bits =
        px_as(pxuword*, &value);

    *bits &= ~PX_FWORD_SIGN_MASK;

    return value;
}

pxi8
pxDirectionUnsigned8(pxu8 value)
{
    return value > 0 ? 1 : 0;
}

pxi8
pxDirectionUnsigned16(pxu16 value)
{
    return value > 0 ? 1 : 0;
}

pxi8
pxDirectionUnsigned32(pxu32 value)
{
    return value > 0 ? 1 : 0;
}

pxi8
pxDirectionUnsigned64(pxu64 value)
{
    return value > 0 ? 1 : 0;
}

pxi8
pxDirectionUnsigned(pxuword value)
{
    return value > 0 ? 1 : 0;
}

pxi8
pxDirectionInteger8(pxi8 value)
{
    if (value > 0) return +1;
    if (value < 0) return -1;

    return 0;
}

pxi8
pxDirectionInteger16(pxi16 value)
{
    if (value > 0) return +1;
    if (value < 0) return -1;

    return 0;
}

pxi8
pxDirectionInteger32(pxi32 value)
{
    if (value > 0) return +1;
    if (value < 0) return -1;

    return 0;
}

pxi8
pxDirectionInteger64(pxi64 value)
{
    if (value > 0) return +1;
    if (value < 0) return -1;

    return 0;
}

pxi8
pxDirectionInteger(pxiword value)
{
    if (value > 0) return +1;
    if (value < 0) return -1;

    return 0;
}

pxi8
pxDirectionFloating32(pxf32 value)
{
    if (value > 0) return +1;
    if (value < 0) return -1;

    return 0;
}

pxi8
pxDirectionFloating64(pxf64 value)
{
    if (value > 0) return +1;
    if (value < 0) return -1;

    return 0;
}

pxi8
pxDirectionFloating(pxfword value)
{
    if (value > 0) return +1;
    if (value < 0) return -1;

    return 0;
}

#endif // PX_CORE_BASE_NUMBER_C
