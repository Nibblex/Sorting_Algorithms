SORTER=sorter
ARRAYGEN=arraygen
CC=@gcc
CFLAGS= -std=c99 -Wall -Werror -Wextra -Wshadow -Wconversion -Wuninitialized -Wbad-function-cast -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations\
        -Wunreachable-code -Wunused-const-variable -Wunused-function -Wbad-function-cast -Wunused-macros -Wunused-parameter -Wunused-macros -O3 -g
LDFLAGS= -lm
VALGRIND=valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes

ARRAYGEN_ARGS?=-l 1000
SORTER_ARGS?=-a heapsort,introsort,mergesort,quicksort,quicksort_std,shellsort,timsort -t sorted,permuted -f human

# Specify the build directory
BUILD_DIR=build

# List of source files
SORTER_SOURCES=$(wildcard *.c algorithms/*.c helpers/*.c)
SORTER_OBJECTS=$(addprefix $(BUILD_DIR)/,$(SORTER_SOURCES:.c=.o))

ARRAYGEN_SOURCES=$(wildcard array_generator/*.c helpers/*.c)
ARRAYGEN_OBJECTS=$(addprefix $(BUILD_DIR)/,$(ARRAYGEN_SOURCES:.c=.o))

all: $(BUILD_DIR) $(SORTER) $(ARRAYGEN)

test: $(BUILD_DIR) $(SORTER) $(ARRAYGEN)
	./$(ARRAYGEN) $(ARRAYGEN_ARGS) | ./$(SORTER) $(SORTER_ARGS) | awk 'NR<=3; NR>3 {print $0 | "sort -n -k 2"}'

memtest: $(BUILD_DIR) $(SORTER) $(ARRAYGEN)
	$(VALGRIND) ./$(ARRAYGEN) $(ARRAYGEN_ARGS) | $(VALGRIND) ./$(SORTER) $(SORTER_ARGS)

$(SORTER): $(SORTER_OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(ARRAYGEN): $(ARRAYGEN_OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Create the build directory
$(BUILD_DIR):
	@mkdir -p $@
	@mkdir -p $(BUILD_DIR)/algorithms
	@mkdir -p $(BUILD_DIR)/array_generator
	@mkdir -p $(BUILD_DIR)/helpers

clean:
	@rm -rf $(BUILD_DIR) $(SORTER) $(ARRAYGEN)

.PHONY: clean all
