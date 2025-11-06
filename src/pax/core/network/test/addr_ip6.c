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
showAddrIp6FromString8(PxString8 string)
{
    PxAddrIp6 value = {};
    pxb8      state = pxAddrIp6FromString8(string, &value);

    printf("ip6 (" BLU("'%48s'") ") -> %s, ",
        string.memory, state != 0 ? TRUE : FALSE);

    for (pxiword i = 0; i < PX_ADDR_IP6_GROUPS; i += 1)
        printf("%4x ", value.items[i]);
    printf("\n");
}

int
main(int argc, char** argv)
{
    printf("Valid IPv6:\n");

    showAddrIp6FromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e:0370:7334"));
    showAddrIp6FromString8(pxs8("fc00::1"));
    showAddrIp6FromString8(pxs8("::1"));
    showAddrIp6FromString8(pxs8("::"));
    showAddrIp6FromString8(pxs8("2001:db8::8a2e:370:7334"));
    showAddrIp6FromString8(pxs8("fe80::1"));
    showAddrIp6FromString8(pxs8("ff02::1"));
    showAddrIp6FromString8(pxs8("2001:0db8:0000:0000:0000:0000:0000:0001"));
    showAddrIp6FromString8(pxs8("2001:db8:0:0:0:0:0:1"));
    showAddrIp6FromString8(pxs8("2001:db8::1"));
    showAddrIp6FromString8(pxs8("3ffe:1900:4545:3:200:f8ff:fe21:67cf"));
    showAddrIp6FromString8(pxs8("2001:db8:1234::5678"));
    showAddrIp6FromString8(pxs8("ff00::"));
    showAddrIp6FromString8(pxs8("2001:0db8:85a3::8a2e:0370:7334"));
    showAddrIp6FromString8(pxs8("2001:db8:0:0:1:0:0:1"));
    showAddrIp6FromString8(pxs8("fe80::200:5eff:fe00:5213"));
    showAddrIp6FromString8(pxs8("2001:db8:abcd:1234:5678:90ab:cdef:1234"));
    showAddrIp6FromString8(pxs8("::ffff:0:0"));

    printf("\nInvalid IPv6:\n");

    showAddrIp6FromString8(pxs8("localhost"));
    showAddrIp6FromString8(pxs8("fe80:0:0:0:200:5efe:192.168.1.1"));
    showAddrIp6FromString8(pxs8("::ffff:192.168.1.1"));
    showAddrIp6FromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e:0370:7334:1"));
    showAddrIp6FromString8(pxs8("2001:0db8::85a3::7334"));
    showAddrIp6FromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e:0370"));
    showAddrIp6FromString8(pxs8("gggg:hhhh:iiii:jjjj:kkkk:llll:mmmm:nnnn"));
    showAddrIp6FromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e:0370:733g"));
    showAddrIp6FromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e:0370:"));
    showAddrIp6FromString8(pxs8(":2001:0db8:85a3:0000:0000:8a2e:0370:7334"));
    showAddrIp6FromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e::7334:1"));
    showAddrIp6FromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e:0370.7334"));
    showAddrIp6FromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e:0370:7334/64"));
    showAddrIp6FromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e:0370:"));
    showAddrIp6FromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e::7334:abcd"));
    showAddrIp6FromString8(pxs8("2001:0db8:::7334"));
    showAddrIp6FromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e:0370:7334:"));
    showAddrIp6FromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e:0370:7334::"));
    showAddrIp6FromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e:0370:FFFFF"));
    showAddrIp6FromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e:0370"));
    showAddrIp6FromString8(pxs8("2001::85a3::"));
    showAddrIp6FromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e:0370:port"));
    showAddrIp6FromString8(pxs8("::ffff:192.168.1.256"));
    showAddrIp6FromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e::-1"));
    showAddrIp6FromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e:0370:7334:5"));
    showAddrIp6FromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e:0370:733.4"));
    showAddrIp6FromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e::7334::"));
    showAddrIp6FromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e:0370:"));
}
