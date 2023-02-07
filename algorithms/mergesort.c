#include "../helpers/sort_helpers.h"

static void mergesort_rec(int a[], unsigned int left, unsigned int right)
{
    unsigned int mid, length = right - left + 1;
    if (length < CHUNK_SIZE)
    {
        insertion_sort(a + left, length);
    }
    else
    {
        mid = (left + right) >> 1;
        mergesort_rec(a, left, mid);
        mergesort_rec(a, mid + 1, right);
        merge(a, left, mid, right);
    }
}

void mergesort(int a[], unsigned int length)
{
    mergesort_rec(a, 0, !length ? 0 : length - 1);
}
