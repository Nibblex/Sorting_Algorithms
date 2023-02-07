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
    DUMP_ARRAY = 1,
    SORTED_TEST = 2,
    PERMUTATION_TEST = 4
};

char *func_names[FUNC_NUM] = {"timsort",
                              "mergesort",
                              "quicksort",
                              "quicksort_std",
                              "insertion_sort",
                              "selection_sort"};

func func_array[FUNC_NUM] = {&timsort,
                             &mergesort,
                             &quicksort,
                             &quicksort_std,
                             &insertion_sort,
                             &selection_sort};

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

static char *parse_args(int argc, char *argv[], int *sign_type, int *order_type, int *options)
{
    char *filepath = NULL;

    int c = 0;
    while ((c = getopt(argc, argv, "i:o:s:dtp")) != -1)
    {
        switch (c)
        {
        case 'i':
            filepath = strdup(optarg);
            break;
        case 'o':
            if (strcmp(optarg, "asc") == 0)
            {
                *order_type = ASC;
            }
            else if (strcmp(optarg, "desc") == 0)
            {
                *order_type = DESC;
            }
            else if (strcmp(optarg, "uns") == 0)
            {
                *order_type = UNSORTED;
            }
            else
            {
                exit(EXIT_FAILURE);
            }
            break;
        case 's':
            if (strcmp(optarg, "pos") == 0)
            {
                *sign_type = POS;
            }
            else if (strcmp(optarg, "neg") == 0)
            {
                *sign_type = NEG;
            }
            else if (strcmp(optarg, "both") == 0)
            {
                *sign_type = BOTH;
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

    return filepath;
}

int main(int argc, char *argv[])
{
    int *array = NULL, *copy = NULL;

    int sign_type = 0, order_type = 0, options = 0;

    unsigned int length, min, max;

    if (argc < 3)
    {
        usage(argv);
        exit(EXIT_FAILURE);
    }

    char *filepath = parse_args(argc, argv, &sign_type, &order_type, &options);
    if (filepath)
    {
        array = array_from_file(filepath);
        length = array_length_from_file(filepath);
    }
    else
    {

        length = (unsigned int)atoi(argv[1]);
        min = (unsigned int)atoi(argv[2]);
        max = (unsigned int)atoi(argv[3]);
        array = array_generator(length, min, max, order_type, sign_type);
    }

    double elapsed;
    printf("Algorithm:                Elapsed miliseconds:      Comparisons:              Swaps:\n");
    printf("-------------------------------------------------------------------------------------------\n");
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

        printf("%-25s %-25g %-25lu %-25lu %s %s\n", func_names[i], elapsed, cmp_counter, swap_counter,
               (options & SORTED_TEST) ? (array_is_sorted(copy, length) ? "sorted_test=OK" : "sorted_test=FAIL") : "",
               (options & PERMUTATION_TEST) ? (array_is_permutation_of(copy, array, length) ? "permutation_test=OK" : "permutation_test=FAIL") : "");

        free(copy);
    }

    free(array);

    return EXIT_SUCCESS;
}
