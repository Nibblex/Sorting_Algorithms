#ifndef _SORT_HELPERS_H
#define _SORT_HELPERS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHUNK_SIZE 32

#ifndef SIZE_MAX
#define SIZE_MAX (unsigned int)(-1)
#endif

#define reset_counters    \
    ({                    \
        swap_counter = 0; \
        cmp_counter = 0;  \
    })

#define _cmp(x, y)                                       \
    ({                                                   \
        cmp_counter++;                                   \
        int _x = (x), _y = (y);                          \
        abs(_x)<abs(_y) ? -1 : abs(_x)> abs(_y) ? 1 : 0; \
    })

#define min(a, b) (_cmp(a, b) < 0 ? (a) : (b))

#define max(a, b) (_cmp(a, b) > 0 ? (a) : (b))

#define swap(a, i, j)                    \
    ({                                   \
        swap_counter++;                  \
        unsigned int _i = (i), _j = (j); \
        int tmp = a[_i];                 \
        a[_i] = a[_j];                   \
        a[_j] = tmp;                     \
        _i;                              \
    })

long unsigned int cmp_counter, swap_counter;

int cmp(const void *a, const void *b);

void merge(int a[], unsigned int left, unsigned int mid, unsigned int right);

/* Sorting algorithms */

void mergesort(int a[], unsigned int length);

void mergesort_iterative(int a[], unsigned int length);

void timsort(int a[], unsigned int length);

void quicksort(int a[], unsigned int length);

void quicksort_std(int a[], unsigned int length);

void quicksort(int a[], unsigned int length);

void multi_set_sort(int a[], unsigned int length);

void insertion_sort(int a[], unsigned int length);

void selection_sort(int a[], unsigned int length);

void permutation_sort(int a[], unsigned int length);

#endif
