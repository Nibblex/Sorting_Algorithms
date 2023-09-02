#include <stdio.h>

#include "counter.h"

struct counter counters;

void counter_init(struct counter *c)
{
    c->cmp_counter = 0;
    c->swap_counter = 0;
    c->recursion_counter = 0;
    c->insertion_sort_counter = 0;
    c->heapsort_counter = 0;
}
