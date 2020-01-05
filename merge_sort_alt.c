#include "sort_helpers.h"


static void merge(int a[], unsigned int izq, unsigned int med, unsigned int der) {
    unsigned int i, j, k, n1, n2;
    n1 = med - izq+1;
    n2 =  der - med;

    /* create temp arrays */
    int L[n1], R[n2];
 
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = a[izq+i];

    for (j = 0; j < n2; j++)
        R[j] = a[med+1+j];
 
    /* Merge the temp arrays back into a[l..r]*/
    i = 0, j = 0, k = izq;
    while (i < n1 && j < n2) {
        if (goes_before(L[i], R[j])) {
            a[k] = L[i];
            i++;
        } else {
            a[k] = R[j];
            j++;
        }
        k++;
    }
    /* Copy the remaining elements of L[], if there are any */
    while (i < n1) {
        a[k] = L[i];
        i++;
        k++;
    }
    /* Copy the remaining elements of R[], if there are any */
    while (j < n2) {
        a[k] = R[j];
        j++;
        k++;
    }
}

static void merge_sort_rec(int a[], unsigned int izq,unsigned int der) {
    unsigned int med;
    if (der > izq) {
        med = (izq + der)/2;
        merge_sort_rec(a, izq, med);
        merge_sort_rec(a, med+1, der);
        merge(a, izq, med, der);
    }
}

void merge_sort_alt(int a[], unsigned int length) {
    merge_sort_rec(a, 0, !length ? 0 : length - 1);
}