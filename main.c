#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "./algorithms/algorithms.h"
#include "./helpers/array_helpers.h"
#include "./helpers/sort_helpers.h"
#include "./helpers/table.h"

#define FUNC_NUM 9

#define GETMS() (1000.0 * clock() / CLOCKS_PER_SEC)

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

static void usage(void)
{
    printf("Usage: sorter [options]\n");
    printf("Options: \n");
    printf("  -d, --dump       Dump the original array \n");
    printf("  -s, --sorted     Test if array is sorted \n");
    printf("  -p, --permutation Test if array is a permutation of the original array \n");
    printf("  -f, --format     Output format (human, csv) \n");
    printf("  -h, --help       Print this help message \n");
}

static int get_format(char *format)
{
    if (strcmp(format, "csv") == 0)
    {
        return CSV;
    }
    else if (strcmp(format, "human") == 0)
    {
        return HUMAN_READABLE;
    }

    return DEFAULT;
}

static void parse_args(int argc, char *argv[], struct table_flags *table_flags)
{
    int c, option_index = 0;

    struct option long_options[] = {
        {"dump", no_argument, 0, 'd'},
        {"sorted", no_argument, 0, 's'},
        {"permutation", no_argument, 0, 'p'},
        {"format", required_argument, 0, 'f'},
        {"help", no_argument, 0, 'h'},
        {0, 0, 0, 0},
    };

    while ((c = getopt_long(argc, argv, "dspf:h", long_options, &option_index)) != -1)
    {
        switch (c)
        {
        case 'd':
            table_flags->dump_array = true;
            break;
        case 's':
            table_flags->sorted_test = true;
            break;
        case 'p':
            table_flags->permutation_test = true;
            break;
        case 'f':
            table_flags->format = get_format(optarg);
            break;
        case 'h':
            usage();
            exit(EXIT_SUCCESS);
        default:
            usage();
            exit(EXIT_FAILURE);
        }
    }
}

int main(int argc, char *argv[])
{
    int *array = NULL, *copy = NULL;
    size_t length;
    double elapsed;
    extern struct counter counters;
    test_result sorted, permuted;
    struct table_flags table_flags = {false, false, false, DEFAULT};
    struct table table;

    parse_args(argc, argv, &table_flags);
    length = array_from_stdin(&array);

    if (table_flags.dump_array)
    {
        printf("Input:\n");
        printf("%lu\n", length);
        array_dump(array, length);
    }

    counter_init(&counters);
    table_init(&table, &table_flags, FUNC_NUM);

    for (size_t i = 0; i < table.max_size; i++)
    {
        // Copy the array
        copy = array_copy(array, length);

        // Sort the copy and measure the time
        elapsed = GETMS();
        algorithms[i].f(copy, length);
        elapsed = GETMS() - elapsed;

        // Check if the array is sorted and if it is a permutation of the original array
        sorted = (table_flags.sorted_test) ? (array_is_sorted(copy, length) ? OK : FAIL) : NOT_TESTED;
        permuted = (table_flags.permutation_test) ? (array_is_permutation_of(array, copy, length) ? OK : FAIL) : NOT_TESTED;

        // Add the record to the table
        table_add_record(&table, algorithms[i].name, elapsed, &counters, sorted, permuted);

        // Free the copy
        free(copy);
    }

    table_print(&table);

    free(array);
    table_free(&table);

    return EXIT_SUCCESS;
}
