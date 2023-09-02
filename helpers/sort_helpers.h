#ifndef _SORT_HELPERS_H
#define _SORT_HELPERS_H

#include <stdlib.h>

#include "../algorithms/xoroshiro128plus.h"

#define rand_pos(state, a, b) ((xrshr128p_next(state) % ((b) - (a) + 1)) + (a))

enum
{
    MID,
    MED3,
    RANDOM,
} pivot_type;

/* Common functions */

int cmp(const void *a, const void *b);

int cmp_desc(const void *a, const void *b);

size_t swap(int a[], size_t i, size_t j);

size_t partition(int a[], size_t left, size_t right, int pivot_type, xrshr128p_state_t *state);

void merge(int a[], size_t left, size_t mid, size_t right);

#endif
