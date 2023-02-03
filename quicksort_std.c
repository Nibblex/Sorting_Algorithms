#include "sort_helpers.h"

static int compare(const void *a, const void *b)
{
    return goes_before(*(int *)a, *(int *)b) ? -1 : 1;
}

void quicksort_std(int a[], unsigned int length)
{
    qsort(a, length, sizeof(int), compare);
}
