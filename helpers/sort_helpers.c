#include "sort_helpers.h"

int cmp(const void *a, const void *b)
{
    return _cmp(*(int *)a, *(int *)b);
}
