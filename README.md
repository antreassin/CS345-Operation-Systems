# CS345 - Operating Systems
Assignment archive for CS345 Operating Systems course

## Course Overview
This repository contains programming assignments for CS345, covering fundamental operating systems concepts including:
- Process management and system calls
- Multithreading and synchronization
- Memory management
- Inter-process communication (IPC)

## Repository Structure

```
CS345-Operation-Systems/
├── Assignment1/          # Process management and system calls
├── Assignment2/          # Multithreading and synchronization
├── Assignment3/          # Memory management
├── Assignment4/          # Inter-process communication
├── common/              # Shared utilities and headers
└── README.md            # This file
```

## Assignments

### Assignment 1: Process Management
Introduction to system calls, process creation with `fork()`, and process synchronization.
- Directory: `Assignment1/`
- Topics: fork, exec, wait, process IDs

### Assignment 2: Multithreading
Working with POSIX threads, mutexes, and handling concurrent access to shared resources.
- Directory: `Assignment2/`
- Topics: pthread, mutex, thread synchronization

### Assignment 3: Memory Management
Dynamic memory allocation, memory leaks, and proper memory management techniques.
- Directory: `Assignment3/`
- Topics: malloc, calloc, realloc, free, valgrind

### Assignment 4: Inter-Process Communication
Various IPC mechanisms including pipes, shared memory, and signals.
- Directory: `Assignment4/`
- Topics: pipes, shared memory, message queues, signals

## Building and Running

Each assignment has its own `Makefile`. To build an assignment:

```bash
cd AssignmentX/
make
```

To run the compiled program:

```bash
./program_name
```

To clean build artifacts:

```bash
make clean
```

## Requirements

- GCC compiler (C99 standard or later)
- POSIX-compliant system (Linux, Unix, macOS)
- pthread library
- make utility
- valgrind (recommended for memory leak detection)

## Getting Started

1. Clone this repository
2. Navigate to the desired assignment directory
3. Read the assignment README
4. Build and run the example programs
5. Modify and complete the assignments as required

## Common Utilities

The `common/` directory contains shared header files and utilities that can be used across assignments. Include them in your code as needed:

```c
#include "../common/common.h"
```

## Additional Resources

- [Linux man pages](https://man7.org/linux/man-pages/)
- [POSIX Threads Programming](https://computing.llnl.gov/tutorials/pthreads/)
- [Valgrind Documentation](https://valgrind.org/docs/manual/manual.html)

## Notes

- Always compile with warnings enabled (`-Wall -Wextra`)
- Use valgrind to check for memory leaks
- Test your programs thoroughly before submission
- Follow proper coding style and documentation practices
