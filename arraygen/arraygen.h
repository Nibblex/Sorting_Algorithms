#ifndef __ARRAYGEN_H__
#define __ARRAYGEN_H__

/**
 * @brief Enumeration for the order type of the elements in the array.
 *
 */
enum order_type
{
    ASC = 1,     /**< Ascending order */
    DESC = 2,    /**< Descending order */
    UNSORTED = 4 /**< Unsorted order */
};

/**
 * @brief Enumeration for the sign type of the elements in the array.
 *
 */
enum sign_type
{
    POS = 8,  /**< Positive sign */
    NEG = 16, /**< Negative sign */
    BOTH = 32 /**< Both positive and negative signs */
};

/**
 * @brief Generates an array of integers with specified length, minimum and maximum values, and options for order and sign of the elements.
 *
 * @param length The length of the array to be generated.
 * @param min The minimum value of the elements in the array.
 * @param max The maximum value of the elements in the array.
 * @param options The options for the order and sign of the elements in the array.
 * @return int* A pointer to the generated array.
 */
int *arraygen(unsigned long int length, long int min, long int max, int options);

#endif
