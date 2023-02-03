#include "sort_helpers.h"

static unsigned int min_pos_from(int a[], unsigned int i, unsigned int length)
{
    unsigned int min_pos = i;
    for (unsigned int j = i + 1; j < length; j++)
    {
        if (goes_before(a[j], a[min_pos]))
        {
            min_pos = j;
        }
    }

    return min_pos;
}

void selection_sort(int a[], unsigned int length)
{
    unsigned int min_pos;
    for (unsigned int i = 0; i < length; i++)
    {
        min_pos = min_pos_from(a, i, length);
        swap(a, i, min_pos);
    }
}
