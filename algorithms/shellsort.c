#include "../helpers/sort_helpers.h"
#include "algorithms.h"

void shellsort(int a[], size_t length)
{
    int key, *i, *j;
    size_t gap;

    for (gap = length; gap >>= 1;)
    {
        for (i = a + gap; i < a + length; i++)
        {
            key = *i;

            for (j = i; j >= a + gap && cmp(&key, j - gap) < 0; j -= gap)
            {
                *j = *(j - gap);
            }

            *j = key;
        }
    }
}
