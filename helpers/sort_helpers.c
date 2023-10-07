#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../helpers/workbench.h"
#include "sort_helpers.h"

typedef int (*cmp_func)(const void *a, const void *b);

int cmp(const void *a, const void *b)
{
    extern struct counter counters;

    counters.cmp_counter++;

    return (*(int *)a - *(int *)b);
}

int *ptr_swap(int *a, int *b)
{
    extern struct counter counters;

    int temp = *a;
    *a = *b;
    *b = temp;

    counters.swap_counter++;

    return b;
}

static int *pivot(int *lo, int *hi, enum pivot_type type, xrshr128p_state_t *state)
{
    int *mid;

    switch (type)
    {
    case MID:
        return lo + ((hi - lo) >> 1);
    case MED3:
        mid = lo + ((hi - lo) >> 1);
        if (cmp(mid, lo) < 0)
        {
            ptr_swap(mid, lo);
        }
        if (cmp(hi, mid) < 0)
        {
            ptr_swap(hi, mid);
        }
        else
        {
            return mid;
        }
        if (cmp(mid, lo) < 0)
        {
            ptr_swap(mid, lo);
        }
        return mid;
    case RANDOM:
        return ptr_rand_pos(*state, lo, hi);
    default:
        fprintf(stderr, "Invalid pivot type\n");
        exit(EXIT_FAILURE);
    }
}

int *partition(int *lo, int *hi, enum pivot_type pivot_type, xrshr128p_state_t *state)
{
    int *piv;

    piv = pivot(lo, hi, pivot_type, state);

    do
    {
        while (cmp(lo, piv) < 0)
            lo++;

        while (cmp(piv, hi) < 0)
            hi--;

        if (lo < hi)
        {
            ptr_swap(lo, hi);
            piv = (piv == lo) ? hi : ((piv == hi) ? lo : piv);
            lo++;
            hi--;
        }
        else if (lo == hi)
        {
            lo++;
            hi--;
            break;
        }

    } while (lo <= hi);

    return hi;
}

void merge(int a[], size_t lo, size_t mid, size_t hi)
{
    size_t n1 = mid - lo + 1;
    size_t n2 = hi - mid;

    int L[n1], R[n2];
    memcpy(L, a + lo, n1 * sizeof(int));
    memcpy(R, a + mid + 1, n2 * sizeof(int));

    size_t i = 0, j = 0, k = lo;
    while (i < n1 && j < n2)
    {
        if (cmp(L + i, R + j) <= 0)
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
