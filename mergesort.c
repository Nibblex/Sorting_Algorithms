#include <string.h>

#include "./helpers/sort_helpers.h"

#define SIZE_MAX (unsigned int)(-1)

static void merge(int a[], unsigned int izq, unsigned int mid, unsigned int der)
{
    unsigned int n1 = mid - izq + 1;
    unsigned int n2 = der - mid;

    int L[n1], R[n2];
    memcpy(L, a + izq, n1 * sizeof(int));
    memcpy(R, a + mid + 1, n2 * sizeof(int));

    unsigned int i = n1 - 1, j = n2 - 1, k = der;
    while (i != SIZE_MAX && j != SIZE_MAX)
    {
        if (cmp(L[i], R[j]) < 0)
        {
            a[k--] = R[j--];
        }
        else
        {
            a[k--] = L[i--];
        }
    }

    if (i)
    {
        memcpy(a + izq, L, (i + 1) * sizeof(int));
    }

    if (j)
    {
        memcpy(a + izq, R, (j + 1) * sizeof(int));
    }
}

static void mergesort_rec(int a[], unsigned int izq, unsigned int der)
{
    unsigned int mid, length = der - izq + 1;
    if (length <= CHUNK_SIZE)
    {
        insertion_sort(a + izq, length);
        return;
    }

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
