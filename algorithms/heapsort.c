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
        unsigned int largest = max(a, length, i, (i << 1) + 1, (i << 1) + 2);

        if (largest == i)
        {
            return;
        }

        swap(a, i, largest);
        i = largest;
    }
}

static void heapsort_it(int a[], unsigned int length)
{
    for (int i = (length >> 1) - 1; i >= 0; i--)
    {
        downheap(a, length, i);
    }

    for (int i = length - 1; i >= 0; i--)
    {
        swap(a, 0, i);
        downheap(a, i, 0);
    }
}

void heapsort(int a[], unsigned int length)
{
    heapsort_it(a, length);
}
