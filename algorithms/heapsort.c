#include "algorithms.h"

static void heapify(int a[], size_t length, int *root, double *counters)
{
    int *leaf, *largest;

    while (1)
    {
        leaf = a + ((root - a) << 1) + 1;
        if (leaf + 1 >= a + length)
        {
            break;
        }

        largest = root;
        if (cmp(leaf, largest, counters) > 0)
        {
            largest = leaf;
        }
        if (cmp(leaf + 1, largest, counters) > 0)
        {
            largest = leaf + 1;
        }
        if (largest == root)
        {
            break;
        }

        root = ptr_swap(root, largest, counters);
    }
}

void heapsort(int a[], size_t length, double *counters)
{
    int *lo, *hi;

    for (lo = a + (length >> 1) - 1; lo >= a; --lo)
    {
        heapify(a, length, lo, counters);
    }

    for (hi = a + length - 1; hi > a; --hi)
    {
        ptr_swap(a, hi, counters);
        heapify(a, (size_t)(hi - a), a, counters);
    }

    ++counters[HEAPSORTS];
}
