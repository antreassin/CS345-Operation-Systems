CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = pipe_example

all: $(TARGET)

$(TARGET): pipe_example.c
	$(CC) $(CFLAGS) -o $(TARGET) pipe_example.c

clean:
	rm -f $(TARGET) *.o

.PHONY: all clean
