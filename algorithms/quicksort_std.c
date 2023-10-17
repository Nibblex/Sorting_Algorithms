#include <stdlib.h>

#include "algorithms.h"

extern int qsort_r(void *base, size_t nmemb, size_t size,
                   int (*compar)(const void *, const void *, void *),
                   void *arg);

void quicksort_std(int a[], size_t length, double *counters)

{
    qsort_r(a, length, sizeof(int), cmp, counters);
}
