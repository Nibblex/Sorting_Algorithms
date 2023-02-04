#include <string.h>

#include "./helpers/sort_helpers.h"

static void merge(int a[], unsigned int izq, unsigned int mid, unsigned int der)
{
    unsigned int n1 = mid - izq + 1;
    unsigned int n2 = der - mid;

    int L[n1], R[n2];
    memcpy(L, a + izq, n1 * sizeof(int));
    memcpy(R, a + mid + 1, n2 * sizeof(int));

    unsigned int i = 0, j = 0, k = izq;
    while (i < n1 && j < n2)
    {
        if (cmp(L[i], R[j]) < 0)
        {
            a[k++] = L[i++];
        }
        else
        {
            a[k++] = R[j++];
        }
    }

    while (i < n1)
    {
        a[k++] = L[i++];
    }

    while (j < n2)
    {
        a[k++] = R[j++];
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
