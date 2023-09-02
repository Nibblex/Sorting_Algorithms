#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "./algorithms/algorithms.h"
#include "./helpers/array_helpers.h"
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

#define print_choices(arr)              \
    do                                  \
    {                                   \
        __typeof__(arr[0]) *_ptr = arr; \
        while (_ptr->name)              \
        {                               \
            printf("%s", _ptr->name);   \
            _ptr++;                     \
            if (_ptr->name)             \
            {                           \
                printf(", ");           \
            }                           \
        }                               \
        printf("\n");                   \
    } while (0)

#define find_choice(arr, choice)                     \
    ({                                               \
        __typeof__(arr[0]) *_ptr, *_res = NULL;      \
        for (_ptr = arr; _ptr->name != NULL; _ptr++) \
        {                                            \
            if (strcmp(_ptr->name, choice) == 0)     \
            {                                        \
                _res = _ptr;                         \
                break;                               \
            }                                        \
        }                                            \
        _res;                                        \
    })

#define select_choices(arr, input)                                                                     \
    ({                                                                                                 \
        char *token;                                                                                   \
        __typeof__(arr[0]) *selected_choices = malloc(sizeof(__typeof__(arr[0])) * strlen(input) / 2); \
        if (selected_choices == NULL)                                                                  \
        {                                                                                              \
            perror("Error de memoria");                                                                \
            exit(EXIT_FAILURE);                                                                        \
        }                                                                                              \
        __typeof__(arr[0]) *choice;                                                                    \
        int count = 0;                                                                                 \
        token = strtok(input, ",");                                                                    \
        while (token != NULL)                                                                          \
        {                                                                                              \
            choice = find_choice(arr, token);                                                          \
            if (choice != NULL)                                                                        \
            {                                                                                          \
                selected_choices[count] = *choice;                                                     \
                count++;                                                                               \
            }                                                                                          \
            token = strtok(NULL, ",");                                                                 \
        }                                                                                              \
        selected_choices[count] = (__typeof__(*selected_choices)){NULL, NULL};                         \
        selected_choices;                                                                              \
    })

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
    print_choices(algorithms);
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
            *selected_algorithms = select_choices(algorithms, optarg);
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
