#ifndef PAX_CORE_MEMORY_DEFINE_H
#define PAX_CORE_MEMORY_DEFINE_H

#include "./import.h"

#define PAX_MEMORY_KB pax_as(paxiword, 1000)
#define PAX_MEMORY_MB pax_as(paxiword, 1000 * 1000)
#define PAX_MEMORY_GB pax_as(paxiword, 1000 * 1000 * 1000)

#define PAX_MEMORY_KIB pax_as(paxiword, 1024)
#define PAX_MEMORY_MIB pax_as(paxiword, 1024 * 1024)
#define PAX_MEMORY_GIB pax_as(paxiword, 1024 * 1024 * 1024)

#endif // PAX_CORE_MEMORY_DEFINE_H
