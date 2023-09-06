#include "../helpers/sort_helpers.h"
#include "algorithms.h"

void shellsort(int a[], size_t length)
{
    int temp;
    size_t j, gap = length;
    while (gap >>= 1)
    {
        for (size_t i = gap; i < length; i++)
        {
            temp = a[i];
            j = i;
            while (j >= gap && cmp(a + j - gap, &temp) > 0)
            {
                a[j] = a[j - gap];
                j -= gap;
            }
            a[j] = temp;
        }
    }
}
