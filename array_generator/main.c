#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arraygen.h"

static void usage(int exit_status)
{
    printf("Usage: arraygen [-l length] [-m min] [-M max] [-o order] [-s sign]\n");
    printf("  -l : Length of the array (default: 10)\n");
    printf("  -m : Minimum value (default: 1)\n");
    printf("  -M : Maximum value (default: 100)\n");
    printf("  -o : Order (asc, desc, default: uns)\n");
    printf("  -s : Sign (pos, neg, default: both (pos and neg))\n");
    printf("  -h : Print this help message\n");
    exit(exit_status);
}

static void print_array(int *array, size_t length)
{
    printf("%lu\n", length);
    for (size_t i = 0; i < length; ++i)
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

    return UNS;
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

    return BOTH;
}

static void parse_args(int argc, char *argv[], struct array_config *config)
{
    int c;

    *config = (struct array_config){.length = 10, .min = 1, .max = 100, .order = UNS, .sign = BOTH};

    while ((c = getopt(argc, argv, "l:m:M:o:s:h")) != -1)
    {
        switch (c)
        {
        case 'l':
            config->length = strtoul(optarg, NULL, 10);
            break;
        case 'm':
            config->min = atoi(optarg);
            break;
        case 'M':
            config->max = atoi(optarg);
            break;
        case 'o':
            config->order = parse_order(optarg);
            break;
        case 's':
            config->sign = parse_sign(optarg);
            break;
        case 'h':
            usage(EXIT_SUCCESS);
            break;
        default:
            usage(EXIT_FAILURE);
        }
    }
}

int main(int argc, char *argv[])
{
    int *array;
    struct array_config config;

    parse_args(argc, argv, &config);

    array = arraygen(&config);

    print_array(array, config.length);

    free(array);

    return EXIT_SUCCESS;
}
