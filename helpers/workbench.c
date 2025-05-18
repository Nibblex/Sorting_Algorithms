#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "array_helpers.h"
#include "workbench.h"

#define getms() ((double)(clock() * 1000) / CLOCKS_PER_SEC)

#define sorting(_sort_by) (_sort_by >= 0 && _sort_by < NUM_COUNTERS)

#define HEADER                                                                         \
  "Algorithm        Elapsed (ms)     Comparisons      Swaps            Recursions    " \
  "   Isorts           Heapsort         Tests (sorted-permuted)\n"

#define TEST_UNTESTED "\x1b[33mUNTESTED\x1b[0m"
#define TEST_OK "\x1b[32mOK\x1b[0m"
#define TEST_FAIL "\x1b[31mFAIL\x1b[0m"

#define print_hls(n)                                                                   \
  do {                                                                                 \
    for (size_t i = 0; i < (n); ++i) {                                                 \
      putchar('-');                                                                    \
    }                                                                                  \
    putchar('\n');                                                                     \
  } while (0)

#define print_header()                                                                 \
  do {                                                                                 \
    print_hls(strlen(HEADER));                                                         \
    printf("%s", HEADER);                                                              \
    print_hls(strlen(HEADER));                                                         \
  } while (0)

#define sum_counters(a, b)                                                             \
  do {                                                                                 \
    for (size_t c = 0; c < NUM_COUNTERS; ++c) {                                        \
      a[c] += b[c];                                                                    \
    }                                                                                  \
  } while (0)

struct thread_data
{
  struct workbench* wb;
  size_t index;
  struct run* total;
};

extern int
qsort_r(void* base,
        size_t nmemb,
        size_t size,
        int (*compar)(const void*, const void*, void*),
        void* arg);

static int
run_cmp(const void* a, const void* b, void* sort_by)
{
  int _sort_by;
  struct algorithm *alg_a, *alg_b;
  double counter_a, counter_b;

  alg_a = (struct algorithm*)a;
  alg_b = (struct algorithm*)b;

  _sort_by = *(int*)sort_by;

  if (!sorting(_sort_by)) {
    return strcmp(alg_a->name, alg_b->name);
  }

  counter_a = alg_a->run.counters[_sort_by];
  counter_b = alg_b->run.counters[_sort_by];

  return counter_a < counter_b ? -1 : counter_a > counter_b;
}

static void
print_row(char* name, struct run* run, char* format)
{
  char* fmt;

  if (strcmp(format, "human") == 0) {
    fmt = "%-16s %-16g %-16lu %-16lu %-16lu %-16lu %-16lu %s-%s\n";
  } else if (strcmp(format, "csv") == 0) {
    fmt = "%s,%g,%lu,%lu,%lu,%lu,%lu,%s,%s\n";
  } else {
    fmt = "%s %g %lu %lu %lu %lu %lu %s %s\n";
  }

  printf(fmt,
         name,
         run->counters[ELAPSED],
         (size_t)run->counters[COMPARISONS],
         (size_t)run->counters[SWAPS],
         (size_t)run->counters[RECURSIONS],
         (size_t)run->counters[ISORTS],
         (size_t)run->counters[HEAPSORTS],
         run->sorted == NULL ? TEST_UNTESTED : run->sorted,
         run->permuted == NULL ? TEST_UNTESTED : run->permuted);
}

static void
run_tests(struct workbench* wb, int* copy, struct run* run)
{
  struct test* test;

  for (test = wb->tests; test < wb->tests + wb->ntests; ++test) {
    if (test->type == SORTED) {
      run->sorted = array_is_sorted(copy, wb->array_length, cmp) ? TEST_OK : TEST_FAIL;
    } else if (test->type == PERMUTED) {
      run->permuted = array_is_permutation_of(copy, wb->array, wb->array_length, cmp)
                        ? TEST_OK
                        : TEST_FAIL;
    }
  }
}

static void
run_algorithm(struct workbench* wb, size_t i, struct run* total)
{
  int* copy;
  struct algorithm* alg = wb->algorithms + i;
  struct run* run = &alg->run;

  /* Make a copy of the array to be sorted. */
  copy = array_copy(wb->array, wb->array_length);

  /* Run the algorithm and measure the elapsed time. */
  run->counters[ELAPSED] = getms();
  alg->f(copy, wb->array_length, run->counters);
  run->counters[ELAPSED] = getms() - run->counters[ELAPSED];

  /* Sum the counters to the total row. */
  sum_counters(total->counters, run->counters);

  /* Run the tests. */
  run_tests(wb, copy, run);

  /* Print row containing the run results. */
  if (!sorting(wb->sort_by)) {
    print_row(alg->name, run, wb->format);
  }

  /* Free the copy. */
  free(copy);
}

static void*
run_algorithm_thread(void* arg)
{
  struct thread_data* data = (struct thread_data*)arg;
  run_algorithm(data->wb, data->index, data->total);
  pthread_exit(NULL);
}

void
wb_run(struct workbench* wb)
{
  struct run total = { 0 };
  pthread_t threads[wb->nalgorithms];
  struct thread_data thread_data[wb->nalgorithms];
  int pthread_result;

  /* Print the input array if the dump flag is set to true. */
  if (wb->dump_array) {
    printf("Input:\n");
    printf("%lu\n", wb->array_length);
    array_dump(wb->array, wb->array_length);
  }

  /* Print header containing the column names when using the human-readable format. */
  if (strcmp(wb->format, "human") == 0) {
    print_header();
  }

  /* Run the algorithms and print the results using threads. */
  for (size_t i = 0; i < wb->nalgorithms; ++i) {
    thread_data[i].wb = wb;
    thread_data[i].index = i;
    thread_data[i].total = &total;

    pthread_result =
      pthread_create(&threads[i], NULL, run_algorithm_thread, (void*)&thread_data[i]);
    if (pthread_result != 0) {
      fprintf(stderr, "Error creating thread %zu: %d\n", i, pthread_result);
      exit(EXIT_FAILURE);
    }
  }

  /* Wait for threads to finish. */
  for (size_t i = 0; i < wb->nalgorithms; ++i) {
    pthread_result = pthread_join(threads[i], NULL);
    if (pthread_result != 0) {
      fprintf(stderr, "Error joining thread %zu: %d\n", i, pthread_result);
      exit(EXIT_FAILURE);
    }
  }

  /* Print the sorted runs if the sort-by flag is set to a valid column. */
  if (sorting(wb->sort_by)) {
    qsort_r(
      wb->algorithms, wb->nalgorithms, sizeof(struct algorithm), run_cmp, &wb->sort_by);

    for (size_t i = 0; i < wb->nalgorithms; ++i) {
      print_row(wb->algorithms[i].name, &wb->algorithms[i].run, wb->format);
    }
  }

  if (strcmp(wb->format, "human") == 0) {
    print_hls(strlen(HEADER));
  }

  /* Print the total row. */
  print_row("Total", &total, wb->format);
}

void
wb_free(struct workbench* wb)
{
  free(wb->array);
}
