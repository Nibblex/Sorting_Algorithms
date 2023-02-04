#include <getopt.h>
#include <time.h>

#include "./helpers/array_helpers.h"
#include "./helpers/sort_helpers.h"

#define MAX_SIZE 100000
#define FUNC_NUM 9

typedef void (*func)(int a[], unsigned int length);

char *func_names[FUNC_NUM] = {"quicksort",
                              "quicksort_rp",
                              "quicksort_std",
                              "timsort",
                              "mergesort",
                              "insertion_sort",
                              "selection_sort",
                              "permutation_sort"};

func func_array[FUNC_NUM] = {&quicksort,
                             &quicksort_rp,
                             &quicksort_std,
                             &timsort,
                             &mergesort,
                             &insertion_sort,
                             &selection_sort,
                             &permutation_sort};

static double getMilliseconds(void)
{
    return 1000.0 * clock() / CLOCKS_PER_SEC;
}

static void print_help(char *program_name)
{
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path> [ OPTIONS ]\n\n"
           "Sort an array given in a file in disk.\n"
           "\n"
           "The input file must have the following format:\n"
           " * The first line must contain only a positive integer,"
           " which is the length of the array.\n"
           " * The second line must contain the members of the array"
           " separated by one or more spaces. Each member must be an integer."
           "\n\n"
           "In other words, the file format is:\n"
           "<amount of array elements>\n"
           "<array elem 1> <array elem 2> ... <array elem N>\n\n"
           "OPTIONS:\n-d dump the array on screen after running the sorting algorithm\n"
           "-s check if the array is sorted after running the algorithm\n"
           "-p check if the array is a permutation of the original one\n\n",
           program_name);
}

static char *parse_filepath(int argc, char *argv[])
{
    if (argc < 2)
    {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    return argv[1];
}

int main(int argc, char *argv[])
{
    double elapsed;
    /* create an array of MAX_SIZE elements and a copy, to do some checks later */
    int array[MAX_SIZE], copy[MAX_SIZE];

    bool dump_array = false, sorted_test = false, permutation_test = false;

    /* parse the filepath given in command line arguments */
    char *filepath = parse_filepath(argc, argv);

    /* parse the file to fill the array and obtain the actual length */
    unsigned int length = array_from_file(array, MAX_SIZE, filepath);

    int c = 0;
    while ((c = getopt(argc, argv, "dsp")) != -1)
    {
        switch (c)
        {
        case 'd':
            dump_array = true;
            break;
        case 's':
            sorted_test = true;
            break;
        case 'p':
            permutation_test = true;
            break;
        case '?':
            print_help(argv[0]);
            exit(EXIT_FAILURE);
            break;
        default:
            break;
        }
    }

    printf("Algorithm:                Elapsed miliseconds:      Comparisons:              Swaps:\n");
    printf("-------------------------------------------------------------------------------------------\n");
    for (unsigned int i = 0; i < FUNC_NUM; i++)
    {
        reset_counters;
        array_copy(copy, array, length);
        elapsed = getMilliseconds();
        func_array[i](copy, length);
        elapsed = getMilliseconds() - elapsed;

        if (dump_array)
        {
            array_dump(copy, length);
        }

        printf("%-25s %-25g %-25lu %-25lu %s %s\n", func_names[i], elapsed, cmp_counter, swap_counter,
               sorted_test ? (array_is_sorted(copy, length) ? "sorted_test=OK" : "sorted_test=FAIL") : "",
               permutation_test ? (array_is_permutation_of(copy, array, length) ? "permutation_test=OK" : "permutation_test=FAIL") : "");
    }

    return EXIT_SUCCESS;
}
