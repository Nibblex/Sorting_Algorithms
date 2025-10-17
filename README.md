# Sorting Algorithms

A comprehensive C implementation of various sorting algorithms with built-in performance benchmarking and testing capabilities. This project provides a flexible framework for comparing and analyzing different sorting algorithms on various types of input data.

## Features

- **10 Sorting Algorithms**: binsort, heapsort, introsort, insertion sort, mergesort, quicksort, quicksort_std (standard library), selection sort, shellsort, and timsort
- **Performance Metrics**: Tracks elapsed time, comparisons, swaps, recursions, and algorithm-specific counters
- **Multiple Output Formats**: Human-readable tables, CSV, and default formats
- **Correctness Testing**: Validates that arrays are properly sorted and are permutations of the original
- **Array Generator**: Flexible tool for generating test arrays with various properties
- **Configurable Testing**: Choose which algorithms and tests to run
- **Memory Safety**: Built with strict compiler flags and supports Valgrind testing

## Prerequisites

- GCC compiler with C99 support
- GNU Make
- pthread library
- (Optional) Valgrind for memory leak testing

## Installation

1. Clone the repository:
```bash
git clone https://github.com/Nibblex/Sorting_Algorithms.git
cd Sorting_Algorithms
```

2. Build the project:
```bash
make
```

This will create two executables:
- `sorter` - The main sorting algorithm benchmarking tool
- `arraygen` - Array generator for creating test inputs

3. Clean build artifacts:
```bash
make clean
```

## Usage

### Array Generator (arraygen)

Generate arrays with specific properties for testing:

```bash
./arraygen [options]
```

**Options:**
- `-l <length>` : Length of the array (default: 10)
- `-m <min>` : Minimum value (default: 1)
- `-M <max>` : Maximum value (default: 100)
- `-o <order>` : Order - `asc` (ascending), `desc` (descending), `uns` (unsorted/random, default)
- `-s <sign>` : Sign - `pos` (positive), `neg` (negative), `rnd` (random), `NONE` (default)
- `-h` : Print help message

**Examples:**
```bash
# Generate an unsorted array of 1000 elements
./arraygen -l 1000

# Generate a sorted ascending array with negative numbers
./arraygen -l 500 -o asc -s neg

# Generate a descending array with values from -50 to 50
./arraygen -l 200 -o desc -m -50 -M 50
```

### Sorter

Sort arrays and benchmark algorithm performance:

```bash
./sorter [options]
```

**Options:**
- `-a, --algorithms <alg1,alg2,...>` : Specify algorithms to run (comma-separated)
- `-t, --tests <test1,test2,...>` : Specify tests to run (comma-separated)
- `-f, --format <format>` : Output format - `human`, `csv`, `default`
- `-s, --sort-by <column>` : Sort results by column number (2-7) - columns are: elapsed, cmp, swap, recursion, isort, heapsort
- `-d, --dump` : Dump the input array to stdout
- `-h, --help` : Print help message

**Available Algorithms:**
- `binsort` - Binary insertion sort
- `heapsort` - Heapsort
- `introsort` - Introspective sort (hybrid algorithm)
- `isort` - Insertion sort
- `mergesort` - Merge sort
- `quicksort` - Quicksort
- `quicksort_std` - Standard library qsort
- `selection_sort` - Selection sort
- `shellsort` - Shell sort
- `timsort` - Timsort (hybrid algorithm)

**Available Tests:**
- `sorted` - Verifies the array is correctly sorted
- `permuted` - Verifies the sorted array is a permutation of the original

**Examples:**
```bash
# Run all algorithms with default tests
./arraygen -l 1000 | ./sorter

# Run specific algorithms with human-readable output
./arraygen -l 5000 | ./sorter -a quicksort,mergesort,heapsort -t sorted,permuted -f human

# Run single algorithm with CSV output
./arraygen -l 10000 | ./sorter -a timsort -f csv

# Sort from an input file
./sorter -a introsort,quicksort < input/unsorted-1000.in

# Dump the array before sorting
./arraygen -l 20 | ./sorter -a quicksort -d
```

## Output Formats

### Human Format
Displays results in a formatted table:
```
-----------------------------------------------------------------------------------------------------------------------------------------------
Algorithm        Elapsed (ms)     Comparisons      Swaps            Recursions       Isorts           Heapsort         Tests (sorted-permuted)
-----------------------------------------------------------------------------------------------------------------------------------------------
introsort        0.405            10146            1771             112              113              0                OK-OK
mergesort        0.583            8718             0                1999             0                0                OK-OK
quicksort        0.550            10150            1800             0                114              0                OK-OK
```

