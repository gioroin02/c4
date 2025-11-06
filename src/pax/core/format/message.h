#ifndef PX_CORE_FORMAT_MESSAGE_H
#define PX_CORE_FORMAT_MESSAGE_H

#include "config.h"

typedef enum PxFormatMsgType
{
    PX_FORMAT_MSG_NONE,

    PX_FORMAT_MSG_STRING_8,
    PX_FORMAT_MSG_STRING_16,
    PX_FORMAT_MSG_STRING_32,

    PX_FORMAT_MSG_UNICODE,

    PX_FORMAT_MSG_UNSIGNED,
    PX_FORMAT_MSG_INTEGER,
    PX_FORMAT_MSG_FLOATING,
    PX_FORMAT_MSG_BOOLEAN,

    PX_FORMAT_MSG_DELEGATE,
}
PxFormatMsgType;

typedef struct PxFormatMsgDelegate
{
    void* ctxt;
    void* proc;
}
PxFormatMsgDelegate;

typedef struct PxFormatMsg
{
    PxFormatMsgType type;

    PxFormatRadix radix;
    PxFormatFlag  flags;

    union
    {
        PxString8  string_8;
        PxString16 string_16;
        PxString32 string_32;

        pxi32 unicode;

        pxuword unsigned_word;
        pxiword integer_word;
        pxfword floating_word;
        pxbword boolean_word;

        PxFormatMsgDelegate delegate;
    };
}
PxFormatMsg;

PxFormatMsg
pxFormatMsgString8(PxString8 value);

PxFormatMsg
pxFormatMsgString16(PxString16 value);

PxFormatMsg
pxFormatMsgString32(PxString32 value);

PxFormatMsg
pxFormatMsgUnicode(pxi32 value);

PxFormatMsg
pxFormatMsgUnsigned(pxuword value);

PxFormatMsg
pxFormatMsgInteger(pxiword value);

PxFormatMsg
pxFormatMsgFloating(pxfword value);

PxFormatMsg
pxFormatMsgBoolean(pxbword value);

PxFormatMsg
pxFormatMsgDelegate(void* ctxt, void* proc);

#endif // PX_CORE_FORMAT_MESSAGE_H
