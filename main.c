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

extern char *strdup(const char *);

struct algorithm algorithms[] = {
    {"heapsort", heapsort},
    {"insertion_sort", insertion_sort},
    {"introsort", introsort},
    {"mergesort", mergesort},
    {"quicksort", quicksort},
    {"quicksort_std", quicksort_std},
    {"selection_sort", selection_sort},
    {"shellsort", shellsort},
    {"timsort", timsort},
    {NULL, NULL},
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

static struct algorithm *find_algorithm(const char *name)
{
    for (int i = 0; algorithms[i].name != NULL; i++)
    {
        if (strcmp(algorithms[i].name, name) == 0)
        {
            return &algorithms[i];
        }
    }
    return NULL;
}

static struct algorithm *select_algorithms(const char *input)
{
    char *input_copy = strdup(input);
    struct algorithm *selected_algorithms = malloc(sizeof(struct algorithm) * strlen(input) / 2);

    if (input_copy == NULL || selected_algorithms == NULL)
    {
        perror("Error de memoria");
        exit(1);
    }

    char *token = strtok(input_copy, ",");
    int count = 0;

    while (token != NULL)
    {
        struct algorithm *found_algorithm = find_algorithm(token);
        if (found_algorithm != NULL)
        {
            selected_algorithms[count] = *found_algorithm;
            count++;
        }
        token = strtok(NULL, ",");
    }

    struct algorithm null_algorithm = {NULL, NULL};
    selected_algorithms[count] = null_algorithm;

    free(input_copy);
    return selected_algorithms;
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

static void parse_args(int argc, char *argv[], struct table_flags *table_flags, struct algorithm **selected_algorithms)
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
            *selected_algorithms = select_algorithms(optarg);
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
        *selected_algorithms = algorithms;
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
    struct algorithm *selected_algorithms;

    parse_args(argc, argv, &table_flags, &selected_algorithms);
    length = array_from_stdin(&array);

    if (table_flags.dump_array)
    {
        printf("Input:\n");
        printf("%lu\n", length);
        array_dump(array, length);
    }

    counter_init(&counters);
    table_init(&table, &table_flags);

    struct algorithm *alg = selected_algorithms;
    while (alg->name)
    {
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
    free(selected_algorithms);
    table_free(&table);

    return EXIT_SUCCESS;
}
