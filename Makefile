SORTER=sorter
ARRAYGEN=arraygen
CC=@gcc
CFLAGS= -std=c99 -Wall -Werror -Wextra -Wshadow -Wconversion -Wuninitialized -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations\
        -Wunreachable-code -Wunused-const-variable -Wunused-function -Wbad-function-cast -Wunused-macros -Wunused-parameter -Wunused-macros -g
LDFLAGS=-pthread
VALGRIND=valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes

OPTIMIZATION?=-O0
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
	./$(ARRAYGEN) $(ARRAYGEN_ARGS) | ./$(SORTER) $(SORTER_ARGS)

memtest: $(BUILD_DIR) $(SORTER) $(ARRAYGEN)
	$(VALGRIND) ./$(ARRAYGEN) $(ARRAYGEN_ARGS) | $(VALGRIND) ./$(SORTER) $(SORTER_ARGS)

$(SORTER): $(SORTER_OBJECTS)
	$(CC) $(CFLAGS) $(OPTIMIZATION) -o $@ $^ $(LDFLAGS)

$(ARRAYGEN): $(ARRAYGEN_OBJECTS)
	$(CC) $(CFLAGS) $(OPTIMIZATION) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) $(OPTIMIZATION) -c $< -o $@

# Create the build directory
$(BUILD_DIR):
	@mkdir -p $@
	@mkdir -p $(BUILD_DIR)/algorithms
	@mkdir -p $(BUILD_DIR)/array_generator
	@mkdir -p $(BUILD_DIR)/helpers

clean:
	@rm -rf $(BUILD_DIR) $(SORTER) $(ARRAYGEN)

.PHONY: clean all
