#include "sort_helpers.h"

static unsigned int pivot_selection(int a[], unsigned int izq, unsigned int der)
{
    unsigned int pivot, med = (izq + der) / 2;

    if ((a[izq] <= a[med] && a[med] <= a[der]) || (a[der] <= a[med] && a[med] <= a[izq]))
    {
        pivot = med;
    }
    else if ((a[med] <= a[izq] && a[izq] <= a[der]) || (a[der] <= a[izq] && a[izq] <= a[med]))
    {
        pivot = izq;
    }
    else
    {
        pivot = der;
    }

    swap(a, izq, pivot);
    return (pivot = izq);
}

static unsigned int partition(int a[], unsigned int izq, unsigned int der)
{
    unsigned int pivot, i = izq + 1, j = der;
    pivot = pivot_selection(a, izq, der);
    while (i <= j)
    {
        if (goes_before(a[i], a[pivot]))
        {
            i++;
        }
        else
        {
            swap(a, i, j);
            j--;
        }
    }
    swap(a, j, pivot);
    return (pivot = j);
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

void quicksort_cp(int a[], unsigned int length)
{
    quicksort_rec(a, 0, !length ? 0 : length - 1);
}
