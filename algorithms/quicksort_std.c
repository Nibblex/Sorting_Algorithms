#include <stdlib.h>

#include "algorithms.h"

void quicksort_std(int a[], size_t length)
{
    qsort(a, length, sizeof(int), cmp);
}
