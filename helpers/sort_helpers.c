#include <string.h>

#include "counter.h"
#include "sort_helpers.h"

#define med3(arr, i, j, k)                                                                                                              \
    ({                                                                                                                                  \
        int _i = arr[i], _b = arr[j], _c = arr[k];                                                                                      \
        (_cmp(_i, _b) > 0 ? (_cmp(_b, _c) > 0 ? j : (_cmp(_i, _c) > 0 ? k : i)) : (_cmp(_i, _c) > 0 ? i : (_cmp(_b, _c) > 0 ? k : j))); \
    })

typedef int (*cmp_func)(const void *a, const void *b);

int cmp(const void *a, const void *b)
{
    extern struct counter counters;
    int cmp = _cmp(*(int *)a, *(int *)b);

    counters.cmp_counter++;

    return cmp;
}

int cmp_desc(const void *a, const void *b)
{
    extern struct counter counters;
    int cmp = _cmp(*(int *)a, *(int *)b);

    counters.cmp_counter++;

    return cmp;
}

size_t swap(int a[], size_t i, size_t j)
{
    extern struct counter counters;

    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;

    counters.swap_counter++;

    return i;
}

size_t pivot(int a[], size_t left, size_t right, xrshr128p_state_t *state, int type)
{
    size_t mid;
    switch (type)
    {
    case MID:
        return left + ((right - left) >> 1);
    case MED3:
        mid = left + ((right - left) >> 1);
        return med3(a, left, mid, right);
    case MED3_2:
        mid = left + ((right - left) >> 1);
        if (cmp(a + mid, a + left) < 0)
        {
            swap(a, left, mid);
        }
        if (cmp(a + right, a + left) < 0)
        {
            swap(a, left, right);
        }
        if (cmp(a + mid, a + right) < 0)
        {
            swap(a, mid, right);
        }
        return right;
    case RANDOM:
        return rand_pos(*state, left, right);
    default:
        return left;
    }
}

size_t partition(int a[], size_t left, size_t right, int pivot_type, xrshr128p_state_t *state)
{
    size_t piv = pivot(a, left, right, state, pivot_type);
    int pivot_value = a[piv];

    size_t i = left - 1;
    size_t j = right + 1;

    while (1)
    {
        do
            i++;
        while (cmp(a + i, &pivot_value) < 0);

        do
            j--;
        while (cmp(a + j, &pivot_value) > 0);

        if (i >= j)
        {
            return j;
        }

        swap(a, i, j);
    }
}

void merge(int a[], size_t left, size_t mid, size_t right)
{
    size_t n1 = mid - left + 1;
    size_t n2 = right - mid;

    int L[n1], R[n2];
    memcpy(L, a + left, n1 * sizeof(int));
    memcpy(R, a + mid + 1, n2 * sizeof(int));

    size_t i = 0, j = 0, k = left;
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

    if (i < n1)
    {
        memcpy(a + k, L + i, (n1 - i) * sizeof(int));
    }

    if (j < n2)
    {
        memcpy(a + k, R + j, (n2 - j) * sizeof(int));
    }
}
