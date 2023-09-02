#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "./algorithms/algorithms.h"
#include "./helpers/array_helpers.h"
#include "./helpers/sort_helpers.h"
#include "./helpers/table.h"

#define GETMS() (1000.0 * clock() / CLOCKS_PER_SEC)

struct algorithm algorithms[] = {
    {"timsort", timsort, false},
    {"mergesort", mergesort, false},
    {"introsort", introsort, false},
    {"quicksort", quicksort, false},
    {"quicksort_std", quicksort_std, false},
    {"shellsort", shellsort, false},
    {"heapsort", heapsort, false},
    {"insertion_sort", insertion_sort, false},
    {"selection_sort", selection_sort, false},
    {NULL, NULL, false},
};

static void print_algorithms(struct algorithm *algorithms)
{
    struct algorithm *alg = algorithms;
    while (alg->name)
    {
        printf("%s", alg->name);
        alg++;
        if (alg->name)
        {
            printf(", ");
        }
    }
    printf("\n");
}

static void enable_algorithms(struct algorithm *algorithms, char *names)
{
    char *token;
    struct algorithm *alg;

    if (strcmp(names, "all") == 0)
    {
        alg = algorithms;
        while (alg->name)
        {
            alg->enabled = true;
            alg++;
        }
        return;
    }

    token = strtok(names, ",");
    while (token)
    {
        alg = algorithms;
        while (alg->name)
        {
            if (strcmp(alg->name, token) == 0)
            {
                alg->enabled = true;
                break;
            }
            alg++;
        }
        token = strtok(NULL, ",");
    }
}

static int parse_format(char *format)
{
    if (strcmp(format, "csv") == 0)
    {
        return CSV;
    }

    return (strcmp(format, "human") == 0) ? HUMAN_READABLE : DEFAULT;
}

static void usage(int exit_status)
{
    printf("Usage: sorter [options]\n");
    printf("Options: \n");
    printf("  -a <algorithm1,algorithm2,...>, --algorithms <algorithm1,algorithm2,...>  Specify the algorithms to test \n");
    printf("\tAvailable algorithms:\n\t");
    print_algorithms(algorithms);
    printf("  -d, --dump                                                                Dump the original array \n");
    printf("  -f <format>, --format <format>                                            Specify the output format, available formats: csv, human, default \n");
    printf("  -h, --help                                                                Print this help message \n");
    printf("  -s, --sorted                                                              Test if array is sorted \n");
    printf("  -p, --permutation                                                         Test if array is a permutation of the original array \n");
    exit(exit_status);
}

static void parse_args(int argc, char *argv[], struct table_flags *table_flags)
{
    int c, option_index = 0;
    bool algorithms_flag = true;

    struct option long_options[] = {
        {"algorithms", required_argument, 0, 'a'},
        {"dump", no_argument, 0, 'd'},
        {"format", required_argument, 0, 'f'},
        {"help", no_argument, 0, 'h'},
        {"sorted", no_argument, 0, 's'},
        {"permutation", no_argument, 0, 'p'},
        {0, 0, 0, 0},
    };

    while ((c = getopt_long(argc, argv, "a:df:hsp", long_options, &option_index)) != -1)
    {
        switch (c)
        {
        case 'a':
            algorithms_flag = false;
            enable_algorithms(algorithms, optarg);
            break;
        case 'd':
            table_flags->dump_array = true;
            break;
        case 'f':
            table_flags->format = parse_format(optarg);
            break;
        case 'h':
            usage(EXIT_SUCCESS);
            break;
        case 's':
            table_flags->sorted_test = true;
            break;
        case 'p':
            table_flags->permutation_test = true;
            break;
        default:
            usage(EXIT_FAILURE);
        }
    }

    if (algorithms_flag)
    {
        enable_algorithms(algorithms, "all");
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
    table_init(&table, &table_flags);

    struct algorithm *alg = algorithms;
    while (alg->name)
    {
        // Skip algorithms that are not selected
        if (!alg->enabled)
        {
            alg++;
            continue;
        }

        // Copy the array
        copy = array_copy(array, length);

        // Sort the copy and measure the time
        elapsed = GETMS();
        alg->f(copy, length);
        elapsed = GETMS() - elapsed;

        // Check if the array is sorted and if it is a permutation of the original array
        sorted = (table_flags.sorted_test) ? (array_is_sorted(copy, length) ? OK : FAIL) : NOT_TESTED;
        permuted = (table_flags.permutation_test) ? (array_is_permutation_of(array, copy, length) ? OK : FAIL) : NOT_TESTED;

        // Add the record to the table
        table_add_record(&table, alg->name, elapsed, &counters, sorted, permuted);

        // Free the copy
        free(copy);

        // Next algorithm
        alg++;
    }

    table_print(&table);

    free(array);
    table_free(&table);

    return EXIT_SUCCESS;
}
