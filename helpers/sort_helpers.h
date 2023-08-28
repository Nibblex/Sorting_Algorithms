#ifndef _SORT_HELPERS_H
#define _SORT_HELPERS_H

#include <stdlib.h>

#include "../algorithms/xoroshiro128plus.h"

#include "counter.h"

#define MAX_THRESH 8

#define U32_MAX ((size_t)-1)

struct counter counters;

#define _cmp(a, b)                                       \
    ({                                                   \
        counters.cmp_counter++;                          \
        int _a = (a), _b = (b);                          \
        abs(_a)<abs(_b) ? -1 : abs(_a)> abs(_b) ? 1 : 0; \
    })

#define _min(a, b) (_cmp(a, b) < 0 ? (a) : (b))

#define _max(a, b) (_cmp(a, b) > 0 ? (a) : (b))

#define swap(a, i, j)              \
    ({                             \
        counters.swap_counter++;   \
        size_t _i = (i), _j = (j); \
        int tmp = a[_i];           \
        a[_i] = a[_j];             \
        a[_j] = tmp;               \
        _i;                        \
    })

#define med3(arr, i, j, k)                                                                                                              \
    ({                                                                                                                                  \
        int _i = arr[i], _b = arr[j], _c = arr[k];                                                                                      \
        (_cmp(_i, _b) > 0 ? (_cmp(_b, _c) > 0 ? j : (_cmp(_i, _c) > 0 ? k : i)) : (_cmp(_i, _c) > 0 ? i : (_cmp(_b, _c) > 0 ? k : j))); \
    })

#define rand_pos(state, a, b) ((xrshr128p_next(state) % ((b) - (a) + 1)) + (a))

enum
{
    MID,
    MED3,
    MED3_2,
    RANDOM,
} pivot_type;

#define pivot(a, left, right, state, type)         \
    ({                                             \
        size_t mid, pivot = left;                  \
        switch (type)                              \
        {                                          \
        case MID:                                  \
            pivot = left + ((right - left) >> 1);  \
            break;                                 \
        case MED3:                                 \
            mid = left + ((right - left) >> 1);    \
            pivot = med3(a, left, mid, right);     \
            break;                                 \
        case MED3_2:                               \
            mid = left + ((right - left) >> 1);    \
            if (cmp(a + mid, a + left) < 0)        \
            {                                      \
                swap(a, left, mid);                \
            }                                      \
            if (cmp(a + right, a + left) < 0)      \
            {                                      \
                swap(a, left, right);              \
            }                                      \
            if (cmp(a + mid, a + right) < 0)       \
            {                                      \
                swap(a, mid, right);               \
            }                                      \
            pivot = right;                         \
            break;                                 \
        case RANDOM:                               \
            pivot = rand_pos(*state, left, right); \
            break;                                 \
        }                                          \
        pivot;                                     \
    })

/* Common functions */

int cmp(const void *a, const void *b);

int cmp_desc(const void *a, const void *b);

size_t partition(int a[], size_t left, size_t right, int pivot_type, xrshr128p_state_t *state);

void merge(int a[], size_t left, size_t mid, size_t right);

#endif
