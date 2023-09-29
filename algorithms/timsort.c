#include "../helpers/sort_helpers.h"
#include "algorithms.h"

#define MIN(a, b) ((a) < (b) ? (a) : (b))

void timsort(int a[], size_t length)
{
    size_t lo, mid, hi, chunks = length / MAX_THRESH;
    for (size_t i = 0; i <= chunks; i++)
    {
        lo = i * MAX_THRESH;
        hi = MIN(lo + MAX_THRESH - 1, length - 1);
        isort(a + lo, hi - lo + 1);
    }

    size_t size = MAX_THRESH;
    while (size < length)
    {
        lo = 0;
        size <<= 1;
        while (lo < length)
        {
            mid = lo + (size >> 1) - 1;
            hi = MIN(lo + size - 1, length - 1);
            if (mid < hi)
            {
                merge(a, lo, mid, hi);
            }
            lo += size;
        }
    }
}
