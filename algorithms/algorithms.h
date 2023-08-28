#ifndef _ALGORITHMS_H
#define _ALGORITHMS_H

#define FUNC_NUM 9

typedef void (*func)(int a[], size_t length);

struct algorithm
{
    char *name;
    func f;
};

/* Sorting algorithms */

void insertion_sort(int a[], size_t length);

void selection_sort(int a[], size_t length);

void quicksort(int a[], size_t length);

void quicksort_std(int a[], size_t length);

void mergesort(int a[], size_t length);

void timsort(int a[], size_t length);

void shellsort(int a[], size_t length);

void heapsort(int a[], size_t length);

void introsort(int a[], size_t length);

#endif
