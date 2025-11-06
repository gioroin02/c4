#ifndef PX_CORE_FORMAT_MESSAGE_C
#define PX_CORE_FORMAT_MESSAGE_C

#include "message.h"

PxFormatMsg
pxFormatMsgString8(PxString8 value)
{
    return (PxFormatMsg) {
        .type  = PX_FORMAT_MSG_STRING_8,
        .radix = PX_FORMAT_RADIX_10,
        .flags = PX_FORMAT_FLAG_NONE,

        .string_8 = value,
    };
}

PxFormatMsg
pxFormatMsgString16(PxString16 value)
{
    return (PxFormatMsg) {
        .type  = PX_FORMAT_MSG_STRING_16,
        .radix = PX_FORMAT_RADIX_10,
        .flags = PX_FORMAT_FLAG_NONE,

        .string_16 = value,
    };
}

PxFormatMsg
pxFormatMsgString32(PxString32 value)
{
    return (PxFormatMsg) {
        .type  = PX_FORMAT_MSG_STRING_32,
        .radix = PX_FORMAT_RADIX_10,
        .flags = PX_FORMAT_FLAG_NONE,

        .string_32 = value,
    };
}

PxFormatMsg
pxFormatMsgUnicode(pxi32 value)
{
    return (PxFormatMsg) {
        .type  = PX_FORMAT_MSG_UNICODE,
        .radix = PX_FORMAT_RADIX_10,
        .flags = PX_FORMAT_FLAG_NONE,

        .unicode = value,
    };
}

PxFormatMsg
pxFormatMsgUnsigned(pxuword value)
{
    return (PxFormatMsg) {
        .type  = PX_FORMAT_MSG_UNSIGNED,
        .radix = PX_FORMAT_RADIX_10,
        .flags = PX_FORMAT_FLAG_NONE,

        .unsigned_word = value,
    };
}

PxFormatMsg
pxFormatMsgInteger(pxiword value)
{
    return (PxFormatMsg) {
        .type  = PX_FORMAT_MSG_INTEGER,
        .radix = PX_FORMAT_RADIX_10,
        .flags = PX_FORMAT_FLAG_NONE,

        .integer_word = value,
    };
}

PxFormatMsg
pxFormatMsgFloating(pxfword value)
{
    return (PxFormatMsg) {
        .type  = PX_FORMAT_MSG_FLOATING,
        .radix = PX_FORMAT_RADIX_10,
        .flags = PX_FORMAT_FLAG_NONE,

        .floating_word = value,
    };
}

PxFormatMsg
pxFormatMsgBoolean(pxbword value)
{
    return (PxFormatMsg) {
        .type  = PX_FORMAT_MSG_BOOLEAN,
        .radix = PX_FORMAT_RADIX_10,
        .flags = PX_FORMAT_FLAG_NONE,

        .boolean_word = value,
    };
}

PxFormatMsg
pxFormatMsgDelegate(void* ctxt, void* proc)
{
    return (PxFormatMsg) {
        .type  = PX_FORMAT_MSG_DELEGATE,
        .radix = PX_FORMAT_RADIX_10,
        .flags = PX_FORMAT_FLAG_NONE,

        .delegate = {
            .ctxt = ctxt,
            .proc = proc,
        },
    };
}

#endif // PX_CORE_FORMAT_MESSAGE_C
