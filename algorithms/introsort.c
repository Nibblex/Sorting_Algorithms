#include <math.h>

#include "../helpers/sort_helpers.h"
#include "algorithms.h"

static void introsort_rec(int a[], size_t left, size_t right, size_t depth_limit)
{
    extern struct counter counters;
    size_t pivot, length = right - left + 1;

    if (length <= MAX_THRESH)
    {
        insertion_sort(a + left, length);
        return;
    }

    if (depth_limit == 0)
    {
        heapsort(a + left, length);
        return;
    }

    pivot = partition(a, left, right, MID, NULL);
    introsort_rec(a, left, pivot, depth_limit - 1);
    introsort_rec(a, pivot + 1, right, depth_limit - 1);

    counters.recursion_counter++;
}

void introsort(int a[], size_t length)
{
    size_t depth_limit = 2 * log(length);
    introsort_rec(a, 0, !length ? 0 : length - 1, depth_limit);
}
