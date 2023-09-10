#include "../helpers/sort_helpers.h"
#include "algorithms.h"

static size_t min_pos_from(int a[], size_t i, size_t length)
{
    size_t j, min_pos = i;

    for (j = i + 1; j < length; j++)
    {
        if (cmp(a + j, a + min_pos) < 0)
        {
            min_pos = j;
        }
    }

    return min_pos;
}

void selection_sort(int a[], size_t length)
{
    size_t i, min_pos;

    for (i = 0; i < length; i++)
    {
        min_pos = min_pos_from(a, i, length);
        swap(a, i, min_pos);
    }
}
