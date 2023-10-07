#include "../helpers/sort_helpers.h"
#include "algorithms.h"

static void mergesort_rec(int a[], size_t lo, size_t hi)
{
    extern struct counter counters;

    size_t mid, length;

    length = hi - lo + 1;
    if (length > 1)
    {
        mid = lo + ((length - 1) >> 1);
        mergesort_rec(a, lo, mid);
        mergesort_rec(a, mid + 1, hi);
        merge(a, lo, mid, hi);
    }

    counters.recursion_counter++;
}

void mergesort(int a[], size_t length)
{
    mergesort_rec(a, 0, !length ? 0 : length - 1);
}
