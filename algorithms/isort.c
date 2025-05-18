#include <string.h>

#include "algorithms.h"

void
isort(int a[], size_t length, double* counters)
{
  int key, *i, *j;

  for (i = a + 1; i < a + length; ++i) {
    key = *i;
    j = i + 1;

    // Linear search for the insertion point
    while (--j > a && cmp(j - 1, &key, counters) > 0)
      ;

    // Shift elements to the right
    memmove(j + 1, j, (size_t)(i - j) * sizeof(int));

    // Insert the element
    *j = key;
  }

  ++counters[ISORTS];
}
