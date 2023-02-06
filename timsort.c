#include <string.h>

#include "./helpers/sort_helpers.h"

#ifndef SIZE_MAX
#define SIZE_MAX (unsigned int)(-1)
#endif

static void merge(int a[], unsigned int left, unsigned int mid, unsigned int right)
{
    unsigned int n1 = mid - left + 1;
    unsigned int n2 = right - mid;

    int L[n1], R[n2];
    memcpy(L, a + left, n1 * sizeof(int));
    memcpy(R, a + mid + 1, n2 * sizeof(int));

    unsigned int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        int _i = L[i], _j = R[j];
        if (_cmp(_i, _j) <= 0)
        {
            a[k++] = L[i++];
        }
        else
        {
            a[k++] = R[j++];
        }
    }

    if (i)
    {
        memcpy(a + k, L + i, (n1 - i) * sizeof(int));
    }

    if (j)
    {
        memcpy(a + k, R + j, (n2 - j) * sizeof(int));
    }
}

static void timsort_it(int a[], unsigned int length)
{
    unsigned int left, mid, right, chunks = length / CHUNK_SIZE;
    for (unsigned int i = 0; i <= chunks; i++)
    {
        left = i * CHUNK_SIZE;
        right = min(left + CHUNK_SIZE - 1, length - 1);
        insertion_sort(a + left, right - left + 1);
    }

    unsigned int size = CHUNK_SIZE;
    while (size < length)
    {
        left = 0;
        size <<= 1;
        while (left < length)
        {
            mid = left + (size >> 1) - 1;
            right = min(left + size - 1, length - 1);
            if (mid < right)
            {
                merge(a, left, mid, right);
            }
            left += size;
        }
    }
}

void timsort(int a[], unsigned int length)
{
    timsort_it(a, length);
}
