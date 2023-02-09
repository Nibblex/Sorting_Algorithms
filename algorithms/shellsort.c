#include "../helpers/sort_helpers.h"

void shellsort(int a[], unsigned int length)
{
    unsigned int gap = length >> 1;
    while (gap > 0)
    {
        for (unsigned int i = gap; i < length; i++)
        {
            int temp = a[i];
            unsigned int j = i;
            while (j >= gap && cmp(a + j - gap, &temp) > 0)
            {
                a[j] = a[j - gap];
                j -= gap;
            }
            a[j] = temp;
        }
        gap >>= 1;
    }
}