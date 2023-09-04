#include <stdio.h>
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

int cmp_desc(const void *a, const void *b)
{
    extern struct counter counters;

    counters.cmp_counter++;

    return (*(int *)b - *(int *)a);
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

static size_t pivot(int a[], size_t left, size_t right, int type, xrshr128p_state_t *state)
{
    size_t mid;
    switch (type)
    {
    case MID:
        return left + ((right - left) >> 1);
    case MED3:
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
        fprintf(stderr, "Invalid pivot type\n");
        exit(EXIT_FAILURE);
    }
}

size_t partition(int a[], size_t left, size_t right, int pivot_type, xrshr128p_state_t *state)
{
    size_t piv = pivot(a, left, right, pivot_type, state);
    int pivot_value = a[piv];

    size_t i = left;
    size_t j = right + 1;

    swap(a, left, piv);

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
            return swap(a, j, left);
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
