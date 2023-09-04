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

static void print_record(struct workbench *wb)
{
    struct run run = wb->last_run;
    char *fmt;

    switch (wb->format)
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
           run.algorithm_name,
           run.elapsed,
           run.counters.cmp_counter,
           run.counters.swap_counter,
           run.counters.recursion_counter,
           run.counters.isort_counter,
           run.counters.heapsort_counter,
           run.sorted == NOT_TESTED ? TEST_NOT_TESTED : (run.sorted == OK ? TEST_OK : TEST_FAIL),
           run.permuted == NOT_TESTED ? TEST_NOT_TESTED : (run.permuted == OK ? TEST_OK : TEST_FAIL));
}

static void run_tests(struct workbench *wb, int *copy)
{
    struct test *test;

    test = wb->tests;
    while (test && test->name)
    {
        if (test->type == SORTED)
        {
            wb->last_run.sorted = array_is_sorted(copy, wb->array_length) ? OK : FAIL;
        }
        else if (test->type == PERMUTED)
        {
            wb->last_run.permuted = array_is_permutation_of(copy, wb->array, wb->array_length) ? OK : FAIL;
        }
        test++;
    }
}

static void run_algorithm(struct workbench *wb, struct algorithm *alg, int *copy)
{
    wb->last_run.algorithm_name = alg->name;

    wb->last_run.elapsed = GETMS();
    alg->f(copy, wb->array_length);
    wb->last_run.elapsed = GETMS() - wb->last_run.elapsed;

    wb->last_run.counters = counters;
}

void workbench_run(struct workbench *wb)
{
    int *copy;
    struct algorithm *alg;

    if (wb->dump_array)
    {
        printf("Input:\n");
        printf("%lu\n", wb->array_length);
        array_dump(wb->array, wb->array_length);
    }

    if (wb->format == HUMAN_READABLE)
    {
        print_header();
    }

    alg = wb->algorithms;
    while (alg->name)
    {
        copy = array_copy(wb->array, wb->array_length);

        memset(&counters, 0, sizeof(struct counter));

        run_algorithm(wb, alg, copy);
        run_tests(wb, copy);
        print_record(wb);

        free(copy);

        alg++;
    }
}

void workbench_free(struct workbench *wb)
{
    free(wb->array);
    free(wb->algorithms);
    free(wb->tests);
}
