#include "algorithms.h"

static void
mergesort_rec(int a[], size_t lo, size_t hi, double* counters)
{
  size_t mid, length;

  length = hi - lo + 1;
  if (length > 1) {
    mid = lo + ((length - 1) >> 1);
    mergesort_rec(a, lo, mid, counters);
    mergesort_rec(a, mid + 1, hi, counters);
    merge(a, lo, mid, hi, counters);
  }

  ++counters[RECURSIONS];
}

void
mergesort(int a[], size_t length, double* counters)
{
  mergesort_rec(a, 0, !length ? 0 : length - 1, counters);
}
