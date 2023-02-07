#include "sort_helpers.h"

int cmp(const void *a, const void *b)
{
    return _cmp(*(int *)a, *(int *)b);
}

int cmp_desc(const void *a, const void *b)
{
    return _cmp(*(int *)b, *(int *)a);
}

void merge(int a[], unsigned int left, unsigned int mid, unsigned int right)
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
