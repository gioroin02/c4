#ifndef PAX_LINUX_PROCESS_SYSTEM_C
#define PAX_LINUX_PROCESS_SYSTEM_C

#if !defined(_POSIX_C_SOURCE)

    #define _POSIX_C_SOURCE 200809L

#endif

#include "./system.h"

#include <linux/time.h>

#include <unistd.h>
#include <errno.h>

#include <pthread.h>

typedef struct timespec Pax_Time_Spec;

paxiword
pax_linux_process_core_amount()
{
    long result = sysconf(_SC_NPROCESSORS_ONLN);

    if (result > 0)
        return pax_as(paxiword, result);

    return 0;
}

void
pax_linux_current_thread_sleep(paxuword millis)
{
    Pax_Time_Spec spec = {0};

    spec.tv_sec  = (millis / 1000);
    spec.tv_nsec = (millis % 1000) * 1000000;

    int result = 0;

    do {
        Pax_Time_Spec rest = {0};

        result = clock_nanosleep(
            CLOCK_MONOTONIC, 0, &spec, &rest);

        spec = rest;
    } while (result == -1 && errno == EINTR);
}

paxiword
pax_linux_current_thread_ident()
{
    return pax_as(paxiword, pthread_self());
}

#endif // PAX_LINUX_PROCESS_SYSTEM_C
