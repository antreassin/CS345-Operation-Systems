CC = gcc
CFLAGS = -Wall -Wextra -std=gnu99 -pthread
TARGET = thread_example

all: $(TARGET)

$(TARGET): thread_example.c
	$(CC) $(CFLAGS) -o $(TARGET) thread_example.c

clean:
	rm -f $(TARGET) *.o

.PHONY: all clean
