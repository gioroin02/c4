#ifndef PAX_CORE_BASE_DEFINE_H
#define PAX_CORE_BASE_DEFINE_H

#include "./platform.h"

#define pax_as(t, x) ((t)(x))

#define pax_block_from_vargs(t, ...) (t[]) {__VA_ARGS__}

#define pax_size(x)          pax_as(paxiword, sizeof(x))
#define pax_size_block(t, x) pax_as(paxiword, sizeof(x) / sizeof(t))

#define pax_size_vargs(t, ...) \
    pax_size_block(t, pax_block_from_vargs(t, __VA_ARGS__))

#define pax_min(x, y) ((x) < (y) ? (x) : (y))
#define pax_max(x, y) ((x) < (y) ? (y) : (x))

#define pax_between(x, l, r) pax_max(l, pax_min(x, r))

#endif // PAX_CORE_BASE_DEFINE_H
