#ifndef _TABLE_H
#define _TABLE_H

#include "array_helpers.h"
#include "counter.h"

#define PRINT_HLS(n)                     \
    do                                   \
    {                                    \
        for (size_t i = 0; i < (n); ++i) \
        {                                \
            putchar('-');                \
        }                                \
        putchar('\n');                   \
    } while (0)

typedef enum test_result
{
    OK,
    FAIL,
    NOT_TESTED
} test_result;

typedef enum table_format
{
    HUMAN_READABLE,
    CSV,
    DEFAULT
} table_format;

struct record
{
    char *algorithm_name;
    double elapsed_time;
    struct counter counters;
    test_result sorted;
    test_result permuted;
};

struct table_flags
{
    bool dump_array;
    bool sorted_test;
    bool permutation_test;
    table_format format;
};

struct table
{
    struct record *records;
    size_t count;
    size_t max_size;
    struct table_flags flags;
};

void table_init(struct table *table, struct table_flags *flags);

void table_add_record(struct table *table, char *algorithm_name, double elapsed_time, struct counter *counters, test_result sorted, test_result permuted);

void table_print(struct table *table);

void table_free(struct table *table);

#endif
