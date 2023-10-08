#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../helpers/array_helpers.h"
#include "workbench.h"

#define GETMS() ((double)(clock() * 1000) / CLOCKS_PER_SEC)

#define HEADER "Algorithm:           Elapsed (ms):        Comparisons:         Swaps:               Recursions:          Insertion sort:           Heapsort:            Tests: (sorted-permuted)\n"

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

struct counter counters;

extern int qsort_r(void *base, size_t nmemb, size_t size,
                   int (*compar)(const void *, const void *, void *),
                   void *arg);

static void print_row(struct run *run, char *format)
{
    char *fmt;

    if (strcmp(format, "human") == 0)
    {
        fmt = "%-20s %-20g %-20lu %-20lu %-20lu %-25lu %-20lu %s-%s\n";
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
           run->elapsed,
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

    for (size_t i = 0; i < NUM_TESTS; ++i)
    {
        test = &wb->tests[i];

        if (test->type == SORTED && test->enabled)
        {
            run->sorted = array_is_sorted(copy, wb->array_length) ? TEST_OK : TEST_FAIL;
        }
        else if (test->type == PERMUTED && test->enabled)
        {
            run->permuted = array_is_permutation_of(copy, wb->array, wb->array_length) ? TEST_OK : TEST_FAIL;
        }
    }
}

static struct run run_algorithm(struct workbench *wb, struct algorithm *alg, int *copy)
{
    struct run run = {0};

    run.algorithm_name = alg->name;

    /* Run the algorithm and measure the elapsed time. */
    run.elapsed = GETMS();
    alg->f(copy, wb->array_length);
    run.elapsed = GETMS() - run.elapsed;

    run.counters = counters;

    return run;
}

static int run_cmp(const void *a, const void *b, void *sort_by)
{
    struct run *run_a = (struct run *)a;
    struct run *run_b = (struct run *)b;

    int _sort_by = *(int *)sort_by;

    switch (_sort_by)
    {
    case 2:
        return run_a->elapsed < run_b->elapsed ? -1 : run_a->elapsed > run_b->elapsed;
    case 3:
        return run_a->counters.cmp_counter < run_b->counters.cmp_counter ? -1 : run_a->counters.cmp_counter > run_b->counters.cmp_counter;
    case 4:
        return run_a->counters.swap_counter < run_b->counters.swap_counter ? -1 : run_a->counters.swap_counter > run_b->counters.swap_counter;
    case 5:
        return run_a->counters.recursion_counter < run_b->counters.recursion_counter ? -1 : run_a->counters.recursion_counter > run_b->counters.recursion_counter;
    case 6:
        return run_a->counters.isort_counter < run_b->counters.isort_counter ? -1 : run_a->counters.isort_counter > run_b->counters.isort_counter;
    case 7:
        return run_a->counters.heapsort_counter < run_b->counters.heapsort_counter ? -1 : run_a->counters.heapsort_counter > run_b->counters.heapsort_counter;
    default:
        return memcmp(run_a->algorithm_name, run_b->algorithm_name, strlen(run_a->algorithm_name));
    }

    return 0;
}

void workbench_run(struct workbench *wb)
{
    int *copy;
    size_t run_count = 0;
    struct algorithm *alg;
    struct run run, total = {0};

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

    /* Run each algorithm and print the results. */
    for (size_t i = 0; i < NUM_ALGORITHMS; ++i)
    {
        alg = &wb->algorithms[i];

        if (!alg->enabled) // Skip disabled algorithms.
        {
            continue;
        }

        /* Make a copy of the array to be sorted. */
        copy = array_copy(wb->array, wb->array_length);

        /* Reset the counters. */
        memset(&counters, 0, sizeof(struct counter));

        /* Run the algorithm. */
        run = run_algorithm(wb, alg, copy);

        /* Update the total row. */
        total.algorithm_name = "Total";
        total.elapsed += run.elapsed;
        total.counters.cmp_counter += run.counters.cmp_counter;
        total.counters.swap_counter += run.counters.swap_counter;
        total.counters.recursion_counter += run.counters.recursion_counter;
        total.counters.isort_counter += run.counters.isort_counter;
        total.counters.heapsort_counter += run.counters.heapsort_counter;

        /* Run the tests. */
        run_tests(wb, copy, &run);

        if (wb->sort_by == 0) // Print the row if not sorting.
        {
            print_row(&run, wb->format);
        }

        /* Add the run to the runs array. */
        wb->runs[run_count++] = run;

        /* Free the copy. */
        free(copy);
    }

    /* Sort the runs by the given column. */
    if (wb->sort_by != 0)
    {
        qsort_r(wb->runs, run_count, sizeof(struct run), run_cmp, &wb->sort_by);

        for (size_t i = 0; i < run_count; ++i)
        {
            print_row(&wb->runs[i], wb->format);
        }
    }

    /* Print the total row when using the human-readable format. */
    if (strcmp(wb->format, "human") == 0)
    {
        print_hls(strlen(HEADER));
        print_row(&total, wb->format);
    }
}

void workbench_free(struct workbench *wb)
{
    free(wb->array);
}
