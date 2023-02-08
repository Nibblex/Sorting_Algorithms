#include "../helpers/sort_helpers.h"

static void timsort_it(int a[], unsigned int length)
{
    unsigned int left, mid, right, chunks = length / MAX_THRESH;
    for (unsigned int i = 0; i <= chunks; i++)
    {
        left = i * MAX_THRESH;
        right = _min(left + MAX_THRESH - 1, length - 1);
        insertion_sort(a + left, right - left + 1);
    }

    unsigned int size = MAX_THRESH;
    while (size < length)
    {
        left = 0;
        size <<= 1;
        while (left < length)
        {
            mid = left + (size >> 1) - 1;
            right = _min(left + size - 1, length - 1);
            if (mid < right)
            {
                merge(a, left, mid, right);
            }
            left += size;
        }
    }
}

void timsort(int a[], unsigned int length)
{
    timsort_it(a, length);
}
