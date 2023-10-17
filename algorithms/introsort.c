#include "algorithms.h"

static void introsort_rec(int *lo, int *hi, size_t depth_limit, double *counters)
{
    int *pivot;
    size_t length;

    length = (size_t)(hi - lo + 1);
    if (length <= MAX_THRESH)
    {
        isort(lo, length, counters);
        return;
    }

    if (depth_limit == 0)
    {
        heapsort(lo, length, counters);
        return;
    }

    pivot = partition(lo, hi, MID, NULL, counters);
    introsort_rec(lo, pivot, depth_limit - 1, counters);
    introsort_rec(pivot + 1, hi, depth_limit - 1, counters);

    ++counters[RECURSIONS];
}

void introsort(int a[], size_t length, double *counters)

{
    size_t depth_limit = log2(length) << 1;
    introsort_rec(a, length == 0 ? a : a + length - 1, depth_limit, counters);
}
