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

static void print_array(int *array, size_t length)
{
    printf("%lu\n", length);
    for (size_t i = 0; i < length; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

static enum order_type parse_order(char *order)
{
    if (strcmp(order, "asc") == 0)
    {
        return ASC;
    }
    else if (strcmp(order, "desc") == 0)
    {
        return DESC;
    }
    else if (strcmp(order, "uns") == 0)
    {
        return UNS;
    }

    print_usage();
    exit(EXIT_FAILURE);
}

static enum sign_type parse_sign(char *sign)
{
    if (strcmp(sign, "pos") == 0)
    {
        return POS;
    }
    else if (strcmp(sign, "neg") == 0)
    {
        return NEG;
    }
    else if (strcmp(sign, "both") == 0)
    {
        return BOTH;
    }

    print_usage();
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    struct array_config config;
    config = (struct array_config){.length = 10, .min = 1, .max = 100, .order = UNS, .sign = POS};
    int c;

    while ((c = getopt(argc, argv, "l:m:M:o:s:")) != -1)
    {
        switch (c)
        {
        case 'l':
            config.length = strtoul(optarg, NULL, 10);
            break;
        case 'm':
            config.min = strtol(optarg, NULL, 10);
            break;
        case 'M':
            config.max = strtol(optarg, NULL, 10);
            break;
        case 'o':
            config.order = parse_order(optarg);
            break;
        case 's':
            config.sign = parse_sign(optarg);
            break;
        default:
            fprintf(stderr, "Invalid option\n");
            print_usage();
            return EXIT_FAILURE;
        }
    }

    int *array = arraygen(&config);
    print_array(array, config.length);

    free(array);

    return EXIT_SUCCESS;
}
