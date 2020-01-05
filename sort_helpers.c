#include "sort_helpers.h"


bool goes_before(int x, int y) {
	goesb_counter++;
    return (x <= y);
}

void swap(int a[], unsigned int i, unsigned int j) {
	swap_counter++;
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

bool array_is_sorted(int a[], unsigned int length) {
    unsigned int i = 1;
    while (i < length && goes_before(a[i-1], a[i]))
        i++;
    return (i >= length);
}