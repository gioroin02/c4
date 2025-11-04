#ifndef PAX_WIN32_NETWORK_SYSTEM_C
#define PAX_WIN32_NETWORK_SYSTEM_C

#include "./system.h"

#define NOMINMAX
#define NOGDI
#define WIN32_MEAN_AND_LEAN

#include <winsock2.h>

paxb8
pax_win32_network_load()
{
    WSADATA data = {0};

    if (WSAStartup(MAKEWORD(2, 2), &data) != 0)
        return 0;

    return 1;
}

void
pax_win32_network_unload()
{
    WSACleanup();
}

#endif // PAX_WIN32_NETWORK_SYSTEM_C
