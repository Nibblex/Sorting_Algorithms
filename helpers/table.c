#include <stdio.h>
#include <stdlib.h>

#include "table.h"

void table_init(struct table *table, int max_size)
{
    table->records = (struct record *)malloc(max_size * sizeof(struct record));
    table->count = 0;
    table->max_size = max_size;
}

void table_add_record(struct table *table, char *algorithm_name, double elapsed_time, struct counter *counters, struct tests *tests)
{
    if (table->count == table->max_size)
    {
        // If the table is full, double its size
        table->max_size *= 2;
        table->records = realloc(table->records, table->max_size * sizeof(struct record));
    }

    // Add the new record to the table
    struct record new_record = {
        .algorithm_name = algorithm_name,
        .elapsed_time = elapsed_time,
        .counters = *counters,
        .tests = *tests,
    };

    table->records[table->count++] = new_record;

    counter_init(counters);
}

void table_print(struct table *table)
{
    struct record record;

    printf("Algorithm:           Elapsed (ms):        Comparisons:         Swaps:               Recursions:          Insertion sort:           Heapsort:            Tests: sorted/permutated\n");
    printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < table->count; i++)
    {
        record = table->records[i];
        printf("%-20s %-20g %-20lu %-20lu %-20lu %-25lu %-20lu %s/%s\n",
               record.algorithm_name,
               record.elapsed_time,
               record.counters.cmp_counter,
               record.counters.swap_counter,
               record.counters.recursion_counter,
               record.counters.insertion_sort_counter,
               record.counters.heapsort_counter,
               record.tests.sorted ? "OK" : "",
               record.tests.permutated ? "OK" : "");
    }
}

void table_free(struct table *table)
{
    free(table->records);
}
