#include <stdio.h>
#include <stdlib.h>

#include "../helpers/sort_helpers.h"

#include "arraygen.h"

extern int
getrandom(void* buf, size_t buflen, unsigned int flags);

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
arraygen(const struct array_config* config)
{
  int *array, seed;
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

  getrandom(&seed, sizeof(seed), 0);
  if (seed == (int)-1) {
    fprintf(stderr, "Failed to get clock time.\n");
    free(array);
    return NULL;
  }

  state = xrshr128p_init(seed);
  for (size_t i = 0; i < config->length; ++i) {
    int val = rand_pos(state, config->min, config->max);

    if (config->sign == POS) {
      val = abs(val);
    } else if (config->sign == NEG) {
      val = -abs(val);
    } else if (config->sign == RND) {
      val *= rand_pos(state, 0, 1) ? 1 : -1;
    }

    array[i] = val;
  }

  if (config->order != UNS) {
    qsort_r(
      array, config->length, sizeof(int), config->order == ASC ? cmp : cmp_desc, NULL);
  }

  return array;
}
