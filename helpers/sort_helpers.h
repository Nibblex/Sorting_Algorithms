#ifndef _SORT_HELPERS_H
#define _SORT_HELPERS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define reset_counters    \
    ({                    \
        swap_counter = 0; \
        cmp_counter = 0;  \
    })

#define cmp(x, y) ({cmp_counter++; abs(x) < abs(y) ? -1 : abs(x) > abs(y) ? 1 : 0; })

#define swap(a, i, j)   \
    ({                  \
        swap_counter++; \
        int tmp = a[i]; \
        a[i] = a[j];    \
        a[j] = tmp;     \
        i;              \
    })

long unsigned int cmp_counter, swap_counter;

/* Sorting algorithms */
void mergesort(int a[], unsigned int length);

void mergesort_iterative(int a[], unsigned int length);

void mergesort_alt(int a[], unsigned int length);

void quicksort(int a[], unsigned int length);

void quicksort_std(int a[], unsigned int length);

void quicksort_rp(int a[], unsigned int length);

void multi_set_sort(int a[], unsigned int length);

void insertion_sort(int a[], unsigned int length);

void selection_sort(int a[], unsigned int length);

void permutation_sort(int a[], unsigned int length);

#endif
