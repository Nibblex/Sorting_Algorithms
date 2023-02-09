#include "../helpers/sort_helpers.h"

static void mergesort_rec(int a[], unsigned int left, unsigned int right)
{
    recursion_counter++;

    unsigned int mid, length = right - left + 1;
    if (length > 1)
    {
        mid = left + ((length - 1) >> 1);
        mergesort_rec(a, left, mid);
        mergesort_rec(a, mid + 1, right);
        merge(a, left, mid, right);
    }
}

void mergesort(int a[], unsigned int length)
{
    mergesort_rec(a, 0, !length ? 0 : length - 1);
}
