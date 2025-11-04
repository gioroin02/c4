#ifndef PAX_CORE_BASE_NUMBER_H
#define PAX_CORE_BASE_NUMBER_H

#include "./define.h"

typedef char          paxi8;
typedef unsigned char paxu8;
typedef unsigned char paxb8;

#define PAX_I8_SIZE pax_size(paxi8)
#define PAX_I8_MAX  pax_as(paxi8, 0x7f)
#define PAX_I8_MIN  pax_as(paxi8, 0x80)

#define PAX_U8_SIZE pax_size(paxu8)
#define PAX_U8_MAX  pax_as(paxu8, 0xff)
#define PAX_U8_MIN  pax_as(paxu8, 0x00)

#define PAX_B8_SIZE pax_size(paxb8)

typedef short          paxi16;
typedef unsigned short paxu16;
typedef unsigned short paxb16;

#define PAX_I16_SIZE pax_size(paxi16)
#define PAX_I16_MAX  pax_as(paxi16, 0x7fff)
#define PAX_I16_MIN  pax_as(paxi16, 0x8000)

#define PAX_U16_SIZE pax_size(paxu16)
#define PAX_U16_MAX  pax_as(paxu16, 0xffff)
#define PAX_U16_MIN  pax_as(paxu16, 0x0000)

#define PAX_B16_SIZE pax_size(paxb16)

#if PAX_WORD >= PAX_WORD_32

    typedef long          paxi32;
    typedef unsigned long paxu32;
    typedef unsigned long paxb32;
    typedef float         paxf32;

    #define PAX_I32_SIZE pax_size(paxi32)
    #define PAX_I32_MAX  pax_as(paxi32, 0x7fffffff)
    #define PAX_I32_MIN  pax_as(paxi32, 0x80000000)

    #define PAX_U32_SIZE pax_size(paxu32)
    #define PAX_U32_MAX  pax_as(paxu32, 0xffffffff)
    #define PAX_U32_MIN  pax_as(paxu32, 0x00000000)

    #define PAX_B32_SIZE pax_size(paxb32)

    #define PAX_F32_SIZE pax_size(paxf32)

    #define PAX_F32_EXP_MAX  pax_as(paxi16, 127)
    #define PAX_F32_EXP_MIN  pax_as(paxi16, -126)
    #define PAX_F32_EXP_BIAS pax_as(paxi16, 127)
    #define PAX_F32_EXP_SIZE pax_as(paxi32, 8)
    #define PAX_F32_EXP_MASK pax_as(paxu32, 0x7f800000)

    #define PAX_F32_FRAC_SIZE pax_as(paxi32, 23)
    #define PAX_F32_FRAC_MASK pax_as(paxu32, 0x007fffff)

    #define PAX_F32_SIGN_SIZE pax_as(paxi32, 1)
    #define PAX_F32_SIGN_MASK pax_as(paxu32, 0x80000000)

#endif

#if PAX_WORD >= PAX_WORD_64

    typedef long long          paxi64;
    typedef unsigned long long paxu64;
    typedef unsigned long long paxb64;
    typedef double             paxf64;

    #define PAX_I64_SIZE pax_size(paxi64)
    #define PAX_I64_MAX  pax_as(paxi64, 0x7fffffffffffffff)
    #define PAX_I64_MIN  pax_as(paxi64, 0x8000000000000000)

    #define PAX_U64_SIZE pax_size(paxu64)
    #define PAX_U64_MAX  pax_as(paxu64, 0xffffffffffffffff)
    #define PAX_U64_MIN  pax_as(paxu64, 0x0000000000000000)

    #define PAX_B64_SIZE pax_size(paxb64)

    #define PAX_F64_SIZE pax_size(paxf64)

    #define PAX_F64_EXP_MAX  pax_as(paxi32, 1023)
    #define PAX_F64_EXP_MIN  pax_as(paxi32, -1022)
    #define PAX_F64_EXP_BIAS pax_as(paxi32, 1023)
    #define PAX_F64_EXP_SIZE pax_as(paxi64, 11)
    #define PAX_F64_EXP_MASK pax_as(paxu64, 0x7ff0000000000000)

    #define PAX_F64_FRAC_SIZE pax_as(paxi64, 52)
    #define PAX_F64_FRAC_MASK pax_as(paxu64, 0x000fffffffffffff)

    #define PAX_F64_SIGN_SIZE pax_as(paxi64, 1)
    #define PAX_F64_SIGN_MASK pax_as(paxu64, 0x8000000000000000)

#endif

