# Assignment 2: Multithreading and Synchronization

## Objective
Understand thread creation, synchronization, and common concurrency issues.

## Description
This assignment covers:
- Thread creation using POSIX threads (pthread)
- Thread synchronization with mutexes
- Condition variables for thread communication
- Critical section management

## Tasks
1. Create a program that spawns multiple threads
2. Implement proper synchronization using mutexes
3. Demonstrate thread-safe operations on shared data
4. Handle race conditions appropriately

## Files
- `thread_example.c` - Example program demonstrating multithreading
- `Makefile` - Build configuration

## Building
```bash
make
```

**Note:** This assignment uses `-std=gnu99` instead of `-std=c99` to enable POSIX extensions like `usleep()` which are commonly used in threading examples.

## Running
```bash
./thread_example
```

## Expected Output
The program should demonstrate multiple threads working correctly with proper synchronization, avoiding race conditions.

## Submission Guidelines
- Ensure no race conditions or deadlocks
- Code must compile without warnings
- Test with different thread counts
- Document synchronization strategy
