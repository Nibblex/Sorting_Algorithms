#include <getopt.h>
#include <string.h>
#include <time.h>

#include "./helpers/array_helpers.h"
#include "./helpers/sort_helpers.h"

#include "array_gen.h"

#define FUNC_NUM 6

typedef void (*func)(int a[], unsigned int length);

enum options
{
    DUMP_ARRAY = 64,
    SORTED_TEST = 128,
    PERMUTATION_TEST = 256
};

char *func_names[FUNC_NUM] = {"timsort",
                              "mergesort",
                              "quicksort",
                              "quicksort_std",
                              "insertion_sort",
                              "selection_sort"};

func func_array[FUNC_NUM] = {timsort,
                             mergesort,
                             quicksort,
                             quicksort_std,
                             insertion_sort,
                             selection_sort};

static double getMilliseconds(void)
{
    return 1000.0 * clock() / CLOCKS_PER_SEC;
}

static void usage(char *argv[])
{
    printf("Usage: %s <length> <min> <max> [options] \n", argv[0]);
    printf("Options: \n");
    printf("  -i <filepath>    Read array from file \n");
    printf("  -o <order>       Order of the array: asc, desc, uns \n");
    printf("  -s <sign>        Sign of the elements: pos, neg, both \n");
    printf("  -d               Dump array \n");
    printf("  -t               Test sorted array is sorted \n");
    printf("  -p               Test permutation array is permutation of original \n");
}

static char *parse_args(int argc, char *argv[], unsigned int *length, unsigned int *min, unsigned int *max, int *options)
{
    char *filepath = NULL;

    if (argc >= 4)
    {
        *length = (unsigned int)atoi(argv[1]);
        *min = (unsigned int)atoi(argv[2]);
        *max = (unsigned int)atoi(argv[3]);
        printf("Length: %u, Min: %u, Max: %u\n", *length, *min, *max);
    }

    int c = 0;
    while ((c = getopt(argc, argv, "i:o:s:dtp")) != -1)
    {
        switch (c)
        {
        case 'i':
            filepath = optarg;
            break;
        case 'o':
            if (strcmp(optarg, "asc") == 0)
            {
                *options |= ASC;
            }
            else if (strcmp(optarg, "desc") == 0)
            {
                *options |= DESC;
            }
            else if (strcmp(optarg, "uns") == 0)
            {
                *options |= UNSORTED;
            }
            else
            {
                usage(argv);
                exit(EXIT_FAILURE);
            }
            break;
        case 's':
            if (strcmp(optarg, "pos") == 0)
            {
                *options |= POS;
            }
            else if (strcmp(optarg, "neg") == 0)
            {
                *options |= NEG;
            }
            else if (strcmp(optarg, "both") == 0)
            {
                *options |= BOTH;
            }
            else
            {
                usage(argv);
                exit(EXIT_FAILURE);
            }
            break;
        case 'd':
            *options |= DUMP_ARRAY;
            break;
        case 't':
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

    if (filepath && (*options & (ASC | DESC | UNSORTED | POS | NEG | BOTH)))
    {
        usage(argv);
        exit(EXIT_FAILURE);
    }

    return filepath;
}

int main(int argc, char *argv[])
{
    int *array = NULL, *copy = NULL;

    int options = 0;

    unsigned int length = 0, min = 0, max = 0;

    char *filepath = parse_args(argc, argv, &length, &min, &max, &options);
    if (filepath)
    {
        printf("Filepath: %s\n", filepath);
        length = array_length_from_file(filepath);
        array = array_from_file(length, filepath);
    }
    else
    {
        array = array_generator(length, min, max, options);
    }

    double elapsed;
    printf("Algorithm:                Elapsed miliseconds:      Comparisons:              Swaps:                    Total:\n");
    printf("--------------------------------------------------------------------------------------------------------------\n");
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

        printf("%-25s %-25g %-25lu %-25lu %-25lu %s %s\n", func_names[i], elapsed, cmp_counter, swap_counter, cmp_counter + swap_counter,
               (options & SORTED_TEST) ? (array_is_sorted(copy, length) ? "sorted_test=OK" : "sorted_test=FAIL") : "",
               (options & PERMUTATION_TEST) ? (array_is_permutation_of(copy, array, length) ? "permutation_test=OK" : "permutation_test=FAIL") : "");

        free(copy);
    }

    free(array);

    return EXIT_SUCCESS;
}
