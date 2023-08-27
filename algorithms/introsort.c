#include <math.h>

#include "../helpers/sort_helpers.h"

static void introsort_rec(int a[], unsigned int left, unsigned int right, unsigned int depth_limit)
{
    counters.recursion_counter++;

    unsigned int length = right - left + 1;

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

    unsigned int pivot = partition(a, left, right, MID, NULL);
    introsort_rec(a, left, pivot, depth_limit - 1);
    introsort_rec(a, pivot + 1, right, depth_limit - 1);
}

void introsort(int a[], unsigned int length)
{
    unsigned int depth_limit = 2 * log(length);
    introsort_rec(a, 0, !length ? 0 : length - 1, depth_limit);
}
