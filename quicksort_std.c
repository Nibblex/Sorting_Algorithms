#include "./helpers/sort_helpers.h"

static int compare(const void *a, const void *b)
{
    return cmp(*(int *)a, *(int *)b);
}

void quicksort_std(int a[], unsigned int length)
{
    qsort(a, length, sizeof(int), compare);
}
