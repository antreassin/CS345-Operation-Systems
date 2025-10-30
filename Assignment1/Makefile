CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = process_example

all: $(TARGET)

$(TARGET): process_example.c
	$(CC) $(CFLAGS) -o $(TARGET) process_example.c

clean:
	rm -f $(TARGET) *.o

.PHONY: all clean
