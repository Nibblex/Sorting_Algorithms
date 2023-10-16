#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "array_helpers.h"
#include "workbench.h"

#define GETMS() ((double)(clock() * 1000) / CLOCKS_PER_SEC)

#define HEADER "Algorithm        Elapsed (ms)     Comparisons      Swaps            Recursions       Isorts           Heapsort         Tests (sorted-permuted)\n"

#define TEST_UNTESTED "\x1b[33mUNTESTED\x1b[0m"
#define TEST_OK "\x1b[32mOK\x1b[0m"
#define TEST_FAIL "\x1b[31mFAIL\x1b[0m"

#define print_hls(n)                     \
    do                                   \
    {                                    \
        for (size_t i = 0; i < (n); ++i) \
        {                                \
            putchar('-');                \
        }                                \
        putchar('\n');                   \
    } while (0)

#define print_header()             \
    do                             \
    {                              \
        print_hls(strlen(HEADER)); \
        printf("%s", HEADER);      \
        print_hls(strlen(HEADER)); \
    } while (0)

struct thread_data
{
    struct workbench *wb;
    size_t index;
    struct run *runs;
};

extern int qsort_r(void *base, size_t nmemb, size_t size,
                   int (*compar)(const void *, const void *, void *),
                   void *arg);

static int run_cmp(const void *a, const void *b, void *sort_by)
{
    int _sort_by;
    struct run *run_a, *run_b;
    struct counter counters_a, counters_b;

    run_a = (struct run *)a;
    run_b = (struct run *)b;

    counters_a = run_a->counters;
    counters_b = run_b->counters;

    _sort_by = *(int *)sort_by;

    switch (_sort_by)
    {
    case 2:
        return counters_a.elapsed < counters_b.elapsed ? -1 : counters_a.elapsed > counters_b.elapsed;
    case 3:
        return counters_a.cmp_counter < counters_b.cmp_counter ? -1 : counters_a.cmp_counter > counters_b.cmp_counter;
    case 4:
        return counters_a.swap_counter < counters_b.swap_counter ? -1 : counters_a.swap_counter > counters_b.swap_counter;
    case 5:
        return counters_a.recursion_counter < counters_b.recursion_counter ? -1 : counters_a.recursion_counter > counters_b.recursion_counter;
    case 6:
        return counters_a.isort_counter < counters_b.isort_counter ? -1 : counters_a.isort_counter > counters_b.isort_counter;
    case 7:
        return counters_a.heapsort_counter < counters_b.heapsort_counter ? -1 : counters_a.heapsort_counter > counters_b.heapsort_counter;
    default:
        return memcmp(run_a->algorithm_name, run_b->algorithm_name, strlen(run_a->algorithm_name));
    }

    return 0;
}

static void print_row(struct run *run, char *format)
{
    char *fmt;

    if (strcmp(format, "human") == 0)
    {
        fmt = "%-16s %-16g %-16lu %-16lu %-16lu %-16lu %-16lu %s-%s\n";
    }
    else if (strcmp(format, "csv") == 0)
    {
        fmt = "%s,%g,%lu,%lu,%lu,%lu,%lu,%s,%s\n";
    }
    else
    {
        fmt = "%s %g %lu %lu %lu %lu %lu %s %s\n";
    }

    printf(fmt,
           run->algorithm_name,
           run->counters.elapsed,
           run->counters.cmp_counter,
           run->counters.swap_counter,
           run->counters.recursion_counter,
           run->counters.isort_counter,
           run->counters.heapsort_counter,
           run->sorted == NULL ? TEST_UNTESTED : run->sorted,
           run->permuted == NULL ? TEST_UNTESTED : run->permuted);
}

static void run_tests(struct workbench *wb, int *copy, struct run *run)
{
    struct test *test;

    for (test = wb->tests; test < wb->tests + wb->ntests; ++test)
    {
        if (test->type == SORTED)
        {
            run->sorted = array_is_sorted(copy, wb->array_length) ? TEST_OK : TEST_FAIL;
        }
        else if (test->type == PERMUTED)
        {
            run->permuted = array_is_permutation_of(copy, wb->array, wb->array_length) ? TEST_OK : TEST_FAIL;
        }
    }
}

