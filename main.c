#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "./algorithms/algorithms.h"
#include "./helpers/array_helpers.h"
#include "./helpers/sort_helpers.h"
#include "./helpers/table.h"

#define FUNC_NUM 9

struct algorithm algorithms[FUNC_NUM] = {
    {"timsort", timsort},
    {"mergesort", mergesort},
    {"introsort", introsort},
    {"quicksort", quicksort},
    {"quicksort_std", quicksort_std},
    {"shellsort", shellsort},
    {"heapsort", heapsort},
    {"insertion_sort", insertion_sort},
    {"selection_sort", selection_sort},
};

enum options
{
    DUMP_ARRAY = 1,
    SORTED_TEST = 2,
    PERMUTATION_TEST = 4
};

static double getms(void)
{
    return 1000.0 * clock() / CLOCKS_PER_SEC;
}

static void usage(void)
{
    printf("Usage: sorter [options]\n");
    printf("Options: \n");
    printf("  -d               Dump the array \n");
    printf("  -s               Test if array is sorted \n");
    printf("  -p               Test if array is a permutation of the original array \n");
}

static int parse_args(int argc, char *argv[])
{
    int opt = 0, options = 0;

    while ((opt = getopt(argc, argv, "dsp")) != -1)
    {
        switch (opt)
        {
        case 'd':
            options |= DUMP_ARRAY;
            break;
        case 's':
            options |= SORTED_TEST;
            break;
        case 'p':
            options |= PERMUTATION_TEST;
            break;
        default:
            usage();
            exit(EXIT_FAILURE);
        }
    }

    return options;
}

int main(int argc, char *argv[])
{
    int *array = NULL, *copy = NULL;
    int options;
    size_t length;
    struct table table;

    length = array_from_stdin(&array);
    printf("Array length: %lu\n", length);

    options = parse_args(argc, argv);
    if (options & DUMP_ARRAY)
    {
        printf("Original array:\n");
        array_dump(array, length);
    }

    double elapsed;

    counter_init(&counters);
    table_init(&table, FUNC_NUM);

    for (size_t i = 0; i < FUNC_NUM; i++)
    {
        struct algorithm algorithm = algorithms[i];
        struct tests tests;

        copy = array_copy(array, length);
        elapsed = getms();
        algorithm.f(copy, length);
        elapsed = getms() - elapsed;

        tests.sorted = (options & SORTED_TEST) && array_is_sorted(copy, length);
        tests.permutated = (options & PERMUTATION_TEST) && array_is_permutation_of(copy, array, length);
        table_add_record(&table, algorithm.name, elapsed, &counters, &tests);

        free(copy);
    }

    table_print(&table);

    free(array);
    table_free(&table);

    return EXIT_SUCCESS;
}
