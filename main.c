#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./helpers/array_helpers.h"
#include "./helpers/workbench.h"

extern char *strdup(const char *);

struct algorithm ALGORITHMS[] = {
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

const size_t NUM_ALGORITHMS = sizeof(ALGORITHMS) / sizeof(ALGORITHMS[0]) - 1;
const char *ALGORITHM_NAMES = "heapsort,insertion_sort,introsort,mergesort,quicksort,quicksort_std,selection_sort,shellsort,timsort";

struct test TESTS[] = {
    {"sorted", SORTED},
    {"permuted", PERMUTED},
    {NULL, 0},
};

const char *TEST_NAMES = "sorted,permuted";

#define find_choice(arr, token)                 \
    ({                                          \
        __typeof__(arr[0]) *_ptr, *_res = NULL; \
        for (_ptr = arr; _ptr->name; _ptr++)    \
        {                                       \
            if (strcmp(_ptr->name, token) == 0) \
            {                                   \
                _res = _ptr;                    \
                break;                          \
            }                                   \
        }                                       \
        _res;                                   \
    })

#define select_choices(arr, input)                                                                        \
    ({                                                                                                    \
        char *token, *input_copy = strdup(input);                                                         \
        __typeof__(arr[0]) *selected_choices = malloc(sizeof(__typeof__(arr[0])) * (NUM_ALGORITHMS + 1)); \
        if (selected_choices == NULL)                                                                     \
        {                                                                                                 \
            perror("Error de memoria");                                                                   \
            exit(EXIT_FAILURE);                                                                           \
        }                                                                                                 \
        __typeof__(arr[0]) *choice = NULL;                                                                \
        int count = 0;                                                                                    \
        token = strtok(input_copy, ",");                                                                  \
        while (token != NULL)                                                                             \
        {                                                                                                 \
            choice = find_choice(arr, token);                                                             \
            if (choice != NULL)                                                                           \
            {                                                                                             \
                selected_choices[count] = *choice;                                                        \
                count++;                                                                                  \
            }                                                                                             \
            token = strtok(NULL, ",");                                                                    \
        }                                                                                                 \
        selected_choices[count] = (__typeof__(*selected_choices)){0};                                     \
        free(input_copy);                                                                                 \
        selected_choices;                                                                                 \
    })

static int parse_format(char *input)
{
    if (strcmp(input, "csv") == 0)
    {
        return CSV;
    }

    return (strcmp(input, "human") == 0) ? HUMAN_READABLE : DEFAULT;
}

static void usage(int exit_status)
{
    printf("Usage: sorter [options]\n");
    printf("Options: \n");

    /* Algorithm options */
    printf("  -a <algorithm1,algorithm2,...>, --algorithms <algorithm1,algorithm2,...>");
    printf("\t\t\t\t\t\t\t\tSpecify the algorithms to run \n");
    printf("\tAvailable algorithms: ");
    printf("%s\n", ALGORITHM_NAMES);

    /* Test options */
    printf("  -t <test1,test2,...>, --tests <test1,test2,...>");
    printf("\t\t\t\t\t\t\t\t\t\t\tSpecify the tests to run \n");
    printf("\tAvailable tests: ");
    printf("%s\n", TEST_NAMES);

    /* Format options */
    printf("  -f <format>, --format <format>");
    printf("\t\t\t\t\t\t\t\t\t\t\t\t\tSpecify the format of the output \n");
    printf("\tAvailable formats: human, csv, default \n");

    /* Dump option */
    printf("  -d, --dump");
    printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tDump the input array to stdout \n");

    /* Help option */
    printf("  -h, --help");
    printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tPrint this help message \n");

    exit(exit_status);
}

static void parse_args(int argc, char *argv[], struct workbench *wb)
{
    int c, option_index = 0;

    struct option long_options[] = {
        {"algorithms", required_argument, 0, 'a'},
        {"tests", required_argument, 0, 't'},
        {"format", required_argument, 0, 'f'},
        {"dump", no_argument, 0, 'd'},
        {"help", no_argument, 0, 'h'},
        {0, 0, 0, 0},
    };

    while ((c = getopt_long(argc, argv, "a:t:f:dh", long_options, &option_index)) != -1)
    {
        switch (c)
        {
        case 'a':
            wb->algorithms = select_choices(ALGORITHMS, optarg);
            break;
        case 't':
            wb->tests = select_choices(TESTS, optarg);
            break;
        case 'f':
            wb->format = parse_format(optarg);
            break;
        case 'd':
            wb->dump_array = true;
            break;
        case 'h':
            usage(EXIT_SUCCESS);
            break;
        default:
            usage(EXIT_FAILURE);
        }
    }

    if (!wb->algorithms)
    {
        wb->algorithms = select_choices(ALGORITHMS, ALGORITHM_NAMES);
    }
}

int main(int argc, char *argv[])
{
    struct workbench wb = {0};

    parse_args(argc, argv, &wb);

    wb.array_length = array_from_stdin(&wb.array);

    workbench_run(&wb);
    workbench_free(&wb);

    return EXIT_SUCCESS;
}
