#ifndef _SORT_HELPERS_H
#define _SORT_HELPERS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define reset_counters     \
    ({                     \
        swap_counter = 0;  \
        goesb_counter = 0; \
    })

#define goes_before(x, y) ({goesb_counter++; abs(x) <= abs(y); })

#define swap(a, i, j)   \
    ({                  \
        swap_counter++; \
        int tmp = a[i]; \
        a[i] = a[j];    \
        a[j] = tmp;     \
        i;              \
    })

long unsigned int goesb_counter, swap_counter;

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
