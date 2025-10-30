# Assignment 3: Memory Management

## Objective
Understand memory allocation, deallocation, and management concepts.

## Description
This assignment explores:
- Dynamic memory allocation with `malloc()`, `calloc()`, `realloc()`
- Memory deallocation with `free()`
- Memory leaks and their prevention
- Memory mapping with `mmap()`
- Understanding stack vs heap memory

## Tasks
1. Implement a simple memory allocator
2. Demonstrate proper memory management
3. Detect and fix memory leaks
4. Work with different memory allocation strategies

## Files
- `memory_example.c` - Example program demonstrating memory management
- `Makefile` - Build configuration

## Building
```bash
make
```

## Running
```bash
./memory_example
```

## Memory Leak Detection
Use valgrind to check for memory leaks:
```bash
valgrind --leak-check=full ./memory_example
```

## Expected Output
The program should allocate and deallocate memory properly without memory leaks.

## Submission Guidelines
- No memory leaks (verify with valgrind)
- Proper error handling for allocation failures
- Document memory management strategy
