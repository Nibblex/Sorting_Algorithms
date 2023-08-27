#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counter.h"

void counter_init(struct counter *c)
{
    c->cmp_counter = 0;
    c->swap_counter = 0;
    c->recursion_counter = 0;
    c->insertion_sort_counter = 0;
    c->heapsort_counter = 0;
}

void counter_print(struct counter *c)
{
    printf("cmp_counter: %lu\n", c->cmp_counter);
    printf("swap_counter: %lu\n", c->swap_counter);
    printf("recursion_counter: %lu\n", c->recursion_counter);
    printf("insertion_sort_counter: %lu\n", c->insertion_sort_counter);
    printf("heapsort_counter: %lu\n", c->heapsort_counter);
}