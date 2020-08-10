SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)
TARGET = libluasdl.so

CFLAGS = -std=c99 -Wall -Werror -fpic
LFLAGS = -shared -llua5.3 -lSDL2

.PHONY: all clean run

all: clean $(TARGET)

clean:
	rm -rf *.o $(TARGET)

run: clean $(TARGET)
	lua demo.lua

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(LFLAGS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

