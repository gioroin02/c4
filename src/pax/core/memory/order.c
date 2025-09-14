#ifndef PX_CORE_MEMORY_BYTE_ORDER_C
#define PX_CORE_MEMORY_BYTE_ORDER_C

#include "order.h"

PxByteOrder
pxByteOrder()
{
    pxu16 word = 0x0001;

    switch (pxCast(pxu8*, &word)[0]) {
        case 0:
            return PX_BYTE_ORDER_NETWORK;

        case 1:
            return PX_BYTE_ORDER_REVERSE;

        default: break;
    }

    return PX_BYTE_ORDER_NONE;
}

void*
pxMemoryNetFromHost(void* memory, pxiword amount, pxiword stride)
{
    if (pxByteOrder() == PX_BYTE_ORDER_REVERSE)
        return pxMemoryFlip(memory, amount * stride, 1);

    return memory;
}

void*
pxMemoryCopyNetFromHost(void* memory, void* value, pxiword amount, pxiword stride)
{
    if (pxByteOrder() == PX_BYTE_ORDER_REVERSE)
        return pxMemoryCopyFlipped(memory, value, amount * stride, 1);

    return pxMemoryCopy(memory, value, amount * stride, 1);
}

void*
pxMemoryHostFromNet(void* memory, pxiword amount, pxiword stride)
{
    if (pxByteOrder() == PX_BYTE_ORDER_REVERSE)
        return pxMemoryFlip(memory, amount * stride, 1);

    return memory;
}

void*
pxMemoryCopyHostFromNet(void* memory, void* value, pxiword amount, pxiword stride)
{
    if (pxByteOrder() == PX_BYTE_ORDER_REVERSE)
        return pxMemoryCopyFlipped(memory, value, amount * stride, 1);

    return pxMemoryCopy(memory, value, amount * stride, 1);
}

pxu16
pxUnsigned16NetFromHost(pxu16 value)
{
    pxu16 result = 0;

    pxMemoryCopyNetFromHost(&result,
        &value, 1, PX_U16_SIZE);

    return result;
}

pxu32
pxUnsigned32NetFromHost(pxu32 value)
{
    pxu32 result = 0;

    pxMemoryCopyNetFromHost(&result,
        &value, 1, PX_U32_SIZE);

    return result;
}

pxu64
pxUnsigned64NetFromHost(pxu64 value)
{
    pxu64 result = 0;

    pxMemoryCopyNetFromHost(&result,
        &value, 1, PX_U64_SIZE);

    return result;
}

pxuword
pxUnsignedNetFromHost(pxuword value)
{
    pxuword result = 0;

    pxMemoryCopyNetFromHost(&result,
        &value, 1, PX_UWORD_SIZE);

    return result;
}

pxu16
pxInteger16NetFromHost(pxi16 value)
{
    pxu16 result = 0;

    pxMemoryCopyNetFromHost(&result,
        &value, 1, PX_I16_SIZE);

    return result;
}

pxu32
pxInteger32NetFromHost(pxi32 value)
{
    pxu32 result = 0;

    pxMemoryCopyNetFromHost(&result,
        &value, 1, PX_I32_SIZE);

    return result;
}

pxu64
pxInteger64NetFromHost(pxi64 value)
{
    pxu64 result = 0;

    pxMemoryCopyNetFromHost(&result,
        &value, 1, PX_I64_SIZE);

    return result;
}

pxuword
pxIntegerNetFromHost(pxiword value)
{
    pxuword result = 0;

    pxMemoryCopyNetFromHost(&result,
        &value, 1, PX_IWORD_SIZE);

    return result;
}

pxu32
pxFloating32NetFromHost(pxf32 value)
{
    pxu32 result = 0;

    pxMemoryCopyNetFromHost(&result,
        &value, 1, PX_F32_SIZE);

    return result;
}

pxu64
pxFloating64NetFromHost(pxf64 value)
{
    pxu64 result = 0;

    pxMemoryCopyNetFromHost(&result,
        &value, 1, PX_F64_SIZE);

    return result;
}

pxuword
pxFloatingNetFromHost(pxfword value)
{
    pxuword result = 0;

    pxMemoryCopyNetFromHost(&result,
        &value, 1, PX_FWORD_SIZE);

    return result;
}

pxu16
pxUnsigned16HostFromNet(pxu16 value)
{
    pxu16 result = 0;

    pxMemoryCopyHostFromNet(&result,
        &value, 1, PX_U16_SIZE);

    return result;
}

pxu32
pxUnsigned32HostFromNet(pxu32 value)
{
    pxu32 result = 0;

    pxMemoryCopyHostFromNet(&result,
        &value, 1, PX_U32_SIZE);

    return result;
}

pxu64
pxUnsigned64HostFromNet(pxu64 value)
{
    pxu64 result = 0;

    pxMemoryCopyHostFromNet(&result,
        &value, 1, PX_U64_SIZE);

    return result;
}

pxuword
pxUnsignedHostFromNet(pxuword value)
{
    pxuword result = 0;

    pxMemoryCopyHostFromNet(&result,
        &value, 1, PX_UWORD_SIZE);

    return result;
}

pxi16
pxInteger16HostFromNet(pxu16 value)
{
    pxi16 result = 0;

    pxMemoryCopyHostFromNet(&result,
        &value, 1, PX_I64_SIZE);

    return result;
}

pxi32
pxInteger32HostFromNet(pxu32 value)
{
    pxi32 result = 0;

    pxMemoryCopyHostFromNet(&result,
        &value, 1, PX_I32_SIZE);

    return result;
}

pxi64
pxInteger64HostFromNet(pxu64 value)
{
    pxi64 result = 0;

    pxMemoryCopyHostFromNet(&result,
        &value, 1, PX_I64_SIZE);

    return result;
}

pxiword
pxIntegerHostFromNet(pxuword value)
{
    pxiword result = 0;

    pxMemoryCopyHostFromNet(&result,
        &value, 1, PX_IWORD_SIZE);

    return result;
}

pxf32
pxFloating32HostFromNet(pxu32 value)
{
    pxf32 result = 0;

    pxMemoryCopyHostFromNet(&result,
        &value, 1, PX_F32_SIZE);

    return result;
}

pxf64
pxFloating64HostFromNet(pxu64 value)
{
    pxf64 result = 0;

    pxMemoryCopyHostFromNet(&result,
        &value, 1, PX_F64_SIZE);

    return result;
}

pxfword
pxFloatingHostFromNet(pxuword value)
{
    pxfword result = 0;

    pxMemoryCopyHostFromNet(&result,
        &value, 1, PX_FWORD_SIZE);

    return result;
}

#endif // PX_CORE_MEMORY_BYTE_ORDER_C
