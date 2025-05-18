#ifndef _SORT_HELPERS_H
#define _SORT_HELPERS_H

#include <stddef.h>

#include "../algorithms/xoroshiro128plus.h"

#define rand_pos(state, a, b)                                                          \
  ((__typeof__(a))(xrshr128p_next(state) % (size_t)((b) - (a) + 1)) + (a))
#define ptr_rand_pos(state, a, b) ((a) + rand_pos(state, 0, (b) - (a)))

#define log2(x)                                                                        \
  ({                                                                                   \
    size_t _i = 0, _x = x;                                                             \
    while (_x >>= 1) {                                                                 \
      ++_i;                                                                            \
    }                                                                                  \
    _i;                                                                                \
  })

enum counter
{
  ELAPSED,
  COMPARISONS,
  SWAPS,
  RECURSIONS,
  ISORTS,
  HEAPSORTS,
};

enum pivot_type
{
  MID,
  MED3,
  RANDOM,
};

/* Common functions */

int
cmp(const void* a, const void* b, void* arg);

int*
ptr_swap(int* a, int* b, double* counters);

int*
partition(int* lo,
          int* hi,
          enum pivot_type pivot_type,
          xrshr128p_state_t* state,
          double* counters);

void
merge(int a[], size_t lo, size_t mid, size_t hi, double* counters);

#endif
