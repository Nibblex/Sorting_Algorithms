#include "../helpers/sort_helpers.h"

void shellsort(int a[], unsigned int length)
{
    int temp;
    unsigned int j, gap = length;
    while (gap >>= 1)
    {
        for (unsigned int i = gap; i < length; i++)
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