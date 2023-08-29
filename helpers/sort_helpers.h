#ifndef _SORT_HELPERS_H
#define _SORT_HELPERS_H

#include <stdlib.h>

#include "../algorithms/xoroshiro128plus.h"

#define MAX_THRESH 8

#define U32_MAX ((size_t)-1)

#define _cmp(a, b)                                       \
    ({                                                   \
        int _a = (a), _b = (b);                          \
        abs(_a)<abs(_b) ? -1 : abs(_a)> abs(_b) ? 1 : 0; \
    })

#define _min(a, b) (_cmp(a, b) < 0 ? (a) : (b))

#define _max(a, b) (_cmp(a, b) > 0 ? (a) : (b))

#define rand_pos(state, a, b) ((xrshr128p_next(state) % ((b) - (a) + 1)) + (a))

enum
{
    MID,
    MED3,
    MED3_2,
    RANDOM,
} pivot_type;

/* Common functions */

int cmp(const void *a, const void *b);

int cmp_desc(const void *a, const void *b);

size_t swap(int a[], size_t i, size_t j);

size_t pivot(int a[], size_t left, size_t right, xrshr128p_state_t *state, int type);

size_t partition(int a[], size_t left, size_t right, int pivot_type, xrshr128p_state_t *state);

void merge(int a[], size_t left, size_t mid, size_t right);

#endif
