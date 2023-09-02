#include "../helpers/sort_helpers.h"
#include "algorithms.h"

#define MIN(a, b) ((a) < (b) ? (a) : (b))

static void timsort_it(int a[], size_t length)
{
    size_t left, mid, right, chunks = length / MAX_THRESH;
    for (size_t i = 0; i <= chunks; i++)
    {
        left = i * MAX_THRESH;
        right = MIN(left + MAX_THRESH - 1, length - 1);
        insertion_sort(a + left, right - left + 1);
    }

    size_t size = MAX_THRESH;
    while (size < length)
    {
        left = 0;
        size <<= 1;
        while (left < length)
        {
            mid = left + (size >> 1) - 1;
            right = MIN(left + size - 1, length - 1);
            if (mid < right)
            {
                merge(a, left, mid, right);
            }
            left += size;
        }
    }
}

void timsort(int a[], size_t length)
{
    timsort_it(a, length);
}
