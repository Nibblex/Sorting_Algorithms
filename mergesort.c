#include <string.h>

#include "./helpers/sort_helpers.h"

#define SIZE_MAX (unsigned int)(-1)

static void merge(int a[], unsigned int left, unsigned int mid, unsigned int right)
{
    unsigned int n1 = mid - left + 1;
    unsigned int n2 = right - mid;

    int L[n1], R[n2];
    memcpy(L, a + left, n1 * sizeof(int));
    memcpy(R, a + mid + 1, n2 * sizeof(int));

    unsigned int i = n1 - 1, j = n2 - 1, k = right;
    while (i != SIZE_MAX && j != SIZE_MAX)
    {
        if (cmp(L + i, R + j) < 0)
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
        memcpy(a + left, L, (i + 1) * sizeof(int));
    }

    if (j)
    {
        memcpy(a + left, R, (j + 1) * sizeof(int));
    }
}

static void mergesort_rec(int a[], unsigned int left, unsigned int right)
{
    unsigned int mid, length = right - left + 1;
    if (length < CHUNK_SIZE)
    {
        insertion_sort(a + left, length);
    }
    else
    {
        mid = (left + right) >> 1;
        mergesort_rec(a, left, mid);
        mergesort_rec(a, mid + 1, right);
        merge(a, left, mid, right);
    }
}

void mergesort(int a[], unsigned int length)
{
    mergesort_rec(a, 0, !length ? 0 : length - 1);
}
