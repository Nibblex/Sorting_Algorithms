#ifndef __ARRAY_GEN_H__
#define __ARRAY_GEN_H__

enum order_type
{
    ASC = 1,
    DESC = 2,
    UNSORTED = 4
};

enum sign_type
{
    POS = 8,
    NEG = 16,
    BOTH = 32
};

int *array_generator(int length, int min, int max, int options);

#endif
