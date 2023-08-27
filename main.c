#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "./helpers/array_helpers.h"
#include "./helpers/sort_helpers.h"

#define FUNC_NUM 9

typedef void (*func)(int a[], unsigned int length);

enum options
{
    DUMP_ARRAY = 1,
    SORTED_TEST = 2,
    PERMUTATION_TEST = 4
};

char *func_names[FUNC_NUM] = {"timsort",
                              "mergesort",
                              "introsort",
                              "quicksort",
                              "quicksort_std",
                              "shellsort",
                              "heapsort",
                              "insertion_sort",
                              "selection_sort"};

func func_array[FUNC_NUM] = {timsort,
                             mergesort,
                             introsort,
                             quicksort,
                             quicksort_std,
                             shellsort,
                             heapsort,
                             insertion_sort,
                             selection_sort};

static double getMilliseconds(void)
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
    unsigned long int length;

    length = array_from_stdin(&array);
    printf("Array length: %lu\n", length);

    options = parse_args(argc, argv);
    if (options & DUMP_ARRAY)
    {
        printf("Original array:\n");
        array_dump(array, length);
    }

    double elapsed;
    printf("Algorithm:           Elapsed (ms):        Comparisons:         Swaps:               Recursions:          Insertion sort:           Heapsort:\n");
    printf("--------------------------------------------------------------------------------------------------------------------------------------------\n");
    for (unsigned int i = 0; i < FUNC_NUM; i++)
    {
        counter_init(&counters);

        copy = array_copy(array, length);
        elapsed = getMilliseconds();
        func_array[i](copy, length);
        elapsed = getMilliseconds() - elapsed;

        printf("%-20s %-20g %-20lu %-20lu %-20lu %-25lu %-25lu %s %s\n",
               func_names[i],
               elapsed,
               counters.cmp_counter,
               counters.swap_counter,
               counters.recursion_counter,
               counters.insertion_sort_counter,
               counters.heapsort_counter,
               (options & SORTED_TEST) ? (array_is_sorted(copy, length) ? "sorted_test=OK" : "sorted_test=FAIL") : "",
               (options & PERMUTATION_TEST) ? (array_is_permutation_of(copy, array, length) ? "permutation_test=OK" : "permutation_test=FAIL") : "");

        if (options & DUMP_ARRAY)
        {
            array_dump(copy, length);
        }

        free(copy);
    }

    free(array);

    return EXIT_SUCCESS;
}
