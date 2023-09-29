#include <string.h>

#include "../helpers/sort_helpers.h"
#include "algorithms.h"

void binsort(int a[], size_t length)
{
    int key, *lo, *hi, *mid, *i;

    for (i = a + 1; i < a + length; ++i)
    {
        key = *i;
        lo = a;
        hi = i;

        // Binary search for the insertion point
        while (lo < hi)
        {
            mid = lo + ((hi - lo) >> 1);
            if (cmp(&key, mid) < 0)
            {
                hi = mid;
            }
            else
            {
                lo = mid + 1;
            }
        }

        // Shift elements to the right
        memmove(lo + 1, lo, (size_t)(i - lo) * sizeof(int));

        // Insert the element
        *lo = key;
    }
}