static void sum_counters(struct counter *a, struct counter *b)
{
    a->elapsed += b->elapsed;
    a->cmp_counter += b->cmp_counter;
    a->swap_counter += b->swap_counter;
    a->recursion_counter += b->recursion_counter;
    a->isort_counter += b->isort_counter;
    a->heapsort_counter += b->heapsort_counter;
}

static void run_algorithm(struct workbench *wb, size_t i, struct run *runs)
{
    int *copy;
    struct algorithm *alg = wb->algorithms + i;
    struct run *run = runs + i;
    struct run *total = runs + wb->nalgorithms;

    run->algorithm_name = alg->name;

    /* Make a copy of the array to be sorted. */
    copy = array_copy(wb->array, wb->array_length);

    /* Run the algorithm and measure the elapsed time. */
    run->counters.elapsed = GETMS();
    alg->f(copy, wb->array_length, &run->counters);
    run->counters.elapsed = GETMS() - run->counters.elapsed;

    /* Sum the counters to the total row. */
    total->algorithm_name = "Total";
    sum_counters(&total->counters, &run->counters);

    /* Run the tests. */
    run_tests(wb, copy, run);

    /* Print the row if the sort-by flag is set to 0. */
    if (wb->sort_by == 0)
    {
        print_row(run, wb->format);
    }

    /* Free the copy. */
    free(copy);
}

static void *run_algorithm_thread(void *arg)
{
    struct thread_data *data = (struct thread_data *)arg;
    run_algorithm(data->wb, data->index, data->runs);
    pthread_exit(NULL);
}

void wb_run(struct workbench *wb)
{
    struct run runs[wb->nalgorithms + 1]; /* +1 for the total row. */
    pthread_t threads[wb->nalgorithms];
    struct thread_data thread_data[wb->nalgorithms];
    int pthread_result;

    /* Print the input array if the dump flag is set to true. */
    if (wb->dump_array)
    {
        printf("Input:\n");
        printf("%lu\n", wb->array_length);
        array_dump(wb->array, wb->array_length);
    }

    /* Print header containing the column names when using the human-readable format. */
    if (strcmp(wb->format, "human") == 0)
    {
        print_header();
    }

    /* Initialize the runs array. */
    memset(runs, 0, sizeof(runs));

    /* Run the algorithms and print the results using threads. */
    for (size_t i = 0; i < wb->nalgorithms; ++i)
    {
        thread_data[i].wb = wb;
        thread_data[i].index = i;
        thread_data[i].runs = runs;

        pthread_result = pthread_create(&threads[i], NULL, run_algorithm_thread, (void *)&thread_data[i]);
        if (pthread_result != 0)
        {
            fprintf(stderr, "Error creating thread %zu: %d\n", i, pthread_result);
            exit(EXIT_FAILURE);
        }
    }

    /* Wait for threads to finish. */
    for (size_t i = 0; i < wb->nalgorithms; ++i)
    {
        pthread_result = pthread_join(threads[i], NULL);
        if (pthread_result != 0)
        {
            fprintf(stderr, "Error joining thread %zu: %d\n", i, pthread_result);
            exit(EXIT_FAILURE);
        }
    }

    /* Print the sorted runs if the sort-by flag is set to a valid column. */
    if (wb->sort_by != 0)
    {
        qsort_r(runs, wb->nalgorithms, sizeof(struct run), run_cmp, &wb->sort_by);

        for (size_t i = 0; i < wb->nalgorithms; ++i)
        {
            print_row(runs + i, wb->format);
        }
    }

    if (strcmp(wb->format, "human") == 0)
    {
        print_hls(strlen(HEADER));
    }

    /* Print the total row. */
    print_row(runs + wb->nalgorithms, wb->format);
}

void wb_free(struct workbench *wb)
{
    free(wb->array);
}
