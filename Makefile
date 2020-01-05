TARGET=sorter
CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -Wbad-function-cast -Wstrict-prototypes\
		-Wmissing-declarations -Wmissing-prototypes -Wno-unused-parameter -Werror\
		-pedantic -g

LIBS += -lm

MSET=multi_set_da.c
vpath $(MSET) multiset

SOURCES=$(shell echo *.c) $(MSET)
OBJECTS=$(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -f $(TARGET) $(OBJECTS)

.PHONY: clean all