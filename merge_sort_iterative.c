#include "sort_helpers.h"

static void merge(int a[], unsigned int izq, unsigned int med, unsigned int der)
{
    int tmp[der + 1];
    unsigned int j = izq, k = med + 1;
    for (unsigned int i = izq; i <= med; i++)
        tmp[i] = a[i];

    for (unsigned int i = izq; i <= der; i++)
    {
        if (j <= med && (k > der || goes_before(tmp[j], a[k])))
        {
            a[i] = tmp[j];
            j++;
        }
        else
        {
            a[i] = a[k];
            k++;
        }
    }
}

static void merge_each(int a[], unsigned int k, unsigned int length)
{
    unsigned int izq, med, der, bl;
    bl = pow(2, k);
    izq = 0;
    med = bl - 1;
    der = 2 * bl - 1;
    while (der < length)
    {
        merge(a, izq, med, der);
        izq = izq + 2 * bl;
        med = med + 2 * bl;
        der = der + 2 * bl;
    }
    if (izq - 1 < length)
        merge(a, izq - 2 * bl, izq - 1, length - 1);
}

void merge_sort_iterative(int a[], unsigned int length)
{
    unsigned int l = log(length) / log(2);
    for (unsigned int i = 0; i < l; i++)
        merge_each(a, i, length);
}