### CSV Format
Outputs comma-separated values for easy parsing:
```
quicksort,0.007,7,0,0,1,0,OK,OK
```

### Default Format
Simple text output with results.

## Performance Metrics

The sorter tracks the following metrics for each algorithm:

- **Elapsed Time**: Wall clock time in milliseconds
- **Comparisons**: Number of element comparisons performed
- **Swaps**: Number of element swaps/moves
- **Recursions**: Number of recursive calls
- **Isorts**: Number of insertion sort calls (for hybrid algorithms)
- **Heapsort**: Number of heapsort calls (for hybrid algorithms)

## Testing

Run the default test suite:
```bash
make test
```

This generates an array of 1000 elements and runs multiple sorting algorithms with validation.

Run memory leak tests with Valgrind:
```bash
make memtest
```

## Input Format

When reading from stdin or files, the input should be formatted as:
```
<array_length>
<element1> <element2> <element3> ... <elementN>
```

Example:
```
5
42 17 93 28 61
```

See the `input/` directory for example input files.

## Project Structure

```
.
├── Makefile              # Build configuration
├── main.c                # Main sorter program
├── algorithms/           # Sorting algorithm implementations
│   ├── algorithms.h      # Algorithm interfaces
│   ├── binsort.c
│   ├── heapsort.c
│   ├── introsort.c
│   ├── isort.c
│   ├── mergesort.c
│   ├── quicksort.c
│   ├── quicksort_std.c
│   ├── selection_sort.c
│   ├── shellsort.c
│   ├── timsort.c
│   └── xoroshiro128plus.h  # Random number generator
├── helpers/              # Utility functions
│   ├── array_helpers.c   # Array I/O and manipulation
│   ├── array_helpers.h
│   ├── sort_helpers.c    # Sorting utility functions
│   ├── sort_helpers.h
│   ├── workbench.c       # Benchmarking framework
│   └── workbench.h
├── array_generator/      # Array generation tool
│   ├── main.c
│   ├── arraygen.c
│   └── arraygen.h
├── input/                # Sample input files
└── build/                # Build artifacts (generated)
```

## Algorithm Descriptions

### Quick Reference

- **Insertion Sort (`isort`)**: Simple O(n²) algorithm, efficient for small arrays
- **Binary Insertion Sort (`binsort`)**: Insertion sort with binary search for position
- **Selection Sort (`selection_sort`)**: O(n²) algorithm, minimizes swaps
- **Shell Sort (`shellsort`)**: Gap-based insertion sort, O(n log n) average case
- **Heap Sort (`heapsort`)**: O(n log n) guaranteed, in-place sorting
- **Merge Sort (`mergesort`)**: O(n log n) stable sort, requires extra space
- **Quick Sort (`quicksort`)**: O(n log n) average, in-place partitioning
- **Introspective Sort (`introsort`)**: Hybrid of quicksort, heapsort, and insertion sort
- **Timsort (`timsort`)**: Hybrid of merge sort and insertion sort, stable
- **Standard Quick Sort (`quicksort_std`)**: Uses C standard library `qsort()`

## Compiler Flags

The project is built with strict compiler warnings enabled:
- `-std=c99` - C99 standard
- `-Wall -Werror -Wextra` - All warnings as errors
- `-Wshadow` - Warn about variable shadowing
- `-Wconversion` - Warn about implicit conversions
- `-Wuninitialized` - Warn about uninitialized variables
- `-Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations` - Function declaration checks
- `-Wunreachable-code` - Warn about unreachable code
- `-Wunused-const-variable -Wunused-function -Wunused-parameter -Wunused-macros` - Warn about unused elements
- `-Wbad-function-cast` - Warn about suspicious function casts
- `-g` - Debug symbols

## Contributing

Contributions are welcome! Areas for improvement:
- Additional sorting algorithms
- More test cases and input scenarios
- Performance optimizations
- Additional output formats
- Extended documentation

## License

This project is open source. Please check with the repository owner for specific license terms.

## Authors

- Nibblex

## Acknowledgments

- Implements classical sorting algorithms from computer science literature
- Uses the xoroshiro128+ random number generator for array generation
