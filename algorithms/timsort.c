#include "algorithms.h"

#define MIN(a, b) ((a) < (b) ? (a) : (b))

void timsort(int a[], size_t length, double *counters)
{
    size_t size, lo, mid, hi, chunks, i;

    chunks = length / MAX_THRESH;
    for (i = 0; i <= chunks; ++i)
    {
        lo = i * MAX_THRESH;
        hi = MIN(lo + MAX_THRESH - 1, length - 1);
        isort(a + lo, hi - lo + 1, counters);
    }

    size = MAX_THRESH;
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
                merge(a, lo, mid, hi, counters);
            }
            lo += size;
        }
    }
}
