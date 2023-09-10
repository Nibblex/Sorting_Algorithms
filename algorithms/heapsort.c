#include "../helpers/sort_helpers.h"
#include "algorithms.h"

#define U32_MAX ((size_t)-1)

#define largest(a, length, i, j, k)                     \
    ({                                                  \
        size_t _largest = i;                            \
        if (j < length && cmp(a + j, a + _largest) > 0) \
        {                                               \
            _largest = j;                               \
        }                                               \
        if (k < length && cmp(a + k, a + _largest) > 0) \
        {                                               \
            _largest = k;                               \
        }                                               \
        _largest;                                       \
    })

static void heapify(int a[], size_t length, size_t root)
{
    size_t j, largest;
    while (1)
    {
        j = (root << 1) + 1;

        largest = largest(a, length, root, j, j + 1);
        if (largest == root)
        {
            break;
        }

        swap(a, root, largest);
        root = largest;
    }
}

void heapsort(int a[], size_t length)
{
    extern struct counter counters;

    for (size_t i = (length >> 1) - 1; i < U32_MAX; i--)
    {
        heapify(a, length, i);
    }

    for (size_t i = length - 1; i < U32_MAX; i--)
    {
        swap(a, 0, i);
        heapify(a, i, 0);
    }

    counters.heapsort_counter++;
}
