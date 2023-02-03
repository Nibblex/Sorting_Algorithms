#include <time.h>

#include "./helpers/sort_helpers.h"

#define rand_pos(izq, der) (srand(time(NULL)), (rand() % ((der) - (izq) + 1)) + (izq))

static unsigned int partition(int a[], unsigned int izq, unsigned int der)
{
    unsigned int pivot = swap(a, izq, rand_pos(izq, der));
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

void quicksort_rp(int a[], unsigned int length)
{
    quicksort_rec(a, 0, !length ? 0 : length - 1);
}
