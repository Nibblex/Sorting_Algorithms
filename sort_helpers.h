#ifndef _SORT_HELPERS_H
#define _SORT_HELPERS_H

#include <getopt.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "array_helpers.h"

unsigned int goesb_counter, swap_counter;

/* Helpers */
bool goes_before(int x, int y);

void swap(int a[], unsigned int i, unsigned int j);

bool array_is_sorted(int a[], unsigned int length);


/* Sorting algorithms */
void merge_sort(int a[], unsigned int length);

void merge_sort_iterative(int a[], unsigned int length);

void merge_sort_alt(int a[], unsigned int length);

void quick_sort(int a[], unsigned int length);

void quick_sort_cp(int a[], unsigned int length);

void quick_sort_dp(int a[], unsigned int length);

void quick_sort_rp(int a[], unsigned int length);

void multi_set_sort(int a[], unsigned int length);

void insertion_sort(int a[], unsigned int length);

void selection_sort(int a[], unsigned int length);

void permutation_sort(int a[], unsigned int length);

#endif