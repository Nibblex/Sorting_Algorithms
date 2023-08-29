#include "../helpers/counter.h"
#include "../helpers/sort_helpers.h"
#include "algorithms.h"

#define largest(a, length, i, j, k)                    \
    ({                                                 \
        size_t largest = i;                            \
        if (j < length && cmp(a + j, a + largest) > 0) \
        {                                              \
            largest = j;                               \
        }                                              \
        if (k < length && cmp(a + k, a + largest) > 0) \
        {                                              \
            largest = k;                               \
        }                                              \
        largest;                                       \
    })

static void heapify(int a[], size_t length, size_t i)
{
    size_t j, largest;
    do
    {
        j = (i << 1) + 1;
        largest = largest(a, length, i, j, j + 1);
    } while (largest != i && (i = swap(a, largest, i), 1));
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
