#ifndef _SORT_HELPERS_H
#define _SORT_HELPERS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

long unsigned int goesb_counter, swap_counter;

/* Helpers */
void reset_counters(void);

bool goes_before(int x, int y);

unsigned int swap(int a[], unsigned int i, unsigned int j);

/* Sorting algorithms */
void mergesort(int a[], unsigned int length);

void mergesort_iterative(int a[], unsigned int length);

void mergesort_alt(int a[], unsigned int length);

void quicksort(int a[], unsigned int length);

void quicksort_std(int a[], unsigned int length);

void quicksort_cp(int a[], unsigned int length);

void quicksort_dp(int a[], unsigned int length);

void quicksort_rp(int a[], unsigned int length);

void multi_set_sort(int a[], unsigned int length);

void insertion_sort(int a[], unsigned int length);

void selection_sort(int a[], unsigned int length);

void permutation_sort(int a[], unsigned int length);

#endif
