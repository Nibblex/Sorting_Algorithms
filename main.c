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

struct test TESTS[] = {
    {"sorted", SORTED},
    {"permuted", PERMUTED},
    {NULL, 0},
};

#define get_choices(arr)                        \
    ({                                          \
        __typeof__(arr[0]) *_ptr = arr;         \
        char _formatted_str[512] = "";          \
        while (_ptr->name)                      \
        {                                       \
            strcat(_formatted_str, _ptr->name); \
            _ptr++;                             \
            if (_ptr->name)                     \
                strcat(_formatted_str, ",");    \
        }                                       \
        _formatted_str;                         \
    })

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

#define select_choices(arr, input)                                                                                  \
    ({                                                                                                              \
        char *token, *input_copy = strdup(input);                                                                   \
        __typeof__(arr[0]) *selected_choices = malloc(sizeof(__typeof__(arr[0])) * (count_commas(input_copy) + 2)); \
        if (selected_choices == NULL)                                                                               \
        {                                                                                                           \
            perror("Error de memoria");                                                                             \
            exit(EXIT_FAILURE);                                                                                     \
        }                                                                                                           \
        __typeof__(arr[0]) *choice;                                                                                 \
        int count = 0;                                                                                              \
        token = strtok(input_copy, ",");                                                                            \
        while (token != NULL)                                                                                       \
        {                                                                                                           \
            choice = find_choice(arr, token);                                                                       \
            if (choice != NULL)                                                                                     \
            {                                                                                                       \
                selected_choices[count] = *choice;                                                                  \
                count++;                                                                                            \
            }                                                                                                       \
            token = strtok(NULL, ",");                                                                              \
        }                                                                                                           \
        selected_choices[count] = (__typeof__(*selected_choices)){0};                                               \
        free(input_copy);                                                                                           \
        selected_choices;                                                                                           \
    })

static void usage(int exit_status)
{
    printf("Usage: sorter [options]\n");
    printf("Options: \n");

    /* Algorithm options */
    printf("  -a <algorithm1,algorithm2,...>, --algorithms <algorithm1,algorithm2,...>");
    printf("\t\t\t\t\t\t\t\tSpecify the algorithms to run \n");
    printf("\tAvailable algorithms: ");
    printf("%s\n", get_choices(ALGORITHMS));

    /* Test options */
    printf("  -t <test1,test2,...>, --tests <test1,test2,...>");
    printf("\t\t\t\t\t\t\t\t\t\t\tSpecify the tests to run \n");
    printf("\tAvailable tests: sorted, permuted \n");

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

static int count_commas(const char *s)
{
    int count = 0;

    for (int i = 0; s[i]; i++)
        if (s[i] == ',')
            count++;

    return count;
}

static int parse_format(char *input)
{
    if (strcmp(input, "csv") == 0)
    {
        return CSV;
    }

    return (strcmp(input, "human") == 0) ? HUMAN_READABLE : DEFAULT;
}

static void parse_args(int argc, char *argv[], struct workbench *wb)
{
    int c, option_index = 0;
    bool algorithms_flag = true;

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
            algorithms_flag = false;
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

    if (algorithms_flag)
    {
        wb->algorithms = select_choices(ALGORITHMS, get_choices(ALGORITHMS));
    }
}

int main(int argc, char *argv[])
{
    int *array = NULL;
    struct workbench wb = {0};

    parse_args(argc, argv, &wb);

    wb.array_length = array_from_stdin(&array);
    wb.array = array;

    workbench_run(&wb);
    workbench_free(&wb);

    return EXIT_SUCCESS;
}
