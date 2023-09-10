#include "../helpers/sort_helpers.h"
#include "algorithms.h"

void shellsort(int a[], size_t length)
{
    size_t i, j, gap;
    int temp;

    for (gap = length; gap >>= 1;)
    {
        for (i = gap; i < length; i++)
        {
            temp = a[i];
            for (j = i; j >= gap && cmp(&temp, a + j - gap) < 0; j -= gap)
            {
                a[j] = a[j - gap];
            }
            a[j] = temp;
        }
    }
}
