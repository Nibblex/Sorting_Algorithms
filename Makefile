TARGET=sorter
CC=@gcc
CFLAGS= -std=c99 -Wall -Werror -Wextra -Wbad-function-cast -Wstrict-prototypes\
		-Wmissing-declarations -Wmissing-prototypes -Wno-unused-parameter -O3 -g

SOURCES=$(shell echo *.c algorithms/*.c helpers/*.c)
OBJECTS=$(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ -lm

clean:
	rm -f -r $(TARGET) *.o algorithms/*.o helpers/*.o

.PHONY: clean all
