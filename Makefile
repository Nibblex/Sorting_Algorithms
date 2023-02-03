TARGET=sorter
CC=gcc
CFLAGS= -Wall -Werror -Wextra -pedantic -std=c99 -Wbad-function-cast -Wstrict-prototypes\
		-Wmissing-declarations -Wmissing-prototypes -Wno-unused-parameter -g

LIBS += -lm

HELPERS=array_helpers.c sort_helpers.c
vpath %.c helpers

SOURCES=$(shell echo *.c) $(HELPERS)
OBJECTS=$(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -f $(TARGET) $(OBJECTS)

.PHONY: clean all
