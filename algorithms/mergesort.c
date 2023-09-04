#include "../helpers/sort_helpers.h"
#include "algorithms.h"

static void mergesort_rec(int a[], size_t left, size_t right)
{
    extern struct counter counters;
    size_t mid, length = right - left + 1;

    if (length > 1)
    {
        mid = left + ((length - 1) >> 1);
        mergesort_rec(a, left, mid);
        mergesort_rec(a, mid + 1, right);
        merge(a, left, mid, right);
    }

    counters.recursion_counter++;
}

void mergesort(int a[], size_t length)
{
    mergesort_rec(a, 0, !length ? 0 : length - 1);
}
