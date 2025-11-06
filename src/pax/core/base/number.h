#ifndef PX_CORE_BASE_NUMBER_H
#define PX_CORE_BASE_NUMBER_H

#include "platform.h"
#include "define.h"

typedef char          pxi8;
typedef unsigned char pxu8;
typedef unsigned char pxb8;

#define PX_I8_SIZE px_size(pxi8)
#define PX_I8_MAX  px_as(pxi8, 0x7f)
#define PX_I8_MIN  px_as(pxi8, 0x80)

#define PX_U8_SIZE px_size(pxu8)
#define PX_U8_MAX  px_as(pxu8, 0xff)
#define PX_U8_MIN  px_as(pxu8, 0x00)

#define PX_B8_SIZE px_size(pxb8)

typedef short          pxi16;
typedef unsigned short pxu16;
typedef unsigned short pxb16;

#define PX_I16_SIZE px_size(pxi16)
#define PX_I16_MAX  px_as(pxi16, 0x7fff)
#define PX_I16_MIN  px_as(pxi16, 0x8000)

#define PX_U16_SIZE px_size(pxu16)
#define PX_U16_MAX  px_as(pxu16, 0xffff)
#define PX_U16_MIN  px_as(pxu16, 0x0000)

#define PX_B16_SIZE px_size(pxb16)

#if PX_WORD >= PX_WORD_32

    typedef long          pxi32;
    typedef unsigned long pxu32;
    typedef unsigned long pxb32;
    typedef float         pxf32;

    #define PX_I32_SIZE px_size(pxi32)
    #define PX_I32_MAX  px_as(pxi32, 0x7fffffff)
    #define PX_I32_MIN  px_as(pxi32, 0x80000000)

    #define PX_U32_SIZE px_size(pxu32)
    #define PX_U32_MAX  px_as(pxu32, 0xffffffff)
    #define PX_U32_MIN  px_as(pxu32, 0x00000000)

    #define PX_B32_SIZE px_size(pxb32)

    #define PX_F32_SIZE px_size(pxf32)

    #define PX_F32_EXP_MAX  px_as(pxi16, 127)
    #define PX_F32_EXP_MIN  px_as(pxi16, -126)
    #define PX_F32_EXP_BIAS px_as(pxi16, 127)
    #define PX_F32_EXP_SIZE px_as(pxi32, 8)
    #define PX_F32_EXP_MASK px_as(pxu32, 0x7f800000)

    #define PX_F32_FRAC_SIZE px_as(pxi32, 23)
    #define PX_F32_FRAC_MASK px_as(pxu32, 0x007fffff)

    #define PX_F32_SIGN_SIZE px_as(pxi32, 1)
    #define PX_F32_SIGN_MASK px_as(pxu32, 0x80000000)

#endif

#if PX_WORD >= PX_WORD_64

    typedef long long          pxi64;
    typedef unsigned long long pxu64;
    typedef unsigned long long pxb64;
    typedef double             pxf64;

    #define PX_I64_SIZE px_size(pxi64)
    #define PX_I64_MAX  px_as(pxi64, 0x7fffffffffffffff)
    #define PX_I64_MIN  px_as(pxi64, 0x8000000000000000)

    #define PX_U64_SIZE px_size(pxu64)
    #define PX_U64_MAX  px_as(pxu64, 0xffffffffffffffff)
    #define PX_U64_MIN  px_as(pxu64, 0x0000000000000000)

    #define PX_B64_SIZE px_size(pxb64)

    #define PX_F64_SIZE px_size(pxf64)

    #define PX_F64_EXP_MAX  px_as(pxi32, 1023)
    #define PX_F64_EXP_MIN  px_as(pxi32, -1022)
    #define PX_F64_EXP_BIAS px_as(pxi32, 1023)
    #define PX_F64_EXP_SIZE px_as(pxi64, 11)
    #define PX_F64_EXP_MASK px_as(pxu64, 0x7ff0000000000000)

    #define PX_F64_FRAC_SIZE px_as(pxi64, 52)
    #define PX_F64_FRAC_MASK px_as(pxu64, 0x000fffffffffffff)

    #define PX_F64_SIGN_SIZE px_as(pxi64, 1)
    #define PX_F64_SIGN_MASK px_as(pxu64, 0x8000000000000000)

#endif

