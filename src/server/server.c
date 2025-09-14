#ifndef C4_SERVER_C
#define C4_SERVER_C

#include "server.h"

C4Server
c4ServerMake(PxArena* arena, pxiword length, PxAddressType type)
{
    C4Server result = {0};

    if (length <= 0) return result;

    result.sessions =
        pxArrayReserve(arena, C4Session*, length);

    if (result.sessions.length > 0)
        result.socket = pxSocketTcpCreate(arena, type);

    return result;
}

pxb8
c4ServerStart(C4Server* self, PxAddress address, pxu16 port)
{
    pxLoggerTrace(LOGGER, "Attivazione porta ${0} ...\n",
        pxFormatCmdUnsigned16(10, PX_FORMAT_OPTION_NONE, port));

    pxb8 state = pxSocketTcpBind(self->socket, address, port);

    if (state != 0) {
        pxLoggerTrace(LOGGER, "Ascolto porta ...\n", {0});

        state = pxSocketTcpListen(self->socket);
    }

    if (state != 0)
        pxLoggerInfo(LOGGER, "Attivazione porta riuscita\n", {0});
    else
        pxLoggerError(LOGGER, "Attivazione porta fallita\n", {0});

    return state;
}

void
c4ServerStop(C4Server* self)
{
    if (self == 0) return;

    for (pxiword i = 0; i < self->sessions.size; i += 1) {
        C4Session* session = 0;

        pxArrayRead(&self->sessions, i,
            C4Session*, &session);

        c4SessionClose(self, session);
    }

    pxSocketTcpDestroy(self->socket);

    self->socket = 0;
}

void
c4ServerBroadcast(C4Server* self, PxArena* arena, C4Session* from, C4Msg value)
{
    for (pxiword i = 0; i < self->sessions.size; i += 1) {
        C4Session* session = 0;

        pxArrayRead(&self->sessions, i,
            C4Session*, &session);

        if (session == from) continue;

        c4SessionWrite(session, arena, value);
    }
}

pxiword
c4ServerFind(C4Server* self, C4Session* value)
{
    for (pxiword i = 0; i < self->sessions.size; i += 1) {
        C4Session* session = 0;

        pxArrayRead(&self->sessions, i,
            C4Session*, &session);

        if (session == value) return i + 1;
    }

    return 0;
}

pxb8
c4ServerGet(C4Server* self, pxiword index, C4Session** value)
{
    return pxArrayRead(&self->sessions, index, C4Session*, value);
}

C4Session*
c4ServerGetOr(C4Server* self, pxiword index, C4Session* value)
{
    C4Session* result = 0;

    if (pxArrayRead(&self->sessions, index, C4Session*, &result) == 0)
        return value;

    return result;
}

C4Session*
c4SessionOpen(C4Server* self, PxArena* arena)
{
    pxLoggerTrace(LOGGER, "Apertura sessione ...\n", {0});

    pxiword size   = self->sessions.size;
    pxiword length = self->sessions.length;
    pxiword offset = pxArenaOffset(arena);

    if (size < 0 || size >= length) return 0;

    C4Session* result = pxArenaReserve(arena, C4Session, 1);

    if (result == 0) return 0;

    result->socket = pxSocketTcpAccept(self->socket, arena);

    if (result->socket != 0) {
        pxArrayInsertTail(&self->sessions, C4Session*, &result);

        PxAddress address = pxSocketTcpGetAddress(result->socket);
        pxu16     port    = pxSocketTcpGetPort(result->socket);

        switch (address.type) {
            case PX_ADDRESS_TYPE_IP4: {
                pxu8 format[] = "Aperta sessione con {addr = [${0}.${1}.${2}.${3}], port = ${4}} ...\n";

                pxLoggerInfo(LOGGER, format,
                    pxFormatCmdUnsigned8(10, PX_FORMAT_OPTION_NONE, address.ip4.a),
                    pxFormatCmdUnsigned8(10, PX_FORMAT_OPTION_NONE, address.ip4.b),
                    pxFormatCmdUnsigned8(10, PX_FORMAT_OPTION_NONE, address.ip4.c),
                    pxFormatCmdUnsigned8(10, PX_FORMAT_OPTION_NONE, address.ip4.d),
                    pxFormatCmdUnsigned16(10, PX_FORMAT_OPTION_NONE, port));
            } break;

            case PX_ADDRESS_TYPE_IP6: {
                pxu8 format[] =
                    "Aperta sessione con {addr = [${0}:${1}:${2}:${3}:${4}:${5}:${6}:${7}], port = ${8}} ...\n";

                pxLoggerInfo(LOGGER, format,
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

        return result;
    }

    pxLoggerError(LOGGER, "Apertura sessione fallita\n", {0});

    pxArenaRewind(arena, offset);

    return 0;
}

pxb8
c4SessionClose(C4Server* self, C4Session* session)
{
    pxiword index = c4ServerFind(self, session);
    pxb8    state = 0;

    if (index == 0) return 0;

    state = pxArrayRemove(&self->sessions,
        index - 1, C4Session*, &session);

    if (state != 0)
        pxSocketTcpDestroy(session->socket);

    return state;
}

pxb8
c4SessionWrite(C4Session* self, PxArena* arena, C4Msg value)
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
c4SessionRead(C4Session* self, PxArena* arena)
{
    pxLoggerTrace(LOGGER, "Attesa di un messaggio ...\n", {0});

    C4Msg result = {0};
    pxiword   offset = pxArenaOffset(arena);

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

#endif // C4_SERVER_C
