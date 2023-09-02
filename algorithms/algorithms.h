#ifndef _ALGORITHMS_H
#define _ALGORITHMS_H

#define MAX_THRESH 15

#define U32_MAX ((size_t)-1)

#include <stdbool.h>

typedef void (*sorting_func)(int a[], size_t length);

struct algorithm
{
    char *name;
    sorting_func f;
    bool enabled;
};

/* Sorting algorithms */

void heapsort(int a[], size_t length);

void insertion_sort(int a[], size_t length);

void introsort(int a[], size_t length);

void mergesort(int a[], size_t length);

void quicksort(int a[], size_t length);

void quicksort_std(int a[], size_t length);

void selection_sort(int a[], size_t length);

void shellsort(int a[], size_t length);

void timsort(int a[], size_t length);

#endif
