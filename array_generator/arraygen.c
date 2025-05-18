#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../helpers/sort_helpers.h"

#include "arraygen.h"

extern int
qsort_r(void* base,
        size_t nmemb,
        size_t size,
        int (*compar)(const void*, const void*, void*),
        void* arg);

static inline int
cmp_desc(const void* a, const void* b, void* arg)
{
  return cmp(b, a, arg);
}

int*
arraygen(struct array_config* config)
{
  int *array, sign;
  xrshr128p_state_t state;

  if (config->max < config->min) {
    fprintf(stderr, "Invalid range: max (%d) < min (%d)\n", config->max, config->min);
    return NULL;
  }

  array = malloc(config->length * sizeof(int));
  if (array == NULL) {
    fprintf(stderr, "Memory allocation failed.\n");
    return NULL;
  }

  state = xrshr128p_init(clock());
  for (size_t i = 0; i < config->length; ++i) {
    int val = rand_pos(state, config->min, config->max);

    if (config->sign == POS) {
      val = abs(val);
    } else if (config->sign == NEG) {
      val = -abs(val);
    } else if (config->sign == RND) {
      sign = rand_pos(state, 0, 1) ? 1 : -1;
      val *= sign;
    }

    array[i] = val;
  }

  if (config->order != UNS) {
    qsort_r(
      array, config->length, sizeof(int), config->order == ASC ? cmp : cmp_desc, NULL);
  }

  return array;
}
