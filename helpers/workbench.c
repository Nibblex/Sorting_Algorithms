#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../helpers/array_helpers.h"
#include "workbench.h"

#define GETMS() (1000.0 * clock() / CLOCKS_PER_SEC)

#define TEST_NOT_TESTED "\x1b[33mNOT TESTED\x1b[0m"
#define TEST_OK "\x1b[32mOK\x1b[0m"
#define TEST_FAIL "\x1b[31mFAIL\x1b[0m"

#define PRINT_HLS(n)                     \
    do                                   \
    {                                    \
        for (size_t i = 0; i < (n); ++i) \
        {                                \
            putchar('-');                \
        }                                \
        putchar('\n');                   \
    } while (0)

struct counter counters;

static void print_header(void)
{
    char *header = "Algorithm:           Elapsed (ms):        Comparisons:         Swaps:               Recursions:          Insertion sort:           Heapsort:            Tests: (sorted-permuted)\n";
    PRINT_HLS(strlen(header));
    printf("%s", header);
    PRINT_HLS(strlen(header));
}

static void print_row(struct run *run, enum table_format format)
{
    char *fmt;

    switch (format)
    {
    case HUMAN_READABLE:
        fmt = "%-20s %-20g %-20lu %-20lu %-20lu %-25lu %-20lu %s-%s\n";
        break;
    case CSV:
        fmt = "%s,%g,%lu,%lu,%lu,%lu,%lu,%s,%s\n";
        break;
    default:
        fmt = "%s %g %lu %lu %lu %lu %lu %s %s\n";
        break;
    }

    printf(fmt,
           run->algorithm_name,
           run->elapsed,
           run->counters.cmp_counter,
           run->counters.swap_counter,
           run->counters.recursion_counter,
           run->counters.isort_counter,
           run->counters.heapsort_counter,
           run->sorted == NOT_TESTED ? TEST_NOT_TESTED : (run->sorted == OK ? TEST_OK : TEST_FAIL),
           run->permuted == NOT_TESTED ? TEST_NOT_TESTED : (run->permuted == OK ? TEST_OK : TEST_FAIL));
}

static void run_tests(struct workbench *wb, int *copy, struct run *run)
{
    struct test *test;

    test = wb->tests;
    while (test && test->name)
    {
        if (test->type == SORTED)
        {
            run->sorted = array_is_sorted(copy, wb->array_length) ? OK : FAIL;
        }
        else if (test->type == PERMUTED)
        {
            run->permuted = array_is_permutation_of(copy, wb->array, wb->array_length) ? OK : FAIL;
        }
        test++;
    }
}

static void run_algorithm(struct workbench *wb, struct algorithm *alg, int *copy)
{
    struct run run;

    run.algorithm_name = alg->name;

    /* Run the algorithm and measure the elapsed time. */
    run.elapsed = GETMS();
    alg->f(copy, wb->array_length);
    run.elapsed = GETMS() - run.elapsed;

    run.counters = counters;

    /* Add the run to the workbench. */
    wb->runs[wb->runs_count++] = run;
}

void workbench_init(struct workbench *wb, size_t num_algorithms)
{
    struct run *runs;

    runs = calloc(num_algorithms, sizeof(struct run));
    if (!runs)
    {
        perror("calloc");
        exit(EXIT_FAILURE);
    }

    wb->array = NULL;
    wb->array_length = 0;
    wb->algorithms = NULL;
    wb->tests = NULL;
    wb->runs = runs;
    wb->runs_count = 0;
    wb->num_algorithms = num_algorithms;
    wb->format = DEFAULT;
    wb->dump_array = false;
}

void workbench_run(struct workbench *wb)
{
    int *copy;
    struct algorithm *alg;

    /* Print the input array if the dump flag is set to true. */
    if (wb->dump_array)
    {
        printf("Input:\n");
        printf("%lu\n", wb->array_length);
        array_dump(wb->array, wb->array_length);
    }

    /* Print header containing the column names when using the human-readable format. */
    if (wb->format == HUMAN_READABLE)
    {
        print_header();
    }

    /* Run each algorithm and print the results. */
    for (size_t i = 0; i < wb->num_algorithms; ++i)
    {
        alg = &wb->algorithms[i];

        copy = array_copy(wb->array, wb->array_length);

        memset(&counters, 0, sizeof(struct counter));

        run_algorithm(wb, alg, copy);

        run_tests(wb, copy, &wb->runs[i]);

        print_row(&wb->runs[i], wb->format);

        free(copy);
    }
}

void workbench_free(struct workbench *wb)
{
    free(wb->array);
    free(wb->algorithms);
    free(wb->tests);
    free(wb->runs);
}
