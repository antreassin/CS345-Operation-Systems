# Assignment 4: Inter-Process Communication (IPC)

## Objective
Learn various mechanisms for processes to communicate with each other.

## Description
This assignment covers:
- Pipes for process communication
- Shared memory using `shmget()` and `shmat()`
- Message queues
- Signals for process notifications
- Understanding different IPC mechanisms and their use cases

## Tasks
1. Implement communication between processes using pipes
2. Demonstrate shared memory usage
3. Handle signals properly
4. Compare different IPC mechanisms

## Files
- `pipe_example.c` - Example program demonstrating pipes
- `Makefile` - Build configuration

## Building
```bash
make
```

## Running
```bash
./pipe_example
```

## Expected Output
The program should demonstrate successful communication between parent and child processes using pipes.

## Submission Guidelines
- Properly handle all system call errors
- Close unused pipe ends
- Demonstrate understanding of IPC concepts
- Document choice of IPC mechanism for different scenarios
