#include <getopt.h>
#include <string.h>
#include <time.h>

#include "./helpers/array_helpers.h"

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

static void usage(char *argv[])
{
    printf("Usage: %s <filepath> [options]\n", argv[0]);
    printf("Options: \n");
    printf("  -d               Dump the array \n");
    printf("  -s               Test if array is sorted \n");
    printf("  -p               Test if array is a permutation of the original array \n");
}

static char *parse_args(int argc, char *argv[], int *options)
{
    char *filepath = NULL;

    if (argc < 2)
    {
        usage(argv);
        exit(EXIT_FAILURE);
    }

    filepath = argv[1];

    int c = 0;
    while ((c = getopt(argc, argv, "dsp")) != -1)
    {
        switch (c)
        {
        case 'd':
            *options |= DUMP_ARRAY;
            break;
        case 's':
            *options |= SORTED_TEST;
            break;
        case 'p':
            *options |= PERMUTATION_TEST;
            break;
        default:
            usage(argv);
            break;
        }
    }

    return filepath;
}

int main(int argc, char *argv[])
{
    int *array = NULL, *copy = NULL;
    int length, options = 0;

    char *filepath = parse_args(argc, argv, &options);
    printf("Filepath: %s\n", filepath);
    length = array_length_from_file(filepath);
    array = array_from_file(length, filepath);

    if (options & DUMP_ARRAY)
    {
        printf("Original array: \n\n");
        array_dump(array, length);
    }

    double elapsed;
    printf("Algorithm:           Elapsed (ms):        Comparisons:         Swaps:               Recursions:          Insertion sort:           Heapsort:\n");
    printf("--------------------------------------------------------------------------------------------------------------------------------------------\n");
    for (unsigned int i = 0; i < FUNC_NUM; i++)
    {
        reset_counters;
        copy = array_copy(array, length);
        elapsed = getMilliseconds();
        func_array[i](copy, length);
        elapsed = getMilliseconds() - elapsed;

        if (options & DUMP_ARRAY)
        {
            array_dump(copy, length);
        }

        printf("%-20s %-20g %-20lu %-20lu %-20lu %-25lu %-25lu %s %s\n",
               func_names[i],
               elapsed,
               cmp_counter,
               swap_counter,
               recursion_counter,
               insertion_sort_counter,
               heapsort_counter,
               (options & SORTED_TEST) ? (array_is_sorted(copy, length) ? "sorted_test=OK" : "sorted_test=FAIL") : "",
               (options & PERMUTATION_TEST) ? (array_is_permutation_of(copy, array, length) ? "permutation_test=OK" : "permutation_test=FAIL") : "");

        free(copy);
    }

    free(array);

    return EXIT_SUCCESS;
}
