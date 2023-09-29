#include "../helpers/sort_helpers.h"
#include "algorithms.h"

void selection_sort(int a[], size_t length)
{
    int *key, *min_ptr;

    for (size_t i = 0; i < length - 1; ++i)
    {
        min_ptr = a + i;

        // Find the minimum element in the unsorted array
        for (key = a + i + 1; key < a + length; ++key)
        {
            if (cmp(key, min_ptr) < 0)
            {
                min_ptr = key;
            }
        }

        if (min_ptr != a + i)
        {
            // Swap the minimum element with the first element of the unsorted array
            ptr_swap(min_ptr, a + i);
        }
    }
}
