#ifndef __XOROSHIRO128PLUS_H__
#define __XOROSHIRO128PLUS_H__

#include <stdint.h>

#define _xrshr128p_rotl(x, k) (((x) << (k)) | ((x) >> (64 - (k))))

#define splitmix64(x)                                       \
    ({                                                      \
        size_t z = (x += UINT64_C(0x9E3779B97F4A7C15));     \
        z = (z ^ (z >> 30)) * UINT64_C(0xBF58476D1CE4E5B9); \
        z = (z ^ (z >> 27)) * UINT64_C(0x94D049BB133111EB); \
        z ^ (z >> 31);                                      \
    })

typedef struct xrshr128p_state
{
    size_t s[2];
} xrshr128p_state_t;

#define xrshr128p_init(_seed)                \
    ({                                       \
        uint64_t __seed = (uint64_t)(_seed); \
        xrshr128p_state_t __state;           \
        __state.s[0] = (__seed);             \
        __state.s[1] = splitmix64(__seed);   \
        __state;                             \
    })

/* size_t in range [0, 2^64-1] */
#define xrshr128p_next(_state)                                           \
    ({                                                                   \
        const size_t __s0 = (_state).s[0];                               \
        size_t __s1 = (_state).s[1];                                     \
        const size_t result = __s0 + __s1;                               \
        __s1 ^= __s0;                                                    \
        (_state).s[0] = _xrshr128p_rotl(__s0, 55) ^ __s1 ^ (__s1 << 14); \
        (_state).s[1] = _xrshr128p_rotl(__s1, 36);                       \
        result;                                                          \
    })

/* double in range [0,1) */
#define xrshr128p_next_double(_state)                     \
    ({                                                    \
        const size_t __x = xrshr128p_next(_state);        \
        const union                                       \
        {                                                 \
            size_t i;                                     \
            double d;                                     \
        } __u = {.i = UINT64_C(0x3FF) << 52 | __x >> 12}; \
        __u.d - 1.0;                                      \
    })

#endif
