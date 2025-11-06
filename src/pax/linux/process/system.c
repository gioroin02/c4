#ifndef PX_LINUX_PROCESS_SYSTEM_C
#define PX_LINUX_PROCESS_SYSTEM_C

#include "system.h"

#if !defined(_POSIX_C_SOURCE)

    #define _POSIX_C_SOURCE 200809L

#endif

#include <unistd.h>
#include <time.h>

#include <pthread.h>

typedef struct timespec PxLinuxTimeSpec;

pxiword
pxLinuxProcessCoreAmount()
{
    long result = sysconf(_SC_NPROCESSORS_ONLN);

    if (result > 0)
        return px_as(pxiword, result);

    return 0;
}

void
pxLinuxCurrentThreadSleep(pxuword millis)
{
    PxLinuxTimeSpec spec;

    spec.tv_sec  = (millis / 1000);
    spec.tv_nsec = (millis % 1000) * 1000000;

    nanosleep(&spec, 0);
}

pxiword
pxLinuxCurrentThreadIdent()
{
    return px_as(pxiword, pthread_self());
}

#endif // PX_LINUX_PROCESS_SYSTEM_C
