#include <string.h>

#include "./helpers/sort_helpers.h"

static void merge(int a[], unsigned int izq, unsigned int mid, unsigned int der)
{
    int tmp[der + 1];
    memcpy(tmp + izq, a + izq, (mid - izq + 1) * sizeof(int));

    unsigned int k = mid + 1;
    for (unsigned int i = izq; i <= der; i++)
    {
        if (izq <= mid && (k > der || cmp(tmp[izq], a[k]) <= 0))
        {
            a[i] = tmp[izq++];
        }
        else
        {
            a[i] = a[k++];
        }
    }
}

static void mergesort_rec(int a[], unsigned int izq, unsigned int der)
{
    unsigned int mid;
    if (der > izq)
    {
        mid = (izq + der) >> 1;
        mergesort_rec(a, izq, mid);
        mergesort_rec(a, mid + 1, der);
        merge(a, izq, mid, der);
    }
}

void mergesort(int a[], unsigned int length)
{
    mergesort_rec(a, 0, !length ? 0 : length - 1);
}
