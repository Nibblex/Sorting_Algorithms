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
    POS = 1,
    NEG = 2,
    BOTH = 4
};

int *array_generator(int length, int min, int max, int order_type, int sign_type);

#endif
