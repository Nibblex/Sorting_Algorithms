#include "../helpers/sort_helpers.h"

static void timsort_it(int a[], unsigned int length)
{
    unsigned int left, mid, right, chunks = length / CHUNK_SIZE;
    for (unsigned int i = 0; i <= chunks; i++)
    {
        left = i * CHUNK_SIZE;
        right = min(left + CHUNK_SIZE - 1, length - 1);
        insertion_sort(a + left, right - left + 1);
    }

    unsigned int size = CHUNK_SIZE;
    while (size < length)
    {
        left = 0;
        size <<= 1;
        while (left < length)
        {
            mid = left + (size >> 1) - 1;
            right = min(left + size - 1, length - 1);
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
