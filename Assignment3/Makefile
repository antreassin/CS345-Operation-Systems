CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
TARGET = memory_example

all: $(TARGET)

$(TARGET): memory_example.c
	$(CC) $(CFLAGS) -o $(TARGET) memory_example.c

clean:
	rm -f $(TARGET) *.o

valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

.PHONY: all clean valgrind
