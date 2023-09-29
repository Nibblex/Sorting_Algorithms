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

void ptr_swap(int *a, int *b)
{
    extern struct counter counters;

    int temp = *a;
    *a = *b;
    *b = temp;

    counters.swap_counter++;
}

static size_t pivot(int a[], size_t lo, size_t hi, int type, xrshr128p_state_t *state)
{
    size_t mid;
    switch (type)
    {
    case MID:
        return lo + ((hi - lo) >> 1);
    case MED3:
        mid = lo + ((hi - lo) >> 1);
        if (cmp(a + mid, a + lo) < 0)
        {
            swap(a, mid, lo);
        }
        if (cmp(a + hi, a + mid) < 0)
        {
            swap(a, hi, mid);
        }
        else
        {
            return mid;
        }
        if (cmp(a + mid, a + lo) < 0)
        {
            swap(a, mid, lo);
        }
        return mid;
    case RANDOM:
        return rand_pos(*state, lo, hi);
    default:
        fprintf(stderr, "Invalid pivot type\n");
        exit(EXIT_FAILURE);
    }
}

size_t partition(int a[], size_t lo, size_t hi, int pivot_type, xrshr128p_state_t *state)
{
    size_t piv;
    int *left_ptr, *right_ptr, *piv_ptr;

    piv = pivot(a, lo, hi, pivot_type, state);
    left_ptr = a + lo;
    right_ptr = a + hi;
    piv_ptr = a + piv;

    do
    {
        while (cmp(left_ptr, piv_ptr) < 0)
        {
            left_ptr++;
        }

        while (cmp(piv_ptr, right_ptr) < 0)
        {
            right_ptr--;
        }

        if (left_ptr < right_ptr)
        {
            ptr_swap(left_ptr, right_ptr);
            if (piv_ptr == left_ptr)
            {
                piv_ptr = right_ptr;
            }
            else if (piv_ptr == right_ptr)
            {
                piv_ptr = left_ptr;
            }
            left_ptr++;
            right_ptr--;
        }
        else if (left_ptr == right_ptr)
        {
            left_ptr++;
            right_ptr--;
            break;
        }

    } while (left_ptr <= right_ptr);

    return (size_t)(right_ptr - a);
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
