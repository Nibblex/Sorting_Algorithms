#include "../helpers/sort_helpers.h"

static void insert(int a[], unsigned int i)
{
    unsigned int j = i;
    while (j > 0 && cmp(a + j - 1, a + j) > 0)
    {
        swap(a, j, j - 1);
        j--;
    }
}

void insertion_sort(int a[], unsigned int length)
{
    for (unsigned int i = 1; i < length; i++)
    {
        insert(a, i);
    }
}
