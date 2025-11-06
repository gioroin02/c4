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
showAddrFromString8(PxString8 string, PxAddrType type)
{
    PxAddr value = {};

    pxMemoryZero(&value, 1, px_size(PxAddr));

    pxb8 state = pxAddrFromString8(string, &value, type);

    switch (type) {
        case PX_ADDR_TYPE_IP4: {
            printf("ip4 (" BLU("'%24s'") ") -> %s, ",
                string.memory, state ? TRUE : FALSE);

            for (pxiword i = 0; i < PX_ADDR_IP4_GROUPS; i += 1)
                printf("%4u ", value.ip4.items[i]);
            printf("\n");
        } break;

        case PX_ADDR_TYPE_IP6: {
            printf("ip6 (" BLU("'%48s'") ") -> %s, ",
                string.memory, state ? TRUE : FALSE);

            for (pxiword i = 0; i < PX_ADDR_IP6_GROUPS; i += 1)
                printf("%4x ", value.ip6.items[i]);
            printf("\n");
        } break;

        default: break;
    }
}

int
main()
{
    printf("Valid IPv4:\n");

    showAddrFromString8(pxs8("0.0.0.0"), PX_ADDR_TYPE_IP4);
    showAddrFromString8(pxs8("000.0.000.0"), PX_ADDR_TYPE_IP4);
    showAddrFromString8(pxs8("127.0.0.1"), PX_ADDR_TYPE_IP4);
    showAddrFromString8(pxs8("192.168.1.1"), PX_ADDR_TYPE_IP4);
    showAddrFromString8(pxs8("10.0.0.255"), PX_ADDR_TYPE_IP4);
    showAddrFromString8(pxs8("172.16.0.1"), PX_ADDR_TYPE_IP4);
    showAddrFromString8(pxs8("255.255.255.255"), PX_ADDR_TYPE_IP4);
    showAddrFromString8(pxs8("8.8.8.8"), PX_ADDR_TYPE_IP4);
    showAddrFromString8(pxs8("100.64.0.1"), PX_ADDR_TYPE_IP4);
    showAddrFromString8(pxs8("169.254.1.1"), PX_ADDR_TYPE_IP4);
    showAddrFromString8(pxs8("198.51.100.42"), PX_ADDR_TYPE_IP4);
    showAddrFromString8(pxs8("1.2.3.4"), PX_ADDR_TYPE_IP4);
    showAddrFromString8(pxs8("203.0.113.7"), PX_ADDR_TYPE_IP4);
    showAddrFromString8(pxs8("128.0.0.1"), PX_ADDR_TYPE_IP4);
    showAddrFromString8(pxs8("192.0.2.123"), PX_ADDR_TYPE_IP4);
    showAddrFromString8(pxs8("172.31.255.254"), PX_ADDR_TYPE_IP4);
    showAddrFromString8(pxs8("10.10.10.10"), PX_ADDR_TYPE_IP4);
    showAddrFromString8(pxs8("192.168.0.0"), PX_ADDR_TYPE_IP4);
    showAddrFromString8(pxs8("192.168.001.1"), PX_ADDR_TYPE_IP4);
    showAddrFromString8(pxs8("192.168.1.01"), PX_ADDR_TYPE_IP4);
    showAddrFromString8(pxs8("172.20.30.40"), PX_ADDR_TYPE_IP4);
    showAddrFromString8(pxs8("209.85.231.104"), PX_ADDR_TYPE_IP4);
    showAddrFromString8(pxs8("240.0.0.1"), PX_ADDR_TYPE_IP4);

    printf("\nInvalid IPv4:\n");

    showAddrFromString8(pxs8("localhost"), PX_ADDR_TYPE_IP4);
    showAddrFromString8(pxs8("256.1.2.3"), PX_ADDR_TYPE_IP4);
    showAddrFromString8(pxs8("1.2.3"), PX_ADDR_TYPE_IP4);
    showAddrFromString8(pxs8("1.2.3.4.5"), PX_ADDR_TYPE_IP4);
    showAddrFromString8(pxs8("10.0.0.0.1"), PX_ADDR_TYPE_IP4);
    showAddrFromString8(pxs8("172.16.1"), PX_ADDR_TYPE_IP4);
    showAddrFromString8(pxs8("192.168.1.1.1"), PX_ADDR_TYPE_IP4);
    showAddrFromString8(pxs8("1.2.3.4."), PX_ADDR_TYPE_IP4);
    showAddrFromString8(pxs8(".1.2.3.4"), PX_ADDR_TYPE_IP4);
    showAddrFromString8(pxs8("192.168.1.256"), PX_ADDR_TYPE_IP4);
    showAddrFromString8(pxs8("abc.def.ghi.jkl"), PX_ADDR_TYPE_IP4);
    showAddrFromString8(pxs8("192.168.1."), PX_ADDR_TYPE_IP4);
    showAddrFromString8(pxs8("192.168.1.1/24"), PX_ADDR_TYPE_IP4);
    showAddrFromString8(pxs8("192.168.1.1..2"), PX_ADDR_TYPE_IP4);
    showAddrFromString8(pxs8("192.168.-1.1"), PX_ADDR_TYPE_IP4);
    showAddrFromString8(pxs8("192.168.1.1a"), PX_ADDR_TYPE_IP4);
    showAddrFromString8(pxs8("192.168.1"), PX_ADDR_TYPE_IP4);
    showAddrFromString8(pxs8("192.168.1.999"), PX_ADDR_TYPE_IP4);
    showAddrFromString8(pxs8("192.168.1.1.2"), PX_ADDR_TYPE_IP4);
    showAddrFromString8(pxs8("192.168.1."), PX_ADDR_TYPE_IP4);
    showAddrFromString8(pxs8("192.168..1.1"), PX_ADDR_TYPE_IP4);
    showAddrFromString8(pxs8("192.168.1.1:80"), PX_ADDR_TYPE_IP4);
    showAddrFromString8(pxs8("300.400.500.600"), PX_ADDR_TYPE_IP4);
    showAddrFromString8(pxs8("192.168.1.1/32"), PX_ADDR_TYPE_IP4);

    printf("\nValid IPv6:\n");

    showAddrFromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e:0370:7334"), PX_ADDR_TYPE_IP6);
    showAddrFromString8(pxs8("fc00::1"), PX_ADDR_TYPE_IP6);
    showAddrFromString8(pxs8("::1"), PX_ADDR_TYPE_IP6);
    showAddrFromString8(pxs8("::"), PX_ADDR_TYPE_IP6);
    showAddrFromString8(pxs8("2001:db8::8a2e:370:7334"), PX_ADDR_TYPE_IP6);
    showAddrFromString8(pxs8("fe80::1"), PX_ADDR_TYPE_IP6);
    showAddrFromString8(pxs8("ff02::1"), PX_ADDR_TYPE_IP6);
    showAddrFromString8(pxs8("2001:0db8:0000:0000:0000:0000:0000:0001"), PX_ADDR_TYPE_IP6);
    showAddrFromString8(pxs8("2001:db8:0:0:0:0:0:1"), PX_ADDR_TYPE_IP6);
    showAddrFromString8(pxs8("2001:db8::1"), PX_ADDR_TYPE_IP6);
    showAddrFromString8(pxs8("3ffe:1900:4545:3:200:f8ff:fe21:67cf"), PX_ADDR_TYPE_IP6);
    showAddrFromString8(pxs8("2001:db8:1234::5678"), PX_ADDR_TYPE_IP6);
    showAddrFromString8(pxs8("ff00::"), PX_ADDR_TYPE_IP6);
    showAddrFromString8(pxs8("2001:0db8:85a3::8a2e:0370:7334"), PX_ADDR_TYPE_IP6);
    showAddrFromString8(pxs8("2001:db8:0:0:1:0:0:1"), PX_ADDR_TYPE_IP6);
    showAddrFromString8(pxs8("fe80::200:5eff:fe00:5213"), PX_ADDR_TYPE_IP6);
    showAddrFromString8(pxs8("2001:db8:abcd:1234:5678:90ab:cdef:1234"), PX_ADDR_TYPE_IP6);
    showAddrFromString8(pxs8("::ffff:0:0"), PX_ADDR_TYPE_IP6);

    printf("\nInvalid IPv6:\n");

    showAddrFromString8(pxs8("localhost"), PX_ADDR_TYPE_IP6);
    showAddrFromString8(pxs8("fe80:0:0:0:200:5efe:192.168.1.1"), PX_ADDR_TYPE_IP6);
    showAddrFromString8(pxs8("::ffff:192.168.1.1"), PX_ADDR_TYPE_IP6);
    showAddrFromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e:0370:7334:1"), PX_ADDR_TYPE_IP6);
    showAddrFromString8(pxs8("2001:0db8::85a3::7334"), PX_ADDR_TYPE_IP6);
    showAddrFromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e:0370"), PX_ADDR_TYPE_IP6);
    showAddrFromString8(pxs8("gggg:hhhh:iiii:jjjj:kkkk:llll:mmmm:nnnn"), PX_ADDR_TYPE_IP6);
    showAddrFromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e:0370:733g"), PX_ADDR_TYPE_IP6);
    showAddrFromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e:0370:"), PX_ADDR_TYPE_IP6);
    showAddrFromString8(pxs8(":2001:0db8:85a3:0000:0000:8a2e:0370:7334"), PX_ADDR_TYPE_IP6);
    showAddrFromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e::7334:1"), PX_ADDR_TYPE_IP6);
    showAddrFromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e:0370.7334"), PX_ADDR_TYPE_IP6);
    showAddrFromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e:0370:7334/64"), PX_ADDR_TYPE_IP6);
    showAddrFromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e:0370:"), PX_ADDR_TYPE_IP6);
    showAddrFromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e::7334:abcd"), PX_ADDR_TYPE_IP6);
    showAddrFromString8(pxs8("2001:0db8:::7334"), PX_ADDR_TYPE_IP6);
    showAddrFromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e:0370:7334:"), PX_ADDR_TYPE_IP6);
    showAddrFromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e:0370:7334::"), PX_ADDR_TYPE_IP6);
    showAddrFromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e:0370:FFFFF"), PX_ADDR_TYPE_IP6);
    showAddrFromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e:0370"), PX_ADDR_TYPE_IP6);
    showAddrFromString8(pxs8("2001::85a3::"), PX_ADDR_TYPE_IP6);
    showAddrFromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e:0370:port"), PX_ADDR_TYPE_IP6);
    showAddrFromString8(pxs8("::ffff:192.168.1.256"), PX_ADDR_TYPE_IP6);
    showAddrFromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e::-1"), PX_ADDR_TYPE_IP6);
    showAddrFromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e:0370:7334:5"), PX_ADDR_TYPE_IP6);
    showAddrFromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e:0370:733.4"), PX_ADDR_TYPE_IP6);
    showAddrFromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e::7334::"), PX_ADDR_TYPE_IP6);
    showAddrFromString8(pxs8("2001:0db8:85a3:0000:0000:8a2e:0370:"), PX_ADDR_TYPE_IP6);
}
