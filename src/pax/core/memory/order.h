#ifndef PX_CORE_MEMORY_BYTE_ORDER_H
#define PX_CORE_MEMORY_BYTE_ORDER_H

#include "import.h"

typedef enum PxByteOrder
{
    PX_BYTE_ORDER_NONE,
    PX_BYTE_ORDER_NETWORK,
    PX_BYTE_ORDER_REVERSE,
    PX_BYET_ORDER_COUNT,
}
PxByteOrder;

PxByteOrder
pxByteOrder();

/* Memory network from host */

void*
pxMemoryNetFromHost(void* memory, pxiword amount, pxiword stride);

void*
pxMemoryCopyNetFromHost(void* memory, void* value, pxiword amount, pxiword stride);

/* Memory host from network */

void*
pxMemoryHostFromNet(void* memory, pxiword amount, pxiword stride);

void*
pxMemoryCopyHostFromNet(void* memory, void* value, pxiword amount, pxiword stride);

/* Numbers network from host */

pxu16
pxUnsigned16NetFromHost(pxu16 value);

pxu32
pxUnsigned32NetFromHost(pxu32 value);

pxu64
pxUnsigned64NetFromHost(pxu64 value);

pxuword
pxUnsignedNetFromHost(pxuword value);

pxu16
pxInteger16NetFromHost(pxi16 value);

pxu32
pxInteger32NetFromHost(pxi32 value);

pxu64
pxInteger64NetFromHost(pxi64 value);

pxuword
pxIntegerNetFromHost(pxiword value);

pxu32
pxFloating32NetFromHost(pxf32 value);

pxu64
pxFloating64NetFromHost(pxf64 value);

pxuword
pxFloatingNetFromHost(pxfword value);

/* Number host from network */

pxu16
pxUnsigned16HostFromNet(pxu16 value);

pxu32
pxUnsigned32HostFromNet(pxu32 value);

pxu64
pxUnsigned64HostFromNet(pxu64 value);

pxuword
pxUnsignedHostFromNet(pxuword value);

pxi16
pxInteger16HostFromNet(pxu16 value);

pxi32
pxInteger32HostFromNet(pxu32 value);

pxi64
pxInteger64HostFromNet(pxu64 value);

pxiword
pxIntegerHostFromNet(pxuword value);

pxf32
pxFloating32HostFromNet(pxu32 value);

pxf64
pxFloating64HostFromNet(pxu64 value);

pxfword
pxFloatingHostFromNet(pxuword value);

#endif // PX_CORE_MEMORY_BYTE_ORDER_H
