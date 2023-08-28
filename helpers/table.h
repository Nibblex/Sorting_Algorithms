#ifndef _TABLE_H
#define _TABLE_H

#include "array_helpers.h"
#include "counter.h"

typedef enum test_result
{
    OK,
    FAIL,
    NOT_TESTED
} test_result;

struct record
{
    char *algorithm_name;
    double elapsed_time;
    struct counter counters;
    test_result sorted;
    test_result permuted;
};

struct table
{
    struct record *records;
    size_t count;
    size_t max_size;
};

void table_init(struct table *table, int max_size);

void table_add_record(struct table *table, char *algorithm_name, double elapsed_time, struct counter *counters, test_result sorted, test_result permuted);

void table_print(struct table *table);

void table_free(struct table *table);

#endif
