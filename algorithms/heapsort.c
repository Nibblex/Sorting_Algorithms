#include "../helpers/sort_helpers.h"

#define largest(a, length, i, j, k)                    \
    ({                                                 \
        unsigned int largest = i;                      \
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

static void heapify(int a[], unsigned int length, unsigned int i)
{
    unsigned int j, largest;
    do
    {
        j = (i << 1) + 1;
        largest = largest(a, length, i, j, j + 1);
    } while (largest != i && (i = swap(a, largest, i), 1));
}

void heapsort(int a[], unsigned int length)
{
    counters.heapsort_counter++;
    for (unsigned int i = (length >> 1) - 1; i < U32_MAX; i--)
    {
        heapify(a, length, i);
    }

    for (unsigned int i = length - 1; i < U32_MAX; i--)
    {
        swap(a, 0, i);
        heapify(a, i, 0);
    }
}
