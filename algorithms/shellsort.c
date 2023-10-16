#include "algorithms.h"

void shellsort(int a[], size_t length, struct counter *counters)
{
    int key, *i, *j;
    size_t gap;

    for (gap = length; gap >>= 1;)
    {
        for (i = a + gap; i < a + length; ++i)
        {
            key = *i;

            for (j = i; j >= a + gap && cmp(&key, j - gap, counters) < 0; j -= gap)
            {
                *j = *(j - gap);
            }

            *j = key;
        }
    }
}
