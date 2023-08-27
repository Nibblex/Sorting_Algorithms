#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arraygen.h"

static void print_usage(void)
{
    printf("Usage: arraygen [-l length] [-m min] [-M max] [-o order] [-s sign]\n");
    printf("  -l : Length of the array (default: 10)\n");
    printf("  -m : Minimum value (default: 1)\n");
    printf("  -M : Maximum value (default: 100)\n");
    printf("  -o : Order (asc, desc, uns, default: uns)\n");
    printf("  -s : Sign (pos, neg, both, default: pos)\n");
}

static void print_array(int *array, unsigned long int length)
{
    printf("%lu\n", length);
    for (unsigned long int i = 0; i < length; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    unsigned long int length = 10;
    long int min = 1;
    long int max = 100;
    int order = UNSORTED;
    int sign = POS; // Default value is POS
    int opt;

    while ((opt = getopt(argc, argv, "l:m:M:o:s:")) != -1)
    {
        switch (opt)
        {
        case 'l':
            length = strtoul(optarg, NULL, 10);
            break;
        case 'm':
            min = strtol(optarg, NULL, 10);
            break;
        case 'M':
            max = strtol(optarg, NULL, 10);
            break;
        case 'o':
            if (strcmp(optarg, "asc") == 0)
            {
                order = ASC;
            }
            else if (strcmp(optarg, "desc") == 0)
            {
                order = DESC;
            }
            else if (strcmp(optarg, "uns") == 0)
            {
                order = UNSORTED;
            }
            break;
        case 's':
            if (strcmp(optarg, "pos") == 0)
            {
                sign = POS;
            }
            else if (strcmp(optarg, "neg") == 0)
            {
                sign = NEG;
            }
            else if (strcmp(optarg, "both") == 0)
            {
                sign = BOTH;
            }
            break;
        default:
            fprintf(stderr, "Invalid option\n");
            print_usage();
            return EXIT_FAILURE;
        }
    }

    int *array = arraygen(length, min, max, order | sign);
    print_array(array, length);

    free(array);
    return EXIT_SUCCESS;
}