#if PAX_WORD == PAX_WORD_64

    typedef paxi64 paxiword;
    typedef paxu64 paxuword;
    typedef paxb64 paxbword;
    typedef paxf64 paxfword;

    #define PAX_IWORD_SIZE PAX_I64_SIZE
    #define PAX_IWORD_MAX  PAX_I64_MAX
    #define PAX_IWORD_MIN  PAX_I64_MIN

    #define PAX_UWORD_SIZE PAX_U64_SIZE
    #define PAX_UWORD_MAX  PAX_U64_MAX
    #define PAX_UWORD_MIN  PAX_U64_MIN

    #define PAX_BWORD_SIZE PAX_B64_SIZE

    #define PAX_FWORD_SIZE PAX_F64_SIZE

    #define PAX_FWORD_EXP_MAX  PAX_F64_EXP_MAX
    #define PAX_FWORD_EXP_MIN  PAX_F64_EXP_MIN
    #define PAX_FWORD_EXP_BIAS PAX_F64_EXP_BIAS
    #define PAX_FWORD_EXP_SIZE PAX_F64_EXP_SIZE
    #define PAX_FWORD_EXP_MASK PAX_F64_EXP_MASK

    #define PAX_FWORD_FRAC_SIZE PAX_F64_FRAC_SIZE
    #define PAX_FWORD_FRAC_MASK PAX_F64_FRAC_MASK

    #define PAX_FWORD_SIGN_SIZE PAX_F64_SIGN_SIZE
    #define PAX_FWORD_SIGN_MASK PAX_F64_SIGN_MASK

#elif PAX_WORD == PAX_WORD_32

    typedef paxi32 paxiword;
    typedef paxu32 paxuword;
    typedef paxb32 paxbword;
    typedef paxf32 paxfword;

    #define PAX_IWORD_SIZE PAX_I32_SIZE
    #define PAX_IWORD_MAX  PAX_I32_MAX
    #define PAX_IWORD_MIN  PAX_I32_MIN

    #define PAX_UWORD_SIZE PAX_U32_SIZE
    #define PAX_UWORD_MAX  PAX_U32_MAX
    #define PAX_UWORD_MIN  PAX_U32_MIN

    #define PAX_BWORD_SIZE PAX_B32_SIZE

    #define PAX_FWORD_SIZE PAX_F32_SIZE

    #define PAX_FWORD_EXP_MAX  PAX_F32_EXP_MAX
    #define PAX_FWORD_EXP_MIN  PAX_F32_EXP_MIN
    #define PAX_FWORD_EXP_BIAS PAX_F32_EXP_BIAS
    #define PAX_FWORD_EXP_SIZE PAX_F32_EXP_SIZE
    #define PAX_FWORD_EXP_MASK PAX_F32_EXP_MASK

    #define PAX_FWORD_FRAC_SIZE PAX_F32_FRAC_SIZE
    #define PAX_FWORD_FRAC_MASK PAX_F32_FRAC_MASK

    #define PAX_FWORD_SIGN_SIZE PAX_F32_SIGN_SIZE
    #define PAX_FWORD_SIGN_MASK PAX_F32_SIGN_MASK

#else

    #error "Unknown platform"

#endif

/* Integer magnitude */

paxu8
pax_magn_i8(paxi8 value);

paxu16
pax_magn_i16(paxi16 value);

paxu32
pax_magn_i32(paxi32 value);

paxu64
pax_magn_i64(paxi64 value);

paxuword
pax_magn_integer(paxiword value);

/* Floating magnitude */

paxf32
pax_magn_f32(paxf32 value);

paxf64
pax_magn_f64(paxf64 value);

paxfword
pax_magn_floating(paxfword value);

/* Unsigned sign */

paxi8
pax_sign_u8(paxu8 value);

paxi8
pax_sign_u16(paxu16 value);

paxi8
pax_sign_u32(paxu32 value);

paxi8
pax_sign_u64(paxu64 value);

paxi8
pax_sign_unsigned(paxuword value);

/* Integer sign */

paxi8
pax_sign_i8(paxi8 value);

paxi8
pax_sign_i16(paxi16 value);

paxi8
pax_sign_i32(paxi32 value);

paxi8
pax_sign_i64(paxi64 value);

paxi8
pax_sign_integer(paxiword value);

/* Floating sign */

paxi8
pax_sign_f32(paxf32 value);

paxi8
pax_sign_f64(paxf64 value);

paxi8
pax_sign_floating(paxfword value);

#endif // PAX_CORE_BASE_NUMBER_H
