#ifndef _SORT_HELPERS_H
#define _SORT_HELPERS_H

#include <stddef.h>

#include "../algorithms/xoroshiro128plus.h"

#define rand_pos(state, a, b) ((__typeof__(a))(xrshr128p_next(state) % (size_t)((b) - (a) + 1)) + (a))
#define ptr_rand_pos(state, a, b) ((a) + rand_pos(state, 0, (b) - (a)))

#define log2(x)                \
    ({                         \
        size_t _i = 0, _x = x; \
        while (_x >>= 1)       \
        {                      \
            _i++;              \
        }                      \
        _i;                    \
    })

/**
 * @brief A struct that holds counters for various operations in sorting algorithms.
 */
struct counter
{
    size_t cmp_counter;       /**< Counter for number of comparisons */
    size_t swap_counter;      /**< Counter for number of swaps */
    size_t recursion_counter; /**< Counter for number of recursive calls */
    size_t isort_counter;     /**< Counter for number of times insertion sort is used */
    size_t heapsort_counter;  /**< Counter for number of times heapsort is used */
};

enum pivot_type
{
    MID,
    MED3,
    RANDOM,
};

/* Common functions */

int cmp(const void *a, const void *b, void *arg);

int *ptr_swap(int *a, int *b, struct counter *counters);

int *partition(int *lo, int *hi, enum pivot_type pivot_type, xrshr128p_state_t *state, struct counter *counters);

void merge(int a[], size_t lo, size_t mid, size_t hi, struct counter *counters);

#endif
