#ifndef PX_CORE_BASE_DEFINE_H
#define PX_CORE_BASE_DEFINE_H

#define __pxString__(x) # x
#define pxString(x)     __pxString__(x)

#define __pxConcat__(x, y) x ## y
#define pxConcat(x, y)    __pxConcat__(x, y)

#define pxArray(t, x)   (t[]) {x}
#define pxVargs(t, ...) (t[]) {__VA_ARGS__}

#define pxCast(t, x) ((t)(x))

#define pxSize(x) pxCast(pxiword, sizeof(x))

#define pxSizeArray(t, x) \
    pxCast(pxiword, sizeof(x) / sizeof(t))

#define pxSizeItems(t, x) \
    pxCast(pxiword, sizeof(pxArray(t, x)) / sizeof(t))

#define pxSizeVargs(t, ...) \
    pxCast(pxiword, sizeof(pxVargs(t, __VA_ARGS__)) / sizeof(t))

#define pxMin(x, y) ((x) < (y) ? (x) : (y))
#define pxMax(x, y) ((x) < (y) ? (y) : (x))

#define pxClamp(x, l, r) pxMax(l, pxMin(x, r))

#endif // PX_CORE_BASE_DEFINE_H
