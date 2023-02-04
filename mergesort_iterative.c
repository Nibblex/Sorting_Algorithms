#include <string.h>

#include "./helpers/sort_helpers.h"

#define CHUNK_SIZE 10

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

static void mergesort_it(int a[], unsigned int length, unsigned int chunks)
{
    unsigned int izq, mid, der;
    for (unsigned int i = 0; i <= chunks; i++)
    {
        izq = i * CHUNK_SIZE;
        der = min(izq + CHUNK_SIZE - 1, length - 1);
        insertion_sort(a + izq, der - izq + 1);
    }

    unsigned int chunk_size = CHUNK_SIZE;
    for (unsigned int i = 1; i < chunks; i >>= 1)
    {
        for (unsigned int j = 0; j < chunks; j += 2)
        {
            izq = j * chunk_size;
            mid = min(izq + chunk_size - 1, length - 1);
            der = min(mid + chunk_size, length - 1);
            merge(a, izq, mid, der);
        }
        chunk_size <<= 1;
        chunks >>= 1;
    }
}

void mergesort_iterative(int a[], unsigned int length)
{
    mergesort_it(a, length, length / CHUNK_SIZE);
}