#if PX_WORD == PX_WORD_64

    typedef pxi64 pxiword;
    typedef pxu64 pxuword;
    typedef pxb64 pxbword;
    typedef pxf64 pxfword;

    #define PX_IWORD_SIZE PX_I64_SIZE
    #define PX_IWORD_MAX  PX_I64_MAX
    #define PX_IWORD_MIN  PX_I64_MIN

    #define PX_UWORD_SIZE PX_U64_SIZE
    #define PX_UWORD_MAX  PX_U64_MAX
    #define PX_UWORD_MIN  PX_U64_MIN

    #define PX_BWORD_SIZE PX_B64_SIZE

    #define PX_FWORD_SIZE PX_F64_SIZE

    #define PX_FWORD_EXP_MAX  PX_F64_EXP_MAX
    #define PX_FWORD_EXP_MIN  PX_F64_EXP_MIN
    #define PX_FWORD_EXP_BIAS PX_F64_EXP_BIAS
    #define PX_FWORD_EXP_SIZE PX_F64_EXP_SIZE
    #define PX_FWORD_EXP_MASK PX_F64_EXP_MASK

    #define PX_FWORD_FRAC_SIZE PX_F64_FRAC_SIZE
    #define PX_FWORD_FRAC_MASK PX_F64_FRAC_MASK

    #define PX_FWORD_SIGN_SIZE PX_F64_SIGN_SIZE
    #define PX_FWORD_SIGN_MASK PX_F64_SIGN_MASK

#elif PX_WORD == PX_WORD_32

    typedef pxi32 pxiword;
    typedef pxu32 pxuword;
    typedef pxb32 pxbword;
    typedef pxf32 pxfword;

    #define PX_IWORD_SIZE PX_I32_SIZE
    #define PX_IWORD_MAX  PX_I32_MAX
    #define PX_IWORD_MIN  PX_I32_MIN

    #define PX_UWORD_SIZE PX_U32_SIZE
    #define PX_UWORD_MAX  PX_U32_MAX
    #define PX_UWORD_MIN  PX_U32_MIN

    #define PX_BWORD_SIZE PX_B32_SIZE

    #define PX_FWORD_SIZE PX_F32_SIZE

    #define PX_FWORD_EXP_MAX  PX_F32_EXP_MAX
    #define PX_FWORD_EXP_MIN  PX_F32_EXP_MIN
    #define PX_FWORD_EXP_BIAS PX_F32_EXP_BIAS
    #define PX_FWORD_EXP_SIZE PX_F32_EXP_SIZE
    #define PX_FWORD_EXP_MASK PX_F32_EXP_MASK

    #define PX_FWORD_FRAC_SIZE PX_F32_FRAC_SIZE
    #define PX_FWORD_FRAC_MASK PX_F32_FRAC_MASK

    #define PX_FWORD_SIGN_SIZE PX_F32_SIGN_SIZE
    #define PX_FWORD_SIGN_MASK PX_F32_SIGN_MASK

#else

    #error "Unknown platform"

#endif

/* Integer magnitude */

pxu8
pxMagnitudeInteger8(pxi8 value);

pxu16
pxMagnitudeInteger16(pxi16 value);

pxu32
pxMagnitudeInteger32(pxi32 value);

pxu64
pxMagnitudeInteger64(pxi64 value);

pxuword
pxMagnitudeInteger(pxiword value);

/* Floating magnitude */

pxf32
pxMagnitudeFloating32(pxf32 value);

pxf64
pxMagnitudeFloating64(pxf64 value);

pxfword
pxMagnitudeFloating(pxfword value);

/* Unsigned direction */

pxi8
pxDirectionUnsigned8(pxu8 value);

pxi8
pxDirectionUnsigned16(pxu16 value);

pxi8
pxDirectionUnsigned32(pxu32 value);

pxi8
pxDirectionUnsigned64(pxu64 value);

pxi8
pxDirectionUnsigned(pxuword value);

/* Integer direction */

pxi8
pxDirectionInteger8(pxi8 value);

pxi8
pxDirectionInteger16(pxi16 value);

pxi8
pxDirectionInteger32(pxi32 value);

pxi8
pxDirectionInteger64(pxi64 value);

pxi8
pxDirectionInteger(pxiword value);

/* Floating sign */

pxi8
pxDirectionFloating32(pxf32 value);

pxi8
pxDirectionFloating64(pxf64 value);

pxi8
pxDirectionFloating(pxfword value);

#endif // PX_CORE_BASE_NUMBER_H
