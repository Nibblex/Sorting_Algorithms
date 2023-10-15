#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./helpers/array_helpers.h"
#include "./helpers/workbench.h"

extern char *strdup(const char *);

const char *ALG_CHOICES = "binsort,heapsort,introsort,isort,mergesort,quicksort,quicksort_std,selection_sort,shellsort,timsort";
const char *TEST_CHOICES = "sorted,permuted";

const struct algorithm ALGORITHMS[] = {
    {"binsort", binsort},
    {"heapsort", heapsort},
    {"introsort", introsort},
    {"isort", isort},
    {"mergesort", mergesort},
    {"quicksort", quicksort},
    {"quicksort_std", quicksort_std},
    {"selection_sort", selection_sort},
    {"shellsort", shellsort},
    {"timsort", timsort},
    {NULL, NULL},
};

const struct test TESTS[] = {
    {"sorted", SORTED},
    {"permuted", PERMUTED},
    {NULL, 0},
};

#define find_choice(arr, arr_size, choice)        \
    ({                                            \
        int _pos = -1;                            \
        for (size_t i = 0; i < arr_size; ++i)     \
        {                                         \
            if (strcmp(arr[i].name, choice) == 0) \
            {                                     \
                _pos = (int)i;                    \
                break;                            \
            }                                     \
        }                                         \
        _pos;                                     \
    })

#define enable_choices(arr, src, choices)               \
    ({                                                  \
        size_t nfound = 0;                              \
        size_t arr_size = sizeof(src) / sizeof(src[0]); \
        char *token = strtok(choices, ",");             \
        int pos;                                        \
        while (token != NULL)                           \
        {                                               \
            pos = find_choice(src, arr_size, token);    \
            if (pos != -1)                              \
            {                                           \
                arr[nfound++] = src[pos];               \
            }                                           \
            token = strtok(NULL, ",");                  \
        }                                               \
        nfound;                                         \
    })

static void usage(int exit_status)
{
    printf("Usage: sorter [options]\n");
    printf("Options: \n");

    /* Algorithm options */
    printf("  -a <algorithm1,algorithm2,...>, --algorithms <algorithm1,algorithm2,...>");
    printf("\t\t\t\t\t\t\t\tSpecify the algorithms to run \n");
    printf("\tAvailable algorithms: %s\n", ALG_CHOICES);

    /* Test options */
    printf("  -t <test1,test2,...>, --tests <test1,test2,...>");
    printf("\t\t\t\t\t\t\t\t\t\t\tSpecify the tests to run \n");
    printf("\tAvailable tests: %s\n", TEST_CHOICES);

    /* Format options */
    printf("  -f <format>, --format <format>");
    printf("\t\t\t\t\t\t\t\t\t\t\t\t\tSpecify the format of the output \n");
    printf("\tAvailable formats: human,csv,default \n");

    /* Sort by column option */
    printf("  -s <column>, --sort-by <column>");
    printf("\t\t\t\t\t\t\t\t\t\t\t\t\tSort the output by the given column \n");
    printf("\tAvailable columns: elapsed,cmp,swap,recursion,isort,heapsort \n");

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
    char *alg_choices = NULL;
    char *test_choices = NULL;

    struct option long_options[] = {
        {"algorithms", required_argument, 0, 'a'},
        {"tests", required_argument, 0, 't'},
        {"format", required_argument, 0, 'f'},
        {"sort-by", required_argument, 0, 's'},
        {"dump", no_argument, 0, 'd'},
        {"help", no_argument, 0, 'h'},
        {0, 0, 0, 0},
    };

    /* Default values */
    wb->format = "default";

    while ((c = getopt_long(argc, argv, "a:t:f:s:dh", long_options, &option_index)) != -1)
    {
        switch (c)
        {
        case 'a':
            alg_choices = strdup(optarg);
            break;
        case 't':
            test_choices = strdup(optarg);
            break;
        case 'f':
            wb->format = optarg;
            break;
        case 's':
            wb->sort_by = atoi(optarg);
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

    alg_choices = alg_choices == NULL ? strdup(ALG_CHOICES) : alg_choices;
    wb->nalgorithms = enable_choices(wb->algorithms, ALGORITHMS, alg_choices);
    free(alg_choices);

    test_choices = test_choices == NULL ? strdup("") : test_choices;
    wb->ntests = enable_choices(wb->tests, TESTS, test_choices);
    free(test_choices);
}

int main(int argc, char *argv[])
{
    struct workbench wb = {0};

    parse_args(argc, argv, &wb);

    wb.array_length = array_from_stdin(&wb.array);

    wb_run(&wb);
    wb_free(&wb);

    return EXIT_SUCCESS;
}
