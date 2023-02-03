#include "sort_helpers.h"

static void update(int a[], unsigned int perm[], unsigned int length)
{
    int aux[length];
    for (unsigned int i = 0; i < length; i++)
    {
        aux[i] = a[perm[i]];
    }

    for (unsigned int i = 0; i < length; i++)
    {
        a[i] = aux[i];
    }
}

static void next_permutation(unsigned int perm[], unsigned int length)
{
    unsigned int i, j;
    i = length - 1;
    while (i > 0 && perm[i - 1] >= perm[i])
    {
        i--;
    }

    j = length - 1;
    while (perm[j] <= perm[i - 1])
    {
        j--;
    }

    swap((int *)perm, i - 1, j);

    j = length - 1;
    while (i < j)
    {
        swap((int *)perm, i++, j--);
    }
}

static bool sorted(int a[], unsigned int perm[], unsigned int length)
{
    unsigned int i = 1;
    while (i < length && goes_before(a[perm[i - 1]], a[perm[i]]))
    {
        i++;
    }

    return i == length;
}

static void mk_fst_permutation(unsigned int perm[], unsigned int length)
{
    for (unsigned int i = 0; i < length; i++)
    {
        perm[i] = i;
    }
}

void permutation_sort(int a[], unsigned int length)
{
    unsigned int perm[length];
    mk_fst_permutation(perm, length);
    while (!sorted(a, perm, length))
    {
        next_permutation(perm, length);
    }
    update(a, perm, length);
}
