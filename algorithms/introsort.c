#include <math.h>

#include "../helpers/sort_helpers.h"
#include "algorithms.h"

static void introsort_rec(int a[], size_t lo, size_t hi, size_t depth_limit)
{
    extern struct counter counters;
    size_t pivot, length = hi - lo + 1;

    if (length <= MAX_THRESH)
    {
        insertion_sort(a + lo, length);
        return;
    }

    if (depth_limit == 0)
    {
        heapsort(a + lo, length);
        return;
    }

    pivot = partition(a, lo, hi, MID, NULL);
    introsort_rec(a, lo, pivot, depth_limit - 1);
    introsort_rec(a, pivot + 1, hi, depth_limit - 1);

    counters.recursion_counter++;
}

void introsort(int a[], size_t length)
{
    size_t depth_limit = 2 * floor(log2(length));
    introsort_rec(a, 0, !length ? 0 : length - 1, depth_limit);
}
