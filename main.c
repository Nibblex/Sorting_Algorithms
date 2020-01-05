#include "sort_helpers.h"

#define MAX_SIZE 100000
#define FUNC_NUM 11

typedef void (*func)(int a[], unsigned int length);

char *func_names[FUNC_NUM] = {"merge_sort",
                              "merge_sort_alt",
                              "merge_sort_iterative",
                              "quick_sort",
                              "quick_sort_cp",
                              "quick_sort_dp",
                              "quick_sort_rp",
                              "multi_set_sort",
                              "insertion_sort",
                              "selection_sort",
                              "permutation_sort"};

func func_array[FUNC_NUM] = {&merge_sort,
                            &merge_sort_alt,
                            &merge_sort_iterative,
                            &quick_sort,
                            &quick_sort_cp,
                            &quick_sort_dp,
                            &quick_sort_rp,
                            &multi_set_sort,
                            &insertion_sort,
                            &selection_sort,
                            &permutation_sort};

static double getMilliseconds(void) {
    return 1000.0 * clock() / CLOCKS_PER_SEC;
}

static void reset_counters(void) {
    swap_counter = 0;
    goesb_counter = 0;
}

static void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path>\n\n"
           "Sort an array given in a file in disk.\n"
           "\n"
           "The input file must have the following format:\n"
           " * The first line must contain only a positive integer,"
           " which is the length of the array.\n"
           " * The second line must contain the members of the array"
           " separated by one or more spaces. Each member must be an integer."
           "\n\n"
           "In other words, the file format is:\n"
           "<amount of array elements>\n"
           "<array elem 1> <array elem 2> ... <array elem N>\n\n",
           program_name);
}

static char *parse_filepath(int argc, char *argv[]) {
    if (argc < 2) {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }
    return argv[1];
}

int main(int argc, char *argv[]) {
    char *filepath = NULL;
    double elapsed;
    bool check;
    if (argc == 3) {
      check = atoi(argv[2]);
    }

    /* parse the filepath given in command line arguments */
    filepath = parse_filepath(argc, argv);
    
    /* create an array of MAX_SIZE elements */
    int array[MAX_SIZE];
    
    /* parse the file to fill the array and obtain the actual length */
    unsigned int length = array_from_file(array, MAX_SIZE, filepath);

    /* create a copy of the array, to do some checks later */
    int copy[MAX_SIZE];

    for (unsigned int i = 0; i < FUNC_NUM; i++) {
        reset_counters();
        array_copy(copy, array, length);
        elapsed = getMilliseconds();
        func_array[i](copy, length);
        elapsed = getMilliseconds() - elapsed;
        //array_dump(copy, length);
        printf("Statistics for %s:\n", func_names[i]);
        printf("Elapsed milliseconds = %g\n", elapsed);
        printf("Comparisons: %u  Swaps: %d\n\n", goesb_counter, swap_counter);
        if (check) {
            assert(array_is_sorted(copy, length));
            assert(array_is_permutation_of(copy, array, length));
        }
    }
    return EXIT_SUCCESS;
}