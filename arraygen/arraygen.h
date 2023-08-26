#ifndef __ARRAYGEN_H__
#define __ARRAYGEN_H__

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

int *arraygen(unsigned long int length, long int min, long int max, int options);

#endif
