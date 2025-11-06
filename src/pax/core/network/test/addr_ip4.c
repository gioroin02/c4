#include "../export.h"

#include <stdio.h>

#define RED(x) "\x1b[91m" x "\x1b[0m"
#define GRN(x) "\x1b[92m" x "\x1b[0m"
#define YLW(x) "\x1b[93m" x "\x1b[0m"
#define BLU(x) "\x1b[94m" x "\x1b[0m"
#define MAG(x) "\x1b[95m" x "\x1b[0m"
#define CYA(x) "\x1b[96m" x "\x1b[0m"

#define TRUE  GRN("T")
#define FALSE RED("F")

void
showAddrIp4FromString8(PxString8 string)
{
    PxAddrIp4 value = {};
    pxb8      state = pxAddrIp4FromString8(string, &value);

    printf("ip6 (" BLU("'%24s'") ") -> %s, ",
        string.memory, state != 0 ? TRUE : FALSE);

    for (pxiword i = 0; i < PX_ADDR_IP4_GROUPS; i += 1)
        printf("%4u ", value.items[i]);
    printf("\n");
}

int
main()
{
    printf("Valid IPv4:\n");

    showAddrIp4FromString8(pxs8("0.0.0.0"));
    showAddrIp4FromString8(pxs8("000.0.000.0"));
    showAddrIp4FromString8(pxs8("127.0.0.1"));
    showAddrIp4FromString8(pxs8("192.168.1.1"));
    showAddrIp4FromString8(pxs8("10.0.0.255"));
    showAddrIp4FromString8(pxs8("172.16.0.1"));
    showAddrIp4FromString8(pxs8("255.255.255.255"));
    showAddrIp4FromString8(pxs8("8.8.8.8"));
    showAddrIp4FromString8(pxs8("100.64.0.1"));
    showAddrIp4FromString8(pxs8("169.254.1.1"));
    showAddrIp4FromString8(pxs8("198.51.100.42"));
    showAddrIp4FromString8(pxs8("1.2.3.4"));
    showAddrIp4FromString8(pxs8("203.0.113.7"));
    showAddrIp4FromString8(pxs8("128.0.0.1"));
    showAddrIp4FromString8(pxs8("192.0.2.123"));
    showAddrIp4FromString8(pxs8("172.31.255.254"));
    showAddrIp4FromString8(pxs8("10.10.10.10"));
    showAddrIp4FromString8(pxs8("192.168.0.0"));
    showAddrIp4FromString8(pxs8("192.168.001.1"));
    showAddrIp4FromString8(pxs8("192.168.1.01"));
    showAddrIp4FromString8(pxs8("172.20.30.40"));
    showAddrIp4FromString8(pxs8("209.85.231.104"));
    showAddrIp4FromString8(pxs8("240.0.0.1"));

    printf("\nInvalid IPv4:\n");

    showAddrIp4FromString8(pxs8("localhost"));
    showAddrIp4FromString8(pxs8("256.1.2.3"));
    showAddrIp4FromString8(pxs8("1.2.3"));
    showAddrIp4FromString8(pxs8("1.2.3.4.5"));
    showAddrIp4FromString8(pxs8("10.0.0.0.1"));
    showAddrIp4FromString8(pxs8("172.16.1"));
    showAddrIp4FromString8(pxs8("192.168.1.1.1"));
    showAddrIp4FromString8(pxs8("1.2.3.4."));
    showAddrIp4FromString8(pxs8(".1.2.3.4"));
    showAddrIp4FromString8(pxs8("192.168.1.256"));
    showAddrIp4FromString8(pxs8("abc.def.ghi.jkl"));
    showAddrIp4FromString8(pxs8("192.168.1."));
    showAddrIp4FromString8(pxs8("192.168.1.1/24"));
    showAddrIp4FromString8(pxs8("192.168.1.1..2"));
    showAddrIp4FromString8(pxs8("192.168.-1.1"));
    showAddrIp4FromString8(pxs8("192.168.1.1a"));
    showAddrIp4FromString8(pxs8("192.168.1"));
    showAddrIp4FromString8(pxs8("192.168.1.999"));
    showAddrIp4FromString8(pxs8("192.168.1.1.2"));
    showAddrIp4FromString8(pxs8("192.168.1."));
    showAddrIp4FromString8(pxs8("192.168..1.1"));
    showAddrIp4FromString8(pxs8("192.168.1.1:80"));
    showAddrIp4FromString8(pxs8("300.400.500.600"));
    showAddrIp4FromString8(pxs8("192.168.1.1/32"));
}
