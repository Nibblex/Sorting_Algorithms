SORTER=sorter
ARRAYGEN=arraygen
CC=@gcc
CFLAGS= -std=c99 -Wall -Werror -Wextra -Wbad-function-cast -Wstrict-prototypes\
        -Wmissing-declarations -Wmissing-prototypes -Wno-unused-parameter -O3 -g
LDFLAGS= -lm

# Specify the build directory
BUILD_DIR=build

# List of source files
SORTER_SOURCES=$(wildcard *.c algorithms/*.c helpers/*.c)
SORTER_OBJECTS=$(addprefix $(BUILD_DIR)/,$(SORTER_SOURCES:.c=.o))

ARRAYGEN_SOURCES=$(wildcard arraygen/*.c helpers/*.c)
ARRAYGEN_OBJECTS=$(addprefix $(BUILD_DIR)/,$(ARRAYGEN_SOURCES:.c=.o))

all: $(BUILD_DIR) $(SORTER) $(ARRAYGEN)

$(SORTER): $(SORTER_OBJECTS)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/$@ $^ $(LDFLAGS)

$(ARRAYGEN): $(ARRAYGEN_OBJECTS)
	$(CC) $(CFLAGS) -o $@/$(ARRAYGEN) $^

$(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	@mkdir -p $@
	@mkdir -p $(BUILD_DIR)/algorithms
	@mkdir -p $(BUILD_DIR)/arraygen
	@mkdir -p $(BUILD_DIR)/helpers

clean:
	rm -rf $(BUILD_DIR) $(ARRAYGEN)/$(ARRAYGEN)

.PHONY: clean all
