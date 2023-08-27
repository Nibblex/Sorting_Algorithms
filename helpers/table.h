#ifndef _TABLE_H_
#define _TABLE_H_

#include "array_helpers.h"
#include "counter.h"

struct record
{
    char *algorithm_name;
    double elapsed_time;
    struct counter counters;
    struct tests tests;
};

struct table
{
    struct record *records;
    int count;
    int max_size;
};

void table_init(struct table *table, int max_size);

void table_add_record(struct table *table, char *algorithm_name, double elapsed_time, struct counter *counters, struct tests *tests);

void table_print(struct table *table);

void table_free(struct table *table);

#endif
