#include "./helpers/sort_helpers.h"

static unsigned int partition(int a[], unsigned int izq, unsigned int der)
{
    unsigned int pivot = izq;
    int pivot_value = a[pivot];
    while (izq <= der)
    {
        if (cmp(a[izq], pivot_value) <= 0)
        {
            izq++;
        }
        else
        {
            swap(a, izq, der);
            der--;
        }
    }

    return swap(a, der, pivot);
}

static void quicksort_rec(int a[], unsigned int izq, unsigned int der)
{
    unsigned int pivot, length = der - izq + 1;
    if (length < CHUNK_SIZE)
    {
        insertion_sort(a + izq, length);
        return;
    }

    if (izq < der + 1)
    {
        pivot = partition(a, izq, der);
        quicksort_rec(a, izq, pivot - 1);
        quicksort_rec(a, pivot + 1, der);
    }
}

void quicksort(int a[], unsigned int length)
{
    quicksort_rec(a, 0, !length ? 0 : length - 1);
}
