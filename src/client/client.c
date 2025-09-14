#ifndef C4_CLIENT_C
#define C4_CLIENT_C

#include "client.h"

C4Client
c4ClientMake(PxArena* arena, pxiword length, PxAddressType type)
{
    C4Client result = {0};

    result.socket = pxSocketTcpCreate(arena, type);

    if (result.socket != 0) {
        result.reader = pxSocketTcpReader(result.socket, arena, length);
        result.writer = pxSocketTcpWriter(result.socket, arena, length);
    }

    return result;
}

pxb8
c4ClientStart(C4Client* self, PxAddress address, pxu16 port)
{
    switch (address.type) {
        case PX_ADDRESS_TYPE_IP4: {
            pxu8 format[] = "Apertura sessione con {addr = [${0}.${1}.${2}.${3}], port = ${4}} ...\n";

            pxLoggerTrace(LOGGER, format,
                pxFormatCmdUnsigned8(10, PX_FORMAT_OPTION_NONE, address.ip4.a),
                pxFormatCmdUnsigned8(10, PX_FORMAT_OPTION_NONE, address.ip4.b),
                pxFormatCmdUnsigned8(10, PX_FORMAT_OPTION_NONE, address.ip4.c),
                pxFormatCmdUnsigned8(10, PX_FORMAT_OPTION_NONE, address.ip4.d),
                pxFormatCmdUnsigned16(10, PX_FORMAT_OPTION_NONE, port));
        } break;

        case PX_ADDRESS_TYPE_IP6: {
            pxu8 format[] =
                "Apertura sessione con {addr = [${0}:${1}:${2}:${3}:${4}:${5}:${6}:${7}], port = ${8}} ...\n";

            pxLoggerTrace(LOGGER, format,
                pxFormatCmdUnsigned16(10, PX_FORMAT_OPTION_NONE, address.ip6.a),
                pxFormatCmdUnsigned16(10, PX_FORMAT_OPTION_NONE, address.ip6.b),
                pxFormatCmdUnsigned16(10, PX_FORMAT_OPTION_NONE, address.ip6.c),
                pxFormatCmdUnsigned16(10, PX_FORMAT_OPTION_NONE, address.ip6.d),
                pxFormatCmdUnsigned16(10, PX_FORMAT_OPTION_NONE, address.ip6.e),
                pxFormatCmdUnsigned16(10, PX_FORMAT_OPTION_NONE, address.ip6.f),
                pxFormatCmdUnsigned16(10, PX_FORMAT_OPTION_NONE, address.ip6.g),
                pxFormatCmdUnsigned16(10, PX_FORMAT_OPTION_NONE, address.ip6.h),
                pxFormatCmdUnsigned16(10, PX_FORMAT_OPTION_NONE, port));
        } break;

        default: break;
    }

    pxb8 state = pxSocketTcpConnect(self->socket, address, port);

    if (state != 0)
        pxLoggerInfo(LOGGER, "Apertura sessione riuscita\n", {0});
    else
        pxLoggerError(LOGGER, "Apertura sessione fallita\n", {0});

    return state;
}

void
c4ClientStop(C4Client* self)
{
    if (self == 0) return;

    pxSocketTcpDestroy(self->socket);

    self->socket = 0;
}

pxb8
c4ClientWrite(C4Client* self, PxArena* arena, C4Msg value)
{
    pxLoggerTrace(LOGGER, "Scrittura di ${0}\n",
        pxFormatCmdDelegate(&value, &c4FormatProcMsg));

    pxiword offset = pxArenaOffset(arena);

    PxJsonWriter writer =
        pxJsonWriterMake(arena, 4, &self->writer);

    pxb8 state = c4JsonWriteMsg(&value, &writer, arena);

    pxArenaRewind(arena, offset);

    if (state != 0)
        pxLoggerInfo(LOGGER, "Scrittura riuscita\n", {0});
    else
        pxLoggerError(LOGGER, "Scrittura fallita\n", {0});

    return state;
}

C4Msg
c4ClientRead(C4Client* self, PxArena* arena)
{
    pxLoggerTrace(LOGGER, "Attesa di un messaggio ...\n", {0});

    C4Msg   result = {0};
    pxiword offset = pxArenaOffset(arena);

    PxJsonReader reader =
        pxJsonReaderMake(arena, 4, &self->reader);

    pxb8 state = c4JsonReadMsg(&result, &reader, arena);

    pxLoggerTrace(LOGGER, "Lettura di ${0}\n",
        pxFormatCmdDelegate(&result, &c4FormatProcMsg));

    pxArenaRewind(arena, offset);

    if (state != 0)
        pxLoggerInfo(LOGGER, "Lettura riuscita\n", {0});
    else
        pxLoggerError(LOGGER, "Lettura fallita\n", {0});

    return result;
}

#endif // C4_CLIENT_C
