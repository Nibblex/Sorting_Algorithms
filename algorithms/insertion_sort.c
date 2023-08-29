#include "../helpers/counter.h"
#include "../helpers/sort_helpers.h"
#include "algorithms.h"

static void insert(int a[], size_t i)
{
    size_t j = i;
    while (j > 0 && cmp(a + j - 1, a + j) > 0)
    {
        swap(a, j, j - 1);
        j--;
    }
}

void insertion_sort(int a[], size_t length)
{
    extern struct counter counters;

    for (size_t i = 1; i < length; i++)
    {
        insert(a, i);
    }

    counters.insertion_sort_counter++;
}
