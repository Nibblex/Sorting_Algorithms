#include "../helpers/sort_helpers.h"

static unsigned int max(int a[], unsigned int length, unsigned int i, unsigned int j, unsigned int k)
{
    unsigned int max = i;

    if (j < length && cmp(a + j, a + max) > 0)
    {
        max = j;
    }

    if (k < length && cmp(a + k, a + max) > 0)
    {
        max = k;
    }

    return max;
}

static void downheap(int a[], unsigned int length, unsigned int i)
{
    while (1)
    {
        unsigned int j = (i << 1) + 1;
        unsigned int largest = max(a, length, i, j, j + 1);

        if (largest == i)
        {
            return;
        }

        i = swap(a, largest, i);
    }
}

static void heapsort_it(int a[], unsigned int length)
{
    for (unsigned int i = (length >> 1) - 1; i < U32_MAX; i--)
    {
        downheap(a, length, i);
    }

    for (unsigned int i = length - 1; i < U32_MAX; i--)
    {
        swap(a, 0, i);
        downheap(a, i, 0);
    }
}

void heapsort(int a[], unsigned int length)
{
    heapsort_it(a, length);
}
