#include "../helpers/sort_helpers.h"

void quicksort_std(int a[], unsigned int length)
{
    qsort(a, length, sizeof(int), cmp);
}
