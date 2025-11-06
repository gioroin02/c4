#ifndef PX_CORE_BASE_DEFINE_H
#define PX_CORE_BASE_DEFINE_H

#define px_as(t, x) ((t)(x))

#define px_array_from_vargs(t, ...) (t[]) {__VA_ARGS__}

#define px_size(x)          px_as(pxiword, sizeof(x))
#define px_size_array(t, x) px_as(pxiword, sizeof(x) / sizeof(t))

#define px_size_vargs(t, ...) px_size_array(t, px_array_from_vargs(t, __VA_ARGS__))

#define px_min(x, y) ((x) < (y) ? (x) : (y))
#define px_max(x, y) ((x) < (y) ? (y) : (x))

#define px_between(x, l, r) px_max(l, px_min(x, r))

#endif // PX_CORE_BASE_DEFINE_H
