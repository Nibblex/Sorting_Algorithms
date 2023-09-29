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
    {"binsort", binsort, false},
    {"heapsort", heapsort, false},
    {"introsort", introsort, false},
    {"isort", isort, false},
    {"mergesort", mergesort, false},
    {"quicksort", quicksort, false},
    {"quicksort_std", quicksort_std, false},
    {"selection_sort", selection_sort, false},
    {"shellsort", shellsort, false},
    {"timsort", timsort, false},
    {NULL, NULL, false},
};

const struct test TESTS[] = {
    {"sorted", SORTED, false},
    {"permuted", PERMUTED, false},
    {NULL, 0, false},
};

#define enable_choice(arr, choice)                      \
    do                                                  \
    {                                                   \
        size_t arr_size = sizeof(arr) / sizeof(arr[0]); \
        for (size_t i = 0; i < arr_size; ++i)           \
        {                                               \
            if (strcmp(arr[i].name, choice) == 0)       \
            {                                           \
                arr[i].enabled = true;                  \
            }                                           \
        }                                               \
    } while (0)

#define enable_choices(arr, choices)   \
    do                                 \
    {                                  \
        char *token;                   \
        token = strtok(choices, ",");  \
        while (token != NULL)          \
        {                              \
            enable_choice(arr, token); \
            token = strtok(NULL, ","); \
        }                              \
    } while (0)

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
    char *alg_choices = NULL, *test_choices = NULL;

    struct option long_options[] = {
        {"algorithms", required_argument, 0, 'a'},
        {"tests", required_argument, 0, 't'},
        {"format", required_argument, 0, 'f'},
        {"sort-by", required_argument, 0, 's'},
        {"dump", no_argument, 0, 'd'},
        {"help", no_argument, 0, 'h'},
        {0, 0, 0, 0},
    };

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

    memcpy(wb->algorithms, ALGORITHMS, sizeof(ALGORITHMS));
    enable_choices(wb->algorithms, alg_choices == NULL ? strdup(ALG_CHOICES) : alg_choices);
    free(alg_choices);

    memcpy(wb->tests, TESTS, sizeof(TESTS));
    enable_choices(wb->tests, test_choices == NULL ? "" : test_choices);
    free(test_choices);
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
