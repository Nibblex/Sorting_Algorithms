#include "sort_helpers.h"
#include "multiset/multi_set_da.h"

static void load_mset(int a[], multi_set m, unsigned int length)
{
	for (unsigned int i = 0; i < length; i++)
		add(m, a[i]);
}

static void load_array(int a[], multi_set m, unsigned int length)
{
	unsigned int i = 0;
	while (!is_empty(m) && i < length)
	{
		a[i] = first(m);
		rm(m, first(m));
		i++;
	}
}

void multi_set_sort(int a[], unsigned int length)
{
	multi_set m = init();
	load_mset(a, m, length);
	load_array(a, m, length);
	destroy(m);
}