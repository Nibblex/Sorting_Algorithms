#include "sort_helpers.h"

static unsigned int partition(int a[], unsigned int izq, unsigned int der)
{
    unsigned int pivot = izq;
    while (izq <= der)
    {
        if (goes_before(a[izq], a[pivot]))
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
    unsigned int pivot;
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
